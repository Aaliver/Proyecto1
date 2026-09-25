#include "servidor.hpp"
#include "controlador.hpp"
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Servidor::Servidor(const Configuracion& config) :
  config(config), serverSocket(socket(AF_INET, SOCK_STREAM, 0)) {}

int Servidor::ejecuta() {

  if (serverSocket == -1)
    throw std::runtime_error("Error al crear el socket del servidor");

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(config.puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    close(serverSocket);
    throw std::runtime_error("Error al vincular el socket al puerto");
  }

  std::printf("Servidor conectado!\n");

  if (listen(serverSocket, 5) == -1) {
    close(serverSocket);
    throw std::runtime_error("Error al escuchar conexiones entrantes");
  }

  std::printf("Esperando conexiones entrantes...\n");

  int clientSocket = accept(serverSocket, nullptr, nullptr);
  if (clientSocket == -1) {
    close(serverSocket);
    throw std::runtime_error("Error al aceptar la conexión entrante");
  }
  Conexion conexion(conexiones.size() + 1, clientSocket);

  std::printf("Conexión establecida con el cliente\n");

  while (true) {
      leerSolicitud(conexion);
  }

  return desconecta();
}

int Servidor::desconecta() {
  for (auto& [nombre, conexion] : conexiones)
    notificar(Controlador::desconectar(conexion, conexiones).mensajeConexiones);
  return close(serverSocket);
}

void Servidor::leerSolicitud(Conexion& conexion) {
  constexpr std::size_t LIMITE = 1024 * 1024;
  char buffer[LIMITE] = {0};
  ssize_t bytes = recv(conexion.getSocket(), buffer, sizeof(buffer), 0);
  if (bytes <= 0) {
    notificar(Controlador::desconectar(conexion, conexiones).mensajeConexiones);
    return;
  }

 const std::string mensaje(buffer, bytes);
 std::printf(">> [%d]: %s", conexion.getNumero(), mensaje.c_str());

 Resultado resultado = Controlador::procesa(mensaje, conexion, conexiones);
 obtenerRespuesta(resultado, conexion);
}

void Servidor::obtenerRespuesta(const Resultado& resultado, Conexion conexion) {
  if (resultado.mensaje.has_value()) {
    const auto& [respuesta, usuario] = resultado.mensaje.value();
    enviaMensaje(respuesta, usuario);
  }
  if (!resultado.exito)
    notificar(Controlador::desconectar(conexion, conexiones).mensajeConexiones);
  if (resultado.notificar)
    notificar(resultado.mensajeConexiones);
}

void Servidor::notificar(const std::string& mensaje) {
  for (const auto& [nombre, conexion] : conexiones)
    enviaMensaje(mensaje, conexion);
}

void Servidor::enviaMensaje(const std::string& mensaje, Conexion conexion) {
    send(conexion.getSocket(), mensaje.c_str(), mensaje.length(), 0);
}

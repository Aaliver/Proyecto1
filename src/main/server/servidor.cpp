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
  Conexion conexion(conexiones.size(), clientSocket);

  std::printf("Conexión establecida con el cliente\n");

  while (true) {
      leerSolicitud(conexion);
  }

  return desconectarse();
}

int Servidor::desconectarse() {
  // for (const auto& [nombre, conexion] : conexiones) {
  //   conexion.desconecta();
  // }
  close(serverSocket);
  //conectado = false;
  return 0;
}

void Servidor::leerSolicitud(Conexion conexion) {
  constexpr std::size_t LIMITE = 1024 * 1024;
  char buffer[LIMITE] = {0};
  ssize_t bytes = recv(conexion.getSocket(), buffer, sizeof(buffer), 0);
  if (bytes <= 0) {
    Controlador::desconectar(conexion);
    return;
  }

 std::string mensaje(buffer, bytes);
 std::printf(">> %s\n", mensaje.c_str());

 Resultado resultado = Controlador::procesa(mensaje, conexion, conexiones);
 obtenerRespuesta(resultado, conexion);
}

void Servidor::obtenerRespuesta(Resultado resultado, Conexion conexion) {
  responderSolicitud(resultado.mensaje, conexion);
  if (!resultado.exito)
    Controlador::desconectar(conexion);
  if (resultado.notificar)
    for (const auto& [llave, valor] : conexiones)
      responderSolicitud(resultado.mensajeConexiones, valor);
}

void Servidor::responderSolicitud(const std::string& respuesta, Conexion conexion) {
    send(conexion.getSocket(), respuesta.c_str(), respuesta.length(), 0);
}

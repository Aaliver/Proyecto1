#include "servidor.hpp"
#include "controlador.hpp"
#include "resultado.hpp"
#include "vista.hpp"
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
    throw std::runtime_error("Error al vincular el socket al puerto.");
  }

  Vista::muestraMensaje("Servidor conectado!\n");

  if (listen(serverSocket, 5) == -1) {
    close(serverSocket);
    throw std::runtime_error("Error al escuchar conexiones entrantes.");
  }

  Vista::muestraMensaje("Esperando conexiones entrantes...\n");

  while (true) {
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1)
      continue;
    Conexion conexion(conexiones.size() + 1, clientSocket);
    hilos.emplace_back(&Servidor::leerSolicitud, this, conexion);
  }

  return desconecta();
}

void Servidor::leerSolicitud(Conexion conexion) {
  Vista::muestraMensaje("Conexión establecida con el cliente.\n");
  constexpr std::size_t LIMITE = 1024 * 1024;
  char buffer[1024];
  std::string acumulado;

  while (true) {
    ssize_t bytes = recv(conexion.getSocket(), buffer, sizeof(buffer), 0);
    if (bytes <= 0) {
      Resultado resultado = Controlador::desconectar(conexion, conexiones, mtx);
      if (!conexion.getUsuario().empty())
        notificar(resultado.msjConexiones);
      break;
    }
    acumulado.append(buffer, bytes);
    std::size_t posicion;
    while ((posicion = acumulado.find('\n')) != std::string::npos) {
      std::string mensaje = acumulado.substr(0, posicion);
      acumulado.erase(0, posicion + 1);
      Vista::muestraMensaje(">> [%d]: %s", conexion.getNumero(), mensaje.c_str());
      obtenerRespuesta(mensaje, conexion);
    }
    if (acumulado.size() >= LIMITE) {
      conexion.desconecta();
      break;
    }
  }
}

void Servidor::obtenerRespuesta(const std::string& solicitud, Conexion& conexion) {
  Resultado resultado = Controlador::procesa(solicitud, conexion, conexiones, mtx);

  if (resultado.mensaje.has_value()) {
    const auto& [respuesta, usuario] = resultado.mensaje.value();
    enviaMensaje(respuesta, usuario);
  }
  if (!resultado.exito)
    conexion.desconecta();
  if (resultado.notificar)
    notificar(resultado.msjConexiones);
}

void Servidor::notificar(const std::string& mensaje) {
  std::lock_guard<std::mutex> lock(mtx);
  for (const auto& [nombre, conexion] : conexiones)
    enviaMensaje(mensaje, conexion);
}

void Servidor::enviaMensaje(const std::string& mensaje, const Conexion& conexion) {
  Vista::muestraMensaje("<< %s", mensaje.c_str());
  send(conexion.getSocket(), mensaje.c_str(), mensaje.length(), 0);
}

int Servidor::desconecta() {
  {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [nombre, conexion] : conexiones)
      conexion.desconecta();
  }
  for (auto& hilo : hilos)
    if (hilo.joinable())
      hilo.join();
  return close(serverSocket);
}

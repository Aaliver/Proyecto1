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

  std::printf("Conexión establecida con el cliente\n");

  while (true) {
      leerSolicitud(clientSocket);
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

void Servidor::leerSolicitud(int clientSocket) {
  char buffer[1024] = {0};
  ssize_t bytes = recv(clientSocket, buffer, sizeof(buffer), 0);

 std::string mensaje(buffer, bytes);
 std::printf(">> %s\n", mensaje.c_str());

 std::string respuesta = Controlador::procesa(mensaje);
 responderSolicitud(respuesta, clientSocket);
}

void Servidor::responderSolicitud(const std::string& mensaje, int clientSocket) {
  send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
}

#include "servidor.hpp"
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

  // const char* message = "Hola desde el servidor";
  // send(clientSocket, message, strlen(message), 0);

  char buffer[1024] = {0};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  std::printf("Mensaje del cliente: %s\n", buffer);

  // close(clientSocket);
  close(serverSocket);

  return 0;
}

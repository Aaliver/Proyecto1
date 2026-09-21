#include "cliente.hpp"
#include "usuario.hpp"
#include <cstdio>
#include <ctime>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Cliente::Cliente(Usuario usuario, int puerto) :
  usuario(usuario), puerto(puerto) {}

int Cliente::ejecuta() {

  std::srand(std::time(nullptr));

  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1)
    throw std::runtime_error("Error al crear el socket del cliente");

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    close(clientSocket);
    throw std::runtime_error("Error al conectar al servidor");
  }

  std::printf("Conectado al servidor!");

  const char* mensaje = "Hola, server";
  send(clientSocket, mensaje, strlen(mensaje), 0);

  close(clientSocket);

  return 0;
}

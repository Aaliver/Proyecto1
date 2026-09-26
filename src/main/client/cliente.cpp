#include "cliente.hpp"
#include "controlador.hpp"
#include "mensaje.hpp"
#include "usuario.hpp"
#include "vista.hpp"
#include <cstdio>
#include <cstring>
#include <ctime>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Cliente::Cliente(Usuario usuario, int puerto) :
  usuario(usuario), puerto(puerto), clientSocket(socket(AF_INET, SOCK_STREAM, 0)) {}

int Cliente::ejecuta() {

  if (clientSocket == -1)
    throw std::runtime_error("Error al crear el socket del cliente.");

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  Vista::muestraMensaje("Esperando conexión con el servidor...");

  if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    close(clientSocket);
    throw std::runtime_error("Error al conectar al servidor.");
  }

  hacerSolicitud(Controlador::conectar(usuario));

  while (usuario.isConectado()){
    constexpr std::size_t LIMITE = 1024 * 1024;
    char buffer[LIMITE] = {0};
    ssize_t bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytes <= 0)
      break;
    std::string mensaje(buffer, bytes);
    Controlador::procesa(mensaje, usuario);
  }

  return desconecta();
}

int Cliente::desconecta() {
  usuario.setConectado(false);
  return close(clientSocket);
}

void Cliente::hacerSolicitud(const std::string& mensaje) {
  send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
}

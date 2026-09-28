#include "cliente.hpp"
#include "controlador.hpp"
#include "vista.hpp"
#include <arpa/inet.h>
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

Cliente::Cliente(Usuario usuario, int puerto, std::string ip) :
  usuario(usuario), puerto(puerto), ip(ip),
  clientSocket(socket(AF_INET, SOCK_STREAM, 0)) {}

int Cliente::ejecuta() {

  if (clientSocket == -1)
    throw std::runtime_error("Error al crear el socket del cliente.");

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(puerto);
  if (inet_pton(AF_INET, ip.c_str(), &serverAddress.sin_addr) != 1)
    throw std::runtime_error("Dirección IP inválida.");

  Vista::muestraMensaje("Esperando conexión con el servidor...\n");

  if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    close(clientSocket);
    throw std::runtime_error("Error al conectar al servidor.");
  }

  hacerSolicitud(Controlador::identifica(usuario));

  std::thread receptor(&Cliente::recibirMensaje, this);
  leerEntrada();
  receptor.join();

  return desconecta();
}

void Cliente::recibirMensaje() {
  char buffer[1024];
  std::string acumulado;
  while (usuario.isConectado()) {
    ssize_t bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytes <= 0)
      break;
    acumulado.append(buffer, bytes);
    std::size_t posicion;
    while ((posicion = acumulado.find('\n')) != std::string::npos) {
      std::string mensaje = acumulado.substr(0, posicion);
      acumulado.erase(0, posicion + 1);
      Controlador::procesaMensaje(mensaje);
    }
    if (acumulado.size() >= LIMITE)
      break;
  }
  usuario.setConectado(false);
}

void Cliente::leerEntrada() {
  std::string entrada;
  while (usuario.isConectado()) {
    std::getline(std::cin, entrada);
    if (!entrada.empty())
      hacerSolicitud(Controlador::procesaSolicitud(entrada, usuario));
  }
}

void Cliente::hacerSolicitud(const std::string& mensaje) {
  if (mensaje.size() > LIMITE) {
    Vista::muestraError("El mensaje ha excedido el máximo de caracteres permitidos y no se eviara.");
    return;
  }
  if (!mensaje.empty())
    send(clientSocket, mensaje.c_str(), mensaje.length(), 0);
}

int Cliente::desconecta() {
  return close(clientSocket);
}

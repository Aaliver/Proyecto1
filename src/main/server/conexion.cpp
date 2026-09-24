#include "conexion.hpp"
#include <unistd.h>

Conexion::Conexion(int numero, int socket) : numero(numero), socket(socket) {}

void Conexion::setUsuario(std::string usuario) {
  this->usuario = usuario;
}

std::string Conexion::getUsuario() const {
  return usuario;
}

int Conexion::getNumero() const {
  return numero;
}

int Conexion::getSocket() const {
  return socket;
}

void Conexion::setEstado(EstadoConexion estado) {
  this->estado = estado;
}

EstadoConexion Conexion::getEstado() const {
  return estado;
}

int Conexion::desconecta() {
  return close(socket);
}

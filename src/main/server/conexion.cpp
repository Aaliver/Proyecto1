#include "conexion.hpp"

Conexion::Conexion(int numero, int socket) : numero(numero), socket(socket) {}

int Conexion::getNumero() {
  return numero;
}

int Conexion::getSocket() {
  return socket;
}

EstadoConexion Conexion::getEstado() {
  return estado;
}

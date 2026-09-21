#include "conexion.hpp"

Conexion::Conexion(std::string nombre, int numero) :
  nombre(nombre), numero(numero) {}

int Conexion::getNumero() {
  return numero;
}

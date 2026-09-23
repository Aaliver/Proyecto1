#include "usuario.hpp"
#include <string>

Usuario::Usuario(std::string nombre) :
  nombre(nombre), estado(EstadoConexion::ACTIVE), color(randomColor()) {}

std::string Usuario::getNombre() const {
  return nombre;
}

void Usuario::setEstado(EstadoConexion estado) {
  this->estado = estado;
}

EstadoConexion Usuario::getEstado() const {
  return estado;
}

std::string Usuario::toColorString() const {
  return pinta(color, nombre);
}

#include "usuario.hpp"

Usuario(string nombre) : nombre(nombre), estado(Estado::Active) {}

std::string Usuario::getNombre() const {
  return nombre;
}

void Usuario::setEstado(Estado estado) {
  this->estado = estado;
}

Estado Usuario::getEstado() const {
  return estado;
}

std::string Usuario::toColorString() const {
  return color.pinta(nombre);
}

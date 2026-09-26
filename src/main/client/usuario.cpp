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

bool Usuario::setConectado(bool conectado) {
  this->conectado = conectado;
}

bool Usuario::isConectado() const {
  return conectado;
}

std::string Usuario::toColorString() const {
  return pinta(color, nombre);
}

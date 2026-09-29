#include "sala.hpp"

Sala::Sala(std::string nombre) : nombre(nombre) {}

std::string Sala::getNombre() const {
  return nombre;
}

const std::unordered_map<std::string,Conexion>& Sala::getIntegrantes() const {
  return integrantes;
}

const std::vector<std::string>& Sala::getInvitados() const {
  return invitados;
}

void Sala::agregaIntegrante(const Conexion& conexion) {
  integrantes.emplace(conexion.getUsuario(), conexion);
}

void Sala::eliminaIntegrante(const Conexion& conexion) {
  integrantes.erase(conexion.getUsuario());
}

bool Sala::estaInvitado(std::string& invitado) const {
  return find(invitados.begin(), invitados.end(), invitado) != invitados.end();
}

void Sala::agregaInvitado(std::string& invitado) {
  invitados.push_back(invitado);
}

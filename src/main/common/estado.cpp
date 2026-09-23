#include "estado.hpp"

std::string_view toString(EstadoConexion estado) {
    switch (estado) {
    case EstadoConexion::ACTIVE: return "ACTIVE";
    case EstadoConexion::AWAY:   return "AWAY";
    case EstadoConexion::BUSY:   return "BUSY";
    }
}

EstadoConexion getEstado(std::string estado) {
  if (estado == "ACTIVE")
    return EstadoConexion::ACTIVE;
  else if (estado == "AWAY")
    return EstadoConexion::AWAY;
  else if (estado == "BUSY")
    return EstadoConexion::BUSY;
  else
    throw std::runtime_error("Estado inválido.");
}

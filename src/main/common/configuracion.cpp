#include "configuracion.hpp"
#include <stdexcept>

namespace {

  uint16_t validaPuerto(const std::string& valor) {
    size_t longitud;
    int puerto = std::stoi(valor, &longitud);
    if (longitud != valor.size() || puerto < 0 || puerto > 65535)
      throw std::out_of_range("Puerto inválido.");
    return static_cast<uint16_t>(puerto);
  }
}

Configuracion Argumentos::valida(int argc, char* argv[]){
  if (argc != 2)
    throw std::runtime_error("Cantidad incorrecta de argumentos.");
  Configuracion config;
  config.puerto = validaPuerto(argv[1]);
  return config;
}

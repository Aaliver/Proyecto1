#include "argumentos.hpp"
#include <stdexcept>

namespace {

  void validaCantidad(int n) {
    if (n != 2)
      throw std::runtime_error("Cantidad incorrecta de argumentos.");
  }

  uint16_t validaPuerto(const std::string& valor) {
    size_t longitud;
    int puerto = std::stoi(valor, &longitud);
    if (longitud != valor.size() || puerto < 0 || puerto > 65535)
      throw std::out_of_range("Puerto inválido.");
    return static_cast<uint16_t>(puerto);
  }
}

Configuracion Argumentos::validaServidor(int argc, char* argv[]){
  validaCantidad(argc);
  Configuracion config;
  config.puerto = validaPuerto(argv[1]);
  return config;
}

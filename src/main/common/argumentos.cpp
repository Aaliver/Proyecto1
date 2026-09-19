#include "argumentos.hpp"
#include <stdexcept>

namespace {

  void validaCantidad(int esperado, int total) {
    if (esperado != total)
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
  validaCantidad(2, argc);
  Configuracion config;
  config.puerto = validaPuerto(argv[1]);
  return config;
}

Configuracion Argumentos::validaCliente(int argc, char* argv[]){
  validaCantidad(5, argc);
  Configuracion config;
  for (int i = 1; i < argc; i++)
    switch (argv[i]) {
    case '-p':
      config.puerto = validaPuerto(argv[++i]);
      break;
    case '-u':
      break;
    default:
      throw std::runtime_error("Argumentos inválidos.");
    }
}

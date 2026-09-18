#include "argumentos.hpp"
#include <stdexcept>

namespace {

  void validaCantidad(int n) {
    if (n != 2)
      throw std::runtime_error("Cantidad incorrecta de argumentos.");
  }

  void validaPuerto(const std::string& valor) {
    size_t longitud;
    int puerto = std::stoi(valor, &longitud);
    if (longitud != valor.size() || puerto < 0 || puerto > 65535)
      throw std::out_of_range("Puerto inválido.");
  }
}

void Argumentos::valida(int argc, char* argv[]){
  validaCantidad(argc);
  validaPuerto(argv[1]);
}

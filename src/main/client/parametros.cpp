#include "parametros.hpp"
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

Parametros Argumentos::valida(int argc, char* argv[]){
  if (argc != 5)
    throw std::runtime_error("Cantidad incorrecta de argumentos.");
  Parametros param;
  for (int i = 1; i < argc; i++)
    if (std::string(argv[i]) == "-p") {
      if (argc <= ++i)
	throw std::runtime_error("Puerto no definido.");
      param.puerto = validaPuerto(argv[i]);
    } else if ("-u") {
      if (argc <= ++i)
	throw std::runtime_error("Nombre de usuario no definido.");
      param.nombre = argv[i];
    } else {
      throw std::runtime_error("Argumentos inválidos.");
    }
  return param;
}

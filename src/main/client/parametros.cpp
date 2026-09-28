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

Parametros Argumentos::valida(int argc, char* argv[]) {
  if (argc != 7)
    throw std::runtime_error("Cantidad incorrecta de argumentos.");
  Parametros param;
  for (int i = 1; i < argc; i++) {
    std::string bandera = std::string(argv[i]);
    if (bandera == "-p") {
      if (argc <= ++i)
	throw std::runtime_error("Puerto no definido.");
      param.puerto = validaPuerto(argv[i]);
    } else if (bandera == "-i") {
      if (argc <= ++i)
	throw std::runtime_error("Dirección ip no definida.");
      param.ip = argv[i];
    } else if (bandera == "-u") {
      if (argc <= ++i)
	throw std::runtime_error("Nombre de usuario no definido.");
      std::string nombre = argv[i];
      if (nombre.length() > 8)
	throw std::runtime_error("La longitud máxima del nombre de usuario es 8.");
      param.nombre = nombre;
    } else {
      throw std::runtime_error("Argumentos inválidos.");
    }
  }
  return param;
}

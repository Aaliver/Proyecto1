#include "argumentos.hpp"
#include "servidor.hpp"
#include <cstdio>
#include <stdexcept>

int error(const char* mensaje) {
  printf("%s\n", mensaje);
  return 1;
}

int main(int argc, char* argv[]) {

  try {
    Configuracion config = Argumentos::validaServidor(argc, argv);
    Servidor servidor(config);
    return servidor.ejecuta();
  } catch (const std::exception& e) {
    return error(e.what());
  }
}

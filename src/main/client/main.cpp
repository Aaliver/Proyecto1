#include "parametros.hpp"
#include "cliente.hpp"
#include <cstdio>
#include <stdexcept>

int error(const char* mensaje) {
  printf("%s\n", mensaje);
  return 1;
}

int main(int argc, char* argv[]) {

  try {
    Parametros param = Argumentos::valida(argc, argv);
    Cliente cliente(Usuario(param.nombre), param.puerto);
    return cliente.ejecuta();
  } catch (const std::exception& e) {
    return error(e.what());
  }
}

#include "vista.hpp"
#include "color.hpp"
#include <cstdarg>
#include <cstdio>

void Vista::muestraMensaje(const char* formato, ...) {
    va_list args;
    va_start(args, formato);
    std::vprintf(formato, args);
    std::printf("\n");
    va_end(args);
}

void Vista::muestraError(const std::string& mensaje) {
  std::printf("%s", pinta(Color::Rojo, mensaje).c_str());
}

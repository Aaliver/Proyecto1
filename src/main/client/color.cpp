#include "color.hpp"
#include <cstdlib>

std::string pinta(Color color, const std::string& cadena) {
  std::string reset = "\033[0m";
  std::string codigo;
  switch (color) {
  case Color::Rojo:
    codigo = "\033[31m"; break;
  case Color::Verde:
    codigo = "\033[32m"; break;
  case Color::Amarillo:
    codigo = "\033[33m"; break;
  case Color::Azul:
    codigo = "\033[34m"; break;
  case Color::Magenta:
    codigo = "\033[35m"; break;
  case Color::Cyan:
    codigo = "\033[36m"; break;
  }
  return codigo + cadena + reset;
}

Color randomColor() {
  int i = std::rand() % 6;
  return static_cast<Color>(i);
}

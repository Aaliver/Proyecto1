#include <iostream>
#include "color.hpp"
#include "usuario.hpp"
#include <ctime>

int main() {

  std::srand(std::time(nullptr));
  std::cout << pinta(randomColor(), "Cliente!") << "\n" << Usuario("Alice").toColorString() << std::endl;
  return 0;
}

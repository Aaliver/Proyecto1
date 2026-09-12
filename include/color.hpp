/**
 * @file color.hpp
 * @brief Definición del color del usuario.
 */

#pragma once
#include <string>

/**
 * @enum Color
 * @brief Enumeración para el color del {@link Usuario}.
 *
 * Los códigos vienen del repo:
 * https://gist.github.com/Alfonzzoj/db207b89d56f24d9d0b17ff93e091be8
 */
enum class Color {

  /** El color rojo. */
  Rojo,
  /** El color verde. */
  Verde,
  /** El color amarillo. */
  Amarillo,
  /** El color azul. */
  Azul,
  /** El color magenta. */
  Magenta,
  /** El color cyan. */
  Cyan
};


/**
 * @brief Regresa una cadena de color.
 * @param color el color del que se quiere pintar la cadena.
 * @param cadena la cadena a pintar.
 * @return una cadena de color.
 */
std::string pinta(Color color, const std::string& cadena);

/**
 * @brief Regresa un color random.
 * @return un color.
 */
Color randomColor();

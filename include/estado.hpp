/**
 * @file estado.hpp
 * @brief Definición del estado del usuario.
 */

#pragma once
#include <string_view>

/**
 * @enum Estado
 * @brief Enumeración para el estado del {@link Usuario}.
 */
enum class Estado {

  /** El estado conectado. */
  Active,
  /** El estado ausente. */
  Away,
  /** El estado ocupado. */
  Busy
};

/**
 * @brief Regresa una representación en cadena del estado.
 * @param estado el estado del cual regresar una cadena.
 * @return una representación en cadena del estado.
 **/
std::string_view toString(Estado estado);

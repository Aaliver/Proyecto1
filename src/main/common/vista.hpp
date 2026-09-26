/**
 * Definción de la vista del {@link Cliente} y {@link Servidor}.
 */

#pragma once
#include <string>

/**
 * @namespace Vista
 * @brief Funciones para mostrar los mensajes que recibe el {@link Cliente} y el
 *        {@link Servidor}.
 */
namespace Vista {

  /**
   * @brief Muestra un mensaje.
   * @param formato el formato del mensaje a mostrar.
   */
  void muestraMensaje(const char* formato, ...);

  /**
   * @brief Muestra un mensaje de error.
   * @param mensaje el mensaje a mostrar.
   */
  void muestraError(const std::string& mensaje);
}

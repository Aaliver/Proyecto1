/**
 * @file estado.hpp
 * @brief Definición del estado del usuario.
 */

#pragma once
#include <string>
#include <string_view>

/**
 * @enum EstadoConexion
 * @brief Enumeración para el estado del {@link Usuario}.
 */
enum class EstadoConexion {

  /** El estado conectado. */
  ACTIVE,
  /** El estado ausente. */
  AWAY,
  /** El estado ocupado. */
  BUSY
};

/**
 * @namespace Estado
 * @brief Funciones para la enum {@link EstadoConexion}.
 */
namespace Estado {

  /**
   * @brief Regresa una representación en cadena del estado.
   * @param estado el estado del cual regresar una cadena.
   * @return una representación en cadena del estado.
   **/
  std::string_view getString(EstadoConexion estado);

  /**
   * @brief Regresa el enunm del estado.
   * @param estado el estado del cual regresar el enum.
   * @return el enum del estado.
   **/
  EstadoConexion getEstado(std::string estado);
}

/**
 * @file usuario.hpp
 * @brief Definición de los usuarios.
 */

#pragma once
#include <string>
#include "estado.hpp"
#include "color.hpp"

/**
 * @class Usuario
 * @brief Definición de un usuario instancia de {@link Cliente}.
 */
class Usuario {

private:

  /* El nombre del usuario. */
  std::string nombre;
  /* El estado del usuario. */
  Estado estado;
  /* El color del usuario. */
  Color color;

public:

  /**
   * @brief El constructor.
   * @param nombre el nombre del usuario.
   */
  Usuario(std::string nombre);

  /**
   * @brief Regresa el nombre del usuario.
   * @return el nombre del usuario.
   */
  std::string getNombre() const;

  /**
   * @brief Define el estado del usuario.
   * @param estado el estado del usuario.
   */
  void setEstado(Estado estado);

  /**
   * @brief Regresa el estado del usuario.
   * @return el estado del usuario.
   */
  Estado getEstado() const;

  /**
   * @brief Regresa una representación en cadena de color del nombre de usuario.
   * @return una representación en cadena de color del nombre de usuario.
   */
  std::string toColorString() const;
};

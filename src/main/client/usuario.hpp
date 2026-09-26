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
  EstadoConexion estado;
  /* El estado de la conexión al servidor. */
  bool conectado;
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
  void setEstado(EstadoConexion estado);

  /**
   * @brief Regresa el estado del usuario.
   * @return el estado del usuario.
   */
  EstadoConexion getEstado() const;

  /**
   * @brief Define el estado de la conexión del usuario.
   * @param conectado el estado de la conexión del usuario.
   */
  bool setConectado(bool conectado);

  /**
   * @brief Nos dice si el usuario esta conectado.
   * @return true si el usuario esta conectado, false en otro caso.
   */
  bool isConectado() const;

  /**
   * @brief Regresa una representación en cadena de color del nombre de usuario.
   * @return una representación en cadena de color del nombre de usuario.
   */
  std::string toColorString() const;
};

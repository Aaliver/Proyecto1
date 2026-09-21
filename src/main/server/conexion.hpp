/**
 * @file conexion.hpp
 * @brief Definción de las conexiones de {@link Servidor}.
 */

#pragma once
#include <string>

/**
 * @class Conexion
 * @brief Definición de una conexion.
 */
class Conexion {

private:

  /* El nombre de la conexión. */
  std::string nombre;
  /* El número de la conexión. */
  int numero;

public:

  /**
   * El constructor.
   * @param nombre el nombre de la conexión.
   * @param numero el número de la conexión.
   */
  Conexion(std::string nombre, int numero);

  /**
   * Regresa el número de la conexión.
   * @return el número de la conexión.
   */
  int getNumero();
};

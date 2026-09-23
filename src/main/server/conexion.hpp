/**
 * @file conexion.hpp
 * @brief Definción de las conexiones de {@link Servidor}.
 */

#pragma once

/**
 * @class Conexion
 * @brief Definición de una conexion.
 */
class Conexion {

private:

  /* El número de la conexión. */
  int numero;
  /* El socket. */
  int socket;

public:

  /**
   * El constructor.
   * @param numero el número de la conexión.
      * @param socket el socket de la conexión.
   */
  Conexion(int numero, int socket);

  /**
   * Regresa el número de la conexión.
   * @return el número de la conexión.
   */
  int getNumero();

  /**
   * Regresa el socket de la conexión.
   * @return el socket de la conexión.
   */
  int getSocket();
};

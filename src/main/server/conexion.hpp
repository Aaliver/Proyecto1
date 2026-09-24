/**
 * @file conexion.hpp
 * @brief Definción de las conexiones de {@link Servidor}.
 */

#pragma once
#include "estado.hpp"

/**
 * @class Conexion
 * @brief Definición de una conexion.
 */
class Conexion {

private:

  /* El usuario de la conexión. */
  std::string usuario;
  /* El número de la conexión. */
  int numero;
  /* El socket de la conexión. */
  int socket;
  /* El estado de la conexión. */
  EstadoConexion estado;

public:

  /**
   * @brief El constructor.
   * @param numero el número de la conexión.
   * @param socket el socket de la conexión.
   */
  Conexion(int numero, int socket);

  /**
   * @brief Define el usuario de la conexión.
   * @param usuario el usuario de la conexión.
   */
  void setUsuario(std::string usuario);

  /**
   * @brief Regresa el usuario de la conexión.
   * @return el usuario de la conexión.
   */
  std::string getUsuario() const;

  /**
   * @brief Regresa el número de la conexión.
   * @return el número de la conexión.
   */
  int getNumero() const;

  /**
   * @brief Regresa el socket de la conexión.
   * @return el socket de la conexión.
   */
  int getSocket() const;

  /**
   * @brief Define el estado de la conexión.
   * @param estado el estado de la conexión.
   */
  void setEstado(EstadoConexion estado);

  /**
   * @brief Regresa el estado de la conexión.
   * @return el estado de la conexión.
   */
  EstadoConexion getEstado() const;

  /**
   * @brief Desconecta la conexión.
   * @return el éxito de la operación.
   */
  int desconecta();
};

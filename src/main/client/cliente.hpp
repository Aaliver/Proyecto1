/**
 * @file cliente.cpp
 * @brief Definición deñ cliente.
 */

#pragma once
#include "usuario.hpp"

/**
 * @class Cliente
 * @brief Definición de un cliente.
 */
class Cliente {

private:

  /* El usuario del cliente. */
  Usuario usuario;
  /* El puerto. */
  int puerto;

public:

  /**
   * @brief El constructor.
   * @param usuario el usuario.
   * @param puerto el puerto.
   */
  Cliente(Usuario usuario, int puerto);

  /**
   * @brief Inicia el cliente.
   */
  int ejecuta();
};

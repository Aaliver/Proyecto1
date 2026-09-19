/**
 * @file servidor.hpp
 * @brief Definición del servidor.
 */

#pragma once
#include "argumentos.hpp"

/**
 * @class Servidor
 * @brief Definición de un servidor.
 */
class Servidor {

private:

  /* La configuración del servidor. */
  Configuracion config;
  /* El socket del servidor. */
  int serverSocket;

public:

  /**
   * @brief El constructor.
   * @param config la configuración del servidor.
   */
  Servidor(const Configuracion& config);

  /**
   * @brief Inicia el servidor.
   */
  int ejecuta();
};

/**
 * @file servidor.hpp
 * @brief Definición del servidor.
 */

#pragma once
#include "argumentos.hpp"
#include "conexion.hpp"
#include <string>
#include <unordered_map>

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
  /* Las conexiones del servidor. */
  std::unordered_map<std::string,Conexion> conexiones;

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

/**
 * @file argumentos.hpp
 * @brief Definición de las funciones que validan las entradas de
 *        {@link Servidor} y {@link Cliente}.
 */

#pragma once
#include <string>

/**
 * @struct Configuracion
 * @brief Representa la configuración de {@link Servidor}
 */
struct Configuracion {

  /** El puerto. */
  uint16_t puerto;
};

/**
 * @namespace Argumentos
 * @brief Funciones para validar los argumentos de entrada.
 */
namespace Argumentos {

  /**
   * @brief Verifica que las entradas del servidor sean validas.
   * @param argc La cantidad de entradas.
   * @param argv El arreglo con las entradas.
   */
  Configuracion validaServidor(int argc, char* argv[]);

  /**
   * @brief Verifica que las entradas del cliente sean validas.
   * @param argc La cantidad de entradas.
   * @param argv El arreglo con las entradas.
   */
  Configuracion validaCliente(int argc, char* argv[]);
}

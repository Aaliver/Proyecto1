/**
 * @file argumentos.hpp
 * @brief Definición de las funciones que validan las entradas de
 *        {@link servidor.cpp}.
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
   * @brief Verifica que las entradas sean validas.
   * @param argc La cantidad de entradas.
   * @param argv El arreglo con las entradas.
   */
  Configuracion valida(int argc, char* argv[]);
}

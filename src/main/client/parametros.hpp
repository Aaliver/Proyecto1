/**
 * @file parametros.hpp
 * @brief Definición de las funciones que validan las entradas del {@link Cliente}.
 */

#pragma once
#include <string>

/**
 * @struct Parametros
 * @brief Representa los parametros del {@link Cliente}.
 */
struct Parametros {

  /** El nombre. */
  std::string nombre;
  /** El puerto. */
  uint16_t puerto;
  /** La ip. */
  std::string ip;
};

/**
 * @namespace Argumentos
 * @brief Funciones para validar los argumentos de entrada.
 */
namespace Argumentos {

  /**
   * @brief Verifica que las entradas del cliente sean validas.
   * @param argc La cantidad de entradas.
   * @param argv El arreglo con las entradas.
   */
  Parametros valida(int argc, char* argv[]);
}

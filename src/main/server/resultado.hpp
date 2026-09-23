/**
 * @file resultado.hpp
 * @brief Definción de los resultados de procesar los {@MensajeCliente} y
 *        {@MensajeServidor}.
 */

#pragma once
#include <string>

/**
 * @brief Definción de un resultado a un mensaje.
 */
struct Resultado {

  /**
   * @brief El mensaje de respuesta para la conexion.
   */
  std::string mensaje;

  /**
   * @brief El mensaje de respuesta para el resto de conexiones.
   */
  std::string mensajeConexiones;

  /**
   * @brief Indica el exito de realizar la operación.
   */
  bool exito;

  /**
   * @brief Indica si hay que notificar al resto de conexiones.
   */
  bool notificar;
};

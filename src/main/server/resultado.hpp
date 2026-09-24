/**
 * @file resultado.hpp
 * @brief Definción de los resultados de procesar los {@link MensajeCliente} y
 *        {@link MensajeServidor}.
 */

#pragma once
#include <tuple>
#include <string>
#include <optional>

/**
 * @brief Definción de un resultado a un mensaje.
 */
struct Resultado {

  /**
   * @brief El mensaje de respuesta y la conexion a la que enviar el mensaje.
   */
  std::optional<std::tuple<std::string, Conexion>> mensaje;

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

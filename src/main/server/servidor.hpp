/**
 * @file servidor.hpp
 * @brief Definición del servidor.
 */

#pragma once
#include "conexion.hpp"
#include "configuracion.hpp"
#include "resultado.hpp"
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

  /**
   * @brief Desconecta el servidor.
   */
  int desconectarse();

  /**
   * @brief Lee solicitudes del {@link Cliente}.
   * @param clientSocket el socket del cliente del que lee.
   */
  void leerSolicitud(Conexion conexion);

  /**
   * @brief Obtiene la respuesta de las solicitudes del {@link Cliente}.
   * @param resultado el resultado de la solicitud.
   * @param conexion la conexion de la que procesa la solicitud.
   */
  void obtenerRespuesta(Resultado resultado, Conexion conexion);

  /**
   * @brief Responde la solicitud del {@link Cliente}.
   * @param respuesta la respuesta que envia.
   * @param conexion la conexion a la que responde.
   */
  void responderSolicitud(const std::string& respuesta, Conexion conexion);
};

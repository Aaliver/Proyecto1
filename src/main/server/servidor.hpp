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
  int desconecta();

  /**
   * @brief Lee solicitudes del {@link Cliente}.
   * @param conexion la conexión de la que lee.
   */
  void leerSolicitud(Conexion& conexion);

  /**
   * @brief Obtiene la respuesta de las solicitudes del {@link Cliente}.
   * @param resultado el resultado de la solicitud.
   * @param conexion la conexion de la que procesa la solicitud.
   */
  void obtenerRespuesta(const Resultado& resultado, Conexion conexion);

  /**
   * @brief Notifica un mensaje a todos los clientes.
   * @param mensaje el mensaje que notifica.
   */
  void notificar(const std::string& mensaje);

  /**
   * @brief Enviar un mensaje al {@link Cliente}.
   * @param mensaje el mensaje que envia.
   * @param conexion la conexion a la que envia el mensaje.
   */
  void enviarMensaje(const std::string& mensaje, Conexion conexion);
};

/**
 * @file servidor.hpp
 * @brief Definición del servidor.
 */

#pragma once
#include "conexion.hpp"
#include "configuracion.hpp"
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
  /* Los hilos del servidor. */
  std::vector<std::thread> hilos;

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
   * @brief Lee solicitudes de la {@link Conexion}.
   * @param conexion la conexión de la que lee.
   */
  void leerSolicitud(Conexion conexion);

  /**
   * @brief Obtiene la respuesta de las solicitudes de la {@link Conexion}.
   * @param solicitud la solicitud de la que obtiene la respuesta.
   * @param conexion la conexion de la que procesa la solicitud.
   */
  void obtenerRespuesta(const std::string& solicitud, Conexion& conexion);

  /**
   * @brief Notifica un mensaje a todos los clientes.
   * @param mensaje el mensaje que notifica.
   */
  void notificar(const std::string& mensaje);

  /**
   * @brief Envia un mensaje al {@link Cliente}.
   * @param mensaje el mensaje que envia.
   * @param conexion la conexion a la que envia el mensaje.
   */
  void enviaMensaje(const std::string& mensaje, const Conexion& conexion);

  /**
   * @brief Desconecta el servidor.
   */
  int desconecta();
};

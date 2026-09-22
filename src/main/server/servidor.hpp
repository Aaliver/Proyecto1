/**
 * @file servidor.hpp
 * @brief Definición del servidor.
 */

#pragma once
#include "configuracion.hpp"
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

  /**
   * @brief Desconecta el servidor.
   */
  int desconectarse();

  /**
   * @brief Lee solicitudes del {@link Cliente}.
   * @param clientSocket el socket del cliente del que lee.
   */
  void leerSolicitud(int clientSocket);

  /**
   * @brief Responde solicitudes del {@link Cliente}.
   * @param mensaje el mensaje con el que responde.
   * @param clientSocket el socket del cliente al que responde.
   */
  void responderSolicitud(const std::string& mensaje, int clientSocket);
};

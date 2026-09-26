/**
 * @file cliente.cpp
 * @brief Definición deñ cliente.
 */

#pragma once
#include "usuario.hpp"
#include <string>

/**
 * @class Cliente
 * @brief Definición de un cliente.
 */
class Cliente {

private:

  /* El usuario del cliente. */
  Usuario usuario;
  /* El puerto del servidor. */
  int puerto;
  /* El socket del cliente. */
  int clientSocket;

public:

  /**
   * @brief El constructor.
   * @param usuario el usuario.
   * @param puerto el puerto.
   */
  Cliente(Usuario usuario, int puerto);

  /**
   * @brief Inicia el cliente.
   */
  int ejecuta();

  /**
   * @brief Conecta el cliente al {@link Servidor}.
   */
  void conecta();

  /**
   * @brief Desconecta el cliente.
   */
  int desconecta();

  /**
   * @brief Hace una solicitud al servidor.
   */
  void hacerSolicitud(const std::string& mensaje);

  /**
   * @brief Recibe un mensaje del servidor.
   */
  void recibeMensaje();
};

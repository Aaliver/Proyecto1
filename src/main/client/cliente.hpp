/**
 * @file cliente.hpp
 * @brief Definición del cliente.
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
  /* La ip del servidor. */
  std::string ip;
  /* El socket del cliente. */
  int clientSocket;

  /* El límite de los mensajes. */
  static constexpr std::size_t LIMITE = 1024 * 1024;

public:

  /**
   * @brief El constructor.
   * @param usuario el usuario.
   * @param puerto el puerto del servidor.
   * @param ip la ip del servidor.
   */
  Cliente(Usuario usuario, int puerto, std::string ip);

  /**
   * @brief Inicia el cliente.
   */
  int ejecuta();

  /**
   * @brief Recibe un mensaje del servidor.
   */
  void recibirMensaje();

  /**
   * @brief Lee la entrada del usuario.
   */
  void leerEntrada();

  /**
   * @brief Hace una solicitud al servidor.
   * @brief mensaje el mensaje con la solicitud.
   */
  void hacerSolicitud(const std::string& mensaje);

  /**
   * @brief Desconecta el cliente.
   */
  int desconecta();
};

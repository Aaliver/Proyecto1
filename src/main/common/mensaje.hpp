/**
 * @file mensaje.hpp
 * @brief Definición de los mensajes.
 */

#pragma once
#include "estado.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

/**
 * @enum MensajeCliente
 * @brief Enumeracuón para los tipos de mensajes del {@link Cliente}.
 */
enum class MensajeCliente {

  /** El mensaje de identificación. */
  IDENTIFY,
  /** El mensaje de cambio de estado . */
  STATUS,
  /** El mensaje de lista de usuarios. */
  USERS,
  /** El mensaje de enviar un texto privado. */
  TEXT,
  /** El mensaje de enviar un texto público. */
  PUBLIC_TEXT,
  /** El mensaje de nueva sala. */
  NEW_ROOM,
  /** El mensaje de invitar a un usuario. */
  INVITE,
  /** El mensaje de unirse a una sala. */
  JOIN_ROOM,
  /** El mensaje de lista de usuarios de la sala. */
  ROOM_USERS,
  /** El mensaje de enviar un texto a un cuarto. */
  ROOM_TEXT,
  /** El mensaje de abandonar un cuarto. */
  LEAVE_ROOM,
  /** El mensaje de desconexión. */
  DISCONNECT
};

/**
 * @enum MensajeServidor
 * @brief Enumeracuón para los tipos de mensajes del {@link Servidor}.
 */
enum class MensajeServidor {

  /** El mensaje de respuesta. */
  RESPONSE,
  /** El mensaje de nuevo usuario . */
  NEW_USER,
  /** El mensaje de nuevo estado . */
  NEW_STATUS,
  /** El mensaje con la lista de usuarios. */
  USER_LIST,
  /** El mensaje de enviar un texto privado. */
  TEXT_FROM,
  /** El mensaje de enviar un texto público. */
  PUBLIC_TEXT_FROM,
  /** El mensaje de invitación. */
  INVITATION,
  /** El mensaje de unirse a una sala. */
  JOINED_ROOM,
  /** El mensaje de lista de usuarios de la sala. */
  ROOM_USER_LIST,
  /** El mensaje de enviar un texto a un cuarto. */
  ROOM_TEXT_FROM,
  /** El mensaje de abandonar un cuarto. */
  LEFT_ROOM,
  /** El mensaje de desconexión. */
  DISCONNECTED,
  /** El mensaje inválido. */
  INVALID
};

/**
 * @namespace Mensaje
 * @brief Funciones para la construcción de los mensajes del {@link Cliente} y del
 *        {@link Servidor}.
 */
namespace Mensaje {

  /**
   * @brief Regresa una cadena del tipo de mensaje.
   * @param mensaje el mensaje.
   * @return una cadena del tipo de mensaje.
   */
  std::string_view getString(MensajeCliente mensaje);

    /**
   * @brief Regresa una cadena del tipo de mensaje.
   * @param mensaje el mensaje.
   * @return una cadena del tipo de mensaje.
   */
  std::string_view getString(MensajeServidor mensaje);

  /**
   * @brief Regresa un enum del tipo de mensaje del cliente.
   * @param mensaje el mensaje.
   * @return un enum del tipo de mensaje.
   */
  MensajeCliente getMsjCliente(const std::string& mensaje);

    /**
   * @brief Regresa un enum del tipo de mensaje del servidor.
   * @param mensaje el mensaje.
   * @return un enum del tipo de mensaje.
   */
  MensajeServidor getMsjServidor(const std::string& mensaje);

  /**
   * @brief Crea un mensaje del cliente.
   * @param datos los datos del mensaje.
   */
  std::string crea(const nlohmann::json& datos = {});

  /**
   * @brief Obten los datos del mensaje.
   * @param mensaje el mensaje del que obtener los datos.
   * @return los datos del mensaje.
   */
  nlohmann::json obtener(const std::string& mensaje);

  /**
   * @brief Regresa el estado del mensaje.
   * @param mensaje el mensaje del que obtener el estado.
   * @return el estado del mensaje.
   */
  EstadoConexion getEstado(const nlohmann::json& mensaje);
};

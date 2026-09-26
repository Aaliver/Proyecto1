/**
 * @brief Definición del controlador del {@link Cliente}.
 */

#pragma once
#include "usuario.hpp"
#include "mensaje.hpp"
#include <string>
#include <nlohmann/json.hpp>

/**
 * @namespace Controlador
 * @brief Funciones para procesar las solicitudes del {@link Cliente}.
 */
namespace Controlador {

  nlohmann::json conectar(Usuario& usuario);
  
  /**
   * @brief Procesa los mensajes que recibe el {@link Cliente}.
   * @param mensaje el mensaje a procesar.
   * @param usuario el usuario que recibe el mensaje.
   */
  void procesa(const std::string& mensaje, Usuario& usuario);

  /**
   * @brief Muestra la respuesta.
   * @param datos los datos de la respuesta.
   * @param tipo el tipo de respuesta.
   * @param usuario el usuario que recibe la respuesta.
   */
  void respuestaServidor(const nlohmann::json& datos, MensajeServidor tipo,
			 Usuario& usuario);

  /**
   * @brief Muestra el mensaje de respuesta del servidor.
   * @param datos los datos del mensaje.
   */
  void respuesta(const nlohmann::json& datos);

  /**
   * @brief Muestra el mensaje de nuevo usuario.
   * @param datos los datos del mensaje.
   */
  void nuevoUsuario(const nlohmann::json& datos);

  /**
   * @brief Muestra el mensaje de nuevo estado.
   * @param datos los datos del mensaje.
   */
  void nuevoEstado(const nlohmann::json& datos);

  /**
   * @brief Muestra el mensaje con la lista de usuarios.
   * @param datos los datos del mensaje.
   */
  void listaUsuarios(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje privado.
   * @param datos los datos del mensaje.
   */
  void textoPrivado(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje público.
   * @param datos los datos del mensaje.
   */
  void textoPublico(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de invitación a una sala.
   * @param datos los datos del mensaje.
   */
  void invitacion(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de unirse a una sala.
   * @param datos los datos del mensaje.
   */
  void unirseSala(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de una sala.
   * @param datos los datos del mensaje.
   */
  void textoSala(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de abandonar una sala.
   * @param datos los datos del mensaje.
   */
  void abandonarSala(const nlohmann::json& datos);

    /**
   * @brief Muestra un mensaje de desconexión.
   * @param datos los datos del mensaje.
   */
  void desconectar(const nlohmann::json& datos);
};

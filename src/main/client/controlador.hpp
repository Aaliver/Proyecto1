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
 * @brief Funciones para procesar las solicitudes del {@link Usuario} y enviar
 *        mensasajes al {@link Servidor}.
 */
namespace Controlador {

  /**
   * @brief Procesa la solicitud que recibe del {@link Usuario}.
   * @param datos los datos de la solicitud.
   * @param usuario el usuario que hace la solicitud.
   * @return la solicitud a enviar al servidor.
   */
  std::string procesaSolicitud(const std::string& datos, Usuario& usuario);

  /**
   * @brief Regresa un dato del stream.
   * @param stream el stream del que obtener el dato.
   * @return un dato del stream.
   */
  std::string getDato(std::stringstream& stream);

  /**
   * @brief Regresa una linea del stream.
   * @param stream el stream del que obtener la linea.
   * @return una linea del stream.
   */
  std::string getLinea(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de identificación.
   * @param usuario el usuario a identificarse.
   * @return una solicitud de identificación.
   */
  std::string identifica(Usuario& usuario);

  /**
   * @brief Regresa una solicitud de cambio de estado.
   * @param usuario el usuario a cambiar de estado.
   * @param stream el stream del que obtener el nuevo estado.
   * @return una solicitud de cambio de estado.
   */
  std::string estado(Usuario& usuario, std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de la lista de usuarios.
   * @return una solicitud de la lista de usuarios.
   */
  std::string listaUsuarios();

  /**
   * @brief Regresa una solicitud de texto privado.
   * @param stream el stream del que obtener el usuario a quien enviar el texto.
   * @return una solicitud de texto privado.
   */
  std::string textoPrivado(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de texto público.
   * @param stream el stream del que obtener el texto a enviar.
   * @return una solicitud de texto público.
   */
  std::string textoPublico(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de nueva sala.
   * @param stream el stream del que obtener la sala nueva.
   * @return una solicitud de nueva sala.
   */
  std::string nuevaSala(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud para invitar a una sala.
   * @param stream el stream del que obtener a que sala invitar y a quien invitar.
   * @return una solicitud para invitar a una sala.
   */
  std::string invitarSala(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud para unirse a una sala.
   * @param stream el stream del que obtener a que sala unirse.
   * @return una solicitud para unirse a una sala.
   */
  std::string unirseSala(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de la lista de usuarios de una sala.
   * @param stream el stream del que obtener a que sala listar.
   * @return una solicitud de la lista de usuarios de una sala.
   */
  std::string listaSala(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de texto a una sala.
   * @param stream el stream del que obtener a que sala enviar el texto.
   * @return una solicitud de texto a una sala.
   */
  std::string textoSala(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de abandonar una sala.
   * @param stream el stream del que obtener a que sala abandonar.
   * @return una solicitud de abandonar una sala.
   */
  std::string abandonarSala(std::stringstream& stream);

  /**
   * @brief Regresa una solicitud de desconexión.
   * @return una solicitud de desconexión.
   */
  std::string desconectar(Usuario& usuario);

  /**
   * @brief Procesa los mensajes que recibe el {@link Cliente}.
   * @param mensaje el mensaje a procesar.
   */
  void procesaMensaje(const std::string& mensaje);

  /**
   * @brief Muestra la respuesta del servidor.
   * @param tipo el tipo de respuesta.
   * @param datos los datos de la respuesta.
   */
  void respuestaServidor(MensajeServidor tipo, const nlohmann::json& datos);

  /**
   * @brief Muestra el mensaje de respuesta.
   * @param datos los datos del mensaje.
   */
  void muestraRespuesta(const nlohmann::json& datos);

  /**
   * @brief Muestra el mensaje de nuevo usuario.
   * @param datos los datos del mensaje.
   */
  void muestraNuevoUsuario(const nlohmann::json& datos);

  /**
   * @brief Muestra el mensaje de nuevo estado.
   * @param datos los datos del mensaje.
   */
  void muestraNuevoEstado(const nlohmann::json& datos);

  /**
   * @brief Muestra el mensaje con la lista de usuarios.
   * @param datos los datos del mensaje.
   */
  void muestraListaUsuarios(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje privado.
   * @param datos los datos del mensaje.
   */
  void muestraTextoPrivado(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje público.
   * @param datos los datos del mensaje.
   */
  void muestraTextoPublico(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de invitación a una sala.
   * @param datos los datos del mensaje.
   */
  void muestraInvitacion(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de unirse a una sala.
   * @param datos los datos del mensaje.
   */
  void muestraUnirseSala(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de una sala.
   * @param datos los datos del mensaje.
   */
  void muestraTextoSala(const nlohmann::json& datos);

  /**
   * @brief Muestra un mensaje de abandonar una sala.
   * @param datos los datos del mensaje.
   */
  void muestraAbandonarSala(const nlohmann::json& datos);

    /**
   * @brief Muestra un mensaje de desconexión.
   * @param datos los datos del mensaje.
   */
  void muestraDesconectar(const nlohmann::json& datos);
};

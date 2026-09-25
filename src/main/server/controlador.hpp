/**
 * @brief Definición del controlador del {@link Servidor}.
 */

#pragma once
#include "conexion.hpp"
#include "mensaje.hpp"
#include "resultado.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

/**
 * @namespace Controlador
 * @brief Funciones para procesar las solicitudes del {@link Cliente}.
 */
namespace Controlador {

  /**
   * @brief Procesa los mensajes que recibe el {@link Servidor}.
   * @param mensaje el mensaje a procesar.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conexiones del servidor.
   * @return el resultado de la operación.
   */
  Resultado procesa(const std::string& mensaje, Conexion& conexion,
		    std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Regresa el resultado del mensaje.
   * @param tipo el tipo del mensaje.
   * @param mensaje el mensaje a responder.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conexiones del servidor.
   * @return el resultado de la operación.
   */
  Resultado resultado(MensajeCliente tipo, const nlohmann::json& mensaje,
		      Conexion& conexion,
		      std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Identifica al usuario del mensaje.
   * @param mensaje el mensaje de identificación del usuario.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conexiones del servidor.
   * @return el resultado de la operación.
   */
  Resultado identificaUsuario(const nlohmann::json& mensaje, Conexion& conexion,
			      std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Cambia el estado de una conexion.
   * @param mensaje el mensaje de cambio de estado.
   * @param conexion la conexion que envio el mensaje.
   * @return el resultado de la operación.
   */
  Resultado cambiaEstado(const nlohmann::json& mensaje, Conexion& conexion);

  /**
   * @brief Regresa la lista de usuarios.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conexiones del servidor.
   * @return el resultado de la operación.
   */
  Resultado listaUsuarios(Conexion conexion,
			  std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Envia un texto privado a otro usuario.
   * @param mensaje el mensaje a enviar.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conexiones del servidor.
   * @return el resultado de la operación.
   */
  Resultado textoPrivado(const nlohmann::json& mensaje, Conexion conexion,
			 std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Envia un texto público a todos los usuarios.
   * @param mensaje el mensaje a enviar.
   * @param conexion la conexion que envio el mensaje.
   * @return el resultado de la operación.
   */
  Resultado textoPublico(const nlohmann::json& mensaje, Conexion conexion);

  Resultado nuevaSala();

  Resultado invitar();

  Resultado unirseSala();

  Resultado usuariosSala();

  Resultado textoSala();

  Resultado abandonarSala();

  /**
   * @brief Desconecta a una conexion.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conexiones del servidor.
   * @return el resultado de la operación.
   */
  Resultado desconectar(Conexion& conexion,
			std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Regresa el resultado de una operación inválida.
   * @param conexion la conexion que envio el mensaje.
   * @param resultado el resultado de la operación.
   * @return el resultado de la operación inválida.
   */
  Resultado invalido(Conexion conexion, std::string resultado);
};

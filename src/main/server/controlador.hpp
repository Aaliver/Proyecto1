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

namespace Controlador {

  /**
   * @brief Procesa los mensajes del {@link Servidor}.
   * @param mensaje el mensaje a procesar.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conecciones del servidor.
   * @return el resultado de la operación.
   */
  Resultado procesa(const std::string& mensaje, Conexion& conexion,
		    std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Identifica al usuario del mensaje.
   * @param mensaje el mensaje de identificación del usuario.
   * @param conexion la conexion que envio el mensaje.
   * @param conexiones el diccionario con las conecciones del servidor.
   * @return el resultado de la operación.
   */
  Resultado identificaUsuario(const nlohmann::json& mensaje, Conexion& conexion,
			      std::unordered_map<std::string, Conexion>& conexiones);

  /**
   * @brief Cambia el estado del usuario.
   * @param mensaje el mensaje de cambio de estado.
   * @param conexion la conexion que envio el mensaje.
   * @return el resultado de la operación.
   */
  Resultado cambiaEstado(const nlohmann::json& mensaje, Conexion& conexion);

  /**
   * @brief Regresa la lista de usuarios.
   * @return el resultado de la operación.
   */
  Resultado listaUsuarios(Conexion conexion,
			  std::unordered_map<std::string, Conexion>& conexiones);

  Resultado textoPrivado(const nlohmann::json& mensaje, Conexion conexion,
			 std::unordered_map<std::string, Conexion>& conexiones);

  Resultado textoPublico(const nlohmann::json& mensaje, Conexion conexion);

  Resultado nuevaSala();

  Resultado invitar();

  Resultado unirseSala();

  Resultado usuariosSala();

  Resultado textoSala();

  Resultado abandonarSala();

  Resultado desconectar(Conexion conexion,
			std::unordered_map<std::string, Conexion>& conexiones);
};

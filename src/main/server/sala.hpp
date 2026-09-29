/**
 * @file sala.hpp
 * @brief Definición de las salas del {@link Servidor}.
 */

#pragma once
#include "conexion.hpp"
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @class Sala
 * @brief Definición de una sala.
 */
class Sala {

private:

  /* El nombre de la sala. */
  std::string nombre;
  /* Los integrantes de la sala. */
  std::unordered_map<std::string,Conexion> integrantes;
  /* Los invitados de la sala. */
  std::vector<std::string> invitados;

public:

  /**
   * @brief El constructor.
   * @param nombre el nombre de la sala.
   */
  Sala(std::string nombre);

  /**
   * @brief Regresa el nombre de la sala.
   * @return el nombre de la sala.
   */
  std::string getNombre() const;

  /**
   * @brief Regresa el diccionario con los integrantes de la sala.
   * @return el diccionario con los integrantes de la sala.
   */
  const std::unordered_map<std::string,Conexion>& getIntegrantes() const;

  /**
   * @brief Regresa el vector con los invitados de la sala.
   * @return el vector con los invitados de la sala.
   */
  const std::vector<std::string>& getInvitados() const;

  /**
   * @brief Agrega un integrante a la sala.
   * @param conexion la conexion del integrante a agregar.
   */
  void agregaIntegrante(const Conexion& conexion);

  /**
   * @brief Elimina un integrante de la sala.
   * @param conexion la conexion del integrante a eliminar.
   */
  void eliminaIntegrante(const Conexion& conexion);

  /**
   * @brief Nos dice si un usuario esta invitado a la sala.
   * @param nombre el nombre del usuario.
   */
  bool estaInvitado(std::string& nombre) const;

  /**
   * @brief Agrega un invitado a la sala.
   * @param invitado el invitado a agregar.
   */
  void agregaInvitado(std::string& invitado);
};

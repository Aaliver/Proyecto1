#include "controlador.hpp"
#include "estado.hpp"
#include "vista.hpp"
#include <sstream>

using json = nlohmann::json;

std::string Controlador::procesaSolicitud(const std::string& datos, Usuario& usuario) {
  std::stringstream stream(datos);
  std::string comando = getDato(stream);
  if (comando == "/identify")
    return identifica(usuario);
  else if (comando == "/status")
    return estado(usuario, stream);
  else if (comando == "/users")
    return listaUsuarios();
  else if (comando == "/private")
    return textoPrivado(stream);
  else if (comando == "/public")
    return textoPublico(stream);
  else if (comando == "/newRoom")
    return nuevaSala(stream);
  else if (comando == "/invite")
    return invitarSala(stream);
  else if (comando == "/joinRoom")
    return unirseSala(stream);
  else if (comando == "/usersRoom")
    return listaSala(stream);
  else if (comando == "/textRoom")
    return textoSala(stream);
  else if (comando == "/leaveRoom")
    return abandonarSala(stream);
  else
    return desconectar(usuario);
}

std::string Controlador::getDato(std::stringstream& stream) {
  std::string dato;
  stream >> dato;
  return dato;
}

std::string Controlador::getLinea(std::stringstream& stream) {
  std::string linea;
  std::getline(stream, linea);
  return linea;
}

std::string Controlador::identifica(Usuario& usuario) {
  usuario.setConectado(true);
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::IDENTIFY)},
      {"username", usuario.getNombre()}
    });
}

std::string Controlador::estado(Usuario& usuario, std::stringstream& stream) {
  std::string estado = getDato(stream);
  EstadoConexion nuevoEstado = Estado::getEstado(estado);
  usuario.setEstado(nuevoEstado);
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::STATUS)},
      {"status", Estado::getString(nuevoEstado)}
    });
}

std::string Controlador::listaUsuarios() {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::USERS)}
    });
}

std::string Controlador::textoPrivado(std::stringstream& stream) {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::TEXT)},
      {"username", getDato(stream)},
      {"text", getLinea(stream)}
    });
}

std::string Controlador::textoPublico(std::stringstream& stream) {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::PUBLIC_TEXT)},
      {"text", getLinea(stream)}
    });
}

std::string Controlador::nuevaSala(std::stringstream& stream) {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::NEW_ROOM)},
      {"roomname", getDato(stream)}
    });
}

std::string Controlador::invitarSala(std::stringstream& stream) {
  json usuarios = json::array();
  std::string nombre;
  while (stream >> nombre)
    usuarios.push_back(nombre);
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::INVITE)},
      {"roomname", getDato(stream)},
      {"usernames", usuarios}
    });
}

std::string Controlador::unirseSala(std::stringstream& stream) {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::JOIN_ROOM)},
      {"roomname", getDato(stream)}
    });
}

std::string Controlador::listaSala(std::stringstream& stream) {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::ROOM_USERS)},
      {"roomname", getDato(stream)}
    });
}

std::string Controlador::textoSala(std::stringstream& stream) {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::ROOM_TEXT)},
      {"roomname", getDato(stream)},
      {"text", getLinea(stream)}
    });
}

std::string Controlador::abandonarSala(std::stringstream& stream) {
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::LEAVE_ROOM)},
      {"roomname", getDato(stream)},
    });
}

std::string Controlador::desconectar(Usuario& usuario) {
  usuario.setConectado(false);
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::DISCONNECT)}
    });
}

void Controlador::procesaMensaje(const std::string& mensaje) {
  if (mensaje.empty())
    return;

  try {
    json datos = Mensaje::obtener(mensaje);
    MensajeServidor tipo = Mensaje::getMsjServidor(datos.at("type"));
    respuestaServidor(tipo, datos);
  } catch (const json::parse_error& e) {
    return;
  } catch (const json::out_of_range& e) {
    return;
  }
}

void Controlador::respuestaServidor(MensajeServidor tipo, const json& datos) {
  switch (tipo) {
  case MensajeServidor::RESPONSE:
    muestraRespuesta(datos); break;
  case MensajeServidor::NEW_USER:
    muestraNuevoUsuario(datos); break;
  case MensajeServidor::NEW_STATUS:
    muestraNuevoEstado(datos); break;
  case MensajeServidor::USER_LIST:
    muestraListaUsuarios(datos); break;
  case MensajeServidor::TEXT_FROM:
    muestraTextoPrivado(datos); break;
  case MensajeServidor::PUBLIC_TEXT_FROM:
    muestraTextoPublico(datos); break;
  case MensajeServidor::INVITATION:
    muestraInvitacion(datos); break;
  case MensajeServidor::JOINED_ROOM:
    muestraUnirseSala(datos); break;
  case MensajeServidor::ROOM_USER_LIST:
    muestraListaUsuarios(datos); break;
  case MensajeServidor::ROOM_TEXT_FROM:
    muestraTextoSala(datos); break;
  case MensajeServidor::LEFT_ROOM:
    muestraAbandonarSala(datos); break;
  case MensajeServidor::DISCONNECTED:
    muestraDesconectar(datos); break;
  }
}

void Controlador::muestraRespuesta(const json& datos) {
  std::string resultado = (datos.at("result") == "SUCCESS") ? "exitosa" : "fallida";
  Vista::muestraMensaje("Operación %s.", resultado.c_str());
}

void Controlador::muestraNuevoUsuario(const json& datos) {
  Vista::muestraMensaje("%s se conecto al chat.",
			datos.at("username").get<std::string>().c_str());
}

void Controlador::muestraNuevoEstado(const json& datos) {
  Vista::muestraMensaje("%s cambio su estado a %s",
			datos.at("username").get<std::string>().c_str(),
			datos.at("status").get<std::string>().c_str());
}

void Controlador::muestraListaUsuarios(const json& datos) {
  Vista::muestraMensaje(datos.at("users").get<std::string>().c_str());
}

void Controlador::muestraTextoPrivado(const json& datos) {
  Vista::muestraMensaje("[Priv] %s: %s",
			datos.at("username").get<std::string>().c_str(),
			datos.at("text").get<std::string>().c_str());
}

void Controlador::muestraTextoPublico(const json& datos) {
  Vista::muestraMensaje("[General] %s: %s",
			datos.at("username").get<std::string>().c_str(),
			datos.at("text").get<std::string>().c_str());
}

void Controlador::muestraInvitacion(const json& datos) {
  Vista::muestraMensaje("%s te invito a la sala %s.",
			datos.at("username").get<std::string>().c_str(),
			datos.at("roomname").get<std::string>().c_str());
}

void Controlador::muestraUnirseSala(const json& datos) {
  Vista::muestraMensaje("%s se unio a la sala %s.",
			datos.at("username").get<std::string>().c_str(),
			datos.at("roomname").get<std::string>().c_str());
}

void Controlador::muestraTextoSala(const json& datos) {
  Vista::muestraMensaje("[%s] %s: %s",
			datos.at("roomname").get<std::string>().c_str(),
			datos.at("username").get<std::string>().c_str(),
			datos.at("text").get<std::string>().c_str());
}

void Controlador::muestraAbandonarSala(const json& datos) {
  Vista::muestraMensaje("%s ha abandonado la sala %s.",
			datos.at("username").get<std::string>().c_str(),
			datos.at("roomname").get<std::string>().c_str());
}

void Controlador::muestraDesconectar(const json& datos) {
  Vista::muestraMensaje("%s se ha desconectado.",
			datos.at("username").get<std::string>().c_str());
}

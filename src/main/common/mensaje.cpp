#include "mensaje.hpp"

std::string_view Mensaje::getString(MensajeCliente mensaje) {
  switch (mensaje) {
  case MensajeCliente::IDENTIFY:             return "IDENTIFY";
  case MensajeCliente::STATUS:               return "STATUS";
  case MensajeCliente::USERS:                return "USERS";
  case MensajeCliente::TEXT:                 return "TEXT";
  case MensajeCliente::PUBLIC_TEXT:          return "PUBLIC_TEXT";
  case MensajeCliente::NEW_ROOM:             return "NEW_ROOM";
  case MensajeCliente::INVITE:               return "INVITE";
  case MensajeCliente::JOIN_ROOM:            return "JOIN_ROOM";
  case MensajeCliente::ROOM_USERS:           return "ROOM_USERS";
  case MensajeCliente::ROOM_TEXT:            return "ROOM_TEXT";
  case MensajeCliente::LEAVE_ROOM:           return "LEAVE_ROOM";
  case MensajeCliente::DISCONNECT:           return "DISCONNECTED";
  }
}

MensajeCliente Mensaje::getMsjCliente(const std::string& mensaje) {
  if (mensaje == "IDENTIFY")
    return MensajeCliente::IDENTIFY;
  else if (mensaje == "STATUS")
    return MensajeCliente::STATUS;
  else if (mensaje == "USERS")
    return MensajeCliente::USERS;
  else if (mensaje == "TEXT")
    return MensajeCliente::TEXT;
  else if (mensaje == "PUBLIC_TEXT")
    return MensajeCliente::PUBLIC_TEXT;
  else if (mensaje == "NEW_ROOM")
    return MensajeCliente::NEW_ROOM;
  else if (mensaje == "INVITE")
    return MensajeCliente::INVITE;
  else if (mensaje == "JOIN_ROOM")
    return MensajeCliente::JOIN_ROOM;
  else if (mensaje == "ROOM_USERS")
    return MensajeCliente::ROOM_USERS;
  else if (mensaje == "ROOM_TEXT")
    return MensajeCliente::ROOM_TEXT;
  else if (mensaje == "LEAVE_ROOM")
    return MensajeCliente::LEAVE_ROOM;
  else
    return MensajeCliente::DISCONNECT;
}

std::string_view Mensaje::getString(MensajeServidor mensaje) {
  switch (mensaje) {
  case MensajeServidor::RESPONSE:            return "RESPONSE";
  case MensajeServidor::NEW_USER:            return "NEW_USER";
  case MensajeServidor::NEW_STATUS:          return "NEW_STATUS";
  case MensajeServidor::USER_LIST:           return "USER_LIST";
  case MensajeServidor::TEXT_FROM:           return "TEXT_FROM";
  case MensajeServidor::PUBLIC_TEXT_FROM:    return "PUBLIC_TEXT_FROM";
  case MensajeServidor::INVITATION:          return "INVITATION";
  case MensajeServidor::JOINED_ROOM:         return "JOINED_ROOM";
  case MensajeServidor::ROOM_USER_LIST:      return "ROOM_USER_LIST";
  case MensajeServidor::ROOM_TEXT_FROM:      return "ROOM_TEXT_FROM";
  case MensajeServidor::LEFT_ROOM:           return "LEFT_ROOM";
  case MensajeServidor::DISCONNECTED:        return "DISCONNECTED";
  }
}

MensajeServidor Mensaje::getMsjServidor(const std::string& mensaje) {
  if ("RESPONSE")
    return MensajeServidor::RESPONSE;
  else if (mensaje == "NEW_USER")
    return MensajeServidor::NEW_USER;
  else if (mensaje == "NEW_STATUS")
    return MensajeServidor::NEW_STATUS;
  else if (mensaje == "USER_LIST")
    return MensajeServidor::USER_LIST;
  else if (mensaje == "TEXT_FROM")
    return MensajeServidor::TEXT_FROM;
  else if (mensaje == "PUBLIC_TEXT_FROM")
    return MensajeServidor::PUBLIC_TEXT_FROM;
  else if (mensaje == "INVITATION")
    return MensajeServidor::INVITATION;
  else if (mensaje == "JOINED_ROOM")
    return MensajeServidor::JOINED_ROOM;
  else if (mensaje == "ROOM_USER_LIST")
    return MensajeServidor::ROOM_USER_LIST;
  else if (mensaje == "ROOM_TEXT_FROM")
    return MensajeServidor::ROOM_TEXT_FROM;
  else if (mensaje == "LEFT_ROOM")
    return MensajeServidor::LEFT_ROOM;
  else
    return MensajeServidor::DISCONNECTED;
}

std::string Mensaje::crea(const nlohmann::json& datos) {
  nlohmann::json mensaje = datos;
  return mensaje.dump() + "\n";
}

nlohmann::json Mensaje::obtener(const std::string& mensaje) {
  return nlohmann::json::parse(mensaje);
}

EstadoConexion Mensaje::getEstado(const nlohmann::json& mensaje) {
  return Estado::getEstado(mensaje["status"]);
}

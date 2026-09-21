#include "mensaje.hpp"

std::string_view tipo(MensajeCliente mensaje) {
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

std::string_view tipo(MensajeServidor mensaje) {
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

#include "controlador.hpp"
#include "estado.hpp"
#include "vista.hpp"

using json = nlohmann::json;


json Controlador::conectar(Usuario& usuario) {
  usuario.setConectado(true);
  return Mensaje::crea({
      {"type", Mensaje::getString(MensajeCliente::IDENTIFY)},
      {"username", usuario.getNombre()}
    });
}


void Controlador::procesa(const std::string& mensaje, Usuario& usuario) {
  if (mensaje.empty())
    return;

  try {
    json datos = Mensaje::obtener(mensaje);
    MensajeServidor tipo = Mensaje::getMsjServidor(datos.at("type"));
    respuestaServidor(datos, tipo, usuario);
  } catch (const json::parse_error& e) {
    return;
  } catch (const json::out_of_range& e) {
    return;
  }
}

void Controlador::respuestaServidor(const json& datos, MensajeServidor tipo,
				    Usuario& usuario) {
  switch (tipo) {
  case MensajeServidor::RESPONSE:
    respuesta(datos);
  case MensajeServidor::NEW_USER:
    nuevoUsuario(datos);
  case MensajeServidor::NEW_STATUS:
    nuevoEstado(datos);
  case MensajeServidor::USER_LIST:
    listaUsuarios(datos);
  case MensajeServidor::TEXT_FROM:
    textoPrivado(datos);
  case MensajeServidor::PUBLIC_TEXT_FROM:
    textoPublico(datos);
  case MensajeServidor::INVITATION:
    invitacion(datos);
  case MensajeServidor::JOINED_ROOM:
    unirseSala(datos);
  case MensajeServidor::ROOM_USER_LIST:
    listaUsuarios(datos);
  case MensajeServidor::ROOM_TEXT_FROM:
    textoSala(datos);
  case MensajeServidor::LEFT_ROOM:
    abandonarSala(datos);
  case MensajeServidor::DISCONNECTED:
    desconectar(datos);
  }
}

void Controlador::respuesta(const json& datos) {
  std::string resultado = (datos.at("result") == "SUCCESS") ? "exitosa" : "fallida";
  Vista::muestraMensaje("Operación %s.", resultado.c_str());
}

void Controlador::nuevoUsuario(const json& datos) {
  Vista::muestraMensaje("%s se conecto al chat.",
			datos.at("username").get<std::string>().c_str());
}

void Controlador::nuevoEstado(const json& datos) {
  // usuario.setEstado(Estado::getEstado(estado));
  Vista::muestraMensaje("%s cambio su estado a %s",
			datos.at("username").get<std::string>().c_str(),
			datos.at("status").get<std::string>().c_str());
}

void Controlador::listaUsuarios(const json& datos) {
  Vista::muestraMensaje(datos.at("users").get<std::string>().c_str());
}

void Controlador::textoPrivado(const json& datos) {
  Vista::muestraMensaje("[Priv] %s: %s",
			datos.at("username").get<std::string>().c_str(),
			datos.at("text").get<std::string>().c_str());
}

void Controlador::textoPublico(const json& datos) {
  Vista::muestraMensaje("[General] %s: %s",
			datos.at("username").get<std::string>().c_str(),
			datos.at("text").get<std::string>().c_str());
}

void Controlador::invitacion(const json& datos) {
  Vista::muestraMensaje("%s te invito a la sala %s.",
			datos.at("username").get<std::string>().c_str(),
			datos.at("roomname").get<std::string>().c_str());
}

void Controlador::unirseSala(const json& datos) {
  Vista::muestraMensaje("%s se unio a la sala %s.",
			datos.at("username").get<std::string>().c_str(),
			datos.at("roomname").get<std::string>().c_str());
}

void Controlador::textoSala(const json& datos) {
  Vista::muestraMensaje("[%s] %s: %s",
			datos.at("roomname").get<std::string>().c_str(),
			datos.at("username").get<std::string>().c_str(),
			datos.at("text").get<std::string>().c_str());
}
void Controlador::abandonarSala(const json& datos) {
  Vista::muestraMensaje("%s ha abandonado la sala %s.",
			datos.at("username").get<std::string>().c_str(),
			datos.at("roomname").get<std::string>().c_str());
}
void Controlador::desconectar(const json& datos) {
  Vista::muestraMensaje("%s se ha desconectado.",
			datos.at("username").get<std::string>().c_str());
}

#include "controlador.hpp"

using diccionario = std::unordered_map<std::string, Conexion>;
using json = nlohmann::json;

Resultado Controlador::procesa(const std::string& mensaje, Conexion& conexion,
			       diccionario& conexiones) {
  try {
    json datos = Mensaje::obtener(mensaje);
    MensajeCliente tipo = Mensaje::getMsjCliente(datos.at("type"));
    if (conexion.getUsuario().empty() && tipo != MensajeCliente::IDENTIFY)
      return invalido(conexion, "NOT_IDENTIFIED");
    return resultado(tipo, datos, conexion, conexiones);
  } catch (const json::parse_error& e) {
    return invalido(conexion, "INVALID");
  } catch (const json::out_of_range& e) {
    return invalido(conexion, "INVALID");
  }
}

Resultado Controlador::resultado(MensajeCliente tipo, const json& mensaje,
				 Conexion& conexion, diccionario& conexiones) {
  switch (tipo) {
  case MensajeCliente::IDENTIFY:
    return identificaUsuario(mensaje, conexion, conexiones);
  case MensajeCliente::STATUS:
    return cambiaEstado(mensaje, conexion);
  case MensajeCliente::USERS:
    return listaUsuarios(conexion, conexiones);
  case MensajeCliente::TEXT:
    return textoPrivado(mensaje, conexion, conexiones);
  case MensajeCliente::PUBLIC_TEXT:
    return textoPublico(mensaje, conexion);
  case MensajeCliente::NEW_ROOM:
    return nuevaSala();
  case MensajeCliente::INVITE:
    return invitar();
  case MensajeCliente::JOIN_ROOM:
    return unirseSala();
  case MensajeCliente::ROOM_USERS:
    return usuariosSala();
  case MensajeCliente::ROOM_TEXT:
    return textoSala();
  case MensajeCliente::LEAVE_ROOM:
    return abandonarSala();
  case MensajeCliente::DISCONNECT:
    return desconectar(conexion, conexiones);
  }
}

Resultado Controlador::identificaUsuario(const json& mensaje, Conexion& conexion,
					 diccionario& conexiones) {
  std::string username = mensaje.at("username");
  bool valido = username.length() <= 8;
  if (valido) {
    auto [it, agregado] = conexiones.insert({username, conexion});
    if (agregado)
      conexion.setUsuario(username);
    valido = agregado;
  }
  std::string resultado = (valido) ? "SUCCESS" : "USER_ALREADY_EXISTS";
  std::string respuesta = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::RESPONSE)},
      {"operation", Mensaje::getString(MensajeCliente::IDENTIFY)},
      {"result", resultado},
      {"extra", username}
    });
  std::string notificacion = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::NEW_USER)},
      {"username", username}
    });
  return {std::make_tuple(respuesta, conexion), notificacion, valido, valido};
}

Resultado Controlador::cambiaEstado(const json& mensaje, Conexion& conexion) {
  EstadoConexion estado = Mensaje::getEstado(mensaje);
  bool exito = estado != conexion.getEstado();
  if (exito)
    conexion.setEstado(estado);
  std::string notificacion = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::NEW_STATUS)},
      {"username", mensaje.at("username")},
      {"status", Estado::getString(estado)}
    });
  return {std::nullopt, notificacion, exito, exito};
}

Resultado Controlador::listaUsuarios(Conexion conexion, diccionario& conexiones) {
  json usuarios;
  for (const auto& [nombre, conexion] : conexiones)
    usuarios[nombre] = Estado::getString(conexion.getEstado());
  bool exito = true;
  std::string respuesta = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::USER_LIST)},
      {"users", usuarios}
    });
  return {std::make_tuple(respuesta, conexion), "", exito, !exito};
}

Resultado Controlador::textoPrivado(const json& mensaje, Conexion conexion,
				    diccionario& conexiones) {
  std::string usuario = mensaje.at("username");
  auto it = conexiones.find(usuario);
  bool existe = it != conexiones.end();
  std::string respuesta = (existe) ?
    Mensaje::crea({
	{"type", Mensaje::getString(MensajeServidor::TEXT_FROM)},
	{"username", conexion.getUsuario()},
	{"text", mensaje.at("text")}
      }) :
    Mensaje::crea({
	{"type", Mensaje::getString(MensajeServidor::RESPONSE)},
	{"operation", Mensaje::getString(MensajeCliente::TEXT)},
	{"result", "NO_SUCH_USER"},
	{"extra", usuario}
      });
  Conexion destino = (existe) ? it->second : conexion;
  return {std::make_tuple(respuesta, destino), "", existe, false};
}

Resultado Controlador::textoPublico(const json& mensaje, Conexion conexion) {
  std::string notificacion = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::PUBLIC_TEXT_FROM)},
      {"username", conexion.getUsuario()},
      {"text", mensaje.at("text")}
    });
  return {std::nullopt, notificacion, true, true};
}

Resultado Controlador::nuevaSala() {
  return {};
}

Resultado Controlador::invitar() {
  return {};
}

Resultado Controlador::unirseSala() {
  return {};
}

Resultado Controlador::usuariosSala() {
  return {};
}

Resultado Controlador::textoSala() {
  return {};
}

Resultado Controlador::abandonarSala() {
  return {};
}

Resultado Controlador::desconectar(Conexion& conexion, diccionario& conexiones) {
  std::string usuario = conexion.getUsuario();
  conexiones.erase(usuario);
  bool exito = conexion.desconecta() >= 0;
  std::string respuesta = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::DISCONNECTED)},
      {"username", usuario}
    });
  return {std::nullopt, respuesta, exito, true};
}

Resultado Controlador::invalido(Conexion conexion, std::string resultado) {
  std::string respuesta = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::RESPONSE)},
      {"operation", "INVALID"},
      {"result", resultado}
    });
  return {std::make_tuple(respuesta, conexion), "", false, false};
}

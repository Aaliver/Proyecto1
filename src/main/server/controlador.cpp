#include "controlador.hpp"

using json = nlohmann::json;

Resultado Controlador::procesa(const std::string& mensaje, Conexion& conexion,
			       std::unordered_map<std::string, Conexion>& conexiones) {
  json datos = Mensaje::obtener(mensaje);
  MensajeCliente tipo = Mensaje::getMsjCliente(datos["type"]);
  switch (tipo) {
  case MensajeCliente::IDENTIFY:
    return identificaUsuario(datos, conexion, conexiones);
  case MensajeCliente::STATUS:
    return cambiaEstado(datos, conexion);
  case MensajeCliente::USERS:
    return listaUsuarios(conexion, conexiones);
  case MensajeCliente::TEXT:
    return textoPrivado(datos, conexion, conexiones);
  case MensajeCliente::PUBLIC_TEXT:
    return textoPublico(datos, conexion);
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
					 std::unordered_map<std::string, Conexion>& conexiones) {
  std::string username = mensaje["username"];
  auto [it, agregado] = conexiones.insert({username, conexion});
  if (agregado)
    conexion.setUsuario(username);
  std::string resultado = (agregado) ? "SUCCESS" : "USER_ALREADY_EXISTS";
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
  return {std::make_tuple(respuesta, conexion),
	  notificacion, agregado, agregado};
}

Resultado Controlador::cambiaEstado(const json& mensaje, Conexion& conexion) {
  EstadoConexion estado = Mensaje::getEstado(mensaje);
  bool exito = estado != conexion.getEstado();
  if (exito)
    conexion.setEstado(estado);
  std::string notificacion = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::NEW_STATUS)},
      {"username", mensaje["username"]},
      {"status", Estado::getString(estado)}
    });
  return {std::nullopt, notificacion, exito, exito};
}

Resultado Controlador::listaUsuarios(Conexion conexion,
				     std::unordered_map<std::string, Conexion>& conexiones) {
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
				    std::unordered_map<std::string, Conexion>& conexiones) {
  std::string usuario = mensaje["username"];
  auto it = conexiones.find(usuario);
  bool existe = it != conexiones.end();
  std::string respuesta = (existe) ?
    Mensaje::crea({
	{"type", Mensaje::getString(MensajeServidor::TEXT_FROM)},
	{"username", conexion.getUsuario()},
	{"text", mensaje["text"]}
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
      {"text", mensaje["text"]}
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

Resultado Controlador::desconectar(Conexion conexion, std::unordered_map<std::string, Conexion>& conexiones) {
  std::string usuario = conexion.getUsuario();
  conexiones.erase(usuario);
  bool exito = conexion.desconecta() >= 0;
  std::string respuesta = Mensaje::crea({
      {"type", Mensaje::getString(MensajeServidor::DISCONNECTED)},
      {"username", usuario}
    });
  return {std::nullopt, respuesta, exito, true};
}

# Proyecto 1 : Chat multiusuario

## Requisitos

Se requiere tener instalados:

+ C++17
+ Meson
+ Ninja
+ Doxygen (opcional para generar la documentación)

## Construcción

Para compilar el programa:

```
meson setup build
meson compile -C build
```

Con los ejecutables en el directorio `build/src/main`.

## Ejecución

Para ejecutar el programa primero levantamos el servidor con el número del puerto:

```
./build/src/main/server/servidor 1234
```

Y después levantamos el cliente:

```
./build/src/main/client/cliente -p 1234 -u alice -i 127.0.0.1
```

Donde `-p` es la bandera para el puerto, `-u` la bandera para el nombre de
usuario y `-i` la bandera para la ip.

## Comandos

Esta es la lista de comandos que acepta el cliente y sus parámetros:

+ `/status`: acepta el nuevo estado del usuario entre `ACTIVE`, `AWAY` y `BUSY`.

+ `/users`: no tiene parámetros.

+ `/private`: recibe el nombre del destinatario y el mensaje a enviar.

+ `/public`: recibe el mensaje.

+ `/newRoom`: recibe el nombre de la nueva sala.

+ `/invite`: recibe el nombre de la sala y los nombres de los usuarios
  invitados separados por espacios.

+ `/joinRoom`: recibe el nombre de la sala a la que unirse.

+ `/usersRoom`: recibe el nombre de la sala de la que obtener los usuarios.

+ `/textRoom`: recibe el nombre de la sala y el mensaje a enviar.

+ `/leaveRoom`: recibe el nombre de la sala a abandonar.

+ `/disconnect`: no tiene parámetros.

## Documentación

Para generar la documentación con Doxygen:

```
doxygen Doxyfile
```

Con la documentación generada en `docs/html/index.html`.

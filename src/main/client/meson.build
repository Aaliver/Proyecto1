client_sources = files('usuario.cpp', 'estado.cpp', 'color.cpp')

lib_client = static_library(
    'client_core',
    client_sources,
)

executable(
    'cliente',
    'cliente.cpp',
    link_with: lib_client,
    install: true,
)

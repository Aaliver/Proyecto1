client_sources = files('usuario.cpp', 'estado.cpp', 'color.cpp')

lib_client = static_library(
    'client_core',
    client_sources,
    include_directories: inc_dir,
)

client_sources = files('cliente.cpp')

executable(
    'cliente',
    client_sources,
    include_directories: inc_dir,
    link_with: lib_client,
    install: true,
)

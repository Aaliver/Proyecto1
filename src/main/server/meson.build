server_sources = files('argumentos.cpp', 'servidor.cpp')

lib_server = static_library(
    'server_core',
    server_sources,
)

executable(
    'servidor',
    'main.cpp',
    link_with: lib_server,
    install: true,
)

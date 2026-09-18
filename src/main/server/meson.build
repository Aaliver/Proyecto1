server_sources = files('argumentos.cpp')

lib_server = static_library(
    'server_core',
    server_sources,
)

executable(
    'servidor',
    'servidor.cpp',
    link_with: lib_server,
    install: true,
)

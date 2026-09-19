client_sources = files('usuario.cpp', 'estado.cpp', 'color.cpp')

lib_client = static_library(
    'client_core',
    client_sources,
    include_directories: common_inc,
    link_with: lib_common,
)

executable(
    'cliente',
    'main.cpp',
    include_directories: common_inc,
    link_with: lib_client,
    install: true,
)

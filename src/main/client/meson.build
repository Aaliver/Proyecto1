client_sources = files(
    'cliente.cpp',
    'parametros.cpp',
    'usuario.cpp',
    'color.cpp',
)

lib_client = static_library(
    'client_core',
    client_sources,
    include_directories: common_inc,
    link_with: lib_common,
    dependencies: json_dep,
)

executable(
    'cliente',
    'main.cpp',
    include_directories: common_inc,
    link_with: lib_client,
    install: true,
)

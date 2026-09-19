server_sources = files('servidor.cpp')

lib_server = static_library(
    'server_core',
    server_sources,
    include_directories: common_inc,
    link_with: lib_common,
)

executable(
    'servidor',
    'main.cpp',
    include_directories: common_inc,
    link_with: lib_server,
    install: true,
)

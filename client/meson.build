imgui_dep = dependency('imgui', fallback: ['imgui', 'imgui_dep'])

client_sources = files('cliente.cpp')

if imgui_dep.found()
    executable(
        'Cliente',
        client_sources,
        dependencies: [imgui_dep],
        install: true,
    )
else
    warning('No se encontró Dear ImGui.')
endif

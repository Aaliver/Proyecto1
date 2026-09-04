imgui_dep = dependency('imgui', required: false)

client_sources = files('Cliente.cpp')

if imgui_dep.found()
  executable('Cliente',
             client_sources,
             dependencies: [imgui_dep],
             install: true)
else
  warning('No se encontró Dear ImGui.')
endif

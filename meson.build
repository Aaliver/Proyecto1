project(
    'chat-multiusuario',
    'cpp',
    default_options: ['cpp_std=c++17', 'warning_level=2'],
)

subdir('server')
subdir('client')
subdir('tests')

doxygen = find_program('doxygen', required: false)

if doxygen.found()
    custom_target(
        'docs',
        input: files('Doxyfile'),
        output: 'html',
        command: [doxygen, '@INPUT@'],
        build_by_default: false,
    )
endif

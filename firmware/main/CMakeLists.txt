add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    # tinyusb
    defs
)

pico_add_extra_outputs(${PROJECT_NAME})

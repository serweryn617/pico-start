add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    defs
    i2c_driver
    uart_driver
    ssd1306
)

pico_add_extra_outputs(${PROJECT_NAME})

add_executable(Lab01
        lab01.c
        )

# pull in common dependencies
target_link_libraries(Lab01 pico_stdlib)
# target_link_libraries(name INTERFACE pico_stdlib)
# target_include_directories(name INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Link to pico_stdlib (gpio, time, etc. functions)
# target_link_libraries(${PROJECT_NAME} 
#     pico_stdlib
# )

# create map/bin/hex file etc.
pico_add_extra_outputs(Lab01)


file(GLOB CARRASCONE_SRC "*.hpp" "*.cpp")

add_executable(carrascone ${CARRASCONE_SRC})

target_link_libraries(carrascone PRIVATE SFML::Graphics SFML::Window SFML::System m Boost::program_options)
target_compile_options(carrascone PRIVATE -Wall -Wextra -Wpedantic)

make_directory(${CMAKE_BINARY_DIR}/resources)
make_directory(${CMAKE_BINARY_DIR}/resources/textures)
make_directory(${CMAKE_BINARY_DIR}/resources/fonts)
file(GLOB TEXTURES "textures/*.png")
file(INSTALL ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/resources/textures)
file(GLOB FONTS "fonts/*.ttf")
file(INSTALL ${FONTS} DESTINATION ${CMAKE_BINARY_DIR}/resources/fonts)

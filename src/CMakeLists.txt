add_executable(carrascone main.cpp)
target_compile_options(carrascone PRIVATE -Wall -Wextra -Wpedantic)

set(CARRASCONE_SRC Castle.cpp Cell.cpp Cloister.cpp Field.cpp Map.cpp MapItem.cpp Menu.cpp Player.cpp PlayerManager.cpp Road.cpp Tile.cpp TileType.cpp)

add_library(carrascone_modules STATIC ${CARRASCONE_SRC})
target_include_directories(carrascone_modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(carrascone_modules PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(carrascone_modules PUBLIC SFML::Graphics m)

target_link_libraries(carrascone PRIVATE carrascone_modules)
target_link_libraries(carrascone PRIVATE SFML::Graphics SFML::Window SFML::System m Boost::program_options)

make_directory(${CMAKE_BINARY_DIR}/resources)
make_directory(${CMAKE_BINARY_DIR}/resources/textures)
make_directory(${CMAKE_BINARY_DIR}/resources/fonts)
file(GLOB TEXTURES "textures/*.png")
file(INSTALL ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/resources/textures)
file(GLOB FONTS "fonts/*.ttf")
file(INSTALL ${FONTS} DESTINATION ${CMAKE_BINARY_DIR}/resources/fonts)

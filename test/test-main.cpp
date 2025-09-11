#include <catch2/catch_session.hpp>
#include <filesystem>
#include <string>
#include "test-main.hpp"

std::string resource_path;

int main(int argc, char* argv[])
{

    const std::filesystem::path program{argv[0]};
    resource_path = program.parent_path().string() + "/../resources/";

    int result = Catch::Session().run(argc, argv);

    return result;
}
#ifndef TEST_MAIN_HPP
#define TEST_MAIN_HPP

#include <string>

extern std::string resource_path;

static inline std::string const& get_resource_path() { return resource_path; }

#endif // TEST_MAIN_HPP
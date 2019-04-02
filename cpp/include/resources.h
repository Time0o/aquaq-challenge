#ifndef RESOURCES_H
#define RESOURCES_H

#include <filesystem>
namespace fs = std::filesystem;


enum { NESTING = 3 };


std::string resource_path(std::string const &resource)
{
    auto source_path = fs::absolute(fs::path(__FILE__));

    auto top_path = source_path;
    for (int i = 0; i < NESTING; ++i)
        top_path = top_path.parent_path();

    auto resource_path = top_path / "resources" / resource;

    return resource_path.string();
}

#endif // RESOURCES_H

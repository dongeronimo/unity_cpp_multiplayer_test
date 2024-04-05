#pragma once
#include <fmt/os.h>

#define INIT_LOG fmt::ostream out = fmt::output_file("libmultiplayer.txt", fmt::file::WRONLY | fmt::file::CREATE | fmt::file::APPEND);
#include "filesystem.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace filesystem
{
	bool file_exists(const char * filename)
	{
		//fs::path path(filename);
		//bool exists = fs::exists(path) && fs::is_regular_file(path);
		
		bool exists = fs::exists(filename) && fs::is_regular_file(filename);

		return exists;
	}
}


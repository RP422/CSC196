#include "filesystem.h"

#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

namespace filesystem
{
	bool file_exists(const char * filename)
	{
		//// We can do this, too, but we can shortcut it.
		//fs::path path(filename);
		//bool exists = fs::exists(path) && fs::is_regular_file(path);
		
		bool exists = fs::exists(filename) && fs::is_regular_file(filename);

		return exists;
	}

	bool file_size(const char * filename, size_t& size)
	{
		bool success = file_exists(filename);

		if (success)
		{
			size = static_cast<size_t>(fs::file_size(filename));
		}

		return success;
	}

	bool read_file(const char * filename, void ** buffer, size_t& size)
	{
		bool success = file_exists(filename);

		if (success)
		{
			std::ifstream stream(filename, std::ios::binary);
			success = stream.is_open();

			if (success && file_size(filename, size))
			{
				*buffer = new char[size];
				stream.read(static_cast<char*>(*buffer), size);
				stream.close();
			}
		}

		return success;
	}

	bool write_file(const char * filename, void * buffer, size_t size)
	{
		bool success = false;

		std::ofstream stream(filename, std::ios::binary);
		success = stream.is_open();

		if (success)
		{
			stream.write(static_cast<char*>(buffer), size);
			stream.close();
		}

		return success;
	}

	void free_file(void * buffer)
	{
		delete[] buffer;
	}

	bool delete_file(const char * filename)
	{
		bool success = file_exists(filename);

		if (success)
		{
			success = fs::remove(filename);
		}

		return success;
	}

	bool copy_file(const char * src, const char * destination, bool overwrite)
	{
		bool success = file_exists(src);

		if (success)
		{
			success = fs::copy_file(src, destination, (overwrite) ? fs::copy_options::overwrite_existing : fs::copy_options::skip_existing);
		}

		return success;
	}

	bool directory_exists(const char * directory)
	{
		bool exists = fs::exists(directory) && fs::is_directory(directory);

		return exists;
	}

	bool copy_directory(const char * src, const char * destination, bool recursive)
	{
		bool success = directory_exists(src);

		if (success)
		{
			fs::copy(src, destination, (recursive) ? fs::copy_options::recursive : fs::copy_options::none); // check this
		}

		return success;
	}

	bool create_directory(const char * directory)
	{
		return fs::create_directories(directory);
	}

	bool delete_directory(const char * directory)
	{
		bool success = file_exists(directory);

		if (success)
		{
			fs::remove_all(directory);
		}

		return success;
	}

	bool delete_empty_directory(const char * directory)
	{
		bool success = file_exists(directory) && fs::is_empty(directory);

		if (success)
		{
			success = fs::remove(directory);
		}

		return success;
	}

	void set_current_path(const char * pathname)
	{
		fs::current_path(pathname);
	}

	void get_current_path(char * pathname, size_t size)
	{
		strcpy_s(pathname, size, fs::current_path().string().c_str());
	}
}


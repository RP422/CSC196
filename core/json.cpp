#include "json.h"
#include "filesystem.h"

#include <iostream>

namespace json
{
	bool load(const char * filename, rapidjson::Document& document)
	{
		bool success = false;
		char* buffer;
		size_t size;

		if (filesystem::read_file(filename, (void**)& buffer, size))
		{
			std::cout << buffer; // Debug
			document.Parse(buffer);
			success = document.IsObject();

			filesystem::free_file(buffer);
		}

		return success;
	}

	bool get_int(const rapidjson::Value & value, const char * property_name, int & r_int)
	{
		bool success = false;
		auto iterator = value.FindMember(property_name);

		if (iterator != value.MemberEnd())
		{
			auto& property = iterator->value;
			if (property.IsInt())
			{
				r_int = property.GetInt();
				success = true;
			}
		}

		return success;
	}
	bool get_float(const rapidjson::Value & value, const char * property_name, float & r_float)
	{
		return false;
	}
	bool get_string(const rapidjson::Value & value, const char * property_name, std::string & r_string)
	{
		return false;
	}
	bool get_bool(const rapidjson::Value & value, const char * property_name, bool & r_bool)
	{
		return false;
	}
	bool get_vector2(const rapidjson::Value & value, const char * property_name, vector2 & r_vector2)
	{
		bool success = false;
		auto iterator = value.FindMember(property_name);

		if (iterator != value.MemberEnd())
		{
			auto& property = iterator->value;
			if (property.IsArray() && property.Size() == 2)
			{
				success = true;

				for (rapidjson::SizeType i = 0; i < 2; i++)
				{
					if (!property[1].IsDouble())
					{
						success = false;
					}
				}

				if (success)
				{
					r_vector2.x = property[0].GetFloat();
					r_vector2.y = property[1].GetFloat();
				}
			}
		}

		return success;
	}
}





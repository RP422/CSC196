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
			buffer[size - 1] = 0; // Make sure there's a newline after the last character in the json
			std::cout << buffer << std::endl; // Debug Line
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
		bool success = false;
		auto iterator = value.FindMember(property_name);

		if (iterator != value.MemberEnd())
		{
			auto& property = iterator->value;
			if (property.IsDouble())
			{
				r_float = (float)property.GetDouble();
				success = true;
			}
		}

		return success;
	}
	bool get_string(const rapidjson::Value & value, const char * property_name, std::string & r_string)
	{
		bool success = false;
		auto iterator = value.FindMember(property_name);

		if (iterator != value.MemberEnd())
		{
			auto& property = iterator->value;
			if (property.IsString())
			{
				r_string = property.GetString();
				success = true;
			}
		}

		return success;
	}
	bool get_bool(const rapidjson::Value & value, const char * property_name, bool & r_bool)
	{
		bool success = false;
		auto iterator = value.FindMember(property_name);

		if (iterator != value.MemberEnd())
		{
			auto& property = iterator->value;
			if (property.IsBool())
			{
				r_bool = property.GetBool();
				success = true;
			}
		}

		return success;
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
	bool get_vector2(const rapidjson::Value & value, const char * property_name, std::vector<vector2>& r_vector2)
	{
		bool success = true;

		for (rapidjson::SizeType i = 0; success && i < value.Size(); i++)
		{
			const rapidjson::Value& vertex = value[i];
			
			if (vertex.IsObject())
			{
				vector2 v2;

				success = get_vector2(vertex, property_name, v2);
				
				if (success)
				{
					r_vector2.push_back(v2);
				}
			}
			else
			{
				success = false;
			}
		}

		return success;
	}
	bool get_color(const rapidjson::Value & value, const char * property_name, color & r_color)
	{
		bool success = false;
		auto iterator = value.FindMember(property_name);

		if (iterator != value.MemberEnd())
		{
			auto& property = iterator->value;
			if (property.IsArray() && property.Size() == 3)
			{
				success = true;

				for (rapidjson::SizeType i = 0; i < 3; i++)
				{
					if (!property[1].IsDouble())
					{
						success = false;
					}
				}

				if (success)
				{
					r_color.r = property[0].GetFloat();
					r_color.g = property[1].GetFloat();
					r_color.b = property[2].GetFloat();
				}
			}
		}

		return success;
	}
}





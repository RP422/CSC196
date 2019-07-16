#pragma once

#include "../math/vector2.h"
#include "../renderer/color.h"
#include "../external/rapidjson/document.h"

#include <string>

namespace json
{
	bool load(const char* filename, rapidjson::Document& document);

	bool get_int(const rapidjson::Value& value, const char* property_name, int& r_int);
	bool get_float(const rapidjson::Value& value, const char* property_name, float& r_float);
	bool get_string(const rapidjson::Value& value, const char* property_name, std::string& r_string);
	bool get_bool(const rapidjson::Value& value, const char* property_name, bool& r_bool);
	bool get_vector2(const rapidjson::Value& value, const char* property_name, vector2& r_vector2);
	bool get_vector2(const rapidjson::Value& value, const char* property_name, std::vector<vector2>& r_vector2);
	bool get_color(const rapidjson::Value& value, const char* property_name, color& r_color);
}
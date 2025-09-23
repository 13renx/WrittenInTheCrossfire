#pragma once

#include <tuple>
#include <string>

class Model
{
	public:
		virtual void init() = 0;
		virtual std::tuple<bool, std::string> save() = 0;
		virtual std::tuple<bool, std::string> load() = 0;
};
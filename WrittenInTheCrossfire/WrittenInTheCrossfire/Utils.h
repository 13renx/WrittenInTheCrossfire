#pragma once
#include <string>
#include "spdlog/spdlog.h"

namespace Utils
{
	namespace Log {
		void info(std::string text);
		void warn(std::string text);
		void error(std::string text);
		void critical(std::string text);
	}
};


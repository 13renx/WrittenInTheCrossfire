#pragma once
#include <string>
#include "spdlog/spdlog.h"

namespace Utils
{
	class Log {
		private:
			static std::string fileName;
			static spdlog::logger logger;

		public:
			static void init();
			static void info(std::string text);
			static void warn(std::string text);
			static void error(std::string text);
			static void critical(std::string text);
		};
};
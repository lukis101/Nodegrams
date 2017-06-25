 /*
	Dreamshows engine test app

	Copyright 2017 Lukas Jonyla

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#include "spdlog/spdlog.h"

#include "Dsse/DssEngine.h"
#include <iostream>

int main( int argc, char* argv[] )
{
	auto l = spdlog::stdout_logger_mt("DsseTest");
	Dsse::Dsse engine(l);

	int ret = engine.Init();
	l->info( "Dsse.Init() = {}", ret);

	ret = engine.Shutdown();
	l->info("Dsse.Shutdown() = {}", ret);

	try
	{
		//auto console = spdlog::stdout_logger_mt("console");
		//auto console = spdlog::stderr_logger_mt("console");
		auto console = spdlog::basic_logger_mt("console", "log.txt");

		// Console logger with color
		//auto console = spdlog::stdout_color_mt("console");
		console->info("Welcome to spdlog!");
		console->error("Some error message with arg{}..", 1);
		console->warn("Easy padding in numbers like {:08d}", 12);
		console->critical("Support for int: {0:d};  hex: {0:X};  oct: {0:o}; bin: {0:b}", 42);
		spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name) function");
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log init failed: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
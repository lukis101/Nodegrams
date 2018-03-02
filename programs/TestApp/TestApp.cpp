 /*
	Dreamshows engine test app

	Copyright 2018 Lukas Jonyla

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

#include <iostream>
#include "Dsse/DssEngine.h"
#include "Dsse/nodes/TestNode.h"

int main( int argc, char* argv[] )
{
	try
	{
	    auto l_dsse = spdlog::stdout_logger_mt("dsse");
        auto l_iolet = spdlog::stdout_logger_mt("iolet");

        dsse::Dsse engine(l_dsse);

	    int ret_init = engine.Init();
        l_dsse->info( "Dsse.Init() = {}", ret_init);

        dsse::TestNode testnode;
        engine.RegisterNode(&testnode);
        testnode.DoLogic();
        engine.ReleaseNode(testnode.GetID());

	    int ret_deinit = engine.Shutdown();
        l_dsse->info("Dsse.Shutdown() = {}", ret_deinit);

		/*
        auto l_console = spdlog::stdout_logger_mt("console");
		//auto l_console = spdlog::basic_logger_mt("console", "log.txt");
        l_console->warn("Easy padding in numbers like {:08d}", 12);
        l_console->critical("Support for int: {0:d};  hex: {0:X};  oct: {0:o}; bin: {0:b}", 42);
		spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name) function");
        */
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log init failed: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

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

#include <memory>
#include <iostream>
#include "spdlog/spdlog.h"

#include "Dsse/DssEngine.h"
#include "Dsse/TypeRegistry.h"
#include "Dsse/inoutlets/InletBase.h"
#include "Dsse/inoutlets/OutletBase.h"

#include "Dsse/datatypes/Boolean.h"
#include "Dsse/datatypes/Float.h"
#include "Dsse/datatypes/Double.h"
#include "Dsse/datatypes/Int32.h"
#include "Dsse/datatypes/Int64.h"

#include "Dsse/nodes/TestNode.h"
#include "Dsse/nodes/time/SysTimeNode.h"

int main( int argc, char* argv[] )
{
	try
	{
        //spdlog::set_level(spdlog::level::debug);
	    auto l_dsse = spdlog::stdout_logger_mt("dsse");
        //l_dsse->set_level(spdlog::level::debug);
	    auto l_dssedat = spdlog::stdout_logger_mt("dsse.data");
        //l_dssedat->set_level(spdlog::level::debug);
        auto l_iolet = spdlog::stdout_logger_mt("iolet");
        //l_iolet->set_level(spdlog::level::debug);

        dsse::Dsse engine(l_dsse);
	    engine.Init();

        engine.typereg->RegisterDataType(new dsse::Boolean(&engine));
        engine.typereg->RegisterDataType(new dsse::Float(&engine));
        engine.typereg->RegisterDataType(new dsse::Double(&engine));
        engine.typereg->RegisterDataType(new dsse::Int32(&engine));
        engine.typereg->RegisterDataType(new dsse::Int64(&engine));

        int tnode = engine.AddNode(new dsse::TestNode(&engine));
        int stnode = engine.AddNode(new dsse::SysTimeNode(&engine));

        l_dsse->info("PrintNodes: \n{}", engine.PrintNodes(true));

        dsse::OutletBase* outl_s32 = engine.GetNode(stnode)->GetOutlet("Seconds");
        dsse::OutletBase* outl_s64 = engine.GetNode(stnode)->GetOutlet("Milliseconds");
        dsse::InletBase* inl_f = engine.GetNode(tnode)->GetInlet("in_float");
        dsse::InletBase* inl_s64 = engine.GetNode(tnode)->GetInlet("in_int64");

        l_dsse->info("I-O connect 1 = {}", outl_s32->ConnectTo(inl_f));
        l_dsse->info("I-O connect 2 = {}", outl_s64->ConnectTo(inl_s64));

        engine.Update();
        engine.Update();

        // TODO disconnect inoutlets

        engine.DeleteNode(tnode);
        engine.DeleteNode(stnode);
	    engine.Shutdown();

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


#include "spdlog/spdlog.h"

#include "Dsse/DataTypes.h"
#include "Dsse/DssEngine.h"
//#include <iostream>

namespace dsse
{
	Dsse::Dsse()
	{
		m_logger = spdlog::stdout_logger_mt("dsse");
	}
	Dsse::Dsse(std::shared_ptr<spdlog::logger> logger)
	{
		m_logger = logger;
	}
	Dsse::~Dsse()
	{
		spdlog::drop(m_logger->name());
	}

	int Dsse::Init()
	{
		m_logger->info("Dsse Initialising..");
		return 0;
	}
	int Dsse::Shutdown()
	{
		m_logger->info("Dsse shutting down..");
		return 0;
	}
} // namespace Dsse
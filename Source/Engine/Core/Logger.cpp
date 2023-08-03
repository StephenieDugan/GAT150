#include "Logger.h"
#include "fileIO.h"
#include <iostream>

namespace Twili
{
	Logger g_logger(&std::cout,LogLevel::info, "log.txt");

	bool Logger::Log(LogLevel loglevel, const std::string filename, int line)
	{
		if (loglevel < m_LogLevel) return false;

		switch (loglevel)
		{
		case Twili::LogLevel::info:
			*this << "INFO: ";
			break;
		case Twili::LogLevel::warning:
			*this << "WARNING: ";
			break;
		case Twili::LogLevel::error:
			*this << "ERROR: ";
			break;
		case Twili::LogLevel::assert:
			*this << "ASSERT: ";
			break;
		default:
			break;

		}
		*this << filename << "(" << line << ")";

		return true;
	}
}
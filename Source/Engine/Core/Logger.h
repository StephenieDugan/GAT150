#pragma once
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#ifdef _DEBUG

#define INFO_LOG(message) { if(Twili::g_logger.Log(Twili::LogLevel::info, __FILE__, __LINE__)) { Twili::g_logger << message << "\n"; }}
#define WARNING_LOG(message) { if(Twili::g_logger.Log(Twili::LogLevel::warning, __FILE__, __LINE__)){ Twili::g_logger << message << "\n"; }}
#define ERROR_LOG(message) { if(Twili::g_logger.Log(Twili::LogLevel::error, __FILE__, __LINE__)){ Twili::g_logger << message << "\n"; }}
#define ASSERT_LOG(condition, message) { if(!condition && Twili::g_logger.Log(Twili::LogLevel::assert, __FILE__, __LINE__)) { Twili::g_logger << message << "\n"; } assert(condition);}
#else
#define INFO_LOG(message) {};
#define WARNING_LOG(message) {};
#define ERROR_LOG(message) {};
#define ASSERT_LOG(condition, message) {};
#endif 
//_DEBUG

namespace Twili
{
	enum  LogLevel
	{
		info,
		warning,
		error,
		assert
};

	class Logger
	{
	public:
		Logger(std::ostream* ostream, LogLevel logLevel, const std::string& filename = "") : m_ostream{ ostream }, m_LogLevel{ logLevel } { if (!filename.empty()) m_fstream.open(filename); };

		bool Log(LogLevel loglevel, const std::string filename, int line);

		template<typename T>
		Logger& operator << (T value);

	private:
		LogLevel m_LogLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;

	};


	template<typename T>
	inline Logger& Logger::operator << (T value)
	{
		if(m_ostream) *m_ostream << value;
		if (m_fstream.is_open())
		{
			m_fstream << value;
			m_fstream.flush();
		}

		return *this;
	}


	extern Logger g_logger;
}
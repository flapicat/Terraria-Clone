#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class Log
{
public:
	static void init();
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; };
private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

//LOG MACROS
#ifdef DEBUG
#define LOG_TRACE(...)     ::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)      ::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)      ::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)     ::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)     ::Log::GetLogger()->fatal(__VA_ARGS__)
#else
#define LOG_TRACE(...)     (void)0
#define LOG_INFO(...)      (void)0
#define LOG_WARN(...)      (void)0
#define LOG_ERROR(...)     (void)0
#define LOG_FATAL(...)     (void)0
#endif
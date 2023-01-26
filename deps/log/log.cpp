#include <log/log.h>

#include <cstdlib>
#include <cstdarg>
#include <string>

#include <android/log.h>

void Log::print(const char* tag, const char* format, ...) 
{
	std::string result;
	va_list args, args_copy;

	va_start(args, format);
	va_copy(args_copy, args);

	int len = vsnprintf(nullptr, 0, format, args);
	if (len < 0) {
		va_end(args_copy);
		va_end(args);
		return;
	}

	if (len > 0) {
		result.resize(len);
		vsnprintf(&result[0], len+1, format, args_copy);
	}

	va_end(args_copy);
	va_end(args);

	__android_log_write(ANDROID_LOG_INFO, tag, result.c_str());
}

void Log::print(const char* format, ...) 
{
	std::string result;
	va_list args, args_copy;

	va_start(args, format);
	va_copy(args_copy, args);

	int len = vsnprintf(nullptr, 0, format, args);
	if (len < 0) {
		va_end(args_copy);
		va_end(args);
		return;
	}

	if (len > 0) {
		result.resize(len);
		vsnprintf(&result[0], len+1, format, args_copy);
	}

	va_end(args_copy);
	va_end(args);

	__android_log_write(ANDROID_LOG_INFO, LOG_TAG, result.c_str());
}
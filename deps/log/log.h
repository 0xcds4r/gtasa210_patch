#pragma once

#define LOG_TAG "AXL"

namespace Log {
	void print(const char* tag, const char* format, ...);
	void print(const char* format, ...);
};
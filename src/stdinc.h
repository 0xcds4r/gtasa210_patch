#pragma once

#define __LIBRARY_NAME__ "libGTASAPatch.so"

#if defined(__aarch64__) 
	#define __ABI_NAME__ "arm64-v8a"
#else
	#define __ABI_NAME__ "armeabi-v7a"
#endif

// SDK INCLUDES
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <cmath>
#include <unistd.h>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <jni.h>
#include <android/log.h>

void Log(const char* tag, const char* format, ...);
uintptr_t getModuleAddress(const char* library);
void writeToMem(uintptr_t dest, uintptr_t src, size_t size);
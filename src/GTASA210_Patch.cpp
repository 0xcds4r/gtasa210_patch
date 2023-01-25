#include <stdinc.h>

uintptr_t g_ptrSAAddr = (uintptr_t)0;
std::vector<uintptr_t> vecFPSAddrs;

jint JNI_OnLoad(JavaVM * vm, void *reserved)
{
	Log("AXL", "Library: %s is loaded! Build time/date: %s %s | ABI: %s",
		__LIBRARY_NAME__,
		__TIME__,
		__DATE__,
		__ABI_NAME__
	);

	srand(time(NULL));

	g_ptrSAAddr = static_cast<uintptr_t>(getModuleAddress("libGTASA.so"));
	
	if(!g_ptrSAAddr) {
		Log("AXL", "Error! libGTASA.so not found!");
		return JNI_ERR;
	}

	vecFPSAddrs.clear();

	unsigned char game_fps = static_cast<unsigned char>(200);

	#if defined(__aarch64__)  // arm64-v8a
		vecFPSAddrs.push_back(0x70A38C);
		vecFPSAddrs.push_back(0x70A43C);
		vecFPSAddrs.push_back(0x70A458);
	#else 					  // armeabi-v7a
		vecFPSAddrs.push_back(0x4D4578);
		vecFPSAddrs.push_back(0x5E492E);
		vecFPSAddrs.push_back(0x5E49C8);
		vecFPSAddrs.push_back(0x5E49E0);
	#endif

	for(uintptr_t fps_address : vecFPSAddrs) {
		writeToMem(g_ptrSAAddr + fps_address, (uintptr_t)&game_fps, 1);
	}

	Log("AXL", "FPS Patch applied!");

	return JNI_VERSION_1_4;
}

void Log(const char* tag, const char* format, ...) 
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
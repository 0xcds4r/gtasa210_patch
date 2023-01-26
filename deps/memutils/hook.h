#pragma once

class Hook {
private:
	uintptr_t memlib_start, memlib_end, mmap_start, mmap_end;
public:
	Hook(uintptr_t start, uintptr_t size = 0x1000, uintptr_t pagesize = 0x2000);
	~Hook() {};
	void install(uintptr_t addr, uintptr_t func, uintptr_t* orig);
	bool IsSpaceLimitReached();
	void writeHookProc(uintptr_t addr, uintptr_t func);
};

typedef struct HookData
{
	const char* libraryName;
	uintptr_t pointer;
	uint8_t byteId;
	Hook* pHook;
};
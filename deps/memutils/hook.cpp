#include <memutils/memutils.h>

Hook::Hook(uintptr_t start, uintptr_t size, uintptr_t pagesize) {
	this->memlib_start = start;
	this->memlib_end = this->memlib_start + size;

	this->mmap_start = (uintptr_t)mmap(0, pagesize, PROT_WRITE | PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	mprotect((void*)(this->mmap_start & 0xFFFFF000), pagesize, PROT_READ | PROT_EXEC | PROT_WRITE);
	this->mmap_end = (this->mmap_start + pagesize);
}

void Hook::writeHookProc(uintptr_t addr, uintptr_t func)
{
    char code[16] = { '\0' };
    memcpy(code, HOOK_PROC, 16);
    *(uint32_t*)&code[12] = (func | 1);
    MemUtils::write(addr, (uintptr_t)code, 16);
}

bool Hook::IsSpaceLimitReached() {
	if(this->memlib_end < (this->memlib_start + 0x10) || this->mmap_end < (this->mmap_start + 0x20)) {
        return true;
    }

    return false;
}

void Hook::install(uintptr_t addr, uintptr_t func, uintptr_t *orig) 
{
    if(this->IsSpaceLimitReached()) {
    	return;
    }

    MemUtils::read(this->mmap_start, addr, 4);
    this->writeHookProc(this->mmap_start+4, addr+4);
    *orig = this->mmap_start+1;
    this->mmap_start += 32;

    MemUtils::jump(addr, this->memlib_start);
    this->writeHookProc(this->memlib_start, func);
    this->memlib_start += 16;
}
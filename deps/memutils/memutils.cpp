#include <memutils/memutils.h>

bool MemUtils::unprotect(uintptr_t ptr, size_t size) {
	return mprotect((void*)(ptr & 0xFFFFF000), PAGE_SIZE + size, PROT_READ | PROT_WRITE | PROT_EXEC);
}

uintptr_t MemUtils::getModuleAddress(const char* library)
{
	char filename[0xFF] = {0},
	buffer[2048] = {0};
	FILE *fp = 0;
	uintptr_t address = 0;

	sprintf( filename, "/proc/%d/maps", getpid() );

	fp = fopen( filename, "rt" );
	if(fp == 0) {
		goto done;
	}

	while(fgets(buffer, sizeof(buffer), fp))
	{
		if( strstr( buffer, library ) )
		{
			address = (uintptr_t)strtoul( buffer, 0, 16 );
			break;
		}
	}

	done:

	if(fp) {
		fclose(fp);
	}

	return address;
}

uintptr_t MemUtils::getModuleLen(const char* library)
{
    char filename[0xFF] = { 0 }, buffer[2048] = { 0 };
    FILE* fp = 0;
    uintptr_t address = 0;

    sprintf(filename, "/proc/%d/maps", getpid());
    fp = fopen(filename, "rt");
    if (fp == 0)
        goto done;
    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (strstr(buffer, library))
        {
            address = (uintptr_t)strtoul(buffer, 0, 16);
            address = (uintptr_t)strtoul(&buffer[9], 0, 16) - address;
            break;
        }
    }

done:
    if (fp)
        fclose(fp);
    return address;
}

void MemUtils::cacheClear(uintptr_t dest, size_t size) {
	__builtin___clear_cache((char*)dest, (char*)(dest+size));
}

void MemUtils::write(uintptr_t dest, uintptr_t src, size_t size)
{
	MemUtils::unprotect(dest);
	memcpy((void*)dest, (void*)src, size);
	MemUtils::cacheClear(dest, size);
}

void MemUtils::read(uintptr_t dest, uintptr_t src, size_t size)
{
    MemUtils::unprotect(src);
    memcpy((void*)dest, (void*)src, size);
}

void MemUtils::makeNOP(uintptr_t addr, size_t size)
{
	for(uintptr_t ptr = addr; ptr != (addr+(size*2)); ptr += 2) {
        MemUtils::write(ptr, (uintptr_t)"\x00\xBF", 2);
    }
}

uintptr_t MemUtils::getSymbolAddress(uintptr_t LibAddr, const char* name)
{
    Dl_info info;
    if (dladdr((void*)LibAddr, &info) == 0)
        return 0;
    return (uintptr_t)dlsym(info.dli_fbase, name);
}

void MemUtils::jump(uintptr_t func, uintptr_t addr)
{
	uint32_t code = ((addr-func-4) >> 12) & 0x7FF | 0xF000 | ((((addr-func-4) >> 1) & 0x7FF | 0xB800) << 16);
    MemUtils::write(func, (uintptr_t)&code, 4);
}

void MemUtils::bxlr(uintptr_t addr) {
	MemUtils::write(addr, (uintptr_t)"\x70\x47", 2);
}

void MemUtils::makeRET(uintptr_t address, bool onlyTwoBytes) {
	if(onlyTwoBytes) {
		MemUtils::write(address, (uintptr_t)"\xF7\x46", 2);
	} else {
		MemUtils::write(address, (uintptr_t)"\x00\x20\xF7\x46", 4);
	}
}
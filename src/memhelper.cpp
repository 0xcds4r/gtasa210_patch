#include <stdinc.h>
#include <sys/mman.h>

#define UNPROT(ptr) \
	mprotect((void*)(ptr & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);

uintptr_t getModuleAddress(const char* library)
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

void writeToMem(uintptr_t dest, uintptr_t src, size_t size)
{
	UNPROT(dest);
	memcpy((void*)dest, (void*)src, size);
	__builtin___clear_cache((char*)dest, (char*)(dest+size));
}
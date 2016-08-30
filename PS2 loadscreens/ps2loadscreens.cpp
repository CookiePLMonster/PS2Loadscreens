#include <Windows.h>
#include <cstdint>
#include "MemoryMgr.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER( hModule );
	UNREFERENCED_PARAMETER( lpReserved );
	if( reason == DLL_PROCESS_ATTACH )
	{
		using namespace Memory;

		// Unprotects the entire section at once, and restores it when going out of scope
		ScopedUnprotect::Section Protect( (HINSTANCE)0x400000, ".text" );

		if (*(DWORD*)0x5C1E75 == 0xB85548EC)
		{
			// III 1.0
			Patch<uint32_t>( 0x48D774, 0x602474FF );	// push dword ptr [espx60h]
			Patch<uint16_t>( 0x48D774+4, 0x21EB );		// jmp 48D79Bh
		}
		else if (*(DWORD*)0x5C2135 == 0xB85548EC)
		{
			// III 1.1
			Patch<uint32_t>( 0x48D874, 0x602474FF );	// push dword ptr [espx60h]
			Patch<uint16_t>( 0x48D874+4, 0x21EB );		// jmp 48D89Bh
		}
		else if (*(DWORD*)0x5C6FD5 == 0xB85548EC)
		{
			// III Steam
			Patch<uint32_t>( 0x48D804, 0x602474FF );	// push dword ptr [espx60h]
			Patch<uint16_t>( 0x48D804+4, 0x21EB );		// jmp 48D82Bh
		}

		else if(*(DWORD*)0x667BF5 == 0xB85548EC)
		{
			// VC 1.0
			Nop( 0x4A69D4, 1 );				// nop
			Patch<uint32_t>( 0x4A69D4+1, 0x782474FF );	// push dword ptr [espx78h]
		}
		else if(*(DWORD*)0x667C45 == 0xB85548EC)
		{
			// VC 1.1
			Nop( 0x4A69F4, 1 );				// nop
			Patch<uint32_t>( 0x4A69F4+1, 0x782474FF );	// push dword ptr [espx78h]
		}
		else if (*(DWORD*)0x666BA5 == 0xB85548EC)
		{
			// VC Steam
			Nop( 0x4A68A4, 1 );				// nop
			Patch<uint32_t>( 0x4A68A4+1, 0x782474FF );	// push dword ptr [espx78h]
		}
		else return FALSE;
	}
	return TRUE;
}

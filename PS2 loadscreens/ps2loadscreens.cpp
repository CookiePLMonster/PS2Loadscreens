#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>

#include "MemoryMgr.h"
#include "Patterns.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER( hModule );
	UNREFERENCED_PARAMETER( lpReserved );
	if( reason == DLL_PROCESS_ATTACH )
	{
		using namespace Memory;
		using namespace hook;

		// Unprotects the entire section at once, and restores it when going out of scope
		ScopedUnprotect::Section Protect( (HINSTANCE)0x400000, ".text" );

		auto loadscIII = pattern( "53 83 EC 50 80 3D" ); // 0x48D770
		auto loadscVC = pattern( "53 83 EC 68 68" ); // 0x4A69D0

		if ( !loadscIII.count_hint(1).empty() )
		{
			auto match = loadscIII.get_one();
			Patch<uint32_t>( match.get<int>( 4 ), 0x602474FF );	// push dword ptr [espx60h]
			Patch<uint16_t>( match.get<int>( 4 + 4 ), 0x21EB );	// jmp 48D79Bh
		}
		else if ( !loadscVC.count_hint(1).empty() )
		{
			auto match = loadscVC.get_one();
			Nop( match.get<int>( 4 ), 1 );				// nop
			Patch<uint32_t>( match.get<int>( 4 + 1 ), 0x782474FF );	// push dword ptr [espx78h]
		}
		else return FALSE;
	}
	return TRUE;
}

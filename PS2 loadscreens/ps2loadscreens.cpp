#include <windows.h>
#include <math.h>
#include <time.h>

#define patch(a, v, s) _patch((void*)(a), (DWORD)(v), (s))
#define charptr(a, v) _charptr((void*)(a), (const char*)(v))

const BYTE iIIILoadscSwitch[] = { 25, 22, 4, 13, 1, 21, 14, 16, 10, 24, 12, 5, 9, 11, 18, 3, 2, 1, 19, 23, 7, 17, 15, 16, 6, 8, 22, 20 };
const BYTE iVCLoadscSwitch[] = { 1, 2, 3, 13, 4, 5, 11, 6, 9, 10, 8, 12, 7, 3 };

void _patch(void* pAddress, DWORD data, DWORD iSize)
{
	DWORD dwProtect[2];
	VirtualProtect(pAddress, iSize, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
	switch(iSize)
	{
		case 1: *(BYTE*)pAddress = (BYTE)data;
			break;
		case 2: *(WORD*)pAddress = (WORD)data;
			break;
		case 4: *(DWORD*)pAddress = (DWORD)data;
			break;
	}
	VirtualProtect(pAddress, iSize, dwProtect[0], &dwProtect[1]);
}

void _charptr(void* pAddress, const char* pChar)
{
	DWORD dwProtect[2];
    VirtualProtect(pAddress, 4, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
    *(DWORD*)pAddress = (DWORD)pChar;
    VirtualProtect(pAddress, 4, dwProtect[0], &dwProtect[1]);
}

__forceinline void PatchPtrs_III_10()
{
	patch(0x48D6AA, 0xEB, 1);
	patch(0x48BEFC, 0x8DC86890, 4);	// nop
	patch(0x48BF00, 0x62, 2);		// push aLoadscName
	patch(0x48E7DF, 0xE8, 1);
	patch(0x48E7E0, 0x48D6A0 - 0x48E7E4, 4);  // call GetRandomSplashScreen
	patch(0x48E7E4, 0x50, 1);				  // push eax
	patch(0x48D790, 0x628DC8, 4);
	patch(0x48D797, 0x628DC8, 4);
	patch(0x48D709, &iIIILoadscSwitch, 4);
	patch(0x48D719, 7, 1);
	patch(0x582E6D, 0x48E7DF - 0x582E71, 4);   // call 48E7DF

	strncpy((char*)0x628DC8, "loadsc0", 8);
	*(DWORD*)0x628E48 = rand() % 8;
}

__forceinline void PatchPtrs_III_11()
{
	patch(0x48D7AA, 0xEB, 1);
	patch(0x48BFEC, 0x8DC86890, 4);	// nop
	patch(0x48BFF0, 0x62, 2);		// push aLoadscName
	patch(0x48E89F, 0xE8, 1);
	patch(0x48E8A0, 0x48D7A0 - 0x48E8A4, 4);  // call GetRandomSplashScreen
	patch(0x48E8A4, 0x50, 1);				  // push eax
	patch(0x48D890, 0x628DC8, 4);
	patch(0x48D897, 0x628DC8, 4);
	patch(0x48D809, &iIIILoadscSwitch, 4);
	patch(0x48D819, 7, 1);
	patch(0x5831AD, 0x48E89F - 0x5831B1, 4);  // call 48E89F

	strncpy((char*)0x628DC8, "loadsc0", 8);
	*(DWORD*)0x628E48 = rand() % 8;
}

__forceinline void PatchPtrs_III_Steam()
{
	patch(0x48D73A, 0xEB, 1);
	patch(0x48BF7C, 0x8DC86890, 4);	// nop
	patch(0x48BF80, 0x63, 2);		// push aLoadscName
	patch(0x48E82F, 0xE8, 1);
	patch(0x48E830, 0x48D730 - 0x48E834, 4);  // call GetRandomSplashScreen
	patch(0x48E834, 0x50, 1);				  // push eax
	patch(0x48D820, 0x638DC8, 4);
	patch(0x48D827, 0x638DC8, 4);
	patch(0x48D799, &iIIILoadscSwitch, 4);
	patch(0x48D7A9, 7, 1);
	patch(0x58309D, 0x48E82F - 0x5830A1, 4);   // call 48E82F

	strncpy((char*)0x638DC8, "loadsc0", 8);
	*(DWORD*)0x628E48 = rand() % 8;
}


__forceinline void PatchPtrs_VC_10()
{
	patch(0x4A6DAA, 0xEB, 1);
	patch(0x4A4B4E, 0x3A346890, 4);	// nop
	patch(0x4A4B52, 0x70, 2);		// push aLoadscName
	patch(0x4A5C3F, 0xE8, 1);
	patch(0x4A5C40, 0x4A6DA0 - 0x4A5C44, 4); // call GetRandomSplashScreen
	patch(0x4A5C44, 0x50, 1);	// push eax
	patch(0x4A69D5, 0x703A34, 4);
	patch(0x4A6E09, &iVCLoadscSwitch, 4);
	patch(0x4A6E19, 7, 1);
	patch(0x600412, 0x4A5C3F - 0x600416, 4);	// call 4A5C3F

	strncpy((char*)0x703A34, "loadsc0", 8);
	*(DWORD*)0x703AB4 = rand() % 4;
}

__forceinline void PatchPtrs_VC_11()
{	
	patch(0x4A6DCA, 0xEB, 1);
	patch(0x4A4B6E, 0x3A346890, 4);	// nop
	patch(0x4A4B72, 0x70, 2);		// push aLoadscName
	patch(0x4A5C5F, 0xE8, 1);
	patch(0x4A5C60, 0x4A6DC0 - 0x4A5C64, 4); // call GetRandomSplashScreen
	patch(0x4A5C64, 0x50, 1);	// push eax
	patch(0x4A69F5, 0x703A34, 4);
	patch(0x4A6E29, &iVCLoadscSwitch, 4);
	patch(0x4A6E39, 7, 1);
	patch(0x600432, 0x4A5C5F - 0x600436, 4);	// call 4A5C5F	

	strncpy((char*)0x703A34, "loadsc0", 8);
	*(DWORD*)0x703AB4 = rand() % 4;
}

__forceinline void PatchPtrs_VC_Steam()
{
	patch(0x4A6C7A, 0xEB, 1);
	patch(0x4A4A0E, 0x2A346890, 4);	// nop
	patch(0x4A4A12, 0x70, 2);		// push aLoadscName
	patch(0x4A5B0F, 0xE8, 1);
	patch(0x4A5B10, 0x4A6C70 - 0x4A5B14, 4); // call GetRandomSplashScreen
	patch(0x4A5B14, 0x50, 1);	// push eax
	patch(0x4A68A5, 0x702A34, 4);
	patch(0x4A6CD9, &iVCLoadscSwitch, 4);
	patch(0x4A6CE9, 7, 1);
	patch(0x600072, 0x4A5B0F - 0x600076, 4);	// call 4A5B0F

	strncpy((char*)0x702A34, "loadsc0", 8);
	*(DWORD*)0x702AB4 = rand() % 4;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		srand ( time(NULL) );
		if (*(DWORD*)0x5C1E70 == 0x53E58955) PatchPtrs_III_10();
		else if (*(DWORD*)0x5C2130 == 0x53E58955) PatchPtrs_III_11();
			else if (*(DWORD*)0x5C6FD0 == 0x53E58955) PatchPtrs_III_Steam();
				else if(*(DWORD*)0x667BF0 == 0x53E58955) PatchPtrs_VC_10();
					else if(*(DWORD*)0x667C40 == 0x53E58955) PatchPtrs_VC_11();
						else if (*(DWORD*)0x666BA0 == 0x53E58955) PatchPtrs_VC_Steam();
							else MessageBox(NULL, "Unknown game version.\nPS2 Loadscreens plugin does not support your Executable version.", "PS2 Loadscreens", MB_ICONWARNING | MB_OK );
	}
	return TRUE;
}

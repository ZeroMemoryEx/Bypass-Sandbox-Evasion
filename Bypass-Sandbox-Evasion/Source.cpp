#include <windows.h>
#include <tlhelp32.h>

/*

 | 3648:C701 C97D2704                                                       |
*/
unsigned long long lv2[] = { 0x36, 0x48, 0xC7, 0x01, 0x40, 0xB8, 0x93, 0x41, 0xC3 ,
							0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
							, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};


DWORD GetPID(const char* pn)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pE;
		pE.dwSize = sizeof(pE);

		if (Process32First(hSnap, &pE))
		{
			if (!pE.th32ProcessID)
				Process32Next(hSnap, &pE);
			do
			{
				if (!_stricmp(pE.szExeFile, pn))
				{
					procId = pE.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &pE));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

int wmain() {

	int i = 0;
	DWORD tpid = 0;
	HANDLE hw = OpenProcess(PROCESS_ALL_ACCESS, 0, tpid = GetPID("ProcessHacker.exe"));
	if (!hw)
		return -2;

	while (i < (sizeof(lv2) / 8))
	{
		if(!WriteProcessMemory(hw, (LPVOID)(0x00007FFB942C1AE0 + i), &lv2[i++], 1, 0))
			return (-1);
	}
	system("pause");
	return 0;
}

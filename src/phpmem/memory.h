#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include <winnt.h>
#include <psapi.h>
#include <stdlib.h>

class memory
{
public:
	memory() {};
	~memory() {};

	static memory* GetInstance() {
		static memory* instance;
		if (!instance)
			instance = new memory;
		return instance;
	};

	void SetHandle(HANDLE handle) {
		m_hProcHandle = handle;
	};

	bool OpenProcessHandle(std::string processName) {
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &entry) == TRUE)
		{
			while (Process32Next(snapshot, &entry) == TRUE)
			{
				if (!strcmp(entry.szExeFile, processName.c_str()))
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
					if (hProcess == INVALID_HANDLE_VALUE)
						return false;

					m_szProcessName = processName;
					m_hProcHandle = hProcess;
					return true;
				}
			}
		}

		CloseHandle(snapshot);
	}

	DWORD GetModuleBase(std::string module) {
		HANDLE moduleHandle = NULL;

		HANDLE hDebugHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, GetProcessId(m_hProcHandle));
		MODULEENTRY32 tModuleEntry32;
		tModuleEntry32.dwSize = sizeof(tModuleEntry32);

		do {
			if (!strcmp(tModuleEntry32.szModule, module.c_str())) {
				return reinterpret_cast<DWORD>(tModuleEntry32.modBaseAddr);
			}
		} while (Module32Next(hDebugHandle, &tModuleEntry32));

		return -1;
	}

	template<typename T> T Read(DWORD address) {
		T buffer;
		SIZE_T bytesRead = NULL;
		ReadProcessMemory(m_hProcHandle, (PVOID)address, (PVOID)&buffer, sizeof(buffer), &bytesRead);
		return buffer;
	};
	template<typename T> int Write(DWORD address, PVOID value) {
		SIZE_T bytesWritten = NULL;
		WriteProcessMemory(m_hProcHandle, (PVOID)address, value, sizeof(T), &bytesWritten);
		return bytesWritten;
	};
	std::string ReadString(DWORD address) {
		char buffer[1024];
		SIZE_T bytesRead = NULL;
		ReadProcessMemory(m_hProcHandle, (PVOID)address, (PVOID)&buffer, sizeof(buffer), &bytesRead);
		return std::string(buffer);
	};

	std::string GetProcessName() {
		return m_szProcessName;
	};

	HANDLE GetProcessHandle() {
		return m_hProcHandle;
	};
private:
	std::string m_szProcessName;
	HANDLE m_hProcHandle;
};
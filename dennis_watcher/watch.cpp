// Dennis Enhanced Edition - Copyright Aarik 2024 - All rights reserved \\

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <wchar.h>

LONG getRegistryString(LPCWSTR key, LPCWSTR subKey, WCHAR* buf, DWORD bufLength) {
	HKEY hKey;
	LONG regReturn = RegOpenKeyExW(HKEY_LOCAL_MACHINE, key, 0, KEY_READ | KEY_WOW64_64KEY, &hKey);
	if (regReturn != ERROR_SUCCESS) {
		DebugBreak();
		return regReturn;
	}

	regReturn = RegQueryValueExW(hKey, subKey, 0, NULL, (LPBYTE)buf, &bufLength);
	if (regReturn != ERROR_SUCCESS) {
		DebugBreak();
		return regReturn;
	}
	return regReturn;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	WCHAR dennisExePath[512];
	WCHAR dennisExePathDir[512];

	LONG status;

	status = getRegistryString(L"SOFTWARE\\Dennis Enhanced Edition", L"", dennisExePathDir, sizeof(dennisExePathDir));

	if (status != ERROR_SUCCESS || wcslen(dennisExePathDir) < 0) {
		MessageBox(NULL, "Unable to find Dennis directory (registry key missing). Please reinstall Dennis.", "Dennis Watcher Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	status = getRegistryString(L"SOFTWARE\\Dennis Enhanced Edition", L"DennisExe", dennisExePath, sizeof(dennisExePath));

	if (status != ERROR_SUCCESS || wcslen(dennisExePath) < 0) {
		MessageBox(NULL, "Unable to find Dennis executable (registry key missing). Please reinstall Dennis.", "Dennis Watcher Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	// Check if the exe actually exists
	FILE* file = _wfopen(dennisExePath, L"r");
	if (!file) {
		MessageBox(NULL, "Unable to open Dennis Executable (exe missing). Please reinstall Dennis.", "Dennis Watcher Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	fclose(file);

	STARTUPINFOW si;
	PROCESS_INFORMATION pi;

	bool isAlive = false;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	DWORD processCode;

	while (true) {

		// Prevents us from using too much cpu
		Sleep(100);

		if (!isAlive) {
			CreateProcessW(
				dennisExePath,
				NULL, 
				NULL, 
				NULL, 
				FALSE, 
				0, 
				NULL,
				dennisExePathDir, // Set the startup path so dectalk can find the dictionary
				&si, // Startup info
				&pi // Process info
			);
			GetExitCodeProcess(pi.hProcess, &processCode);
			if (processCode == STILL_ACTIVE)
				isAlive = true;
			else
				continue;
		}

		if (isAlive) {
			GetExitCodeProcess(pi.hProcess, &processCode);
			if (processCode != STILL_ACTIVE)
				isAlive = false;
		}
	}

	return 0;

}
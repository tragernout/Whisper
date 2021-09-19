#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <ws2tcpip.h>
#include <VersionHelpers.h>
#include <Lmcons.h>
#include <fstream>

#pragma comment(lib, "Ws2_32.lib")

static void RunShell();
INT versionGet();
LPCWSTR userGet();
LPCWSTR diskGet();
void createMetaFile(LPCWSTR username);
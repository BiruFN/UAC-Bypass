// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "struct.h"
#include "util.h"
#include "hooks.h"

static VOID Main()
{
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);

    std::cout << "[=] Made by BiruFN" << std::endl;

    auto GetObjectFullNameAddress = Util::FindPattern(
        "\x40\x53\x48\x83\xEC\x20\x48\x8B\xC2\x48\x8B\xD9\x48\x85\xD2\x75\x43",
		"xxxxxxxxxxxxxxxxx"
    );
    GetObjectFullName = decltype(GetObjectFullName)(GetObjectFullNameAddress);

    auto ProcessEventAddress = Util::FindPattern(
        "\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8D\x6C\x24\x00\x48\x89\x9D\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC5\x48\x89\x85\x00\x00\x00\x00\x8B\x41\x0C\x45\x33\xF6\x3B\x05\x00\x00\x00\x00\x4D\x8B\xF8\x48\x8B\xF2\x4C\x8B\xE1\x41\xB8\x00\x00\x00\x00\x7D\x2A",
		"xxxxxxxxxxxxxxx????xxxx?xxx????xxx????xxxxxx????xxxxxxxx????xxxxxxxxxxx????xx"
    );
    ProcessEvent = decltype(ProcessEvent)(ProcessEventAddress);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(reinterpret_cast<void**>(&ProcessEvent), ProcessEventHook);
    DetourTransactionCommit();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Main();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


#pragma once

class Util
{
private:
	static BOOL MaskCompare(PVOID buffer, LPCSTR pattern, LPCSTR mask)
	{
		for (auto value = reinterpret_cast<PBYTE>(buffer); *mask; ++pattern, ++mask, ++value)
		{
			if (*mask == 'x' && *reinterpret_cast<LPCBYTE>(pattern) != *value)
				return false;
		}

		return true;
	}

public:
	static PVOID FindPattern(LPCSTR pattern, LPCSTR mask)
	{
		MODULEINFO info = { 0 };

		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));

		info.SizeOfImage -= static_cast<DWORD>(strlen(mask));

		for (auto index = 0UL; index < info.SizeOfImage; ++index)
		{
			auto address = reinterpret_cast<PBYTE>(info.lpBaseOfDll) + index;

			if (MaskCompare(address, pattern, mask))
				return address;
		}

		return nullptr;
	}
};

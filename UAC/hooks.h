#pragma once

void* (__fastcall* GetObjectFullName)(FString*, void*);

void* (*ProcessEvent)(void* object, void* function, void* params);

void* ProcessEventHook(void* vObject, void* vFunction, void* vParams)
{
	FString* fFunction = new FString();
	GetObjectFullName(fFunction, vFunction);

	std::string Function = fFunction->ToString();

	if (Function == "/Script/UACBase.UACNetworkComponent:SendClientHello")
	{
		return nullptr;
	}
	if (Function == "/Script/UACBase.UACNetworkComponent:SendPacketToServer")
	{
		return nullptr;
	}
	if (Function == "/Script/UACBase.UACNetworkComponent:SendPacketToClient")
	{
		return nullptr;
	}

	return ProcessEvent(vObject, vFunction, vParams);
}
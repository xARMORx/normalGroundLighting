#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <memory>
#include "memwrapper/memwrapper.h"

struct CVector { float x, y, z; };
struct RwTexture {};

using CHud__DrawRadarPrototype = void(__cdecl*)();
std::unique_ptr<memwrapper::memhook<CHud__DrawRadarPrototype>> CHud_DrawRadarHook;

using CShadows__StoreStaticShadowPrototype = bool(__cdecl*)(int, char, RwTexture*, CVector*, float, float, float, float, int, unsigned char, unsigned char, unsigned char, float, float, float, char, float);
std::unique_ptr<memwrapper::memhook<CShadows__StoreStaticShadowPrototype>> CShadows__StoreStaticShadowHook;

RwTexture* rwReadTexture(const char* name, int maskName) {
	return reinterpret_cast<RwTexture* (__cdecl*)(const char*, int)>(0x7F3AC0)(name, maskName);
}

int CTxdStore__FindTxdSlot(const char* name) {
	return reinterpret_cast<int(__cdecl*)(const char*)>(0x731850)(name);
}

void CTxdStore__SetCurrentTxd(int ptr) {
	reinterpret_cast<void(__cdecl*)(int)>(0x7319C0)(ptr);
}

class AsiPlugin{
public:
	explicit AsiPlugin();
	virtual ~AsiPlugin();
} AsiPlugin;

#endif // !_MAIN_H_
#include "main.h"

RwTexture* my_texture;

bool __cdecl CShadows__StoreStaticShadow(int id, char type, RwTexture* texture, CVector* center, float upX, float upY, float rightX, float rightY, int intensity, unsigned char r, unsigned char g, unsigned char b, float zDistance, float scale, float drawDistance, char bTemporary, float upDistance) {
	return CShadows__StoreStaticShadowHook->call<int, char, RwTexture*, CVector*, float, float, float, float, int, unsigned char, unsigned char, unsigned char, float, float, float, char, float>(id, type, my_texture, center, upX, upY, rightX, rightY, intensity, r, g, b, zDistance, scale, drawDistance, bTemporary, upDistance);
}

void __cdecl CHud__DrawRadar() {
	static bool init;
	if (!init) {
		int ptr = CTxdStore__FindTxdSlot("particle");
		CTxdStore__SetCurrentTxd(ptr);
		my_texture = rwReadTexture("newLight", 0);
		if (my_texture != nullptr) {
			CShadows__StoreStaticShadowHook = std::make_unique<memwrapper::memhook<CShadows__StoreStaticShadowPrototype>>(0x455F23, &CShadows__StoreStaticShadow);
			CShadows__StoreStaticShadowHook->install();
		}
		else
			MessageBoxA(**reinterpret_cast<HWND**>(0xC17054), "Ошибка!\nПлагин не смог найти текстуру newLight в particle.txd!\nПлагин не сможет работать без данной текстуры", "normalGroundLight", MB_OK | MB_ICONERROR);
		init = true;
	}

	CHud_DrawRadarHook->call();
}

AsiPlugin::AsiPlugin() {
	CHud_DrawRadarHook = std::make_unique<memwrapper::memhook<CHud__DrawRadarPrototype>>(0x58A330, &CHud__DrawRadar);
	CHud_DrawRadarHook->install();
}

AsiPlugin::~AsiPlugin() {
	CHud_DrawRadarHook->remove();
	CShadows__StoreStaticShadowHook->remove();
}
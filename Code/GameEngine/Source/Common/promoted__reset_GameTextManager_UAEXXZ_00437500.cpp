// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?reset@GameTextManager@@UAEXXZ: Code/GameEngine/Source/GameClient/GameText.cpp
// Grok promote from masm_dumps — retail 0x00437500 size 85
// was: Code/masm_dumps/GameTextManager_reset.asm

class GameTextManager { public: virtual void reset(void); };

extern "C" void __stdcall gameTextPrepare(void *, int, void *, int);
extern "C" void __cdecl gameTextRelease(void *);

// ?reset@GameTextManager@@UAEXXZ
void GameTextManager::reset(void)
{
	void *first = *(void **)((unsigned char *)this + 0x7828);
	if (first) {
		void *array = (unsigned char *)first - 4;
		gameTextPrepare(first, 8, *(void **)array, 0x0041510E);
		gameTextRelease(array);
		*(void **)((unsigned char *)this + 0x7828) = 0;
	}
	void *second = *(void **)((unsigned char *)this + 0x782C);
	if (second) {
		gameTextRelease(second);
		*(void **)((unsigned char *)this + 0x782C) = 0;
	}
}


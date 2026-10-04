// Open-BFME5 conversions.

extern "C" char *strcpy(char *d, const char *s);
#pragma intrinsic(strcpy)

// Retail IAT slot 0x01359344 is MSVCR71 _strlwr (imports.csv); the old
// function-pointer spelling referenced the same address under an undefined
// name. Spelled as the import so the indirect call resolves.
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *s);

// Defined by game/Libraries/Source/assetmanager/Render_Obj_Exists.cpp at
// 0x009EBB80 (?Render_Obj_Exists@@YA_NPBD@Z); same address the old alias
// referenced, so the direct call bytes are unchanged.
bool Render_Obj_Exists(const char *s);

char bfmeHasVNV(const char *s)
{
	char n1[512];

	if (s == 0)
		return 0;

	strcpy(n1, "a*");
	strcpy(n1 + 2, s);
	_strlwr(n1);
	return Render_Obj_Exists(n1);
}

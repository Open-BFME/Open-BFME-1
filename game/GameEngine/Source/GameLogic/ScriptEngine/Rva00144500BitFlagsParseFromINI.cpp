// ?rva00144500@@YAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);	// retail 0x008509C0
};

// The per-instantiation routine whose `this` is the BitFlags being filled in,
// reached through the ILT at 0x0004A7AF -> retail 0x00141320 (11-name list).
class Rva00141320BitFlagsParser
{
public:
	Bool parseToken(const char *token, Bool *foundNormal, Bool *foundAddOrSub);
};

// BitFlags<11>::parseFromINI-shaped driver: token loop hoisted the same way
// BitFlagsParseFromINI.cpp's <116>/<45> instantiations are, but the caller for
// this width has no template instance in the current tree yet so it is left
// as a plain address-derived function rather than a fabricated template name.
void __cdecl rva00144500(INI *ini, void *instance, void *store, const void *userData)
{
	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for (const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull())
	{
		if (!((Rva00141320BitFlagsParser *)store)->parseToken(token, &foundNormal, &foundAddOrSub))
			break;
	}
}

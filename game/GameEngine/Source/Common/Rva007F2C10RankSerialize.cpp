// cl: /DNDEBUG /MD /GS
//
// Open-BFME5: retail 0x007F2C10 (249 B). GameSpy rank-period attribute
// serializer (strings TXN, key, ownerType, minRank, maxRank, periodId,
// periodPast, keys.%d, keys.[]). Sibling of the 0x007F3980 serializer
// (attributes.%d.key/value); this one tags a single int per entry
// instead of a key/value pair. Identity of the owning message class is
// not recovered; every callee is address-derived. /GS is proven by the
// ___security_cookie load/check pair.

class Rva007E8AC0
{
public:
	void run();
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC(void *name, void *value);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *name, void *value);
};

struct Rva007F2C10Msg
{
	unsigned char m_pad00[0x1c];
	int m_tag;
};

extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);
extern void *g_bfme0130A6A8;

void __stdcall rva007F2C10Serialize(Rva007F2C10Msg *msg, int key, int ownerType,
	int minRank, int maxRank, int periodId, int periodPast, int *keys, int count)
{
	void *global = g_bfme0130A6A8;
	((Rva007E8AC0 *)msg)->run();
	msg->m_tag = 0x72616e6b;
	((BfmeThingCIC *)msg)->bfmeGoCIC((void *)"TXN", global);
	((BfmeThingCIC *)msg)->bfmeGoCIC((void *)"key", (void *)key);
	((BfmeThingCIB *)msg)->bfmeGoCIB((void *)"ownerType", (void *)ownerType);
	((BfmeThingCIB *)msg)->bfmeGoCIB((void *)"minRank", (void *)minRank);
	((BfmeThingCIB *)msg)->bfmeGoCIB((void *)"maxRank", (void *)maxRank);
	((BfmeThingCIB *)msg)->bfmeGoCIB((void *)"periodId", (void *)periodId);
	((BfmeThingCIB *)msg)->bfmeGoCIB((void *)"periodPast", (void *)periodPast);

	for (int i = 0; i < count; ++i)
	{
		char buffer[32];
		sprintf(buffer, "keys.%d", i);
		((BfmeThingCIC *)msg)->bfmeGoCIC(buffer, (void *)keys[i]);
	}

	((BfmeThingCIB *)msg)->bfmeGoCIB((void *)"keys.[]", (void *)count);
}

// @?rva007F2C10Serialize@@YGXPAURva007F2C10Msg@@HHHHHHPAHH@Z 0x007F2C10

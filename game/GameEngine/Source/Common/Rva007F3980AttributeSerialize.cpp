// cl: /DNDEBUG /MD /GS
//
// Open-BFME5: retail 0x007F3980 (248 B). GameSpy/club-service attribute
// serializer (strings TXN, clubId, userId, attributes.[], attributes.%d.key,
// attributes.%d.value at 0x011298ac/0x112b178/0x112b170/0x112a90c/
// 0x112a640/0x112a62c). Identity of the owning message class is not
// recovered; every callee is address-derived. /GS is proven by the
// ___security_cookie load/check pair.

class Rva007E8AC0 { public: void run(); };
class BfmeThingCIC { public: void bfmeGoCIC(void*, void*); };
class BfmeThingCIB { public: void bfmeGoCIB(void*, void*); };
class Rva007E8810Message { public: void addInt64(const char*, __int64); };

class Rva007F3980Msg
{
public:

	unsigned char m_pad00[0x1c];
	int m_tag;
};

struct Rva007F3980Pair
{
	int key;
	int value;
};

extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);
extern void *g_bfme0130A714;

void __stdcall rva007F3980Serialize(Rva007F3980Msg *msg, __int64 clubId,
	__int64 userId, Rva007F3980Pair *pairs, int count)
{
	void *txn = g_bfme0130A714;
	((Rva007E8AC0*)msg)->run();
	msg->m_tag = 0x636c7562;
	((BfmeThingCIC*)msg)->bfmeGoCIC((void *)"TXN", txn);
	((Rva007E8810Message*)msg)->addInt64("clubId", clubId);
	((Rva007E8810Message*)msg)->addInt64("userId", userId);
	((BfmeThingCIB*)msg)->bfmeGoCIB((void *)"attributes.[]", (void *)(int)count);

	for (unsigned i = 0; i < (unsigned)count; ++i)
	{
		char buffer[64] = "";
		sprintf(buffer, "attributes.%d.key", i);
		((BfmeThingCIC*)msg)->bfmeGoCIC(buffer, (void *)(int)pairs[i].key);

		sprintf(buffer, "attributes.%d.value", i);
		((BfmeThingCIC*)msg)->bfmeGoCIC(buffer, (void *)(int)pairs[i].value);
	}
}

// @?rva007F3980Serialize@@YGXPAVRva007F3980Msg@@_J1PAURva007F3980Pair@@H@Z 0x007F3980

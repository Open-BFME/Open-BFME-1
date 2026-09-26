// ?rva007F3980Serialize@@YGXPAVRva007F3980Msg@@_J1PAURva007F3980Pair@@H@Z
// partial score=0.4 date=2026-09-21
// cl: /DNDEBUG /MD /GS
//
// Open-BFME5: retail 0x007F3980 (248 B). GameSpy/club-service attribute
// serializer (strings TXN, clubId, userId, attributes.[], attributes.%d.key,
// attributes.%d.value at 0x011298ac/0x112b178/0x112b170/0x112a90c/
// 0x112a640/0x112a62c). Identity of the owning message class is not
// recovered; every callee is address-derived. /GS is proven by the
// ___security_cookie load/check pair.

class Rva007F3980Msg
{
public:
	void run();
	void bfmeGoCIC(void *name, void *value);
	void bfmeGoCIB(void *name, void *value);
	void addInt64(const char *name, __int64 value);

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
	msg->run();
	msg->bfmeGoCIC((void *)"TXN", g_bfme0130A714);
	msg->m_tag = 0x636c7562;
	msg->addInt64("clubId", clubId);
	msg->addInt64("userId", userId);
	msg->bfmeGoCIB((void *)"attributes.[]", (void *)(int)count);

	for (int i = 0; i < count; ++i)
	{
		char buffer[64];
		sprintf(buffer, "attributes.%d.key", i);
		msg->bfmeGoCIC(buffer, (void *)(int)pairs[i].key);

		sprintf(buffer, "attributes.%d.value", i);
		msg->bfmeGoCIC(buffer, (void *)(int)pairs[i].value);
	}
}

// @?rva007F3980Serialize@@YGXPAVRva007F3980Msg@@_J1PAURva007F3980Pair@@H@Z 0x007F3980

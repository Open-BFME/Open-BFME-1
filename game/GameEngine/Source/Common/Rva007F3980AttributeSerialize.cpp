// cl: /DNDEBUG /MD /GS
//
// Open-BFME5: retail 0x007F3980 (248 B). GameSpy/club-service attribute
// serializer (strings TXN, clubId, userId, attributes.[], attributes.%d.key,
// attributes.%d.value at 0x011298ac/0x112b178/0x112b170/0x112a90c/
// 0x112a640/0x112a62c). Identity of the owning message class is not
// recovered; every callee is address-derived. /GS is proven by the
// ___security_cookie load/check pair.

class Rva007E8AC0 { public: void run(); };
class BfmeC994 { public: void addString( const char *key, const char *value ); };
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
// Layout view of the static at 0x0130A710; +4 holds its second constructor argument.
class Rva007F01F0
{
public:
	int m_00;
	int m_04;
	int m_08;
};
extern Rva007F01F0 bfmeRva0130A710Slot;

void __stdcall rva007F3980Serialize(Rva007F3980Msg *msg, __int64 clubId,
	__int64 userId, Rva007F3980Pair *pairs, int count)
{
	void *txn = (void *)bfmeRva0130A710Slot.m_04;
	((Rva007E8AC0*)msg)->run();
	msg->m_tag = 0x636c7562;
	((BfmeC994*)msg)->addString("TXN", (const char *)txn);
	((Rva007E8810Message*)msg)->addInt64("clubId", clubId);
	((Rva007E8810Message*)msg)->addInt64("userId", userId);
	((BfmeThingCIB*)msg)->bfmeGoCIB((void *)"attributes.[]", (void *)(int)count);

	for (unsigned i = 0; i < (unsigned)count; ++i)
	{
		char buffer[64] = "";
		sprintf(buffer, "attributes.%d.key", i);
		((BfmeC994*)msg)->addString(buffer, (const char *)(int)pairs[i].key);

		sprintf(buffer, "attributes.%d.value", i);
		((BfmeC994*)msg)->addString(buffer, (const char *)(int)pairs[i].value);
	}
}

// @?rva007F3980Serialize@@YGXPAVRva007F3980Msg@@_J1PAURva007F3980Pair@@H@Z 0x007F3980

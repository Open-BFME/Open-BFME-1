// cl: /GS
// Open-BFME5 conversions.

extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);

typedef __int64 FeslInt64;

// retail 0x007E8E90
class Rva007E8810Message
{
public:
	void addInt64(const char *key, FeslInt64 value);
};

// Matched serializers at 0x007E8A10 and 0x007E88D0; both are
// thiscall RET 8. The integer writer forwards its second word as an int.
class BfmeC994
{
public:
	void addString(const char *key, const char *value);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *key, void *value);
};

class BfmeMsgVJF
{
public:
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

// retail 0x007E8AC0
class Rva007E8AC0 { public: void run(); };

struct BfmePairVJF
{
	void *m_bfme00;
	void *m_bfme04;
};

// Retail hands addInt64 each "users.N" key as a single 64-bit value, and a
// BfmePairVJF already is one 8-byte slot, so the entry is read in place instead
// of being loaded as two pointers and recombined at the call site.

// Shipped zero transaction-string pointer, VA 0x0130A630.
void *g_Va0130A630 = 0;

void __stdcall bfmeGoVJF(BfmeMsgVJF *m, BfmePairVJF *arr, int n)
{
	char buf[0x10];
	void *g = g_Va0130A630;
	((Rva007E8AC0*)m)->run();
	m->m_bfme1c = 0x6664626b;
	((BfmeC994 *)m)->addString("TXN", (const char *)g);
	for (int i = 0; i < n; ++i)
	{
		sprintf(buf, "users.%d", i);
		((Rva007E8810Message *)m)->addInt64(buf, *reinterpret_cast<const FeslInt64 *>(&arr[i]));
	}
	((BfmeThingCIB *)m)->bfmeGoCIB("users.[]", (void *)n);
}

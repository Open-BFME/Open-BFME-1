// ?rva007F9A40GetOrCreateSlot@BfmeMgrVPE@@QAEPAUBfmeSlotVPE@@PBURva007F9A40Key@@HH@Z
// Address-derived: find-or-allocate a BfmeSlotVPE (class/struct reused from
// Code/GameEngine/Source/Common/BfmeConv1559.cpp), then fill it from a
// 12-byte source key struct plus two extra int fields.
#pragma intrinsic(strcmp)
extern "C" int strcmp(const char *, const char *);

struct Rva007F9A40Key
{
	const char *a;
	const char *b;
	int c;

	bool matches(const Rva007F9A40Key *other) const;
};

struct BfmeSlotVPE
{
	char m_bfme00;
	char m_pad1[3];
	Rva007F9A40Key m_key;
	int m_10;
	int m_14;
};

struct Rva007F96C0Rec;
class Rva007FA2C0
{
public:
	Rva007F96C0Rec *lookup(void *rawKey);
};

class BfmeMgrVPE
{
public:
	BfmeSlotVPE* bfmeAllocSlotVPE();
	char m_bfmePad000[0x10];
	int m_bfme10;
	char m_bfmePad014[0x394];
	BfmeSlotVPE m_bfme3a8[0x20];

	BfmeSlotVPE* rva007F9A40GetOrCreateSlot(const Rva007F9A40Key* key, int a4, int a5);
};

bool Rva007F9A40Key::matches(const Rva007F9A40Key *other) const
{
	if (strcmp(a, other->a) != 0)
		return false;
	if (c != 0)
		return c == other->c;
	return strcmp(b, other->b) == 0;
}

BfmeSlotVPE* BfmeMgrVPE::rva007F9A40GetOrCreateSlot(const Rva007F9A40Key* key, int a4, int a5)
{
	BfmeSlotVPE* slot = (BfmeSlotVPE *)
		((Rva007FA2C0 *)this)->lookup((void *)key);
	if (!slot)
		slot = bfmeAllocSlotVPE();

	slot->m_key = *key;
	slot->m_10 = a4;
	slot->m_14 = a5;
	return slot;
}

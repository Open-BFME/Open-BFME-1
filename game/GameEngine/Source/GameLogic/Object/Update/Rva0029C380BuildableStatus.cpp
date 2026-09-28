// cl: /DNDEBUG /MD
// Retail 0x0029C380 (111B): exact shape via the measured definition-order
// lever (Int val = record->m_word10 before the key load).
//
// Identity anchors (all independently matched/proven, none invented):
//   * caller: dump body 0x0029E330 reaches this body through ILT 0x00020824;
//   * Object::getControllingPlayer 0x001BE3F0 (matched, Object.cpp) supplies
//     the Player; the +0x684 subobject is the build-index selector the
//     matched AIPlayer_findFactory.cpp caller (ILT 0x0000A7A9 -> 0x000FA8B0)
//     already addresses as Player+0x684 with the same (key-pointer, int)
//     argument pair;
//   * float threshold g_bfmeDefaultBU at 0x01075334 (pinned symbol);
//   * embedded record walk through this+0x20 virtual slots +0x48/+0x4C with
//     type-3 filter, and the owner+0x28 fallback return.
// The containing owner class and the record/selector method names remain
// unproven, so everything keeps the address token Rva0029C380.
typedef int Int;
typedef bool Bool;

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva0029C380Key
{
	int m_a;
	int m_b;
};

extern void j_0000a7a9();
extern void j_0001e204();

class Rva0029C380Selector
{
public:
	__forceinline int find(Rva0029C380Key *key, int val)
	{
		typedef int (Rva0029C380Selector::*Call)(Rva0029C380Key *, int);
		union { void (*raw)(); Call member; } target;
		target.raw = j_0000a7a9;
		return (this->*target.member)(key, val);
	}
	__forceinline float evaluate(int index)
	{
		typedef float (Rva0029C380Selector::*Call)(int);
		union { void (*raw)(); Call member; } target;
		target.raw = j_0001e204;
		return (this->*target.member)(index);
	}
};

extern float g_bfmeDefaultBU;

struct Rva0029C380Record
{
	unsigned int m_pad00;
	unsigned int m_type;
	Rva0029C380Key *m_key08;
	Int m_pad0c;
	Int m_val10;
};

class Rva0029C380Embedded
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44();
	virtual Rva0029C380Record *slot48();
	virtual Rva0029C380Record *slot4C(Rva0029C380Record *record);
};

class Rva0029C380
{
public:
	Rva0029C380Record *m0029C380();
private:
	char m_pad00[8];
	Object *m_related08;
	char m_pad0c[0x14];
	Rva0029C380Embedded m_embedded;
	char m_pad24[4];
	void *m_fallback28;
};

// ?m0029C380@Rva0029C380@@QAEPAURva0029C380Record@@XZ
Rva0029C380Record *Rva0029C380::m0029C380()
{
	Rva0029C380Embedded *embedded = &m_embedded;
	Rva0029C380Record *record = embedded->slot48();
	while (record != 0)
	{
		if (record->m_type == 3)
		{
			Player *player = m_related08->getControllingPlayer();
			Rva0029C380Selector *selector = (Rva0029C380Selector *)((char *)player + 0x684);
			Int val = record->m_val10;
			Rva0029C380Key *key = record->m_key08;
			int index = selector->find(key, val);
			float value = selector->evaluate(index);
			if (value >= g_bfmeDefaultBU)
				return record;
		}
		record = embedded->slot4C(record);
	}
	return (Rva0029C380Record *)m_fallback28;
}

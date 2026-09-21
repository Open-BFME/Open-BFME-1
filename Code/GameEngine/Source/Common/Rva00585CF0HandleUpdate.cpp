// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /I.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include "Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "reference/shims/stringbaseunicode/Common/UnicodeString.h"
// Retail 0x00585CF0: preserve the banked type/member labels and keep
// address tokens on unproven method identities. The range at +24/+28
// is searched for zero by STL __find at 0x005853B0. Its empty iterator
// tag explains the two equal-address arguments; it is not an output pair.
class Rva003C8340Item;

class BfmeObjYF
{
public:
	unsigned char m_bfmeHeadYF[0x10];
	int m_bfme10YF;
	Rva003C8340Item *m_field14;
	unsigned char m_bfmeMidYF[0x24 - 0x18];
	const int *m_bfme24YF;
	const int *m_bfme28YF;
	unsigned char m_bfmeMid2YF[0x30 - 0x2c];
	int m_bfme30YF;
	unsigned char m_bfmeMid3YF[0x38 - 0x34];
	bool m_field38;
	char m_pad39[3];
	int m_bfme3CYF;
};

struct BfmeHandleYF
{
	__forceinline BfmeHandleYF(const BfmeHandleYF &o) { m_bfmePtrYF = o.m_bfmePtrYF; }

	BfmeObjYF *m_bfmePtrYF;
};

void bfmeGo1064C(int a, int b);

class BfmeHostYF
{
public:
	void bfmeUpdateYF_00585CF0(BfmeHandleYF h);
	void bfmeNoteYF_00585C20(BfmeHandleYF h);
	void rva00585D60(BfmeHandleYF h);
	void rva00585E90(BfmeHandleYF h);
};

void BfmeHostYF::bfmeUpdateYF_00585CF0(BfmeHandleYF h)
{
	BfmeObjYF *o = h.m_bfmePtrYF;

	bfmeNoteYF_00585C20(h);

	const int *n = o->m_bfme28YF;
	int v = 0;

	if (std::find(o->m_bfme24YF, n, v) != n)
	{
		if (o->m_bfme3CYF != 2)
		{
			bfmeGo1064C(o->m_bfme10YF, 2);
			o->m_bfme3CYF = 2;
		}

		o->m_bfme30YF = 2;
	}
}

// Shared manager calls retain their already-matched address-derived identities.
class Rva003C8340Item {};
class Rva003C8340 {
public:
	void set(Rva003C8340Item *value);
	char m_pad00[8];
	Rva003C8340Item *m_current;
};
class Rva003C6200Item;
class Rva003C6200Owner {
public: void update(Rva003C6200Item *item, bool force);
};
class Glo012F1028Type {
public:
	void rva003C4740();
	char m_pad00[0x28];
	Rva003C8340 *m_field28;
};
extern Glo012F1028Type *Glo012F1028;
class Rva003BCA20 { public: void go(); };
class BfmeGameCW { public: void rva0060D4C0(void *what); };
extern BfmeGameCW *g_bfmeGameCW;
struct Rva005A63D0Mouse {
	virtual void bfmeSlot0AAX();
	virtual void bfmeSlot1AAX();
	virtual void bfmeSlot2AAX();
	virtual void bfmeSlot3AAX();
	virtual void bfmeSlot4AAX();
	virtual void bfmeSlot5AAX();
	virtual void bfmeSlot6AAX();
	virtual void bfmeSlot7AAX();
	virtual void bfmeSlot8AAX();
	virtual void bfmeSlot9AAX();
	virtual void bfmeSlot10AAX();
	virtual void bfmeSlot11AAX();
	virtual void bfmeSlot12AAX();
	virtual void bfmeSlot13AAX();
	virtual void bfmeSetCursorAAX(int kind);
};
extern Rva005A63D0Mouse *TheMouse;

// Retail 0x00585D60: handle callback; events 2/3 update +38 and event 5
// requests the final transition. Cache the range end as retail does.
void BfmeHostYF::rva00585D60(BfmeHandleYF h)
{
	BfmeObjYF *o = h.m_bfmePtrYF;
	bfmeNoteYF_00585C20(h);
	const int *end = o->m_bfme28YF;
	bool activate = false;
	for (const int *i = o->m_bfme24YF; i != end; ++i) {
		switch (*i) {
			case 2: o->m_field38 = true; break;
			case 3: o->m_field38 = false; break;
			case 5: activate = true; break;
		}
	}
	if (o->m_field38) {
		TheMouse->bfmeSetCursorAAX(5);
		Glo012F1028->m_field28->set(o->m_field14);
		((Rva003C6200Owner*)Glo012F1028->m_field28)->update((Rva003C6200Item*)o->m_field14, false);
	}
	int state = 2;
	if (Glo012F1028->m_field28->m_current == o->m_field14) state = 3;
	if (state != o->m_bfme3CYF) {
		bfmeGo1064C(o->m_bfme10YF, state);
		o->m_bfme3CYF = state;
	}
	if (activate) {
		Glo012F1028->rva003C4740();
		g_bfmeGameCW->rva0060D4C0(0);
		TheMouse->bfmeSetCursorAAX(1);
		((Rva003BCA20*)Glo012F1028)->go();
	}
}

struct Rva00579160Manager {
	unsigned int rva0046B2A0(const AsciiString &name);
};
extern Rva00579160Manager *Rva00579160TheManager;
void _bfme_setLivingWorldRegionName(int index, const UnicodeString &text);
void _bfme_setLivingWorldRegionBonus(int index, const UnicodeString &text);
void Open2SendNotice51B050(int index);
// Retail 0x00585E90: event 1 formats the witnessed portrait key, erases
// that manager entry, clears both region labels, and stores state 4.
void BfmeHostYF::rva00585E90(BfmeHandleYF h)
{
	BfmeObjYF *o = h.m_bfmePtrYF;
	bfmeNoteYF_00585C20(h);
	const int *end = o->m_bfme28YF;
	const int *begin = o->m_bfme24YF;
	int id = o->m_bfme10YF;
	if (std::find(begin, end, 1) != end) {
		AsciiString name;
		name.format("Popup%d/ButtonClip/Portrait", id);
		Rva00579160TheManager->rva0046B2A0(name);
		_bfme_setLivingWorldRegionName(id, UnicodeString::TheEmptyString);
		_bfme_setLivingWorldRegionBonus(id, UnicodeString::TheEmptyString);
		Open2SendNotice51B050(id);
		o->m_bfme30YF = 4;
	}
}

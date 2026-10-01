int __stdcall bfmeFindNC(void *key);

class Glo012F1028Type
{
public:
	bool bfmeCheckAAX(int id);
	void bfmeApplyAAX(int id);
	void bfmeTailAAX(int index);
};

extern Glo012F1028Type *Glo012F1028;

struct Rva005A63D0Mouse
{
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

// Retail's singleton at 0x012F4C5C is EA's Mouse *TheMouse; (defined once in
// GameClient/Input/Mouse.cpp).  This TU keeps its own view of the layout and
// casts at the use so the reference links to the one global.
class Mouse;
extern Mouse *TheMouse;

struct BfmeArgAAX
{
	unsigned char m_bfmeHeadAAX[8];
	int m_bfme08AAX;
	void *m_bfme0CAAX;
};

void __stdcall bfmeDispatchAAX(BfmeArgAAX *a, int kind);

void __stdcall bfmeDispatchAAX(BfmeArgAAX *a, int kind)
{
	switch (kind)
	{
		case 1:
		{
			int id = a->m_bfme08AAX;

			if (Glo012F1028->bfmeCheckAAX(id))
			{
				((Rva005A63D0Mouse *)TheMouse)->bfmeSetCursorAAX(5);
				Glo012F1028->bfmeApplyAAX(a->m_bfme08AAX);
			}

			break;
		}

		case 2:
		{
			void *k = a->m_bfme0CAAX;
			int r = bfmeFindNC(k);

			if (r != -1)
				Glo012F1028->bfmeTailAAX(r);

			break;
		}
	}
}

// 0x0060D510: the same eligibility check, cursor change and apply as case 1
// above, as its own stdcall entry that tail-calls the apply.
struct BfmeArg0060D510
{
	unsigned char m_bfmeHead0060D510[8];
	int m_bfme08_0060D510;
};

void __stdcall bfmeApplyCursor0060D510(BfmeArg0060D510 *a);

void __stdcall bfmeApplyCursor0060D510(BfmeArg0060D510 *a)
{
	int id = a->m_bfme08_0060D510;

	if (Glo012F1028->bfmeCheckAAX(id))
	{
		((Rva005A63D0Mouse *)TheMouse)->bfmeSetCursorAAX(5);
		Glo012F1028->bfmeApplyAAX(a->m_bfme08_0060D510);
	}
}

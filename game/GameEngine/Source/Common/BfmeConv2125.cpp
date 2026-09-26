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

extern Rva005A63D0Mouse *TheMouse;

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
				TheMouse->bfmeSetCursorAAX(5);
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

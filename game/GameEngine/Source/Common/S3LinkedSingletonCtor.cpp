// Retail 0x00490420, 40 bytes, from targets/game/reverse/reloc_names.csv.
//
// It has no call at all: its base constructor is inline and consists
// of storing the base vftable and pushing this onto a global singly-linked
// list at +0x04. The derived vftable then overwrites the base's, which is the
// ordinary two-vptr-store shape of a constructor with a polymorphic base. The
// flag at +0x0C is written as a byte, so it is a bool.

class BfmeLinkedSingleton;

extern BfmeLinkedSingleton *TheBfmeSingletonHead;			// 0x012F3350

class BfmeLinkedSingleton
{
public:
	BfmeLinkedSingleton(void)
	{
		m_bfmeNext = TheBfmeSingletonHead;

		TheBfmeSingletonHead = this;
	}

	virtual void bfmeSlot00(void);

	BfmeLinkedSingleton *m_bfmeNext;				// +0x04
};

class Gen_00490420 : public BfmeLinkedSingleton
{
public:
	Gen_00490420(void);

	virtual void bfmeSlot00(void);

private:
	int m_bfme0008;							// +0x08
	bool m_bfme000C;						// +0x0C
};

// ??0Gen_00490420@@QAE@XZ
Gen_00490420::Gen_00490420(void)
	: m_bfme0008(0),
	  m_bfme000C(true)
{
}

// cl: /DNDEBUG /MD /EHsc

// Retail layout: 0x005B5470 installs vftable 0x0110DE48, already pinned as
// ??_7BfmeOwnVVD@@6B@ by the landed destructor
// Code/GameEngine/Source/Common/BfmeConv1663.cpp (??1BfmeOwnVVD@@QAE@XZ,
// 0x005B5330), and stores `this` into the singleton at 0x012F4C84, already
// pinned in reverse/symbols.csv both as TheLookAtTranslator and as
// g_bfmeSingletonVVD -- but that name pin is stale for this address: the
// real ??0LookAtTranslator@@QAE@XZ is already matched elsewhere at
// 0x005A6580 (Code/GameEngine/Source/GameClient/MessageStream/
// LookAtTranslator_ctor.cpp, vtable 0x0110D62C), a different class entirely.
// This constructor is therefore address-derived, not LookAtTranslator; the
// BfmeOwnVVD name (shared with the already-landed dtor) is kept for
// consistency with that file. The array-new-with-ctor helper call (element
// size 0x20, count 8) uses the same BfmeElemVVD ctor/dtor pair as that file:
// the dtor is the existing pin ??1BfmeElemVVD@@QAE@XZ,0x0001479A; the ctor
// is newly pinned here as ??0BfmeElemVVD@@QAE@XZ,0x00418A07 (additive; the
// same address already carries an unrelated ??0BfmeS1059@@QAE@XZ pin
// through Code/gen_small/thunks_011.cpp -> FUN_00796AD0).
//
// Retail interleaves two groups of zero-stores around the array
// construction: some fields are zeroed via the (compiler-ordered)
// member-construction phase before the array, and the rest are zeroed by
// ordinary body statements that always run after all member construction
// (including the array) -- exactly the split used here (init-list members
// vs. body-assigned members).

class BfmeElemVVD
{
public:
	BfmeElemVVD();
	~BfmeElemVVD();
	char m_bfmePad00[0x20];
};

class BfmeBaseVVD
{
public:
	BfmeBaseVVD() { }
	~BfmeBaseVVD() { }
	virtual void bfmeSlot0VVD();
};

class BfmeOwnVVD : public BfmeBaseVVD
{
public:
	BfmeOwnVVD();
	~BfmeOwnVVD();

private:
	unsigned int m_04;                    // +0x04 body-set
	unsigned int m_08;                    // +0x08 body-set
	unsigned int m_0c;                    // +0x0c body-set
	unsigned int m_10;                    // +0x10 body-set
	unsigned int m_14;                    // +0x14 body-set
	unsigned int m_18;                    // +0x18 body-set
	unsigned char m_1c;                   // +0x1c init-list
	unsigned char m_pad1d[3];
	unsigned int m_20;                    // +0x20 body-set
	unsigned int m_24;                    // +0x24 body-set
	unsigned int m_28;                    // +0x28 body-set
	unsigned int m_2c;                    // +0x2c body-set
	unsigned int m_30;                    // +0x30 body-set
	unsigned int m_34;                    // +0x34 body-set
	unsigned char m_38;                   // +0x38 init-list
	unsigned char m_39;                   // +0x39 init-list
	unsigned char m_3a;                   // +0x3a init-list
	unsigned char m_3b;                   // +0x3b init-list
	unsigned char m_3c;                   // +0x3c init-list
	unsigned char m_pad3d[3];
	unsigned int m_40;                    // +0x40 init-list
	unsigned int m_44;                    // +0x44 init-list
	BfmeElemVVD m_bfme48[8];              // +0x48 .. +0x148
	unsigned int m_148;                   // +0x148 body-set
	unsigned int m_pad14c;
	unsigned int m_150;                   // +0x150 body-set
	unsigned char m_154;                  // +0x154 body-set
	unsigned char m_155;                  // +0x155 body-set
	unsigned char m_156;                  // +0x156 body-set
	unsigned char m_157;                  // +0x157 body-set
};

extern BfmeOwnVVD *g_bfmeSingletonVVD;

// ?d_005b5470@@YAXXZ
BfmeOwnVVD::BfmeOwnVVD()
	: m_1c(0), m_38(0), m_39(0), m_3a(0), m_3b(0), m_3c(0), m_40(0), m_44(0)
{
	m_148 = 0;
	m_150 = 0;
	m_154 = 0;
	m_155 = 0;
	m_156 = 0;
	m_157 = 0;
	m_08 = 0;
	m_04 = 0;
	m_18 = 0;
	m_14 = 0;
	m_10 = 0;
	m_0c = 0;
	m_24 = 0;
	m_20 = 0;
	m_34 = 0;
	m_30 = 0;
	m_2c = 0;
	m_28 = 0;

	g_bfmeSingletonVVD = this;
}

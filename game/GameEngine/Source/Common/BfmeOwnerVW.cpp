// Open-BFME5: the display-owner constructor at retail 0x00491D20, 104 bytes.
//
// The list-registering base at 0x010F9AD8 is the one already modelled in
// Bfme5FortyEight.cpp (head at 0x012F3350, count at +8, armed flag at +0xC).
// This body installs a second table, 0x010F9C08, between the base constructor
// and its own members, so that store belongs to an intermediate base rather
// than to the constructor body -- a body assignment would sink past the
// string copy.

extern int g_bfmeVtableVWa[];					// retail 0x010F9AD8
extern int g_bfmeVtableVWc[];					// retail 0x010F9C08

class BfmeStrVW
{
public:
	BfmeStrVW(const BfmeStrVW &other);
	~BfmeStrVW(void);

private:
	char *m_bfmeData;
};

class BfmeBaseVW;

extern BfmeBaseVW *g_bfmeListVW;				// retail 0x012F3350

class BfmeBaseVW
{
public:
	__forceinline BfmeBaseVW(void)
	{
		m_bfmeVtable = g_bfmeVtableVWa;

		m_bfmeNext = g_bfmeListVW;

		g_bfmeListVW = this;

		m_bfmeCount = 0;
		m_bfmeArmed = true;
	}

	~BfmeBaseVW(void);

	int *m_bfmeVtable;					// +0x00
	BfmeBaseVW *m_bfmeNext;					// +0x04
	int m_bfmeCount;					// +0x08
	bool m_bfmeArmed;					// +0x0C
};

// The second table lands with the flag, not with the base stores, so it is
// installed from the flag's own initializer rather than from a base body.
__forceinline bool bfmeInstallVW(BfmeBaseVW *self)
{
	self->m_bfmeVtable = g_bfmeVtableVWc;

	return false;
}

class Gen_00491D20 : public BfmeBaseVW
{
public:
	Gen_00491D20(const BfmeStrVW &name);

	bool m_bfmeFlag;					// +0x10
	BfmeStrVW m_bfmeName;					// +0x14
};

// ??0Gen_00491D20@@QAE@ABVBfmeStrVW@@@Z
Gen_00491D20::Gen_00491D20(const BfmeStrVW &name)
	: m_bfmeFlag(bfmeInstallVW(this)), m_bfmeName(name)
{
}

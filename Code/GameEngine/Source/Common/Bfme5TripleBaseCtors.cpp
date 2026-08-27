// Four constructors over the same three-base hierarchy.
//
// Each forwards its two arguments to the first base and does nothing else, yet
// five vftable stores follow the call. The first two belong to the second and
// third bases, whose own constructors are empty and fold in; the last three are
// the most-derived class writing its own primary and two secondary vptrs, which
// MSVC always emits after the base constructors have run.
//
// The base widths place the secondary vptrs: twelve bytes for the first base
// puts the second at +0x0C and the third at +0x10. Every vftable address is a
// DIR32 relocation, so the four bodies differ only in those words.

class BfmeBaseP0
{
public:
	BfmeBaseP0(void *first, void *second);
	virtual void bfmeSlot0(void);

private:
	int m_bfmeFields[2];					// +0x04
};

class BfmeBasePA { public: virtual void bfmeSlotA(void); };
template <int RetailCopy>
class BfmeBasePB { public: virtual void bfmeSlotB(void); };


class Gen_00200AE0 : public BfmeBaseP0, public BfmeBasePA, public BfmeBasePB<0>
{
public:
	Gen_00200AE0(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotA(void);
	virtual void bfmeSlotB(void);
};

class Gen_00216300 : public BfmeBaseP0, public BfmeBasePA, public BfmeBasePB<1>
{
public:
	Gen_00216300(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotA(void);
	virtual void bfmeSlotB(void);
};

class Gen_00250690 : public BfmeBaseP0, public BfmeBasePA, public BfmeBasePB<2>
{
public:
	Gen_00250690(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotA(void);
	virtual void bfmeSlotB(void);
};

class Gen_00253C30 : public BfmeBaseP0, public BfmeBasePA, public BfmeBasePB<3>
{
public:
	Gen_00253C30(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotA(void);
	virtual void bfmeSlotB(void);
};

// ??0Gen_00200AE0@@QAE@PAX0@Z
Gen_00200AE0::Gen_00200AE0(void *first, void *second)
	: BfmeBaseP0(first, second)
{
}

// ??0Gen_00216300@@QAE@PAX0@Z
Gen_00216300::Gen_00216300(void *first, void *second)
	: BfmeBaseP0(first, second)
{
}

// ??0Gen_00250690@@QAE@PAX0@Z
Gen_00250690::Gen_00250690(void *first, void *second)
	: BfmeBaseP0(first, second)
{
}

// ??0Gen_00253C30@@QAE@PAX0@Z
Gen_00253C30::Gen_00253C30(void *first, void *second)
	: BfmeBaseP0(first, second)
{
}

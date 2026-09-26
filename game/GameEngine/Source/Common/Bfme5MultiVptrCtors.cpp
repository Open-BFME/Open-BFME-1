// Four constructors that only forward, over hierarchies with several vftables.
//
// Each hands its two arguments to a base and does nothing else; everything
// after the call is vptr bookkeeping. Where a secondary base has no
// constructor of its own, its store folds in ahead of the most-derived set --
// that is the lone store that precedes the rest in three of these. A zeroed
// field in that same stretch belongs to the folded base, not to the derived
// class: MSVC writes the most-derived vptrs after every base is built, so a
// member initialiser of its own would land after them, not before.
//
// The offsets give the widths away: 0x0C, 0x10 and 0x18 for the first, 0x14
// and 0x18 for the next two, 0x70 and 0x74 for the last.

class BfmeQ0 { public: virtual void bfmeSlot0(void); private: int m_bfmeFields[2]; };
class BfmeQA { public: virtual void bfmeSlotA(void); };
class BfmeQB { public: virtual void bfmeSlotB(void); private: int m_bfmeField; };
class BfmeQC { public: virtual void bfmeSlotC(void); };

class BfmeQMiddle : public BfmeQ0, public BfmeQA, public BfmeQB, public BfmeQC
{
public:
	BfmeQMiddle(void *first, void *second);			// retail 0x0000C315
};

class Gen_002D7770 : public BfmeQMiddle
{
public:
	Gen_002D7770(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotA(void);
	virtual void bfmeSlotB(void);
	virtual void bfmeSlotC(void);
};

class BfmeR0 { public: virtual void bfmeSlot0(void); private: int m_bfmeFields[4]; };
class BfmeRA { public: virtual void bfmeSlotA(void); };
class BfmeRB_005F2D20 { public: virtual void bfmeSlotB(void); };
class BfmeRB_005F6530 { public: virtual void bfmeSlotB(void); };

class BfmeRMiddle : public BfmeR0, public BfmeRA
{
public:
	BfmeRMiddle(void *first, void *second);			// retail 0x00041CBD
};

class Gen_005F2D20 : public BfmeRMiddle, public BfmeRB_005F2D20
{
public:
	Gen_005F2D20(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotA(void);
	virtual void bfmeSlotB(void);
};

class Gen_005F6530 : public BfmeRMiddle, public BfmeRB_005F6530
{
public:
	Gen_005F6530(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotA(void);
	virtual void bfmeSlotB(void);
};

class BfmeS0 { public: virtual void bfmeSlot0(void); private: char m_bfmePad[0x6C]; };
class BfmeSX
{
public:
	BfmeSX(void) : m_bfmeField(0) {}
	virtual void bfmeSlotX(void);

private:
	int m_bfmeField;					// +0x04
};

class BfmeSMiddle : public BfmeS0
{
public:
	BfmeSMiddle(void *first, void *second);			// retail 0x00025306
};

class Gen_006949B0 : public BfmeSMiddle, public BfmeSX
{
public:
	Gen_006949B0(void *first, void *second);
	virtual void bfmeSlot0(void);
	virtual void bfmeSlotX(void);
};

// ??0Gen_002D7770@@QAE@PAX0@Z
Gen_002D7770::Gen_002D7770(void *first, void *second)
	: BfmeQMiddle(first, second)
{
}

// ??0Gen_005F2D20@@QAE@PAX0@Z
Gen_005F2D20::Gen_005F2D20(void *first, void *second)
	: BfmeRMiddle(first, second)
{
}

// ??0Gen_005F6530@@QAE@PAX0@Z
Gen_005F6530::Gen_005F6530(void *first, void *second)
	: BfmeRMiddle(first, second)
{
}

// ??0Gen_006949B0@@QAE@PAX0@Z
Gen_006949B0::Gen_006949B0(void *first, void *second)
	: BfmeSMiddle(first, second)
{
}

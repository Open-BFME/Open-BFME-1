// Four constructors that zero three words and hand two arguments plus the
// address of one of them to a starter.
//
// The three zero stores are not one object: the frame's copy of this lands
// between the second and the third, which is where the base ends and the
// member begins. A two-word base with no destructor is constructed first, the
// this-slot is written, then the one-word member -- the one that does have a
// destructor -- is constructed and the state word goes to zero. Putting all
// three words in a single member gets the this-slot written first instead and
// the bodies no longer line up.
//
// The unwind frame exists only for that member; the starter is what might
// throw with it live.

class BfmeSehPair
{
public:
	BfmeSehPair(void) : m_bfmeA(0), m_bfmeB(0) {}

private:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
};

class BfmeSehSlot
{
public:
	BfmeSehSlot(void) : m_bfmeC(0) {}
	~BfmeSehSlot(void);

private:
	int m_bfmeC;						// +0x00
};

class Gen_0049A330 : public BfmeSehPair
{
public:
	Gen_0049A330(void *first, void *second, void *third);
	void bfmeStart(void *first, void *second, void **slot);	// retail 0x00014100

private:
	BfmeSehSlot m_bfmeSlot;					// +0x08
};

class Gen_00654F20 : public BfmeSehPair
{
public:
	Gen_00654F20(void *first, void *second, void *third);
	void bfmeStart(void *first, void *second, void **slot);	// retail 0x0002648B

private:
	BfmeSehSlot m_bfmeSlot;					// +0x08
};

class Gen_00844340 : public BfmeSehPair
{
public:
	Gen_00844340(void *first, void *second, void *third);
	void bfmeStart(void *first, void *second, void **slot);	// retail 0x0002A531

private:
	BfmeSehSlot m_bfmeSlot;					// +0x08
};

class Gen_008443A0 : public BfmeSehPair
{
public:
	Gen_008443A0(void *first, void *second, void *third);
	void bfmeStart(void *first, void *second, void **slot);	// retail 0x00042BB8

private:
	BfmeSehSlot m_bfmeSlot;					// +0x08
};

// ??0Gen_0049A330@@QAE@PAX00@Z
Gen_0049A330::Gen_0049A330(void *first, void *second, void *third)
{
	bfmeStart(first, second, &second);
}

// ??0Gen_00654F20@@QAE@PAX00@Z
Gen_00654F20::Gen_00654F20(void *first, void *second, void *third)
{
	bfmeStart(first, second, &second);
}

// ??0Gen_00844340@@QAE@PAX00@Z
Gen_00844340::Gen_00844340(void *first, void *second, void *third)
{
	bfmeStart(first, second, &second);
}

// ??0Gen_008443A0@@QAE@PAX00@Z
Gen_008443A0::Gen_008443A0(void *first, void *second, void *third)
{
	bfmeStart(first, second, &second);
}

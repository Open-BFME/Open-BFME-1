// Ten array-owning destructors. (The eleventh, at 0x00938040, was identified
// as DynamicVectorClass<TextureStatisticsStruct>::Clear and now lives in
// game/Libraries/Source/WWVegas/WW3D2/TextureStatisticsVector.cpp.)
//
// Each frees an owned array with delete[] only when the pointer at +0x04 is
// non-null AND the ownership byte at +0x0D is set, then clears the ownership
// byte and the count at +0x08. The delete[] expands inline -- element count
// read from base-4, eh vector destructor iterator, then the array free -- so
// these are ordinary source, not the compiler-generated vector deleting
// destructors that the family at 0x0005F1A0 turned out to be.
//
// Seven of them are three bytes longer than the other four, and the extra
// bytes are a vptr store: the long ones belong to polymorphic classes, the
// short ones to plain classes that clear a field at +0x10 in the same slot.
// The element size pushed to the iterator gives each element type's width.

typedef bool Bool;

// MSVC 7.1 folds `delete []` onto the scalar ??3@YAXPAX@Z unless the array
// form is declared where it can see it; retail calls ??_V@YAXPAX@Z here.
void operator delete[](void *block);


class BfmeElementA
{
public:
	~BfmeElementA(void);					// retail 0x00030652

private:
	char m_bfmeBytes[4];
};

class BfmeElementB
{
public:
	~BfmeElementB(void);					// retail 0x0001AAD2

private:
	char m_bfmeBytes[0x74];
};

class BfmeElementC
{
public:
	~BfmeElementC(void);					// retail 0x00937390

private:
	char m_bfmeBytes[0xc];
};

class BfmeElementD
{
public:
	~BfmeElementD(void);					// retail 0x00018FCF

private:
	char m_bfmeBytes[0x24];
};

class Gen_00930B10
{
public:
	virtual void bfmeSlot0(void);

	~Gen_00930B10(void);

private:
	BfmeElementA *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
};

class Gen_00930C10
{
public:
	~Gen_00930C10(void);

private:
	char m_bfmeHead[4];
	BfmeElementA *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
	int m_bfmeExtra;					// +0x10
};

class Gen_00930DB0
{
public:
	virtual void bfmeSlot0(void);

	~Gen_00930DB0(void);

private:
	BfmeElementA *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
};

class Gen_00936CB0
{
public:
	virtual void bfmeSlot0(void);

	~Gen_00936CB0(void);

private:
	BfmeElementB *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
};

class Gen_00936DA0
{
public:
	~Gen_00936DA0(void);

private:
	char m_bfmeHead[4];
	BfmeElementB *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
	int m_bfmeExtra;					// +0x10
};

class Gen_00936E40
{
public:
	virtual void bfmeSlot0(void);

	~Gen_00936E40(void);

private:
	BfmeElementB *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
};

class Gen_009380E0
{
public:
	virtual void bfmeSlot0(void);

	~Gen_009380E0(void);

private:
	BfmeElementC *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
};

class Gen_0093E1A0
{
public:
	virtual void bfmeSlot0(void);

	~Gen_0093E1A0(void);

private:
	BfmeElementD *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
};

class Gen_0093E3B0
{
public:
	~Gen_0093E3B0(void);

private:
	char m_bfmeHead[4];
	BfmeElementD *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
	int m_bfmeExtra;					// +0x10
};

class Gen_0093E9C0
{
public:
	virtual void bfmeSlot0(void);

	~Gen_0093E9C0(void);

private:
	BfmeElementD *m_bfmeArray;				// +0x04
	int m_bfmeCount;					// +0x08
	char m_bfmeGap;						// +0x0C
	Bool m_bfmeOwns;					// +0x0D
	char m_bfmeGap2[2];
};

// ??1Gen_00930B10@@QAE@XZ
Gen_00930B10::~Gen_00930B10(void)
{
	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_00930C10@@QAE@XZ
Gen_00930C10::~Gen_00930C10(void)
{
	m_bfmeExtra = 0;

	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_00930DB0@@QAE@XZ
Gen_00930DB0::~Gen_00930DB0(void)
{
	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_00936CB0@@QAE@XZ
Gen_00936CB0::~Gen_00936CB0(void)
{
	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_00936DA0@@QAE@XZ
Gen_00936DA0::~Gen_00936DA0(void)
{
	m_bfmeExtra = 0;

	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_00936E40@@QAE@XZ
Gen_00936E40::~Gen_00936E40(void)
{
	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_009380E0@@QAE@XZ
Gen_009380E0::~Gen_009380E0(void)
{
	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_0093E1A0@@QAE@XZ
Gen_0093E1A0::~Gen_0093E1A0(void)
{
	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_0093E3B0@@QAE@XZ
Gen_0093E3B0::~Gen_0093E3B0(void)
{
	m_bfmeExtra = 0;

	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

// ??1Gen_0093E9C0@@QAE@XZ
Gen_0093E9C0::~Gen_0093E9C0(void)
{
	if (m_bfmeArray && m_bfmeOwns)
	{
		delete [] m_bfmeArray;

		m_bfmeArray = 0;
	}

	m_bfmeOwns = false;
	m_bfmeCount = 0;
}

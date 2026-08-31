// Six flag-then-forward wrappers.
//
// Each ORs one bit into a dword member and tail-jumps to a no-argument member
// of the same class. The immediate width follows the mask: 0x80 does not fit a
// signed byte, so that one alone carries a full dword immediate and runs three
// bytes longer.

typedef unsigned int UnsignedInt;


class Gen_00088B60
{
public:
	void bfmeClearForward(void);
	void bfmeForward(void);

private:
	void bfmeNext(void);					// ILT 0x00031FCF

	char m_bfmeHead[0x44];
	UnsignedInt m_bfmeFlags;				// +0x44
};

class Gen_000B5690
{
public:
	void bfmeForward(void);

private:
	void bfmeNext(void);					// ILT 0x000242A3

	char m_bfmeHead[0x98];
	UnsignedInt m_bfmeFlags;				// +0x98
};

class Gen_000B56A0
{
public:
	void bfmeForward(void);

private:
	void bfmeNext(void);					// ILT 0x0002F699

	char m_bfmeHead[0x98];
	UnsignedInt m_bfmeFlags;				// +0x98
};

class Gen_000B56B0
{
public:
	void bfmeForward(void);

private:
	void bfmeNext(void);					// ILT 0x00016455

	char m_bfmeHead[0x98];
	UnsignedInt m_bfmeFlags;				// +0x98
};

class Gen_000B56C0
{
public:
	void bfmeForward(void);

private:
	void bfmeNext(void);					// ILT 0x0001AD2A

	char m_bfmeHead[0x98];
	UnsignedInt m_bfmeFlags;				// +0x98
};

class Gen_000B56D0
{
public:
	void bfmeForward(void);

private:
	void bfmeNext(void);					// ILT 0x0003990A

	char m_bfmeHead[0x98];
	UnsignedInt m_bfmeFlags;				// +0x98
};

// ?bfmeClearForward@Gen_00088B60@@QAEXXZ
void Gen_00088B60::bfmeClearForward(void)
{
	m_bfmeFlags &= ~0x10U;

	bfmeNext();
}

// ?bfmeForward@Gen_00088B60@@QAEXXZ
void Gen_00088B60::bfmeForward(void)
{
	m_bfmeFlags |= 0x10;

	bfmeNext();
}

// ?bfmeForward@Gen_000B5690@@QAEXXZ
void Gen_000B5690::bfmeForward(void)
{
	m_bfmeFlags |= 0x8;

	bfmeNext();
}

// ?bfmeForward@Gen_000B56A0@@QAEXXZ
void Gen_000B56A0::bfmeForward(void)
{
	m_bfmeFlags |= 0x10;

	bfmeNext();
}

// ?bfmeForward@Gen_000B56B0@@QAEXXZ
void Gen_000B56B0::bfmeForward(void)
{
	m_bfmeFlags |= 0x20;

	bfmeNext();
}

// ?bfmeForward@Gen_000B56C0@@QAEXXZ
void Gen_000B56C0::bfmeForward(void)
{
	m_bfmeFlags |= 0x40;

	bfmeNext();
}

// ?bfmeForward@Gen_000B56D0@@QAEXXZ
void Gen_000B56D0::bfmeForward(void)
{
	m_bfmeFlags |= 0x80;

	bfmeNext();
}

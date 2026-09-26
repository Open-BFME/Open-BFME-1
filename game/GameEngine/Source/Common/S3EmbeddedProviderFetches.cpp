// Nine 15-byte bodies with one shape:
//
//     mov eax, [ecx + 4]      the vptr of a sub-object embedded at +0x04
//     add ecx, 4              which is what this is addressed as
//     call [eax]              its slot 0, no arguments
//     mov ecx, eax
//     jmp <getter>            a tail call on whatever came back
//
// The vptr is read from this+4 and ecx is then moved to this+4, so the thing
// being dispatched on is a POLYMORPHIC MEMBER sitting at +0x04, not a base and
// not a pointer -- a pointer would be loaded, not have its address taken.
//
// The tail targets are three of the seven-byte getters already in the ledger,
// and their rows fix the return type: QAEHXZ, so these return Int too. Seven
// of the nine go to 0x007E9F70 and one each to 0x007E9F80 and 0x007E9F90,
// which is the only thing separating them -- the bodies are otherwise
// identical, so every name here is derived from its own address.

class Gen_007e9f70
{
public:
	int m(void);							// retail 0x007E9F70
};

class Gen_007e9f80
{
public:
	int m(void);							// retail 0x007E9F80
};

class Gen_007e9f90
{
public:
	int m(void);							// retail 0x007E9F90
};

class BfmeGetterProvider70
{
public:
	virtual Gen_007e9f70 *bfmeGet(void);
};

class BfmeGetterProvider80
{
public:
	virtual Gen_007e9f80 *bfmeGet(void);
};

class BfmeGetterProvider90
{
public:
	virtual Gen_007e9f90 *bfmeGet(void);
};

class Gen_007e9a40
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider70 m_bfmeProvider;			// +0x04
};

class Gen_007f1150
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider70 m_bfmeProvider;			// +0x04
};

class Gen_007f1e90
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider70 m_bfmeProvider;			// +0x04
};

class Gen_007f2d60
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider70 m_bfmeProvider;			// +0x04
};

class Gen_007f3310
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider70 m_bfmeProvider;			// +0x04
};

class Gen_007f3ff0
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider70 m_bfmeProvider;			// +0x04
};

class Gen_007f4370
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider70 m_bfmeProvider;			// +0x04
};

class Gen_007fbaa0
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider80 m_bfmeProvider;			// +0x04
};

class Gen_007fcf00
{
public:
	int bfmeFetch(void);

private:
	char m_bfmeHead[0x04];
	BfmeGetterProvider90 m_bfmeProvider;			// +0x04
};

// ?bfmeFetch@Gen_007e9a40@@QAEHXZ
int Gen_007e9a40::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007f1150@@QAEHXZ
int Gen_007f1150::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007f1e90@@QAEHXZ
int Gen_007f1e90::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007f2d60@@QAEHXZ
int Gen_007f2d60::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007f3310@@QAEHXZ
int Gen_007f3310::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007f3ff0@@QAEHXZ
int Gen_007f3ff0::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007f4370@@QAEHXZ
int Gen_007f4370::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007fbaa0@@QAEHXZ
int Gen_007fbaa0::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// ?bfmeFetch@Gen_007fcf00@@QAEHXZ
int Gen_007fcf00::bfmeFetch(void)
{
	return m_bfmeProvider.bfmeGet()->m();
}

// Six guarded delegating wrappers, retail 0x00730EB0, 0x00730ED0, 0x00730EF0,
// 0x006C89F0, 0x006C8A20 and 0x006C8A40.
//
// All six read one pointer member, return false when it is null, and otherwise
// hand the call straight on. The first three read +0x10 and the last three
// +0x3094, and the first three each delegate into one of the last three
// through an incremental-link thunk, which is why the jump target is the ILT
// slot rather than the body itself.
//
// Five of them tail-jump because the callee takes exactly the arguments they
// were given. 0x006C89F0 is the exception: it appends a literal false, so the
// argument count no longer matches and the call cannot be a tail jump -- it
// calls and then rets 8 on its own.
//
// The false exit is xor al,al, a byte, so the result is Bool and not Int. It
// has to be a plain `return false` after the guarded call rather than an else,
// or the compiler folds the two exits together and drops the xor.

typedef bool Bool;

class Gen_00730EB0Target
{
public:
	Bool bfmeForward(void *a, void *b);			// ILT 0x00049328
};

class Gen_00730ED0Target
{
public:
	Bool bfmeForward(void *a, void *b);			// ILT 0x00027EE9
};

class Gen_00730EF0Target
{
public:
	Bool bfmeForward(void *a, void *b);			// ILT 0x0002CAF7
};

class Gen_006C89F0Target
{
public:
	Bool bfmeApply(void *a, void *b, Bool flag);		// ILT 0x000486EE
};

class Gen_006C8A20Target
{
public:
	Bool bfmeForward(void *a, void *b);			// ILT 0x0003A03A
};

class Gen_006C8A40Target
{
public:
	Bool bfmeForward(void *a, void *b);			// ILT 0x0001551E
};

class Gen_00730EB0
{
public:
	Bool bfmeForward(void *a, void *b);

private:
	char m_bfmeHead[0x10];
	Gen_00730EB0Target *m_bfmeImpl;				// +0x10
};

class Gen_00730ED0
{
public:
	Bool bfmeForward(void *a, void *b);

private:
	char m_bfmeHead[0x10];
	Gen_00730ED0Target *m_bfmeImpl;				// +0x10
};

class Gen_00730EF0
{
public:
	Bool bfmeForward(void *a, void *b);

private:
	char m_bfmeHead[0x10];
	Gen_00730EF0Target *m_bfmeImpl;				// +0x10
};

class Gen_006C89F0
{
public:
	Bool bfmeForward(void *a, void *b);

private:
	char m_bfmeHead[0x3094];
	Gen_006C89F0Target *m_bfmeImpl;				// +0x3094
};

class Gen_006C8A20
{
public:
	Bool bfmeForward(void *a, void *b);

private:
	char m_bfmeHead[0x3094];
	Gen_006C8A20Target *m_bfmeImpl;				// +0x3094
};

class Gen_006C8A40
{
public:
	Bool bfmeForward(void *a, void *b);

private:
	char m_bfmeHead[0x3094];
	Gen_006C8A40Target *m_bfmeImpl;				// +0x3094
};

// ?bfmeForward@Gen_00730EB0@@QAE_NPAX0@Z
Bool Gen_00730EB0::bfmeForward(void *a, void *b)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a, b);

	return false;
}

// ?bfmeForward@Gen_00730ED0@@QAE_NPAX0@Z
Bool Gen_00730ED0::bfmeForward(void *a, void *b)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a, b);

	return false;
}

// ?bfmeForward@Gen_00730EF0@@QAE_NPAX0@Z
Bool Gen_00730EF0::bfmeForward(void *a, void *b)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a, b);

	return false;
}

// ?bfmeForward@Gen_006C89F0@@QAE_NPAX0@Z
Bool Gen_006C89F0::bfmeForward(void *a, void *b)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeApply(a, b, false);

	return false;
}

// ?bfmeForward@Gen_006C8A20@@QAE_NPAX0@Z
Bool Gen_006C8A20::bfmeForward(void *a, void *b)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a, b);

	return false;
}

// ?bfmeForward@Gen_006C8A40@@QAE_NPAX0@Z
Bool Gen_006C8A40::bfmeForward(void *a, void *b)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a, b);

	return false;
}

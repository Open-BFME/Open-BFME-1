// Thirteen 23-byte bodies with one shape:
//
//     push both stack arguments back in the order they arrived
//     call a member of this class -- ecx is never set, so it is still the
//         incoming this and the call needs no instruction to say so
//     test al,al / setne al
//
// The setne is a narrowing: test al,al rather than test eax,eax says the
// callee hands back a byte, and the caller turns it into a bool. Written as
// `return raw(a, b);` -- the implicit char-to-bool conversion is exactly
// test al,al / setne al. Spelling it `!= 0` instead gives MSVC a different
// idiom, neg al / sbb eax,eax / neg eax, and a byte more.
//
// Four of the thirteen reach 0x002DF120 and nine reach 0x002DF100, both
// through their own incremental-link thunks, so each wrapper gets its own
// declaration of the callee and its own pin -- the shared target does not make
// them the same class. Every name is derived from its own address.

class Gen_002da6b0
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0001D813
};

class Gen_002da6d0
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002dad40
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002db220
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002dcc60
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002dd290
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002ddc80
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0001D813
};

class Gen_002ddca0
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002de220
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002de840
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

class Gen_002dec00
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0001D813
};

class Gen_002df4c0
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0001D813
};

class Gen_002df4e0
{
public:
	bool bfmeMatch(void *first, void *second);

private:
	unsigned char bfmeMatchRaw(void *first, void *second);		// ILT 0x0002DB69
};

// ?bfmeMatch@Gen_002da6b0@@QAE_NPAX0@Z
bool Gen_002da6b0::bfmeMatch(void *first, void *second)
{
	return bfmeMatchRaw(first, second);
}

// ?bfmeMatch@Gen_002dcc60@@QAE_NPAX0@Z
bool Gen_002dcc60::bfmeMatch(void *first, void *second)
{
	return bfmeMatchRaw(first, second);
}

// ?bfmeMatch@Gen_002de840@@QAE_NPAX0@Z
bool Gen_002de840::bfmeMatch(void *first, void *second)
{
	return bfmeMatchRaw(first, second);
}

// ?bfmeMatch@Gen_002dec00@@QAE_NPAX0@Z
bool Gen_002dec00::bfmeMatch(void *first, void *second)
{
	return bfmeMatchRaw(first, second);
}


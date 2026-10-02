// Four wrappers from a family of thirteen 23-byte bodies with one shape:
//
//     push both stack arguments back in the order they arrived
//     call the shared predicate -- ecx is never set, so it is still the
//         incoming this and the call needs no instruction to say so
//     test al,al / setne al
//
// The setne is a narrowing: test al,al rather than test eax,eax says the
// callee hands back a byte, and the caller turns it into a bool. Written as
// `return raw(a, b);` -- the implicit char-to-bool conversion is exactly
// test al,al / setne al. Spelling it `!= 0` instead gives MSVC a different
// idiom, neg al / sbb eax,eax / neg eax, and a byte more.
//
// The shared predicates are defined as Rva002DF120::test and
// Rva002DF100::test. The wrappers below reach them through ILTs 0x0001D813
// and 0x0002DB69 respectively; the casts preserve the incoming this pointer.

class Rva002DF120
{
public:
	unsigned char test(void *first, void *second);
};

class Rva002DF100
{
public:
	unsigned char test(void *first, void *second);
};

class Gen_002da6b0
{
public:
	bool bfmeMatch(void *first, void *second);
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
};

class Gen_002dec00
{
public:
	bool bfmeMatch(void *first, void *second);
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
	return ((Rva002DF120 *)this)->test(first, second);
}

// ?bfmeMatch@Gen_002dcc60@@QAE_NPAX0@Z
bool Gen_002dcc60::bfmeMatch(void *first, void *second)
{
	return ((Rva002DF100 *)this)->test(first, second);
}

// ?bfmeMatch@Gen_002de840@@QAE_NPAX0@Z
bool Gen_002de840::bfmeMatch(void *first, void *second)
{
	return ((Rva002DF100 *)this)->test(first, second);
}

// ?bfmeMatch@Gen_002dec00@@QAE_NPAX0@Z
bool Gen_002dec00::bfmeMatch(void *first, void *second)
{
	return ((Rva002DF120 *)this)->test(first, second);
}

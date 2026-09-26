// Five make-from-argument bodies.
//
// Each is one new expression on a class constructed from the single argument:
// allocate, test the block, construct, return it, with the failed allocation
// taking its own zero-returning exit. The unwind frame and the state word
// going to zero hold the raw block so it can be freed if the constructor
// throws.
//
// Four clean their argument on the way out and one does not, which is the
// calling convention showing through; the fifth also has a class small enough
// for its size to be pushed as a byte, and those two facts together are the
// seven bytes it saves.


class BfmeMadeBase_0045DC70
{
public:
	BfmeMadeBase_0045DC70(void *owner);

private:
	char m_bfmeFields[0x268];
};

class BfmeMade_0045DC70 : public BfmeMadeBase_0045DC70
{
public:
	__declspec(noinline) BfmeMade_0045DC70(void *owner);	// retail 0x00043063

private:
	int m_bfmeTail;
};

class BfmeMade_00494200
{
public:
	BfmeMade_00494200(void *owner);			// retail 0x00028F8D

private:
	int m_bfmeFields[0x9A];
};

class BfmeMade_0078D390
{
public:
	BfmeMade_0078D390(void *owner);			// retail 0x0003707E

private:
	int m_bfmeFields[0xBE];
};

class BfmeMade_0078F520
{
public:
	BfmeMade_0078F520(void *owner);			// retail 0x0003707E

private:
	int m_bfmeFields[0xBE];
};

class BfmeMade_009CB5F0
{
public:
	BfmeMade_009CB5F0(void *owner);			// retail 0x009CB4E0

private:
	int m_bfmeFields[0xA];
};

// ?bfmeMake_0045DC70@@YGPAVBfmeMade_0045DC70@@PAX@Z
BfmeMade_0045DC70 * __stdcall bfmeMake_0045DC70(void *owner)
{
	return new BfmeMade_0045DC70(owner);
}

// ??0BfmeMade_0045DC70@@QAE@PAX@Z
__declspec(noinline) BfmeMade_0045DC70::BfmeMade_0045DC70(void *owner)
	: BfmeMadeBase_0045DC70(owner)
{
	*(volatile unsigned int *)this = 0x010F7160;
	m_bfmeTail = 0;
}

// ?bfmeMake_00494200@@YGPAVBfmeMade_00494200@@PAX@Z
BfmeMade_00494200 * __stdcall bfmeMake_00494200(void *owner)
{
	return new BfmeMade_00494200(owner);
}

// ?bfmeMake_0078D390@@YGPAVBfmeMade_0078D390@@PAX@Z
BfmeMade_0078D390 * __stdcall bfmeMake_0078D390(void *owner)
{
	return new BfmeMade_0078D390(owner);
}

// ?bfmeMake_0078F520@@YGPAVBfmeMade_0078F520@@PAX@Z
BfmeMade_0078F520 * __stdcall bfmeMake_0078F520(void *owner)
{
	return new BfmeMade_0078F520(owner);
}

// ?bfmeMake_009CB5F0@@YAPAVBfmeMade_009CB5F0@@PAX@Z
BfmeMade_009CB5F0 * __cdecl bfmeMake_009CB5F0(void *owner)
{
	return new BfmeMade_009CB5F0(owner);
}

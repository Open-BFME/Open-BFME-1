// Seven more bodies: three reference-counted copy constructors at 0x006C54C0,
// 0x006C5630 and 0x00749E10, and four short-widening constructors at
// 0x00529B60, 0x0054F920, 0x0054FA00 and 0x0056E900.
//
// The copy constructors take the source's pointer, store it, and bump a
// refcount only when it is not null. The refcount is incremented with a
// sixteen-bit inc at +0x04 of the shared block, so it is an unsigned short,
// and the store of the pointer lands between the test and the branch because
// the compiler schedules it into the gap -- writing the assignment first and
// the guarded increment after reproduces that.
//
// The other four read a SIGNED short through the argument (movsx, not movzx),
// widen it once, and hand the same widened value to a __cdecl helper twice --
// one push eax for each argument, cleaned by add esp,8 -- storing the result
// at +0x04 and returning this.

struct BfmeShortSource
{
	short m_bfmeValue;
};

int bfmeMake_00529B60(int a, int b);				// ILT 0x000364C6
int bfmeMake_0054F920(int a, int b);				// ILT 0x0000B500
int bfmeMake_0054FA00(int a, int b);				// ILT 0x00029771
int bfmeMake_0056E900(int a, int b);				// ILT 0x0003C65A
unsigned int bfmeHashCombineA(unsigned int left, unsigned int right);	// ILT 0x00042FA0

struct BfmeSharedBlock
{
	char m_bfmeHead[4];
	unsigned short m_bfmeRefCount;				// +0x04
};

class Gen_006C54C0
{
public:
	Gen_006C54C0(const Gen_006C54C0 &other);

private:
	BfmeSharedBlock *m_bfmeData;
};

class Gen_006C5630
{
public:
	Gen_006C5630(const Gen_006C5630 &other);

private:
	BfmeSharedBlock *m_bfmeData;
};

class Gen_00749E10
{
public:
	Gen_00749E10(const Gen_00749E10 &other);

private:
	BfmeSharedBlock *m_bfmeData;
};

class Gen_00529B60
{
public:
	Gen_00529B60(const BfmeShortSource *source);
	Gen_00529B60 bfmeAdvance(int);

private:
	Gen_00529B60(int value) { m_bfmeResult = value; }

	char m_bfmeHead[4];
	int m_bfmeResult;					// +0x04
};

class Gen_0054F920
{
public:
	Gen_0054F920(const BfmeShortSource *source);

private:
	char m_bfmeHead[4];
	int m_bfmeResult;					// +0x04
};

class Gen_0054FA00
{
public:
	Gen_0054FA00(const BfmeShortSource *source);

private:
	char m_bfmeHead[4];
	int m_bfmeResult;					// +0x04
};

class Gen_0056E900
{
public:
	Gen_0056E900(const BfmeShortSource *source);

private:
	char m_bfmeHead[4];
	int m_bfmeResult;					// +0x04
};

// ??0Gen_006C54C0@@QAE@ABV0@@Z
Gen_006C54C0::Gen_006C54C0(const Gen_006C54C0 &other)
{
	m_bfmeData = other.m_bfmeData;

	if (m_bfmeData)
		++m_bfmeData->m_bfmeRefCount;
}

// ??0Gen_006C5630@@QAE@ABV0@@Z
Gen_006C5630::Gen_006C5630(const Gen_006C5630 &other)
{
	m_bfmeData = other.m_bfmeData;

	if (m_bfmeData)
		++m_bfmeData->m_bfmeRefCount;
}

// ??0Gen_00749E10@@QAE@ABV0@@Z
Gen_00749E10::Gen_00749E10(const Gen_00749E10 &other)
{
	m_bfmeData = other.m_bfmeData;

	if (m_bfmeData)
		++m_bfmeData->m_bfmeRefCount;
}

// ??0Gen_00529B60@@QAE@PBUBfmeShortSource@@@Z
Gen_00529B60::Gen_00529B60(const BfmeShortSource *source)
{
	m_bfmeResult = bfmeMake_00529B60(source->m_bfmeValue, source->m_bfmeValue);
}

// ?bfmeAdvance@Gen_00529B60@@QAE?AV1@H@Z
Gen_00529B60 Gen_00529B60::bfmeAdvance(int)
{
	int previous = m_bfmeResult;
	m_bfmeResult = bfmeHashCombineA(m_bfmeResult, 0xE4CD9C42);
	return Gen_00529B60(previous);
}

// ??0Gen_0054F920@@QAE@PBUBfmeShortSource@@@Z
Gen_0054F920::Gen_0054F920(const BfmeShortSource *source)
{
	m_bfmeResult = bfmeMake_0054F920(source->m_bfmeValue, source->m_bfmeValue);
}

// ??0Gen_0054FA00@@QAE@PBUBfmeShortSource@@@Z
Gen_0054FA00::Gen_0054FA00(const BfmeShortSource *source)
{
	m_bfmeResult = bfmeMake_0054FA00(source->m_bfmeValue, source->m_bfmeValue);
}

// ??0Gen_0056E900@@QAE@PBUBfmeShortSource@@@Z
Gen_0056E900::Gen_0056E900(const BfmeShortSource *source)
{
	m_bfmeResult = bfmeMake_0056E900(source->m_bfmeValue, source->m_bfmeValue);
}

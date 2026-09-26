// Four memberwise copy constructors.
//
// Each copies its plain fields one at a time and then hands the trailing
// member its own copy constructor -- the only call in the body, and the reason
// the fields ahead of it are copied inline rather than block-moved.
//
// The field widths are readable straight off: three byte moves then a dword in
// two of them, four dwords in the other two. There is no unwind frame because
// nothing constructed before the call needs destroying.

typedef bool Bool;

class BfmeCopyPart_000C08E0
{
public:
	BfmeCopyPart_000C08E0(const BfmeCopyPart_000C08E0 &other);	// retail 0x0001D10B
};

class Gen_000C08E0
{
public:
	Gen_000C08E0(const Gen_000C08E0 &other);

private:
	Bool m_bfmeA;						// +0x00
	Bool m_bfmeB;						// +0x01
	Bool m_bfmeC;						// +0x02
	int m_bfmeD;						// +0x04
	BfmeCopyPart_000C08E0 m_bfmePart;			// +0x08
};

class BfmeCopyPart_000C0DF0
{
public:
	BfmeCopyPart_000C0DF0(const BfmeCopyPart_000C0DF0 &other);	// retail 0x0000EAF2
};

class Gen_000C0DF0
{
public:
	Gen_000C0DF0(const Gen_000C0DF0 &other);

private:
	Bool m_bfmeA;						// +0x00
	Bool m_bfmeB;						// +0x01
	Bool m_bfmeC;						// +0x02
	int m_bfmeD;						// +0x04
	BfmeCopyPart_000C0DF0 m_bfmePart;			// +0x08
};

class BfmeCopyPart_004256E0
{
public:
	BfmeCopyPart_004256E0(const BfmeCopyPart_004256E0 &other);	// retail 0x000083E1
};

class Gen_004256E0
{
public:
	Gen_004256E0(const Gen_004256E0 &other);

private:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeD;						// +0x0C
	BfmeCopyPart_004256E0 m_bfmePart;			// +0x10
};

class BfmeCopyPart_00425940
{
public:
	BfmeCopyPart_00425940(const BfmeCopyPart_00425940 &other);	// retail 0x0001400B
};

class Gen_00425940
{
public:
	Gen_00425940(const Gen_00425940 &other);

private:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeD;						// +0x0C
	BfmeCopyPart_00425940 m_bfmePart;			// +0x10
};

// ??0Gen_000C08E0@@QAE@ABV0@@Z
Gen_000C08E0::Gen_000C08E0(const Gen_000C08E0 &other)
	: m_bfmeA(other.m_bfmeA), m_bfmeB(other.m_bfmeB), m_bfmeC(other.m_bfmeC),
	  m_bfmeD(other.m_bfmeD), m_bfmePart(other.m_bfmePart)
{
}

// ??0Gen_000C0DF0@@QAE@ABV0@@Z
Gen_000C0DF0::Gen_000C0DF0(const Gen_000C0DF0 &other)
	: m_bfmeA(other.m_bfmeA), m_bfmeB(other.m_bfmeB), m_bfmeC(other.m_bfmeC),
	  m_bfmeD(other.m_bfmeD), m_bfmePart(other.m_bfmePart)
{
}

// ??0Gen_004256E0@@QAE@ABV0@@Z
Gen_004256E0::Gen_004256E0(const Gen_004256E0 &other)
	: m_bfmeA(other.m_bfmeA), m_bfmeB(other.m_bfmeB), m_bfmeC(other.m_bfmeC),
	  m_bfmeD(other.m_bfmeD), m_bfmePart(other.m_bfmePart)
{
}

// ??0Gen_00425940@@QAE@ABV0@@Z
Gen_00425940::Gen_00425940(const Gen_00425940 &other)
	: m_bfmeA(other.m_bfmeA), m_bfmeB(other.m_bfmeB), m_bfmeC(other.m_bfmeC),
	  m_bfmeD(other.m_bfmeD), m_bfmePart(other.m_bfmePart)
{
}

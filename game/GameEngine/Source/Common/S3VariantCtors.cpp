// Nine variant constructors in two shapes.
//
// Every one takes three dword slots -- ret 0xC -- and hands back this, and
// every one writes only the dword at +0x04. The selector is compared against
// two FIRST and one second, in that order, which is what an if/else-if chain
// gives; a switch would have ordered them the other way or built a table.
//
// 0x00390830, 0x003CA5F0, 0x0054F770, 0x0054F7C0 and 0x00596C40 read the
// second argument as a plain dword. 0x00529340, 0x0054F720, 0x0054F810 and
// 0x0056E860 read it with movsx, so there the parameter is a signed short, and
// they reach for the same four helpers the short-widening constructors already
// use. In both shapes the widened value is handed to the helper twice.

unsigned int bfmeMakeW0(unsigned int a, unsigned int b);		// ILT 0x0004B28B
unsigned int bfmeMakeW1(unsigned int a, unsigned int b);		// ILT 0x00002B8F
unsigned int bfmeMakeW2(unsigned int a, unsigned int b);		// ILT 0x00025225
unsigned int bfmeMakeW3(unsigned int a, unsigned int b);		// ILT 0x0000403E
unsigned int bfmeMakeW4(unsigned int a, unsigned int b);		// ILT 0x000283D5

int bfmeMake_00529B60(int a, int b);					// ILT 0x000364C6
int bfmeMake_0054F920(int a, int b);					// ILT 0x0000B500
int bfmeMake_0054FA00(int a, int b);					// ILT 0x00029771
int bfmeMake_0056E900(int a, int b);					// ILT 0x0003C65A
unsigned int bfmeHashCombineA(unsigned int left, unsigned int right);	// ILT 0x00042FA0

enum { BFME_KIND_MADE = 1, BFME_KIND_GIVEN = 2 };


class Gen_00390830
{
public:
	Gen_00390830(int kind, unsigned int made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_003CA5F0
{
public:
	Gen_003CA5F0(int kind, unsigned int made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F770
{
public:
	Gen_0054F770(int kind, unsigned int made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F7C0
{
public:
	Gen_0054F7C0(int kind, unsigned int made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_00596C40
{
public:
	Gen_00596C40(int kind, unsigned int made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_00529340
{
public:
	Gen_00529340(int kind, short made, unsigned int given);
	Gen_00529340 bfmeAdvance();

private:
	Gen_00529340(unsigned int value) { m_bfmeValue = value; }

	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F720
{
public:
	Gen_0054F720(int kind, short made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054F810
{
public:
	Gen_0054F810(int kind, short made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0056E860
{
public:
	Gen_0056E860(int kind, short made, unsigned int given);

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

// ??0Gen_00390830@@QAE@HII@Z
Gen_00390830::Gen_00390830(int kind, unsigned int made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMakeW0(made, made);
}

// ??0Gen_003CA5F0@@QAE@HII@Z
Gen_003CA5F0::Gen_003CA5F0(int kind, unsigned int made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMakeW1(made, made);
}

// ??0Gen_0054F770@@QAE@HII@Z
Gen_0054F770::Gen_0054F770(int kind, unsigned int made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMakeW2(made, made);
}

// ??0Gen_0054F7C0@@QAE@HII@Z
Gen_0054F7C0::Gen_0054F7C0(int kind, unsigned int made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMakeW3(made, made);
}

// ??0Gen_00596C40@@QAE@HII@Z
Gen_00596C40::Gen_00596C40(int kind, unsigned int made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMakeW4(made, made);
}

// ??0Gen_00529340@@QAE@HFI@Z
Gen_00529340::Gen_00529340(int kind, short made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMake_00529B60(made, made);
}

// ?bfmeAdvance@Gen_00529340@@QAE?AV1@XZ
Gen_00529340 Gen_00529340::bfmeAdvance()
{
	m_bfmeValue = bfmeHashCombineA(m_bfmeValue, 0xE4CD9C42);
	return Gen_00529340(m_bfmeValue);
}

// ??0Gen_0054F720@@QAE@HFI@Z
Gen_0054F720::Gen_0054F720(int kind, short made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMake_0054F920(made, made);
}

// ??0Gen_0054F810@@QAE@HFI@Z
Gen_0054F810::Gen_0054F810(int kind, short made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMake_0054FA00(made, made);
}

// ??0Gen_0056E860@@QAE@HFI@Z
Gen_0056E860::Gen_0056E860(int kind, short made, unsigned int given)
{
	if (kind == BFME_KIND_GIVEN)
		m_bfmeValue = given;
	else if (kind == BFME_KIND_MADE)
		m_bfmeValue = bfmeMake_0056E900(made, made);
}

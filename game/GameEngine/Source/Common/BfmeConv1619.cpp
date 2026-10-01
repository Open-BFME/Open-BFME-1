// Open-BFME5 conversions.

class BfmeStrVTN
{
public:
	BfmeStrVTN(const BfmeStrVTN &other);
	char *m_bfme00;
};

class BfmeHostVTN;

// retail walks the override chain through ILT 0x000022BB, which targets
// Overridable::getFinalOverride (matching row 0x00087A80).
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class BfmeSinkVTN
{
};

class BfmeHostVTN
{
public:
	int m_bfme00;
	BfmeSinkVTN *m_bfme04;
	char m_bfmePad08[0x18];
	BfmeStrVTN m_bfme20;
};

class BfmeOwnVTN
{
public:
	BfmeStrVTN bfmeNameVTN();
};

BfmeStrVTN BfmeOwnVTN::bfmeNameVTN()
{
	BfmeHostVTN *host = *(BfmeHostVTN **)((char *)this - 0x60);
	volatile int scratch = 0;

	if (host != 0 && host->m_bfme04 != 0)
		host = (BfmeHostVTN *)(const void *)((const Overridable *)host->m_bfme04)->getFinalOverride();

	return host->m_bfme20;
}

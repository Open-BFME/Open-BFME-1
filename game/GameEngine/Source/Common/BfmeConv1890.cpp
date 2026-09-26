extern const char g_bfmeEmptyAA[];

struct BfmeStrAA
{
	char *m_bfmeDataAA;
};

class BfmeSubAA
{
public:
	void bfmeLookupAA(float *out, const char *text);
};

class BfmeOwnerAA
{
public:
	void bfmeGetAA(BfmeStrAA *name, int *outX, int *outY);

	unsigned char m_bfmeHeadAA[4];
	BfmeSubAA m_bfmeSubAA;
};

void BfmeOwnerAA::bfmeGetAA(BfmeStrAA *name, int *outX, int *outY)
{
	float pos[2];

	const char *text = name->m_bfmeDataAA != 0 ? name->m_bfmeDataAA + 8 : g_bfmeEmptyAA;

	m_bfmeSubAA.bfmeLookupAA(pos, text);

	if (outX != 0)
		*outX = (int)pos[0];

	if (outY != 0)
		*outY = (int)pos[1];
}

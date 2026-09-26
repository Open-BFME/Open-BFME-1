class BfmeTmplERD;

class BfmeStrERD
{
public:
	BfmeStrERD(const char *text);

	~BfmeStrERD() { releaseBuffer(); }

	void *m_bfmeDataERD;

private:
	void releaseBuffer();
};

class BfmeMgrERD
{
public:
	BfmeTmplERD *bfmeFindERD(const BfmeStrERD &name);
};

extern BfmeMgrERD *g_bfmeMgrERD;

class BfmeSysERD
{
public:
	BfmeSysERD(BfmeTmplERD *tmpl);

	unsigned char m_bfmeBodyERD[0xd0];
};

BfmeSysERD * __stdcall bfmeMakeERD(const char *name)
{
	BfmeTmplERD *tmpl;

	{
		const BfmeStrERD &text = BfmeStrERD(name);

		tmpl = g_bfmeMgrERD->bfmeFindERD(text);
	}

	if (tmpl == 0)
		return 0;

	return new BfmeSysERD(tmpl);
}

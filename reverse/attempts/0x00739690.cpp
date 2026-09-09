// ?bfmeFixupCE@@YADPAVMeshClass@@@Z
// partial score=0.97 date=2026-09-09
struct ShaderClass
{
	__forceinline ShaderClass(int bits) { m_bfmeBitsCE = bits; }
	__forceinline ShaderClass(const ShaderClass &o) { m_bfmeBitsCE = o.m_bfmeBitsCE; }

	int m_bfmeBitsCE;
};

class MeshMatDescClass
{
public:
	void Set_Single_Shader(ShaderClass s, int i);

	unsigned char m_bfmeHeadCE[0x94];
	int m_bfme94CE;
};

class MeshModelClass
{
public:
	unsigned char m_bfmeHeadCE[0x9c];
	MeshMatDescClass *m_bfme9CCE;
};

class MeshClass;

char bfmeFixupThunkCE(MeshClass *m);

class MeshClass
{
public:
	virtual void bfmeDropCE();
	virtual void bfmeV04CE();
	virtual void bfmeV08CE();
	virtual int bfmeIsMultiCE();
	virtual void bfmeV10CE();
	virtual void bfmeV14CE();
	virtual void bfmeV18CE();
	virtual void bfmeV1CCE();
	virtual void bfmeV20CE();
	virtual void bfmeV24CE();
	virtual void bfmeV28CE();
	virtual void bfmeV2CCE();
	virtual void bfmeV30CE();
	virtual void bfmeV34CE();
	virtual void bfmeV38CE();
	virtual void bfmeV3CCE();
	virtual void bfmeV40CE();
	virtual void bfmeV44CE();
	virtual void bfmeV48CE();
	virtual void bfmeV4CCE();
	virtual void bfmeV50CE();
	virtual void bfmeV54CE();
	virtual void bfmeV58CE();
	virtual void bfmeV5CCE();
	virtual void bfmeV60CE();
	virtual void bfmeV64CE();
	virtual void bfmeV68CE();
	virtual int bfmeCountCE();
	virtual void bfmeV70CE();
	virtual MeshClass *bfmeSubCE(int i);

	void Make_Unique(bool b);
	MeshModelClass *Get_Model();

	int m_bfme04CE;
};

char bfmeFixupCE(MeshClass *m)
{
	if (m == 0)
		return 0;

	if (m->bfmeIsMultiCE() == 0)
	{
		m->Make_Unique(false);

		MeshModelClass *mm = m->Get_Model();

		if (mm == 0)
			return 0;

		int bits = mm->m_bfme9CCE->m_bfme94CE;

		mm->m_bfme9CCE->Set_Single_Shader(ShaderClass((bits & 0xffff7f3f) | 0x4020), 0);

		if (--m->m_bfme04CE == 0)
			m->bfmeDropCE();

		return 1;
	}

	int n = m->bfmeCountCE();
	char ok = 0;

	for (int i = 0; i < n; i++)
	{
		MeshClass *sub = m->bfmeSubCE(i);

		if (bfmeFixupThunkCE(sub))
			ok = 1;

		if (sub != 0 && --sub->m_bfme04CE == 0)
			sub->bfmeDropCE();
	}

	return ok;
}

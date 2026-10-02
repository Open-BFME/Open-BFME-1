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

// Retail's global at 0x012F64BC is ParticleSystemManager *TheParticleSystemManager;
// only the global's spelling matters to the link, so the pointee keeps this
// TU's own template-lookup view (BfmeMgrERD) and is cast at the use.
class ParticleSystemManager;

class BfmeMgrERD
{
public:
	BfmeTmplERD *bfmeFindERD(const BfmeStrERD &name);
};

extern ParticleSystemManager *TheParticleSystemManager;

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

		tmpl = ((BfmeMgrERD *)TheParticleSystemManager)->bfmeFindERD(text);
	}

	if (tmpl == 0)
		return 0;

	return new BfmeSysERD(tmpl);
}

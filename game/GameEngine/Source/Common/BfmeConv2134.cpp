class TextureClass
{
public:
	void Release_Ref();
};

class Rva009EBCE0AssetReference
{
public:
	__forceinline ~Rva009EBCE0AssetReference()
	{
		if (m_bfmePtrXQ != 0)
			m_bfmePtrXQ->Release_Ref();
	}

	TextureClass *m_bfmePtrXQ;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Gen00970F80
{
public:
	__forceinline Gen00970F80() { m_bfmeRefXQ = 0; }
	Gen00970F80(void *ref);
	__declspec(noinline) ~Gen00970F80();

	void *m_bfmeRefXQ;
};

Gen00970F80 bfmeMakeXQ(const char *name)
{
	if (name == 0)
		return Gen00970F80();

	return Gen00970F80(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

// Factory 00970FD0's FuncInfo E4E410 state 0 destroys this return object
// through C5F030 -> 00970EA0. The native owner keeps its constructor address;
// the former NetCommandRef byte alias describes a different lifetime/callee.
// See identity_evidence/20261003-factory-970fd0-cleanup.md.
Gen00970F80::~Gen00970F80()
{
	if (m_bfmeRefXQ != 0)
		static_cast<TextureClass *>(m_bfmeRefXQ)->Release_Ref();
}

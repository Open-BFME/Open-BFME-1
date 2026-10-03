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
		if (m_bfmePtrXV != 0)
			m_bfmePtrXV->Release_Ref();
	}

	TextureClass *m_bfmePtrXV;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Gen00972540
{
public:
	__forceinline Gen00972540() { m_bfmeRefXV = 0; }
	Gen00972540(void *ref);
	~Gen00972540();

	void *m_bfmeRefXV;
};

Gen00972540 bfmeMakeXV(const char *name)
{
	if (name == 0)
		return Gen00972540();

	return Gen00972540(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

// Factory972590 constructs this hidden result via matched ctor972540.
// FuncInfo E4E818 state0/C5F3D0 calls destructor9723A0; the separate
// lookup temporary in state1 goes through ILT27C41 to5C640.
Gen00972540::~Gen00972540()
{
	if (m_bfmeRefXV)
		((TextureClass *)m_bfmeRefXV)->Release_Ref();
}

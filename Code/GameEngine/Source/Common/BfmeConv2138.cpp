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
		if (m_bfmePtrXU != 0)
			m_bfmePtrXU->Release_Ref();
	}

	TextureClass *m_bfmePtrXU;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Gen00971E40
{
public:
	__forceinline Gen00971E40() { m_bfmeRefXU = 0; }
	Gen00971E40(void *ref);
	~Gen00971E40();

	void *m_bfmeRefXU;
};

Gen00971E40 bfmeMakeXU(const char *name)
{
	if (name == 0)
		return Gen00971E40();

	return Gen00971E40(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

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
		if (m_bfmePtrXR != 0)
			m_bfmePtrXR->Release_Ref();
	}

	TextureClass *m_bfmePtrXR;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Gen00970940
{
public:
	__forceinline Gen00970940() { m_bfmeRefXR = 0; }
	Gen00970940(void *ref);
	~Gen00970940();

	void *m_bfmeRefXR;
};

Gen00970940 bfmeMakeXR(const char *name)
{
	if (name == 0)
		return Gen00970940();

	return Gen00970940(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

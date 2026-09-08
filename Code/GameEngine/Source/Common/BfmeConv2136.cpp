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
		if (m_bfmePtrXS != 0)
			m_bfmePtrXS->Release_Ref();
	}

	TextureClass *m_bfmePtrXS;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Gen00971360
{
public:
	__forceinline Gen00971360() { m_bfmeRefXS = 0; }
	Gen00971360(void *ref);
	~Gen00971360();

	void *m_bfmeRefXS;
};

Gen00971360 bfmeMakeXS(const char *name)
{
	if (name == 0)
		return Gen00971360();

	return Gen00971360(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

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
		if (m_bfmePtrXY != 0)
			m_bfmePtrXY->Release_Ref();
	}

	TextureClass *m_bfmePtrXY;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Gen0090BE20
{
public:
	__forceinline Gen0090BE20() { m_bfmeRefXY = 0; }
	Gen0090BE20(void *ref);
	~Gen0090BE20();

	void *m_bfmeRefXY;
};

Gen0090BE20 bfmeMakeXY(const char *name)
{
	if (name == 0)
		return Gen0090BE20();

	return Gen0090BE20(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

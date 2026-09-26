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
		if (m_bfmePtrXW != 0)
			m_bfmePtrXW->Release_Ref();
	}

	TextureClass *m_bfmePtrXW;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Gen008FF1B0
{
public:
	__forceinline Gen008FF1B0() { m_bfmeRefXW = 0; }
	Gen008FF1B0(void *ref);
	~Gen008FF1B0();

	void *m_bfmeRefXW;
};

Gen008FF1B0 bfmeMakeXW(const char *name)
{
	if (name == 0)
		return Gen008FF1B0();

	return Gen008FF1B0(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

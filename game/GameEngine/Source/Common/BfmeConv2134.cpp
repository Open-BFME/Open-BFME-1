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
	~Gen00970F80();

	void *m_bfmeRefXQ;
};

Gen00970F80 bfmeMakeXQ(const char *name)
{
	if (name == 0)
		return Gen00970F80();

	return Gen00970F80(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

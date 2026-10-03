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
	__declspec(noinline) ~Gen008FF1B0();

	void *m_bfmeRefXW;
};

Gen008FF1B0 bfmeMakeXW(const char *name)
{
	if (name == 0)
		return Gen008FF1B0();

	return Gen008FF1B0(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
}

// The factory's FuncInfo state 0 destroys its completed return object through
// 0x008FEB80.  This is the same address-named owner constructed at 0x008FF1B0,
// not the NetCommandRef destructor formerly used as an unrelated byte alias.
// See targets/game/reverse/identity_evidence/20261003-factory-result-cleanup.md.
Gen008FF1B0::~Gen008FF1B0()
{
	if (m_bfmeRefXW != 0)
		static_cast<TextureClass *>(m_bfmeRefXW)->Release_Ref();
}

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

// Retail 90BE20 initializes this one-pointer owner. Factory 90BE70 constructs
// that type in its hidden result; its FuncInfo E4A840 state0 dispatches this
// returned object to 90BD50 (C5B800), distinct from ctor member cleanup5C640.
Gen0090BE20::~Gen0090BE20()
{
	if (m_bfmeRefXY)
		((TextureClass *)m_bfmeRefXY)->Release_Ref();
}

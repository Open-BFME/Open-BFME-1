// cl: /DNDEBUG /MD /EHsc

// The retail body at 0x0078CD80 tears down W3DFontLibrary's BFME font cache
// before it calls the already matched FontLibrary base destructor.  The
// 0x01120544 vtable store, W3DGameClient's W3DFontLibrary type, and the
// adjacent 0x0078CE50 loadFontData body prove this destructor identity.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class FontLibrary : public SubsystemInterface
{
public:
	virtual ~FontLibrary();
	virtual void fontLibraryAnchor() = 0;
};

class BFMERetailFontLibrary : public FontLibrary
{
public:
	virtual void anchor() = 0;
};

class FontCharsClass
{
public:
	virtual void Release_Ref();
	int m_ref_count;
};

class BFMEFontCharsListBase
{
public:
	virtual void unused();
	virtual bool Resize(int new_size);

	FontCharsClass **m_vector;
	int m_vector_max;
	int m_active_count;
};

class BFMEFontCharsList : public BFMEFontCharsListBase
{
public:

	FontCharsClass *&operator[](int index) { return m_vector[index]; }

	void Delete_All()
	{
		m_active_count = 0;
		if (m_active_count < m_vector_max / 4)
			Resize(m_active_count);
	}
};

extern BFMEFontCharsList g_BFMEFontCharsList;

class GameFont;

class W3DFontLibrary : public BFMERetailFontLibrary
{
public:
	virtual ~W3DFontLibrary();

protected:
	virtual bool loadFontData(GameFont *font);
};

W3DFontLibrary::~W3DFontLibrary()
{
	for (int i = 0; i < g_BFMEFontCharsList.m_active_count; ++i)
	{
		FontCharsClass *font = g_BFMEFontCharsList[i];
		if (--font->m_ref_count == 0)
			font->Release_Ref();
	}

	g_BFMEFontCharsList.Delete_All();
}

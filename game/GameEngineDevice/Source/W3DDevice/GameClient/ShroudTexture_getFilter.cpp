// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: BFME ShroudTexture::getFilter ABI slice.
// Retail returns the texture's filter subobject at +0x1c and otherwise
// constructs a function-local fallback filter at the fixed 20-byte shape.
// The existing Gen_00920A20 body owns that retail constructor; this TU keeps
// the wrapper's recovered ShroudFilter identity and local-static codegen.

class Gen_00920A20
{
public:
	Gen_00920A20(int mode);

private:
	char _storage[0x14];
};

class ShroudFilter
{
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

private:
	void *m_texture;
};

// ?getFilter@ShroudTexture@@QAEPAVShroudFilter@@XZ
ShroudFilter *ShroudTexture::getFilter(void)
{
	if (m_texture) {
		return reinterpret_cast<ShroudFilter *>(
			reinterpret_cast<char *>(m_texture) + 0x1c);
	}

	static Gen_00920A20 fallback(0);
	return reinterpret_cast<ShroudFilter *>(&fallback);
}

// cl: /DNDEBUG /MD /EHsc

// Retail 0x007286B0. Texture pointer assignment: Add_Ref is the inline
// inc-word-at-+4; Release_Ref is TextureBaseClass::Release_Ref at 0x009EB7A0.
// No self-assign guard.

class TextureBaseClass
{
public:
	void Add_Ref() { ++*(unsigned short *)((char *)this + 4); }
	void Release_Ref();
};

class Gen_007286b0
{
public:
	Gen_007286b0 &operator=(const Gen_007286b0 &that);

private:
	TextureBaseClass *m_texture;
};

// ??4Gen_007286b0@@QAEAAV0@ABV0@@Z
Gen_007286b0 &Gen_007286b0::operator=(const Gen_007286b0 &that)
{
	if (that.m_texture)
		that.m_texture->Add_Ref();
	if (m_texture)
		m_texture->Release_Ref();
	m_texture = that.m_texture;
	return *this;
}

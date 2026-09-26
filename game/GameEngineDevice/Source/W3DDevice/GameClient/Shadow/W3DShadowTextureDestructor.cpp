// cl: /DNDEBUG /MD /EHsc
// Retail 0x007AF4E0: W3DShadowTexture::~W3DShadowTexture.
//
// The BFME layout keeps the texture reference at +0x30 after the two
// eight-byte RefCountClass/HashableClass bases and the 32-byte name buffer.

class TextureClass
{
public:
	void Release_Ref(void);
};

class RefCountClass
{
public:
	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass(void) {}

private:
	int m_refs;
};

class HashableClass
{
public:
	virtual ~HashableClass(void) {}
	virtual const char *Get_Key(void) = 0;

private:
	HashableClass *m_next;
};

class W3DShadowTexture : public RefCountClass, public HashableClass
{
public:
	~W3DShadowTexture(void);

private:
	char m_namebuf[32];
	TextureClass *m_texture;
};

W3DShadowTexture::~W3DShadowTexture(void)
{
	if (m_texture)
		m_texture->Release_Ref();
}

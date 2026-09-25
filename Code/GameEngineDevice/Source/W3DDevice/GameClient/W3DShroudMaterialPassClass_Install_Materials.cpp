// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0071A680, 140 bytes: W3DShroudMaterialPassClass::Install_Materials.
// Identity: vtable 0x011209C8 (W3DShroudMaterialPassClass) slot 1 reaches this
// body through ILT 0x00029262; slot 2 is the matched UnInstall_Materials at
// 0x0071A110. Zero Hour twin W3DShroud.cpp; BFME passes the shroud texture as
// a ref-counted TextureHandle (getShroudTexture ILT 0x00013BBF) and stores it
// in the handle table at 0x012F9D28 before setShader(ST_SHROUD_TEXTURE 0).

class TextureBaseClass
{
public:
	void Release_Ref();

private:
	char m_pad0[4];

public:
	unsigned short m_word4; // incremented on copy; Release_Ref drops it
};

class TextureHandle
{
public:
	~TextureHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}

	const TextureHandle &operator=(const TextureHandle &other)
	{
		if (other.m_p)
			++other.m_p->m_word4;
		if (m_p)
			m_p->Release_Ref();
		m_p = other.m_p;
		return *this;
	}

	TextureBaseClass *m_p;
};

class W3DShroud
{
public:
	TextureHandle getShroudTexture();
};

class BaseHeightMapRenderObjClass
{
	char m_pad0[0x30B8];
	W3DShroud *m_shroud;

public:
	W3DShroud *getShroud() { return m_shroud; }
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern TextureHandle g_bfmeTableDU[];

class W3DShaderManager
{
public:
	enum ShaderTypes { ST_SHROUD_TEXTURE = 5 };
	static int setShader(ShaderTypes shader, int pass);
	static void setTexture(int stage, const TextureHandle &texture) { g_bfmeTableDU[stage] = texture; }
};

class W3DShroudMaterialPassClass
{
public:
	virtual void Install_Materials(void) const;
};

// ?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ
void W3DShroudMaterialPassClass::Install_Materials(void) const
{
	if (TheTerrainRenderObject->getShroud())
	{
		W3DShaderManager::setTexture(0, TheTerrainRenderObject->getShroud()->getShroudTexture());
		W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 0);
	}
}

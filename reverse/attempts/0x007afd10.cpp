// ?getTexture@BFMEShadowManagerLayoutGetTextureShim@@QAEPAVW3DShadowTexture@@PBD@Z
// partial score=0.42 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include <string.h>

typedef char Char;
typedef int Int;

class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

class Gen_00920a60
{
public:
	void m(Int value);

	Char m_pad00[0x0c];
	Int m_uAddress;
	Int m_vAddress;
};

class ShroudFilter : public Gen_00920a60
{
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

	TextureClass *m_texture;
};

class HashableClass
{
public:
	virtual ~HashableClass(void);
	virtual const Char *Get_Key(void);

	HashableClass *m_next;
};

class HashTableClass
{
public:
	HashableClass *Find(const Char *key);
	void Add(HashableClass *entry);
};

class W3DShadowTextureManager
{
public:
	HashTableClass *texturePtrTable;
};

class RefCountClass
{
public:
	virtual void Delete_This(void);

	Int m_refs;
};

class W3DShadowTexture : public RefCountClass, public HashableClass
{
public:
	W3DShadowTexture(void) throw();

	void Add_Ref(void)
	{
		++m_refs;
	}

	Char m_namebuf[32];
	TextureClass *m_texture;
	Char m_tail[0x70];
};

class BFMEShadowManagerLayoutGetTextureShim
{
public:
	W3DShadowTexture *getTexture(const Char *name);

private:
	Char m_pad00[0x24c];
	W3DShadowTextureManager *m_W3DShadowTextureManager;
};

W3DShadowTexture *BFMEShadowManagerLayoutGetTextureShim::getTexture(
	const Char *name)
{
	Char textureName[64];
	Int length = (Int)strlen(name);
	if (length > 0x3b)
		length = 0x3b;

	strncpy(textureName, name, length);
	strcpy(textureName + length, ".tga");

	HashableClass *hashable = m_W3DShadowTextureManager->texturePtrTable->Find(textureName);
	W3DShadowTexture *texture = 0;
	if (hashable)
		texture = (W3DShadowTexture *)((Char *)hashable - 8);
	if (texture)
		texture->Add_Ref();
	if (texture)
		return texture;

	BFMEWaterTrackTextureHandle textureHandle =
		BFMEGetWaterTrackTexture(textureName, 0, 0);
	if (!textureHandle.m_texture)
		return 0;

	((ShroudTexture *)&textureHandle)->getFilter()->m_uAddress = 1;
	((ShroudTexture *)&textureHandle)->getFilter()->m_vAddress = 1;
	((ShroudTexture *)&textureHandle)->getFilter()->m(0);

	W3DShadowTexture *newTexture = new W3DShadowTexture;
	strncpy(newTexture->m_namebuf, textureName, 0x1f);
	newTexture->m_namebuf[0x1f] = 0;
	newTexture->Add_Ref();
	m_W3DShadowTextureManager->texturePtrTable->Add(
		(HashableClass *)newTexture);

	if (textureHandle.m_texture)
		++*(unsigned short *)((Char *)textureHandle.m_texture + 4);
	if (newTexture->m_texture)
		newTexture->m_texture->Release_Ref();
	newTexture->m_texture = textureHandle.m_texture;
	return newTexture;
}

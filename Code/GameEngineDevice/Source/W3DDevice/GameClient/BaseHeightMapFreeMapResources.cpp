// ?freeMapResources@BaseHeightMapRenderObjClass@@UAEHXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?freeMapResources@BaseHeightMapRenderObjClass@@UAEHXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// Open-BFME5: clean C++ reconstruction of the BFME terrain resource release.

class BaseHeightMapInlineRef
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		if (--m_refCount == 0)
			Delete_This();
	}
private:
	int m_refCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	virtual int freeMapResources(void);
private:
	void freeScorchBuffers(void);
	char m_pad0[0x2fd4];
	BaseHeightMapInlineRef *m_ref2fd8;
	BaseHeightMapInlineRef *m_ref2fdc;
	char m_pad1[0x2ff4 - 0x2fe0];
	BaseHeightMapInlineRef *m_ref2ff4;
	char m_pad2[0x304c - 0x2ff8];
	BaseHeightMapInlineRef *m_ref304c;
	TextureBaseClass *m_ref3050;
	TextureBaseClass *m_ref3054;
	TextureBaseClass *m_ref3058;
	TextureBaseClass *m_ref305c;
	TextureBaseClass *m_ref3060;
	TextureBaseClass *m_ref3064;
	TextureBaseClass *m_ref3068;
	char m_pad3[0x3090 - 0x306c];
	TextureBaseClass *m_ref3090;
};

int BaseHeightMapRenderObjClass::freeMapResources(void)
{
	freeScorchBuffers();
	if (m_ref2fd8) { m_ref2fd8->Release_Ref(); m_ref2fd8 = 0; }
	if (m_ref2fdc) { m_ref2fdc->Release_Ref(); m_ref2fdc = 0; }
	if (m_ref304c) { m_ref304c->Release_Ref(); m_ref304c = 0; }
	if (m_ref3050) { m_ref3050->Release_Ref(); m_ref3050 = 0; }
	if (m_ref3054) { m_ref3054->Release_Ref(); m_ref3054 = 0; }
	if (m_ref3058) { m_ref3058->Release_Ref(); m_ref3058 = 0; }
	if (m_ref305c) { m_ref305c->Release_Ref(); m_ref305c = 0; }
	if (m_ref3060) { m_ref3060->Release_Ref(); m_ref3060 = 0; }
	if (m_ref3064) { m_ref3064->Release_Ref(); m_ref3064 = 0; }
	if (m_ref3068) { m_ref3068->Release_Ref(); m_ref3068 = 0; }
	if (m_ref3090) { m_ref3090->Release_Ref(); m_ref3090 = 0; }
	if (m_ref2ff4) { m_ref2ff4->Release_Ref(); m_ref2ff4 = 0; }
	return 0;
}

// ?freeScorchBuffers@BaseHeightMapRenderObjClass@@AAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ reconstruction of the BFME scorch-buffer release.

class BaseHeightMapScorchRef
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
private:
	void freeScorchBuffers(void);
	char m_pad[0xd0];
	BaseHeightMapScorchRef *m_vertexBuffer;
	BaseHeightMapScorchRef *m_indexBuffer;
	TextureBaseClass *m_texture;
};

void BaseHeightMapRenderObjClass::freeScorchBuffers(void)
{
	if (m_vertexBuffer) { m_vertexBuffer->Release_Ref(); m_vertexBuffer = 0; }
	if (m_indexBuffer) { m_indexBuffer->Release_Ref(); m_indexBuffer = 0; }
	if (m_texture) { m_texture->Release_Ref(); m_texture = 0; }
}

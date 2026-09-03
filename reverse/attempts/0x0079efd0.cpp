// ??1WaterRenderObjClass@@QAE@XZ
// partial score=0.8 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// BFME WaterRenderObjClass destructor reconstruction at retail 0x0079EFD0.

class WaterGridRef
{
public:
	virtual void Delete_This(void) = 0;
	int references;
	void Release_Ref(void)
	{
		--references;
		if (references == 0)
			Delete_This();
	}
};

class WaterComRef
{
public:
	virtual void Query(void) = 0;
	virtual void AddRef(void) = 0;
	virtual void __stdcall Release(void) = 0;
};

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class SkyBoxRenderObject
{
public:
	void Release_Ref(void);
};

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

void W3DRadarResetLock(void);
void BFME_DX8_Thread_Assert(void);
class WaterDestructorGuard
{
public:
	~WaterDestructorGuard(void)
	{
		BFME_DX8_Thread_Assert();
	}
};

class WaterRenderObjClass
{
public:
	~WaterRenderObjClass(void);

private:
	unsigned char m_beforeCC[0xcc];
	WaterGridRef *m_gridRef;
	unsigned char m_before124[0x54];
	WaterComRef *m_vertexBuffer;
	WaterComRef *m_indexBuffer;
	unsigned char m_before130[4];
	WaterComRef *m_bumpTexture0;
	WaterComRef *m_bumpTexture1;
	WaterComRef *m_bumpTexture2;
	unsigned char m_before24c[0x110];
	TextureBaseClass *m_reflectionTexture;
	unsigned char m_before254[4];
	SkyBoxRenderObject *m_skyBox;
	unsigned char m_before2b0[0x58];
	WaterComRef *m_waterTexture0;
	WaterComRef *m_waterTexture1;
	WaterComRef *m_waterTexture2;
};

WaterRenderObjClass::~WaterRenderObjClass(void)
{
	W3DRadarResetLock();
	WaterDestructorGuard guard;

	if (m_gridRef != 0) {
		m_gridRef->Release_Ref();
		m_gridRef = 0;
	}

	if (m_vertexBuffer != 0) {
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	if (m_indexBuffer != 0) {
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_reflectionTexture != 0) {
		TextureBaseClass *reflection = m_reflectionTexture;
		if (reflection != 0)
			reflection->Release_Ref();
		m_reflectionTexture = 0;
	}
	if (m_skyBox != 0)
		m_skyBox->Release_Ref();

	if (m_bumpTexture0 != 0) {
		m_bumpTexture0->Release();
		m_bumpTexture0 = 0;
	}
	if (m_bumpTexture1 != 0) {
		m_bumpTexture1->Release();
		m_bumpTexture1 = 0;
	}
	if (m_waterTexture0 != 0) {
		m_waterTexture0->Release();
		m_waterTexture0 = 0;
	}
	if (m_waterTexture2 != 0) {
		m_waterTexture2->Release();
		m_waterTexture2 = 0;
	}
	if (m_waterTexture1 != 0) {
		m_waterTexture1->Release();
		m_waterTexture1 = 0;
	}
	if (m_bumpTexture2 != 0) {
		m_bumpTexture2->Release();
		m_bumpTexture2 = 0;
	}

}

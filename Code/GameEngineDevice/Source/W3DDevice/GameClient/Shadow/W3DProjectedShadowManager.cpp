// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ??0W3DProjectedShadowManager@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
// readable body of ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
// readable body of ?ReAcquireResources@W3DProjectedShadowManager@@QAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
// readable body of ?ReleaseResources@W3DProjectedShadowManager@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
//
// The manager's construction, its list reset, and the two halves of its device
// resource cycle. Four files carried four copies of W3DProjectedShadowManager
// and each could only see what its own body reached: the constructor knew the
// object runs to +0x254 but called its first three fields m_04, m_08 and m_0C;
// removeAllShadows knew those three are the shadow lists but stopped at +0x10;
// ReleaseResources reached +0x24C through a cast on `this`; and
// ReAcquireResources declared no fields at all. 201 lines across four files
// become 175 in one, and the constructor's three anonymous words get the names
// removeAllShadows proves.
//
// The two device buffers live at fixed addresses rather than in the object,
// and the pair is what ties these two bodies together: ReAcquireResources
// creates the index buffer into 0x01306E08 and the vertex buffer into
// 0x01306E04, and ReleaseResources releases and clears exactly those two.

typedef long HRESULT;

// The manager holds no pointer to these: retail addresses both buffers as
// globals, ReAcquireResources filling them and ReleaseResources emptying them.
class ShadowBuffer
{
};

typedef void (__stdcall *ShadowBufferRelease)(ShadowBuffer *);

class W3DShadowContainerShim { public: void release(void); };

#define DEVICE_SLOT(n) virtual void slot##n();

class ShadowDevice
{
public:
	DEVICE_SLOT(0) DEVICE_SLOT(1) DEVICE_SLOT(2) DEVICE_SLOT(3)
	DEVICE_SLOT(4) DEVICE_SLOT(5) DEVICE_SLOT(6) DEVICE_SLOT(7)
	DEVICE_SLOT(8) DEVICE_SLOT(9) DEVICE_SLOT(10) DEVICE_SLOT(11)
	DEVICE_SLOT(12) DEVICE_SLOT(13) DEVICE_SLOT(14) DEVICE_SLOT(15)
	DEVICE_SLOT(16) DEVICE_SLOT(17) DEVICE_SLOT(18) DEVICE_SLOT(19)
	DEVICE_SLOT(20) DEVICE_SLOT(21) DEVICE_SLOT(22) DEVICE_SLOT(23)
	DEVICE_SLOT(24) DEVICE_SLOT(25)
	virtual HRESULT __stdcall createVertexBuffer(unsigned int length, unsigned int usage,
		unsigned int fvf, unsigned int pool, ShadowBuffer **buffer, void *sharedHandle);
	virtual HRESULT __stdcall createIndexBuffer(unsigned int length, unsigned int usage,
		unsigned int format, unsigned int pool, ShadowBuffer **buffer, void *sharedHandle);
};

#undef DEVICE_SLOT

class ShadowLightEnvironment007AF5A0
{
public:
	ShadowLightEnvironment007AF5A0();
	~ShadowLightEnvironment007AF5A0();

private:
	unsigned char m_data[0x228];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadow.h
class W3DProjectedShadow
{
public:
	unsigned char m_head[4];
	bool m_unused;
	unsigned char m_body[0xCF];
	W3DProjectedShadow *m_next;
};

// The walk is a helper rather than three copies of a loop. Written out three
// times the compiler materialises the constants afresh in each; shared, the
// values 0 and 1 are live across all three bodies and earn registers, which is
// what retail holds them in -- edx and bl, with ebx pushed to afford the second.
static void markListUnused(W3DProjectedShadow *shadow)
{
	while (shadow) {
		shadow->m_unused = true;
		shadow = shadow->m_next;
	}
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shadow.h
class ProjectedShadowManager
{
public:
	~ProjectedShadowManager();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadow.h
class W3DProjectedShadowManager : public ProjectedShadowManager
{
public:
	W3DProjectedShadowManager();
	virtual ~W3DProjectedShadowManager();
	void removeAllShadows(void);
	bool ReAcquireResources();
	void ReleaseResources(void);

private:
	// The reference declares two lists, m_shadowList and m_decalList. Retail
	// walks three and takes the one at +0x0C first, so BFME added a list ahead
	// of the pair in processing order but behind them in the layout.
	W3DProjectedShadow *m_shadowList;			// +0x04
	W3DProjectedShadow *m_decalList;			// +0x08
	W3DProjectedShadow *m_simpleDecalList;			// +0x0C
	void *m_10;
	void *m_14;
	void *m_18;
	void *m_1C;
	void *m_20;
	ShadowLightEnvironment007AF5A0 m_lightEnvironment;	// +0x24 .. +0x24B
	W3DShadowContainerShim *m_24C;
	void *m_250;
};

// ??0W3DProjectedShadowManager@@QAE@XZ
W3DProjectedShadowManager::W3DProjectedShadowManager()
{
	m_simpleDecalList = 0;
	m_shadowList = 0;
	m_decalList = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_250 = 0;
	m_24C = 0;
	m_20 = 0;
}

// ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ
void W3DProjectedShadowManager::removeAllShadows(void)
{
	W3DProjectedShadow *shadow;

	shadow = m_simpleDecalList;
	m_simpleDecalList = 0;
	markListUnused(shadow);

	shadow = m_shadowList;
	m_shadowList = 0;
	markListUnused(shadow);

	shadow = m_decalList;
	m_decalList = 0;
	markListUnused(shadow);
}

// ?ReAcquireResources@W3DProjectedShadowManager@@QAE_NXZ
bool W3DProjectedShadowManager::ReAcquireResources()
{
	ShadowDevice *device = *(ShadowDevice **)0x01340534;
	ShadowBuffer **indexBuffer = (ShadowBuffer **)0x01306E08;
	if (device->createIndexBuffer(0x20000, 0x208, 101, 0, indexBuffer, 0) < 0)
		return false;

	if (*(ShadowBuffer **)0x01306E04 == 0
		&& device->createVertexBuffer(0x100000, 0x208, 0, 0,
			(ShadowBuffer **)0x01306E04, 0) < 0)
		return false;

	return true;
}

// ?ReleaseResources@W3DProjectedShadowManager@@QAEXXZ
void W3DProjectedShadowManager::ReleaseResources(void)
{
	W3DShadowContainerShim *container = m_24C;
	container->release();
	ShadowBuffer *first =
		*(ShadowBuffer **)0x01306E08;
	if (first)
		((ShadowBufferRelease)(*(void ***)first)[2])(first);
	ShadowBuffer *second =
		*(ShadowBuffer **)0x01306E04;
	if (second)
		((ShadowBufferRelease)(*(void ***)second)[2])(second);
	*(ShadowBuffer **)0x01306E08 = 0;
	*(ShadowBuffer **)0x01306E04 = 0;
}

// cl: /DNDEBUG /DWIN32 /MD /EHsc

// W3DShadowHelperManager::ReAcquireResources, retail 0x007B9810.
// The constructor at 0x007C10D0 zeros seven fields in the 0x1c-byte object
// allocated at 0x01306F18. The W3DShadowManager constructor calls that
// constructor for its first manager, and its ReAcquireResources wrapper calls
// this body through the same global.

typedef long HRESULT;
typedef bool Bool;

#define TRUE true
#define FALSE false

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock(void) { W3DRadarResetLock(); }
	~BfmeRadarResetLock(void) { W3DRadarResetUnlock(); }
};

class GenAlpha
{
public:
	__declspec(noinline) void h00024D2A(void);
};

class W3DBufferManager
{
public:
	Bool ReAcquireResources(void);
};

class BfmeD3DDevice
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual HRESULT __stdcall CreateVertexBuffer(unsigned length, unsigned usage,
		unsigned fvf, unsigned pool, void **vertexBuffer, void *sharedHandle);
	virtual HRESULT __stdcall CreateIndexBuffer(unsigned length, unsigned usage,
		unsigned format, unsigned pool, void **indexBuffer, void *sharedHandle);
};

extern W3DBufferManager *TheBfmeReleaseOwner; // 0x01306DE8
extern unsigned BfmeShadowIndexCount; // 0x012BBEC4
extern unsigned BfmeShadowVertexCount; // 0x012BBEC0

class W3DShadowHelperManager
{
public:
	Bool ReAcquireResources(void);
};

Bool W3DShadowHelperManager::ReAcquireResources(void)
{
	BfmeRadarResetLock guard;
	reinterpret_cast<GenAlpha *>(this)->h00024D2A();

	BfmeD3DDevice *device = *(BfmeD3DDevice **)0x01340534;
	if (device->CreateIndexBuffer(BfmeShadowIndexCount + BfmeShadowIndexCount,
		0x208, 101, 0,
		(void **)0x01306F20, 0) < 0)
		return FALSE;

	if (*(void **)0x01306F1C == 0)
	{
		if (device->CreateVertexBuffer(BfmeShadowVertexCount * 3 * 4, 0x208, 0, 0,
			(void **)0x01306F1C, 0) < 0)
			return FALSE;
	}

	if (TheBfmeReleaseOwner)
	{
		if (!TheBfmeReleaseOwner->ReAcquireResources())
			return FALSE;
	}

	return TRUE;
}

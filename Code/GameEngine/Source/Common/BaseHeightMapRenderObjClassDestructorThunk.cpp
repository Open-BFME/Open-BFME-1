// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME BaseHeightMapRenderObjClass destructor. This lane-local mirror keeps
// the retail BFME additions (two vector<bool> objects and terrain buffers)
// while leaving the imported ZH header untouched.

void __cdecl bfmeFreeScalar(void *block); // retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes); // retail 0x0082E5F0
void __cdecl operator delete[](void *block); // retail 0x00881EF0

class TextureBaseClass
{
public:
	void Release_Ref(void); // retail 0x009EB7A0
};

class TextureRef
{
public:
	TextureBaseClass *m_ptr;

	~TextureRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
};

class AsciiString;

template <typename T> class StringBase
{
	friend class AsciiString;
	~StringBase(void) {}
	void releaseBuffer(void); // retail 0x00887940
	T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	~AsciiString(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

class BfmeVectorBool
{
public:
	~BfmeVectorBool(void)
	{
		int *start = m_start;
		if (start)
		{
			unsigned int bytes = sizeof(int) * (m_end - start);
			if (bytes > 0x80)
				bfmeFreeScalar(start);
			else
				bfmeDeallocate(start, bytes);
		}
	}

	int *m_start;
	unsigned int m_startBit;
	int *m_finish;
	unsigned int m_finishBit;
	int *m_end;
};

class BfmeVirtualBuffer
{
public:
	virtual ~BfmeVirtualBuffer(void);
};

class Rva006D6FD0
{
public:
	~Rva006D6FD0(void);
};

class W3DWaypointBuffer
{
public:
	~W3DWaypointBuffer(void);
};

class W3DRoadBuffer
{
public:
	~W3DRoadBuffer(void);
};

class W3DBridgeBuffer
{
public:
	~W3DBridgeBuffer(void);
};

class Rva006DED60RoadBuffer
{
public:
	~Rva006DED60RoadBuffer(void);
};

class W3DShroud
{
public:
	~W3DShroud(void);
};

class TaintBuffer
{
public:
	~TaintBuffer(void);
};

struct BfmeArrayElement
{
	int m_value;
};

class BfmeTreeBuffer
{
public:
	virtual ~BfmeTreeBuffer(void);
};

class RenderObjBaseA
{
public:
	virtual ~RenderObjBaseA(void);
	int m_pad;
};

class RenderObjBaseB
{
public:
	virtual ~RenderObjBaseB(void);
};

class RenderObjClass : public RenderObjBaseA, public RenderObjBaseB
{
public:
	virtual ~RenderObjClass(void);
	char m_pad[0xbc];
};

class DX8_CleanupHook
{
public:
	virtual void ReleaseResources(void) = 0;
	virtual void ReAcquireResources(void) = 0;
};

class Snapshot
{
public:
	virtual ~Snapshot(void) {}
};

class BaseHeightMapRenderObjClass
	: public RenderObjClass, public DX8_CleanupHook, public Snapshot
{
public:
	virtual ~BaseHeightMapRenderObjClass(void);
	virtual int freeMapResources(void);

private:
	char m_pad_d0[0x08];
	TextureRef m_textureD8;
	char m_pad_dc_to_3020[0x3020 - 0xdc];
	BfmeVectorBool m_visibleCliff;
	BfmeVectorBool m_impassableCliff;
	char m_pad3048[0x04];
	void *m_resource304c;
	TextureRef m_texture3050;
	TextureRef m_texture3054;
	TextureRef m_texture3058;
	TextureRef m_texture305c;
	TextureRef m_texture3060;
	TextureRef m_texture3064;
	TextureRef m_texture3068;
	char m_pad306c[0x04];
	AsciiString m_string3070;
	AsciiString m_string3074;
	AsciiString m_string3078;
	AsciiString m_string307c;
	AsciiString m_string3080;
	AsciiString m_string3084;
	AsciiString m_string3088;
	AsciiString m_string308c;
	TextureRef m_texture3090;
	BfmeTreeBuffer *m_treeBuffer;
	BfmeVirtualBuffer *m_buffer3098;
	BfmeVirtualBuffer *m_propBuffer;
	Rva006D6FD0 *m_bibBuffer;
	BfmeVirtualBuffer *m_waypointBuffer;
	W3DWaypointBuffer *m_roadBuffer;
	W3DRoadBuffer *m_bridgeBuffer;
	W3DBridgeBuffer *m_shroudBuffer;
	Rva006DED60RoadBuffer *m_buffer30b4;
	W3DShroud *m_buffer30b8;
	TaintBuffer *m_buffer30bc;
	BfmeArrayElement *m_shoreLineTilePositions;
};

// ??1BaseHeightMapRenderObjClass@@UAE@XZ
// Direct member destructor identities follow the existing rows at 0x006DEA80, 0x006D6FD0, 0x00746800, 0x0070FAF0, 0x006D8A80, 0x0071B3D0, and 0x00727380.
BaseHeightMapRenderObjClass::~BaseHeightMapRenderObjClass(void)
{
	freeMapResources();

	if (m_treeBuffer) {
		delete m_treeBuffer;
		m_treeBuffer = 0;
	}
	if (m_buffer30b4) {
		delete m_buffer30b4;
		m_buffer30b4 = 0;
	}
	if (m_buffer3098) {
		delete m_buffer3098;
		m_buffer3098 = 0;
	}
	if (m_propBuffer) {
		delete m_propBuffer;
		m_propBuffer = 0;
	}
	if (m_bibBuffer) {
		delete m_bibBuffer;
		m_bibBuffer = 0;
	}
	if (m_bridgeBuffer) {
		delete m_bridgeBuffer;
		m_bridgeBuffer = 0;
	}
	if (m_shroudBuffer) {
		delete m_shroudBuffer;
	}
	if (m_waypointBuffer) {
		delete m_waypointBuffer;
	}
	if (m_roadBuffer) {
		delete m_roadBuffer;
		m_roadBuffer = 0;
	}
	if (m_buffer30b8) {
		delete m_buffer30b8;
		m_buffer30b8 = 0;
	}
	if (m_buffer30bc) {
		delete m_buffer30bc;
		m_buffer30bc = 0;
	}
	if (m_shoreLineTilePositions) {
		delete [] m_shoreLineTilePositions;
		m_shoreLineTilePositions = 0;
	}
}

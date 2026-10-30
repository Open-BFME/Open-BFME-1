// ?initHeightData@BaseHeightMapRenderObjClass@@UAEHHHPAVWorldHeightMap@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#include <Lib/BaseType.h>
typedef Region2D Rva006D0590Bounds;
class Rva006D0590TreeBoundsView {
public:
    char m_padding[0x1440];
    Rva006D0590Bounds m_at1440;
    void setBounds(const Rva006D0590Bounds &bounds) { m_at1440 = bounds; }
};
typedef int Int;
typedef unsigned short UnsignedShort;

class WorldHeightMap;
template <typename T> class RefMultiListIterator;

#define VIRTUAL_SLOT(n) virtual void slot##n(void);
class VSlots16
{
public:
	VIRTUAL_SLOT(000) VIRTUAL_SLOT(001) VIRTUAL_SLOT(002) VIRTUAL_SLOT(003)
	VIRTUAL_SLOT(004) VIRTUAL_SLOT(005) VIRTUAL_SLOT(006) VIRTUAL_SLOT(007)
	VIRTUAL_SLOT(008) VIRTUAL_SLOT(009) VIRTUAL_SLOT(010) VIRTUAL_SLOT(011)
	VIRTUAL_SLOT(012) VIRTUAL_SLOT(013) VIRTUAL_SLOT(014) VIRTUAL_SLOT(015)
};
class VSlots32 : public VSlots16
{
public:
	VIRTUAL_SLOT(016) VIRTUAL_SLOT(017) VIRTUAL_SLOT(018) VIRTUAL_SLOT(019)
	VIRTUAL_SLOT(020) VIRTUAL_SLOT(021) VIRTUAL_SLOT(022) VIRTUAL_SLOT(023)
	VIRTUAL_SLOT(024) VIRTUAL_SLOT(025) VIRTUAL_SLOT(026) VIRTUAL_SLOT(027)
	VIRTUAL_SLOT(028) VIRTUAL_SLOT(029) VIRTUAL_SLOT(030) VIRTUAL_SLOT(031)
};
class VSlots48 : public VSlots32
{
public:
	VIRTUAL_SLOT(032) VIRTUAL_SLOT(033) VIRTUAL_SLOT(034) VIRTUAL_SLOT(035)
	VIRTUAL_SLOT(036) VIRTUAL_SLOT(037) VIRTUAL_SLOT(038) VIRTUAL_SLOT(039)
	VIRTUAL_SLOT(040) VIRTUAL_SLOT(041) VIRTUAL_SLOT(042) VIRTUAL_SLOT(043)
	VIRTUAL_SLOT(044) VIRTUAL_SLOT(045) VIRTUAL_SLOT(046) VIRTUAL_SLOT(047)
};
class VSlots64 : public VSlots48
{
public:
	VIRTUAL_SLOT(048) VIRTUAL_SLOT(049) VIRTUAL_SLOT(050) VIRTUAL_SLOT(051)
	VIRTUAL_SLOT(052) VIRTUAL_SLOT(053) VIRTUAL_SLOT(054) VIRTUAL_SLOT(055)
	VIRTUAL_SLOT(056) VIRTUAL_SLOT(057) VIRTUAL_SLOT(058) VIRTUAL_SLOT(059)
	VIRTUAL_SLOT(060) VIRTUAL_SLOT(061) VIRTUAL_SLOT(062) VIRTUAL_SLOT(063)
};
class VSlots80 : public VSlots64
{
public:
	VIRTUAL_SLOT(064) VIRTUAL_SLOT(065) VIRTUAL_SLOT(066) VIRTUAL_SLOT(067)
	VIRTUAL_SLOT(068) VIRTUAL_SLOT(069) VIRTUAL_SLOT(070) VIRTUAL_SLOT(071)
	VIRTUAL_SLOT(072) VIRTUAL_SLOT(073) VIRTUAL_SLOT(074) VIRTUAL_SLOT(075)
	VIRTUAL_SLOT(076) VIRTUAL_SLOT(077) VIRTUAL_SLOT(078) VIRTUAL_SLOT(079)
};
class VSlots96 : public VSlots80
{
public:
	VIRTUAL_SLOT(080) VIRTUAL_SLOT(081) VIRTUAL_SLOT(082) VIRTUAL_SLOT(083)
	VIRTUAL_SLOT(084) VIRTUAL_SLOT(085) VIRTUAL_SLOT(086) VIRTUAL_SLOT(087)
	VIRTUAL_SLOT(088) VIRTUAL_SLOT(089) VIRTUAL_SLOT(090) VIRTUAL_SLOT(091)
	VIRTUAL_SLOT(092) VIRTUAL_SLOT(093) VIRTUAL_SLOT(094) VIRTUAL_SLOT(095)
};
class RenderObjClass : public VSlots96
{
public:
	VIRTUAL_SLOT(096) VIRTUAL_SLOT(097) VIRTUAL_SLOT(098) VIRTUAL_SLOT(099)
	VIRTUAL_SLOT(100) VIRTUAL_SLOT(101) VIRTUAL_SLOT(102) VIRTUAL_SLOT(103)
	virtual void Set_Force_Visible(int);
	VIRTUAL_SLOT(105) VIRTUAL_SLOT(106) VIRTUAL_SLOT(107) VIRTUAL_SLOT(108)
	VIRTUAL_SLOT(109) VIRTUAL_SLOT(110) VIRTUAL_SLOT(111) VIRTUAL_SLOT(112)
	VIRTUAL_SLOT(113) VIRTUAL_SLOT(114) VIRTUAL_SLOT(115) VIRTUAL_SLOT(116)
	VIRTUAL_SLOT(117) VIRTUAL_SLOT(118) VIRTUAL_SLOT(119) VIRTUAL_SLOT(120)
	VIRTUAL_SLOT(121) VIRTUAL_SLOT(122) VIRTUAL_SLOT(123) VIRTUAL_SLOT(124)
	VIRTUAL_SLOT(125) VIRTUAL_SLOT(126) VIRTUAL_SLOT(127) VIRTUAL_SLOT(128)
	VIRTUAL_SLOT(129) VIRTUAL_SLOT(130) VIRTUAL_SLOT(131) VIRTUAL_SLOT(132)
};
#undef VIRTUAL_SLOT

class W3DShroud
{
public:
	void init(WorldHeightMap *, float, float);
};

class TaintBuffer
{
public:
	void init(WorldHeightMap *, float, float);
};

class W3DRoadBuffer
{
public:
	void setMap(WorldHeightMap *);
};

class TextureClass
{
public:
	void Release_Ref(void);
};

#include <ascii_string.h>

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	BFMEWaterTrackTextureHandle &operator=(const BFMEWaterTrackTextureHandle &other) {
		if (other.m_texture)
			++*(unsigned short *)((char *)other.m_texture + 4);
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = other.m_texture;
		return *this;
	}

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *, int, int);
extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);
extern void j_00034d56(void);
class GlobalData;
// The defined global is ?TheWritableGlobalData@@3PAVGlobalData@@A (data_rows).
extern GlobalData *TheWritableGlobalData;
extern char *Rva006A16B0Empty;
extern "C" char bfmeTagBNH[];
struct BfmeObjRB;
extern BfmeObjRB *g_bfmeGlobRB;
extern unsigned Rva012BA6DC;
extern void Rva009EBAC0(int);
extern void *bfmeGoEMEb(void *);

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::_Rb_tree<Rva001408C0Key, Rva001408C0Key,
    _STL::_Identity<Rva001408C0Key>, _STL::less<Rva001408C0Key>,
    _STL::allocator<Rva001408C0Key> > Rva006D0590Tree;
class Rva001408C0Set {
public:
    Rva006D0590Tree m_tree;
    unsigned m_at0C;
    bool m_at10;
    Rva001408C0Set() : m_at0C(0), m_at10(true) {}
    void insert(const Rva001408C0Key &value) {
        _STL::pair<Rva006D0590Tree::iterator, bool> result = m_tree.insert_unique(value);
        if (result.second)
            m_at10 = true;
    }
};

class Rva006D6050
{
public:
	void init(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
};

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType);
};

class BaseHeightMapRenderObjClass : public RenderObjClass
{
public:
	virtual Int initHeightData(Int, Int, WorldHeightMap *,
		RefMultiListIterator<RenderObjClass> *);
	virtual Int freeMapResources(void);

	void updateShorelineTiles(Int, Int, Int, Int, WorldHeightMap *);
	void initDestAlphaLUT(void);
private:
	void allocateScorchBuffers(void);
public:
    char m_padding4[0xd8];
    int m_atDC;
    int m_atE0;
    char m_paddingE4[0x2ee4];
    int m_at2FC8;
    char m_padding2FCC[0x28];
    WorldHeightMap * m_map;
    char m_padding2FF8[0x11];
    bool m_at3009;
    char m_padding300A[0x2];
    float m_at300C;
    float m_at3010;
    char m_padding3014[0x8];
    float m_at301C;
    char m_padding3020[0x28];
    void * m_at3048;
    void * m_at304C;
    char m_padding3050[0x8];
    BFMEWaterTrackTextureHandle m_at3058;
    BFMEWaterTrackTextureHandle m_at305C;
    char m_padding3060[0x4];
    BFMEWaterTrackTextureHandle m_at3064;
    BFMEWaterTrackTextureHandle m_at3068;
    char m_padding306C[0x4];
    AsciiString m_at3070;
    AsciiString m_at3074;
    AsciiString m_at3078;
    AsciiString m_at307C;
    AsciiString m_at3080;
    AsciiString m_at3084;
    AsciiString m_at3088;
    AsciiString m_at308C;
    void * m_at3090;
    char m_padding3094[0x4];
    Rva006D0590TreeBoundsView * m_at3098;
    char m_padding309C[0x10];
    W3DRoadBuffer * m_at30AC;
    char m_padding30B0[0x8];
    W3DShroud * m_at30B8;
    TaintBuffer * m_at30BC;
    char m_padding30C0[0x4];
    int m_at30C4;
    char m_padding30C8[0x4];
    float m_at30CC;
    bool m_at30D0;
};

class WorldHeightMap {
public:
    virtual void Delete_This();
    int m_at04;
    int m_width;
    int m_at0C;
    int m_at10;
    char m_padding14[0xc];
    int m_dataSize;
    UnsignedShort *m_data;
    int getXExtent() { return m_width; }
    int getYExtent() { return m_at0C; }
    int getBorderSize() { return m_at10; }
    UnsignedShort getHeight(int x, int y) {
        int index = (y * m_width) + x;
        if ((index >= 0) && (index < m_dataSize) && m_data)
            return m_data[index];
        else
            return 0;
    }
};

template <typename T> static inline T &field(void *object, unsigned offset)
{
	return *(T *)((char *)object + offset);
}

static inline void setMapReference(BaseHeightMapRenderObjClass *object,
	WorldHeightMap *map)
{
	if (map)
		++map->m_at04;

	WorldHeightMap *old = object->m_map;
	if (old && --old->m_at04 == 0) {
		class RefDispatch { public: virtual void Delete_This(void); };
		reinterpret_cast<RefDispatch *>(old)->Delete_This();
	}

	object->m_map = map;
}

static inline void setWaterTrackTexture(TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		destination->Release_Ref();
	destination = texture.m_texture;
}

static inline const char *assetName(const AsciiString &name)
{
	return name.str();
}

static inline Rva001408C0Target *findAsset(const AsciiString &name)
{
	typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *);
	return ((FindPrototypeFn)bfmeGoEMEb)(assetName(name));
}

/** Allocate a heightmap of x by y vertices and fill with initial height values.
Also allocates all rendering resources such as vertex buffers, index buffers, shaders, and materials.*/
Int BaseHeightMapRenderObjClass::initHeightData(Int x, Int y,
	WorldHeightMap *pMap, RefMultiListIterator<RenderObjClass> *)
{
	setMapReference(this, pMap);	//update our heightmap pointer in case it changed since last call.
	m_at30D0 = false;

	W3DShroud *shroud = m_at30B8;
	if (shroud) {
		shroud->init(pMap, field<float>(TheWritableGlobalData, 0x1bc), field<float>(TheWritableGlobalData, 0x1bc));
	}

	TaintBuffer *taint = m_at30BC;
	if (taint) {
		taint->init(m_map, field<float>(TheWritableGlobalData, 0x1bc), field<float>(TheWritableGlobalData, 0x1bc));
	}

	m_at30AC->setMap(
		m_map);

	void *data = 0;
	if (pMap)
		data = pMap->m_data;
	Rva006D0590TreeBoundsView *tree = m_at3098;
	if (tree) {
		Rva006D0590Bounds bounds;
		bounds.lo.x = 0.0f;
		bounds.lo.y = 0.0f;
		bounds.hi.x = (float)(pMap->getXExtent() - 2 * pMap->getBorderSize()) * 10.0f;
		bounds.hi.y = (float)(pMap->getYExtent() - 2 * pMap->getBorderSize()) * 10.0f;
		tree->setBounds(bounds);
	}

	m_at30C4 = 0;
	//Do some preprocessing on map to extract useful data
	if (pMap) {
		//Find min/max values for all terrain heights, useful for rendering optimization
		int width = pMap->getXExtent();
		int height = pMap->getYExtent();
		int minHeight = 0xffff;
		int maxHeight = 0;
		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
				UnsignedShort current = pMap->getHeight(i, j);
				if (current < minHeight)
					minHeight = current;
				if (maxHeight < current)
					maxHeight = current;
			}
		}
		float heightScale = 0.0390625f;
		m_at300C = (float)minHeight * heightScale;
		m_at3010 = (float)maxHeight * heightScale;
		//Find all shoreline tiles so they can get extra alpha blend
		updateShorelineTiles(0, 0, width - 1, height - 1, pMap);
		if (m_at301C != m_at30CC)
			initDestAlphaLUT();
	}

	reinterpret_cast<RenderObjClass *>(this)->Set_Force_Visible(1);	//terrain is always visible.
	m_at3009 = true;
	m_at2FC8 = 0;
	m_atDC = 0;
	m_atE0 = 0;

	// If the textures aren't allocated (usually because of a hardware reset) need to allocate.
	if (data && m_at3090 == 0) {
		//requested heightmap different from old one.
		//allocate a new one.
		freeMapResources();	//free old data and ib/vb
		setMapReference(this, pMap);	//update our heightmap pointer in case it changed since last call.

		{
			AsciiString &string3070 = m_at3070;
			if (!field<void *>(&string3070, 0) || field<unsigned short>(field<void *>(&string3070, 0), 4) == 0)
				string3070.set(m_at3080);
		}
		{
			AsciiString &string3074 = m_at3074;
			if (!field<void *>(&string3074, 0) || field<unsigned short>(field<void *>(&string3074, 0), 4) == 0)
				string3074.set(m_at3084);
		}
		{
			AsciiString &string3078 = m_at3078;
			if (!field<void *>(&string3078, 0) || field<unsigned short>(field<void *>(&string3078, 0), 4) == 0)
				string3078.set(m_at3088);
		}
		{
			AsciiString &string307c = m_at307C;
			if (!field<void *>(&string307c, 0) || field<unsigned short>(field<void *>(&string307c, 0), 4) == 0)
				string307c.set(m_at308C);
		}

		Rva001408C0Set assets;
		{
			AsciiString &string3070 = m_at3070;
			assets.insert(findAsset(string3070));
		}
		{
			AsciiString &string3074 = m_at3074;
			assets.insert(findAsset(string3074));
		}
		{
			AsciiString &string3078 = m_at3078;
			assets.insert(findAsset(string3078));
		}
		{
			AsciiString &string307c = m_at307C;
			assets.insert(findAsset(string307c));
		}
		assets.insert((Rva001408C0Target *)bfmeGoEMEb(bfmeTagBNH));
		Rva009EBAC0((int)&assets);

		{
			AsciiString &string3074 = m_at3074;
			m_at3058 = BFMEGetWaterTrackTexture((char *)assetName(string3074), 0, 0);
		}
		g_bfmeGlobRB = (BfmeObjRB *)&m_at3058;
		{
			AsciiString &string3070 = m_at3070;
			m_at305C = BFMEGetWaterTrackTexture((char *)assetName(string3070), 0, 0);
		}
		W3DRadarResetLock();
		{
			AsciiString &string3078 = m_at3078;
			m_at3064 = BFMEGetWaterTrackTexture((char *)assetName(string3078), 0, 0);
		}
		{
			AsciiString &string307c = m_at307C;
			m_at3068 = BFMEGetWaterTrackTexture((char *)assetName(string307c), 0, 0);
		}

		((Rva006D6050 *)&m_at3090)->init(
			0x100, 1, 0x15, 1, 1, 0);
		initDestAlphaLUT();
		union { void (*f)(); void (BaseHeightMapRenderObjClass::*m)(); } scorchCall;
		scorchCall.f = &j_00034d56;
		(this->*scorchCall.m)();
		allocateScorchBuffers();
		m_at304C =
			VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		m_at3048 = (void *)Rva012BA6DC;	//		ShaderClass::_PresetOpaqueShader;
		bfmeUnlock1179();
	}
	return 0;
}

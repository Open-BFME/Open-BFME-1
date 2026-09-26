// ?initHeightData@BaseHeightMapRenderObjClass@@UAEHHHPAVWorldHeightMap@@PAV?$RefMultiListIterator@VRenderObjClass@@@@_N@Z
// partial score=0.25 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

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

class AsciiString
{
public:
	void set(const AsciiString &other);

	char *m_data;
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

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
extern void Rva009EBAC0(int);
extern void *bfmeGoEMEb(void *);

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

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
	void allocateScorchBuffers(void);
};

class WorldHeightMap
{
};

template <typename T> static inline T &field(void *object, unsigned offset)
{
	return *(T *)((char *)object + offset);
}

static inline void setMapReference(BaseHeightMapRenderObjClass *object,
	WorldHeightMap *map)
{
	if (map)
		++field<int>(map, 4);

	WorldHeightMap *old = field<WorldHeightMap *>(object, 0x2ff4);
	if (old && --field<int>(old, 4) == 0) {
		class RefDispatch { public: virtual void Delete_This(void); };
		reinterpret_cast<RefDispatch *>(old)->Delete_This();
	}

	field<WorldHeightMap *>(object, 0x2ff4) = map;
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
	return name.m_data ? name.m_data + 8 : (const char *)0x0107388b;
}

static inline Rva001408C0Target *findAsset(const AsciiString &name)
{
	typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *);
	return ((FindPrototypeFn)bfmeGoEMEb)(assetName(name));
}

Int BaseHeightMapRenderObjClass::initHeightData(Int x, Int y,
	WorldHeightMap *pMap, RefMultiListIterator<RenderObjClass> *)
{
	setMapReference(this, pMap);
	field<unsigned char>(this, 0x30d0) = 0;

	W3DShroud *shroud = field<W3DShroud *>(this, 0x30b8);
	if (shroud) {
		float partition = *(float *)((char *)*(void **)0x012ed5c8 + 0x1bc);
		shroud->init(pMap, partition, partition);
	}

	TaintBuffer *taint = field<TaintBuffer *>(this, 0x30bc);
	if (taint) {
		float partition = *(float *)((char *)*(void **)0x012ed5c8 + 0x1bc);
		taint->init(field<WorldHeightMap *>(this, 0x2ff4), partition,
			partition);
	}

	field<W3DRoadBuffer *>(this, 0x30ac)->setMap(
		field<WorldHeightMap *>(this, 0x2ff4));

	void *data = pMap ? field<void *>(pMap, 0x24) : 0;
	void *tree = field<void *>(this, 0x3098);
	if (tree) {
		int border = field<int>(pMap, 0x10);
		int width = field<int>(pMap, 8) - 2 * border;
		int height = field<int>(pMap, 0xc) - 2 * border;
		float scale = *(float *)0x01075c74;
		field<float>(tree, 0x1440) = 0.0f;
		field<float>(tree, 0x1444) = 0.0f;
		field<float>(tree, 0x1448) = (float)width * scale;
		field<float>(tree, 0x144c) = (float)height * scale;
	}

	field<int>(this, 0x30c4) = 0;
	if (pMap) {
		int width = field<int>(pMap, 8);
		int height = field<int>(pMap, 0xc);
		int dataSize = field<int>(pMap, 0x20);
		int minHeight = 0xffff;
		int maxHeight = 0;
		int index = 0;
		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i, ++index) {
				UnsignedShort current = 0;
				if (index >= 0 && index < dataSize && data)
					current = ((UnsignedShort *)data)[index];
				if (current < minHeight)
					minHeight = current;
				if (maxHeight < current)
					maxHeight = current;
			}
		}
		float heightScale = *(float *)0x010f653c;
		field<float>(this, 0x300c) = (float)minHeight * heightScale;
		field<float>(this, 0x3010) = (float)maxHeight * heightScale;
		updateShorelineTiles(0, 0, width - 1, height - 1, pMap);
		if (field<float>(this, 0x30cc) != field<float>(this, 0x301c))
			initDestAlphaLUT();
	}

	reinterpret_cast<RenderObjClass *>(this)->Set_Force_Visible(1);
	field<unsigned char>(this, 0x3009) = 1;
	field<int>(this, 0x2fc8) = 0;
	field<int>(this, 0xdc) = 0;
	field<int>(this, 0xe0) = 0;

	if (data && field<void *>(this, 0x3090) == 0) {
		freeMapResources();
		setMapReference(this, pMap);

		AsciiString &string3070 = field<AsciiString>(this, 0x3070);
		AsciiString &string3074 = field<AsciiString>(this, 0x3074);
		AsciiString &string3078 = field<AsciiString>(this, 0x3078);
		AsciiString &string307c = field<AsciiString>(this, 0x307c);
		if (!string3070.m_data || *(unsigned short *)(string3070.m_data + 4) == 0)
			string3070.set(field<AsciiString>(this, 0x3080));
		if (!string3074.m_data || *(unsigned short *)(string3074.m_data + 4) == 0)
			string3074.set(field<AsciiString>(this, 0x3084));
		if (!string3078.m_data || *(unsigned short *)(string3078.m_data + 4) == 0)
			string3078.set(field<AsciiString>(this, 0x3088));
		if (!string307c.m_data || *(unsigned short *)(string307c.m_data + 4) == 0)
			string307c.set(field<AsciiString>(this, 0x308c));

		Rva001408C0Set assets;
		assets.insert(findAsset(string3070));
		assets.insert(findAsset(string3074));
		assets.insert(findAsset(string3078));
		assets.insert(findAsset(string307c));
		assets.insert((Rva001408C0Target *)0x0111dc1c);
		Rva009EBAC0((int)&assets);

		setWaterTrackTexture(field<TextureClass *>(this, 0x3058),
			BFMEGetWaterTrackTexture((char *)assetName(string3074), 0, 0));
		setWaterTrackTexture(field<TextureClass *>(this, 0x305c),
			BFMEGetWaterTrackTexture((char *)assetName(string3070), 0, 0));
		W3DRadarResetLock();
		setWaterTrackTexture(field<TextureClass *>(this, 0x3064),
			BFMEGetWaterTrackTexture((char *)assetName(string3078), 0, 0));
		setWaterTrackTexture(field<TextureClass *>(this, 0x3068),
			BFMEGetWaterTrackTexture((char *)assetName(string307c), 0, 0));

		((Rva006D6050 *)((char *)this + 0x3090))->init(
			0x100, 1, 0x15, 1, 1, 0);
		initDestAlphaLUT();
		allocateScorchBuffers();
		allocateScorchBuffers();
		field<void *>(this, 0x304c) =
			VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		field<void *>(this, 0x3048) = *(void **)0x012ba6dc;
		bfmeUnlock1179();
	}
	return 0;
}

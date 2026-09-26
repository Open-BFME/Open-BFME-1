// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct SceneVectorElement
{
	int m_value;
};

template class _STL::vector<SceneVectorElement>;

template <class T> struct StringInlineData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	void set(const StringBase<T> &other);
	void releaseBuffer();
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() { releaseBuffer(); }
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();

private:
	unsigned char m_pad[0x104];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	void setName(AsciiString name) { m_name = name; }

private:
	AsciiString m_name;
};

struct BfmeSceneListNode
{
	void *m_prev;
	void *m_next;
	void *m_nextList;
	void *m_objectLink;
	void *m_list;
};

class BfmeRefSceneList
{
public:
	BfmeRefSceneList()
	{
		volatile BfmeSceneListNode *head = &m_head;
		head->m_nextList = 0;
		head->m_next = 0;
		head->m_prev = 0;
		head->m_objectLink = 0;
		head->m_list = 0;
		head->m_prev = (void *)head;
		m_head.m_next = &m_head;
		m_head.m_objectLink = 0;
		m_head.m_nextList = 0;
		m_vtable = 0x01120A4C;
	}
	~BfmeRefSceneList();

private:
	unsigned int m_vtable;
	BfmeSceneListNode m_head;
};

class LightEnvironmentClass
{
public:
	LightEnvironmentClass();
	~LightEnvironmentClass();

private:
	unsigned char m_data[0x228];
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	int NumRefs;

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}
};

class LightClass
{
public:
	enum LightType { DIRECTIONAL = 1 };
	LightClass(LightType type);
	virtual ~LightClass();

private:
	unsigned char m_data[0x120];
};

class RenderObjClass;

class MapObject
{
public:
	virtual ~MapObject();
	void setRenderObj(RenderObjClass *object);
};

class ShaderClass
{
	public:
	enum SrcBlendFuncType { SRCBLEND_SRC_ALPHA = 2 };
	enum DstBlendFuncType { DSTBLEND_ONE_MINUS_SRC_ALPHA = 3 };
	unsigned int m_bits;
	ShaderClass() {}
	ShaderClass(const ShaderClass &other) : m_bits(other.m_bits) {}
	ShaderClass(unsigned int bits) : m_bits(bits) {}
	ShaderClass &operator=(const ShaderClass &other)
	{
		m_bits = other.m_bits;
		return *this;
	}

	void Set_Src_Blend_Func(SrcBlendFuncType value)
	{
		m_bits &= ~5U;
		m_bits |= value;
	}

	void Set_Dst_Blend_Func(DstBlendFuncType value)
	{
		m_bits &= ~12U;
		m_bits |= value;
	}
};

static ShaderClass PlayerColorShader;

class MaterialPassClass : public MapObject
{
public:
	MaterialPassClass();
	virtual ~MaterialPassClass();
	void Set_Shader(ShaderClass shader);

private:
	unsigned char m_data[0x34];
};

class BfmeShroudMaterialPassClass : public MaterialPassClass
{
public:
	BfmeShroudMaterialPassClass() : MaterialPassClass(), m_flag(0) {}

private:
	unsigned char m_flag;
};

class VertexMaterialClass : public RefCountClass
{
public:
	VertexMaterialClass();
	void Set_Ambient(float red, float green, float blue);
	void Set_Diffuse(float red, float green, float blue);
	void Set_Emissive(float red, float green, float blue);
	void Set_Lighting(bool value)
	{
		m_crcDirty = true;
		m_useLighting = value;
	}

private:
	unsigned char m_data[0x60];
	bool m_crcDirty;
	bool m_useLighting;
	unsigned char m_pad[2];
};

class GlobalData
{
	unsigned char m_pad[0xa44];

public:
	int m_maxVisibleTranslucentObjects;
	int m_potentialOccludersCount;
	int m_potentialOccludeesCount;
	int m_nonOccludersCount;
};

#define TheWritableGlobalData (*(GlobalData **)0x012ED5C8)

class RTS3DScene : public SimpleSceneClass, public SubsystemInterface
{
public:
	RTS3DScene();
	virtual ~RTS3DScene();

private:
	BfmeRefSceneList m_dynamicLightList;
	volatile bool m_drawTerrainOnly;
	unsigned char m_headerPad[3];
	LightClass * volatile m_globalLight[4];
	LightClass *m_scratchLight;
	int m_infantryAmbient[3];
	LightClass * volatile m_infantryLight[4];
	volatile int m_numGlobalLights;
	LightEnvironmentClass m_defaultLightEnvironment;
	LightEnvironmentClass m_foggedLightEnvironment;
	LightEnvironmentClass m_ambientLightEnvironment;
	volatile bool m_passFlag;
	unsigned char m_passPad[3];
	MaterialPassClass *m_shroudMaterialPass;
	MaterialPassClass *m_maskMaterialPass;
	MaterialPassClass *m_heatVisionMaterialPass;
	MaterialPassClass *m_occludedMaterialPass[32];
	int m_occludedObjectsCount;
	int m_translucentObjectsCount;
	void **m_translucentObjectsBuffer;
	void *m_reserved;
	void *m_potentialOccluders;
	void *m_potentialOccludees;
	void *m_nonOccludersOrOccludees;
	int m_potentialOccludersCount;
	int m_potentialOccludeesCount;
	int m_nonOccluderOrOccludeeCount;
	_STL::vector<SceneVectorElement> m_sceneVector;
	void *m_camera;
};

RTS3DScene::RTS3DScene()
{
	setName("RTS3DScene");
	m_drawTerrainOnly = false;
	m_numGlobalLights = 0;
	m_passFlag = true;
	m_globalLight[0] = 0;
	m_infantryLight[0] = 0;
	m_globalLight[1] = 0;
	m_infantryLight[1] = 0;
	m_globalLight[2] = 0;
	m_infantryLight[2] = 0;
	m_globalLight[3] = 0;
	m_infantryLight[3] = 0;
	_ReadWriteBarrier();
	m_infantryAmbient[0] = 0;
	m_infantryAmbient[1] = 0;
	m_infantryAmbient[2] = 0;

	m_scratchLight = new LightClass(LightClass::DIRECTIONAL);
	m_shroudMaterialPass = new BfmeShroudMaterialPassClass();
	m_occludedObjectsCount = 0;
	m_maskMaterialPass = new MaterialPassClass();
	m_heatVisionMaterialPass = new MaterialPassClass();

	VertexMaterialClass *vertexMaterial = new VertexMaterialClass();
	vertexMaterial->Set_Lighting(true);
	vertexMaterial->Set_Ambient(0.0f, 0.0f, 0.0f);
	vertexMaterial->Set_Diffuse(0.02f, 0.01f, 0.0f);
	vertexMaterial->Set_Emissive(0.5f, 0.2f, 0.0f);
	m_maskMaterialPass->setRenderObj((RenderObjClass *)vertexMaterial);
	ShaderClass shader = PlayerColorShader;
	shader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_SRC_ALPHA);
	m_maskMaterialPass->Set_Shader(shader);
	vertexMaterial->Release_Ref();
	m_heatVisionMaterialPass->setRenderObj((RenderObjClass *)vertexMaterial);
	shader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);
	m_heatVisionMaterialPass->Set_Shader(shader);

	m_translucentObjectsCount = 0;
	GlobalData *global_data = TheWritableGlobalData;
	int translucent_count = 0;
	if (global_data)
		translucent_count = global_data->m_maxVisibleTranslucentObjects;
	if (translucent_count)
		m_translucentObjectsBuffer = new void *[translucent_count];
	else
		m_translucentObjectsBuffer = 0;

	m_potentialOccludersCount = 0;
	m_potentialOccludeesCount = 0;
	m_nonOccluderOrOccludeeCount = 0;
	m_reserved = 0;
	m_potentialOccluders = 0;
	m_potentialOccludees = 0;
	m_nonOccludersOrOccludees = 0;
	m_potentialOccluders = new void *[TheWritableGlobalData->m_potentialOccludersCount];
	m_potentialOccludees = new void *[TheWritableGlobalData->m_potentialOccludeesCount];
	m_nonOccludersOrOccludees = new void *[TheWritableGlobalData->m_nonOccludersCount];

	for (int i = 0; i < 32; ++i)
		m_occludedMaterialPass[i] = 0;
	m_camera = 0;
}

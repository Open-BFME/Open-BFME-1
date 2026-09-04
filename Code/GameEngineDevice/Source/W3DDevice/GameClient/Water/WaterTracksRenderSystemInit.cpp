// cl: /DNDEBUG /MD
// Retail 0x007AB9A0: WaterTracksRenderSystem::init.
//
// This TU keeps the BFME global and WaterTracksObj layouts local.  The retail
// body calls the separately emitted track-object constructor and uses the
// BFME water-level field at TheGlobalData+0x7c.

typedef unsigned int UnsignedInt;

class ShaderClass
{
public:
    static ShaderClass _PresetAlphaShader;

    UnsignedInt m_bits;

    inline void Set_Cull_Mode(void)
    {
        m_bits &= 0xffefffff;
    }
};

class VertexMaterialClass
{
public:
    enum PresetType
    {
        PRESET_ALPHA = 0
    };

    static VertexMaterialClass *Get_Preset(PresetType preset);
};

class WaterTracksObjInitShim
{
public:
	WaterTracksObjInitShim *construct(void);

	unsigned char m_beforeLinks[0xb0];
	WaterTracksObjInitShim *m_next;
	WaterTracksObjInitShim *m_prev;

	private:
};

extern void *TheGlobalData;
extern void *operator new(unsigned int size);

class WaterTracksRenderSystemInitShim
{
public:
	void ReAcquireResources(void);
	void init(void);

private:
	unsigned char m_beforeMaterial[8];
	VertexMaterialClass *m_vertexMaterialClass;
    ShaderClass m_shaderClass;
	WaterTracksObjInitShim *m_usedModules;
	WaterTracksObjInitShim *m_freeModules;
	int m_stripSizeX;
	int m_stripSizeY;
	int m_batchStart;
	float m_level;
};

void WaterTracksRenderSystemInitShim::init(void)
{
	m_stripSizeX = 2;
	m_stripSizeY = 2;
	m_level = *(float *)((unsigned char *)TheGlobalData + 0x7c);
	ReAcquireResources();
    m_vertexMaterialClass = VertexMaterialClass::Get_Preset((VertexMaterialClass::PresetType)0);

    m_shaderClass = ShaderClass::_PresetAlphaShader;
    m_shaderClass.Set_Cull_Mode();

	if (m_freeModules || m_usedModules)
		return;

	WaterTracksObjInitShim *mod;
	int i = 0;
	while (i < 2000)
	{
		mod = (WaterTracksObjInitShim *)operator new(0xb8);
		if (!mod)
			break;
		mod = mod->construct();
		if (!mod)
			break;

		mod->m_prev = 0;
		mod->m_next = m_freeModules;
		if (m_freeModules)
			m_freeModules->m_prev = mod;
		++i;
		m_freeModules = mod;
	}
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Clean BFME layout for the RTS3DScene destructor at retail RVA 0x00713510.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct SceneVectorElement
{
	int m_value;
};

template class _STL::vector<SceneVectorElement>;

class RefCountClass
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

class SimpleSceneClass
{
public:
	virtual ~SimpleSceneClass();

private:
	unsigned char m_pad[0x104];
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	unsigned char m_name[4];
};

class BfmeRefSceneList
{
public:
	virtual ~BfmeRefSceneList();

private:
	unsigned char m_nodes[0x14];
};

class Gen_uw_0094a880
{
public:
	~Gen_uw_0094a880();

private:
	unsigned char m_data[0x228];
};

class RTS3DScene : public SimpleSceneClass, public SubsystemInterface
{
public:
	virtual ~RTS3DScene();

private:
	BfmeRefSceneList m_dynamicLightList;
	unsigned char m_header[4];
	RefCountClass *m_globalLight[4];
	RefCountClass *m_scratchLight;
	unsigned char m_infantryAmbient[0xc];
	RefCountClass *m_infantryLight[4];
	int m_numGlobalLights;
	Gen_uw_0094a880 m_defaultLightEnvironment;
	Gen_uw_0094a880 m_foggedLightEnvironment;
	Gen_uw_0094a880 m_ambientLightEnvironment;
	unsigned char m_passFlag;
	unsigned char m_passPad[3];
	RefCountClass *m_shroudMaterialPass;
	RefCountClass *m_maskMaterialPass;
	RefCountClass *m_heatVisionMaterialPass;
	RefCountClass *m_occludedMaterialPass[32];
	int m_occludedObjectsCount;
	int m_potentialOccludersCount;
	void **m_translucentObjectsBuffer;
	void *m_reserved;
	void *m_potentialOccluders;
	void *m_potentialOccludees;
	void *m_nonOccludersOrOccludees;
	int m_translucentObjectsCount;
	int m_occludedObjectsCapacity;
	int m_nonOccluderOrOccludeeCount;
	_STL::vector<SceneVectorElement> m_sceneVector;
	void *m_camera;
};

RTS3DScene::~RTS3DScene()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_globalLight[i])
		{
			m_globalLight[i]->Release_Ref();
			m_globalLight[i] = 0;
		}
		if (m_infantryLight[i])
		{
			m_infantryLight[i]->Release_Ref();
			m_infantryLight[i] = 0;
		}
	}

	if (m_scratchLight)
	{
		m_scratchLight->Release_Ref();
		m_scratchLight = 0;
	}

	if (m_shroudMaterialPass)
	{
		m_shroudMaterialPass->Release_Ref();
		m_shroudMaterialPass = 0;
	}
	if (m_maskMaterialPass)
	{
		m_maskMaterialPass->Release_Ref();
		m_maskMaterialPass = 0;
	}
	if (m_heatVisionMaterialPass)
	{
		m_heatVisionMaterialPass->Release_Ref();
		m_heatVisionMaterialPass = 0;
	}

	if (m_translucentObjectsBuffer)
		delete [] m_translucentObjectsBuffer;
	if (m_nonOccludersOrOccludees)
		delete [] m_nonOccludersOrOccludees;
	if (m_potentialOccludees)
		delete [] m_potentialOccludees;
	if (m_potentialOccluders)
		delete [] m_potentialOccluders;

	for (int i = 0; i < 32; ++i)
	{
		if (m_occludedMaterialPass[i])
		{
			m_occludedMaterialPass[i]->Release_Ref();
			m_occludedMaterialPass[i] = 0;
		}
	}
}

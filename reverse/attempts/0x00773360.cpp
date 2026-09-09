// ??0W3DScriptedModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.35 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC
// stlport
// BFME W3DScriptedModelDraw constructor, retail 0x00773360 (1185B).
//
// This is the BFME-sized W3D model-draw base used by the scripted and vehicle
// draw modules.  The public ZH header stops at the first few pointers; the
// member ordering below follows the retail constructor/destructor packet:
// intrusive particle tracker list at +0x48, tree at +0x8c, four 12-byte
// recoil vectors at +0xac, three slot records at +0xdc, the ten-dword zero
// packet at +0x148, decal pairs at +0x178/+0x1bc and the two layout strings at
// +0x200.

#include <list>
#include <set>
#include <vector>
#include <stddef.h>

typedef bool Bool;
typedef int ParticleSystemID;

class Thing;
class ModuleData;

class DrawModule
{
public:
	DrawModule(Thing *, const ModuleData *);
	virtual void drawModuleAnchor();

private:
	unsigned char m_data[8];
};

class W3DModelDrawInterface
{
public:
	virtual void w3dModelDrawInterfaceAnchor();
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle() throw(...)
		: m_system(0), m_previous(0), m_next(0)
	{
	}

	~BfmeParticleSystemHandle() throw();

	void *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

// The three opaque members use the existing unwind pins.  They are each three
// dwords in this object; the retail constructor's explicit stores prove that
// shape even though their gameplay names are not needed here.
class Gen_uwm_00034329
{
public:
	Gen_uwm_00034329() : m_00(0), m_04(0), m_08(0) {}
	~Gen_uwm_00034329();

	int m_00;
	int m_04;
	int m_08;
};

class Gen_uwm_0000b073
{
public:
	Gen_uwm_0000b073() : m_00(0), m_04(0), m_08(0) {}
	~Gen_uwm_0000b073();

	int m_00;
	int m_04;
	int m_08;
};

class Gen_uwm_0000b109
{
public:
	Gen_uwm_0000b109() : m_00(0), m_04(0), m_08(0) {}
	~Gen_uwm_0000b109();

	int m_00;
	int m_04;
	int m_08;
};

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString();
	void set(const char *, int);
	void releaseBuffer();

	char *m_data;
};

class RadiusDecal
{
public:
	RadiusDecal();
	~RadiusDecal();

	unsigned char m_data[0x10];
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();

	unsigned char m_data[0x34];
};

// The retail callbacks at ILT 0x3e94b/0x35972 construct and destroy a
// three-dword value.  Keeping this as a POD-shaped non-trivial element lets
// STLport's vector-constructor helper supply the same four-element EH packet.
struct Gen_p12cd
{
public:
	int m_00;
	int m_04;
	int m_08;
};

// updateSubObjectsFromShroud proves that the first payload dword at list-node
// +0x08 is a ParticleSystemID.  Retail's constructor allocates 0x1c-byte list
// nodes, so the BFME tracker payload is 20 bytes (the links consume 8 bytes).
// The remaining four dwords have no independent identity in this constructor;
// keep them opaque until a tracker body proves their meaning.
struct BfmeParticleSystemTracker
{
	ParticleSystemID m_id;
	unsigned char m_opaque[16];
};

class BfmeZeroFields10
{
public:
	BfmeZeroFields10()
	{
		m_00 = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_10 = 0;
		m_14 = 0;
		m_18 = 0;
		m_1c = 0;
		m_20 = 0;
		m_24 = 0;
	}

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
};

struct BfmeSlot
{
	BfmeSlot() : m_head(0) {}

	int m_head;
	int m_pad[6];
};

class Drawable
{
public:
	const float *getTransformMatrix() const;

	unsigned char m_data[0xfc];
	void *m_object;
};

class Object
{
public:
	int getNightIndicatorColor() const;
	int getIndicatorColor() const;
};

class GlobalData
{
public:
	unsigned char m_data[0x218];
	int m_timeOfDay;
};

class GameLODManager
{
public:
	unsigned char m_data[0x16c4];
	int m_level;
};

extern GlobalData *TheWritableGlobalData;
extern GameLODManager *TheGameLODManager;

class W3DScriptedModelDraw : public DrawModule, public W3DModelDrawInterface
{
public:
	W3DScriptedModelDraw(Thing *, const ModuleData *);

	// This is a local ABI probe; keeping the packet public lets the compile-time
	// checks below reject an accidental STL layout drift.
	public:
	void *m_state10;
	void *m_state14;
	BfmeParticleSystemHandle m_particleHandle;
	int m_indicatorColor;
	int m_modelCondition;
	Bool m_hidden;
	Bool m_fullyObscuredByShroud;
	Bool m_isHidden;
	Bool m_hasShadow;
	Bool m_hasTerrainDecal;
	unsigned char m_pad31[3];
	void *m_renderObject;
	RetailLayoutString m_modelName;
	void *m_shadow;
	void *m_terrainDecal;
	void *m_trackRenderObject;
	_STL::list<BfmeParticleSystemTracker> m_particleSystemIDs;
	Gen_uwm_00034329 m_member4c;
	Gen_uwm_00034329 m_member58;
	Bool m_ready;
	Bool m_ready2;
	Bool m_ready3;
	Bool m_ready4;
	int m_flag68;
	int m_field6c;
	float m_field70;
	int m_field74;
	float m_field78;
	float m_field7c;
	float m_field80;
	Bool m_field84;
	int m_field88;
	_STL::set<int> m_tree;
	RetailLayoutString m_string98;
	int m_field9c;
	int m_lodResult;
	int m_lodResult2;
	int m_fielda8;
	_STL::vector<Gen_p12cd> m_recoil[4];
	BfmeSlot m_slots[3];
	Gen_uwm_0000b073 m_field130;
	Gen_uwm_0000b109 m_field13c;
	BfmeZeroFields10 m_zero148;
	Bool m_field170;
	Bool m_field171;
	Bool m_field172;
	Bool m_field173;
	int m_field174;
	RadiusDecal m_radiusDecal;
	RadiusDecalTemplate m_radiusDecalTemplate;
	RadiusDecal m_radiusDecal2;
	RadiusDecalTemplate m_radiusDecalTemplate2;
	RetailLayoutString m_string200;
	RetailLayoutString m_strings[2];
	int m_field20c;
	Bool m_field210;
	unsigned char m_pad211[3];
	int m_field214;
	int m_field218;
	int m_field21c;
	unsigned char m_pad220[0xc];
	int m_field22c;
	Bool m_field230;
	Bool m_field231;
	Bool m_field232;
	unsigned char m_pad233;
	float m_matrix[13];
	int m_field268;
	float m_bounds[4];
};

typedef char W3DScriptedModelDraw_size_check
	[(sizeof(W3DScriptedModelDraw) == 0x27c) ? 1 : -1];
typedef char W3DScriptedModelDraw_handle_check
	[(offsetof(W3DScriptedModelDraw, m_particleHandle) == 0x18) ? 1 : -1];
typedef char W3DScriptedModelDraw_list_check
	[(offsetof(W3DScriptedModelDraw, m_particleSystemIDs) == 0x48) ? 1 : -1];
typedef char W3DScriptedModelDraw_tree_check
	[(offsetof(W3DScriptedModelDraw, m_tree) == 0x8c) ? 1 : -1];
typedef char W3DScriptedModelDraw_recoil_check
	[(offsetof(W3DScriptedModelDraw, m_recoil) == 0xac) ? 1 : -1];
typedef char W3DScriptedModelDraw_decal_check
	[(offsetof(W3DScriptedModelDraw, m_radiusDecal) == 0x178) ? 1 : -1];
typedef char W3DScriptedModelDraw_strings_check
	[(offsetof(W3DScriptedModelDraw, m_string200) == 0x200) ? 1 : -1];
typedef char W3DScriptedModelDraw_string_array_check
	[(offsetof(W3DScriptedModelDraw, m_strings) == 0x204) ? 1 : -1];
typedef char BfmeParticleSystemTracker_size_check
	[(sizeof(BfmeParticleSystemTracker) == 0x14) ? 1 : -1];
typedef char W3DScriptedModelDraw_zero_packet_check
	[(offsetof(W3DScriptedModelDraw, m_zero148) == 0x148) ? 1 : -1];

// ??0W3DScriptedModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DScriptedModelDraw::W3DScriptedModelDraw(Thing *thing,
	const ModuleData *moduleData)
	: DrawModule(thing, moduleData)
	, m_particleHandle()
	, m_modelName()
	, m_particleSystemIDs()
	, m_member4c()
	, m_member58()
	, m_tree()
	, m_string98()
	, m_recoil()
	, m_slots()
	, m_field130()
	, m_field13c()
	, m_zero148()
	, m_radiusDecal()
	, m_radiusDecalTemplate()
	, m_radiusDecal2()
	, m_radiusDecalTemplate2()
	, m_string200()
	, m_strings()
{
	m_modelName.set("", 0);
	m_flag68 = 1;
	m_ready = true;
	m_ready2 = false;
	m_state14 = 0;
	m_state10 = 0;
	m_indicatorColor = 0;
	m_renderObject = 0;
	m_shadow = 0;
	m_isHidden = true;
	m_hasShadow = false;
	m_hasTerrainDecal = false;
	m_fullyObscuredByShroud = false;
	m_terrainDecal = 0;
	m_trackRenderObject = 0;
	m_modelCondition = -1;
	m_hidden = false;
	extern int g_Va012F8064;
	m_field9c = ~g_Va012F8064;
	m_field84 = true;
	m_field88 = 0;
	m_field170 = false;
	m_field171 = false;
	m_field172 = false;
	m_field6c = 0;
	m_field74 = 0;
	m_field78 = 1.0f;
	m_field7c = 1.0f;
	m_field80 = 1.0f;
	m_field70 = 0.0f;
	m_lodResult = 0;
	m_lodResult2 = 0;
	m_fielda8 = 5;
	m_string200.releaseBuffer();
	for (int i = 0; i < 2; ++i)
		m_strings[i].releaseBuffer();
	m_field20c = 0;
	m_field22c = 0;
	m_field210 = false;
	m_field214 = 0;
	m_field218 = 0;
	m_field21c = 0;
	*((unsigned char *)this + 0x1fc) = 1;
	m_field230 = false;
	m_field231 = true;
	m_field232 = false;
	m_field268 = -1;
	m_bounds[0] = -9999.0f;
	m_bounds[1] = -9999.0f;
	m_bounds[2] = -9999.0f;
	m_bounds[3] = -9999.0f;

	Drawable *drawable = *(Drawable **)((unsigned char *)this + 8);
	if (drawable)
	{
		Object *object = (Object *)drawable->m_object;
		if (object)
		{
			if (TheWritableGlobalData->m_timeOfDay == 4)
				m_indicatorColor = object->getNightIndicatorColor();
			else
				m_indicatorColor = object->getIndicatorColor();
		}
	}

	if (*(ModuleData **)((unsigned char *)this + 4) && drawable)
	{
		unsigned char *module = *(unsigned char **)((unsigned char *)this + 4);
		unsigned char *draw = (unsigned char *)drawable;
		draw[0xe4] = module[0x10d];
		*(int *)(draw + 0xe8) = *(int *)(module + 0x110);
		*(int *)(draw + 0xec) = *(int *)(module + 0x114);
	}

	if (drawable)
	{
		const float *matrix = drawable->getTransformMatrix();
		m_matrix[0] = matrix[0];
		m_matrix[1] = matrix[1];
		m_matrix[2] = matrix[2];
		m_matrix[3] = matrix[3];
		m_matrix[4] = matrix[4];
		m_matrix[5] = matrix[5];
		m_matrix[6] = matrix[6];
		m_matrix[7] = matrix[7];
		m_matrix[8] = matrix[8];
		m_matrix[9] = matrix[9];
		m_matrix[10] = matrix[10];
		m_matrix[11] = matrix[11];
		m_matrix[12] = 1.0f;
	}
	else
	{
		m_matrix[1] = 0.0f;
		m_matrix[2] = 0.0f;
		m_matrix[3] = 0.0f;
		m_matrix[0] = 1.0f;
		m_matrix[4] = 0.0f;
		m_matrix[5] = 1.0f;
		m_matrix[6] = 0.0f;
		m_matrix[7] = 0.0f;
		m_matrix[8] = 0.0f;
		m_matrix[9] = 0.0f;
		m_matrix[10] = 1.0f;
		m_matrix[11] = 0.0f;
		m_matrix[12] = 1.0f;
	}

	int level = TheGameLODManager->m_level;
	switch (level)
	{
	case 0:
	case 1:
		m_lodResult = 2;
		break;
	case 2:
		m_lodResult = 1;
		break;
	default:
		m_lodResult = 0;
		break;
	}
}

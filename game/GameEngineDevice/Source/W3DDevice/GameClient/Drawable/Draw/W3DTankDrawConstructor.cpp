// cl: /DNDEBUG /MD /EHsc
// BFME W3DTankDraw constructor at retail 0x0077F050.
//
// The shipped ZH header describes a shorter W3DModelDraw subobject.  The
// constructor's own retail stores prove the BFME dual-vtable base and the
// two intrusive particle handles, so this TU keeps that ABI view local.

typedef bool Bool;

class Thing;
class ModuleData;

class DrawModule
{
public:
	virtual void drawModuleAnchor();

private:
	unsigned char m_data[8];
};

class W3DModelDrawInterface
{
public:
	virtual void w3dModelDrawInterfaceAnchor();
};

class W3DScriptedModelDraw : public DrawModule, public W3DModelDrawInterface
{
public:
	W3DScriptedModelDraw(Thing *, const ModuleData *);
	~W3DScriptedModelDraw() throw();

private:
	unsigned char m_unmodelled_10[0x27c - 0x10];
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

struct BfmeVector2
{
	BfmeVector2(float x, float y)
		: X(x), Y(y)
	{
	}

	float X;
	float Y;
};

struct BfmeMaterialOverride
{
	BfmeMaterialOverride()
		: m_structId(0x01234567), m_customUVOffset(0.0f, 0.0f)
	{
	}

	int m_structId;
	BfmeVector2 m_customUVOffset;
};

struct TreadObjectInfo
{
	void *m_robj;
	int m_type;
	BfmeMaterialOverride m_materialSettings;
};

struct BfmeCoord3
{
	float x;
	float y;
	float z;
};

class W3DTankDraw : public W3DScriptedModelDraw
{
public:
	W3DTankDraw(Thing *, const ModuleData *);

protected:
	void createEmitters();

private:
	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;
	void *m_prevRenderObj;
	TreadObjectInfo m_treads[4];
	int m_treadCount;
	BfmeCoord3 m_lastDirection;
};

// The retail constructor calls the incremental-link thunk, whose body is the
// already matched W3DTankDraw::createEmitters implementation at 0x0077EC40.
#pragma comment(linker, "/alternatename:?createEmitters@W3DTankDraw@@IAEXXZ=?j_0001b32e@@YAXXZ")

// ??0W3DTankDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DTankDraw::W3DTankDraw(Thing *thing, const ModuleData *moduleData)
	: W3DScriptedModelDraw(thing, moduleData), m_prevRenderObj(0)
{
	for (int i = 0; i < 4; ++i)
		m_treads[i].m_robj = 0;

	m_treadCount = 0;
	m_lastDirection.x = 1.0f;
	m_lastDirection.y = 0.0f;
	m_lastDirection.z = 0.0f;

	createEmitters();
}

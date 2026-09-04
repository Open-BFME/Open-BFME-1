// ??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.88 date=2026-09-04
// cl: /DBFME_MODULE_NO_MPO /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "Common/FileSystem.h"
#include "Common/ThingTemplate.h"
#include "GameClient/Drawable.h"
#include "GameClient/Shadow.h"
#include "WW3D2/RendObj.h"
#include "W3DDevice/GameClient/Module/W3DDefaultDraw.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"

// By-value LTAName: StringBase out-of-line copy/dtor (0x887B60 / 0x887940),
// isEmpty is the retail word-at-+4 test, str() is data+8.
template <typename T> struct BfmeStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class BfmeString;
	StringBase();
	StringBase(const StringBase<T> &other);
	~StringBase();
	BfmeStringData<T> *m_data;
};

class BfmeString : private StringBase<char>
{
public:
	BfmeString() : StringBase<char>() {}
	BfmeString(const BfmeString &other) : StringBase<char>(other) {}
	~BfmeString() {}
	const char *str(void) const { return m_data ? m_data->m_text : ""; }
	bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

// Overlay of ThingTemplate / Overridable: vptr, then next-override at +4.
// getLTAName is the 32-byte +0x5C copy at 0x00751390 (thunk 0x47D16).
class BfmeOverride
{
public:
	virtual void bfmeOverrideAnchor();
	BfmeOverride *friend_getFinalOverride();
	BfmeString getLTAName() const;
	BfmeOverride *m_nextOverride;
};

class BfmeThingView
{
public:
	virtual void bfmeThingAnchor();
	BfmeOverride *m_template;
};

struct BFMEShadowTypeInfo
{
	char m_ShadowName[128];
	int m_type;
	char m_allowUpdates;
	char m_allowWorldAlign;
	char m_pad[2];
	float m_sizeX;
	float m_sizeY;
	float m_offsetX;
	float m_offsetY;
	int m_unused98;
	float m_extra9C;
};

RenderObjClass *Create_Render_Obj(const char *name, float scale, int color);

// BFME RenderObjClass slots: Set_Transform at +0x54, Set_User_Data at +0x154.
class BfmeRO
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20();
	virtual void Set_Transform(const Matrix3D &m);
	virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
	virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
	virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
	virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
	virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
	virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
	virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
	virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
	virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
	virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73();
	virtual void s74(); virtual void s75(); virtual void s76(); virtual void s77();
	virtual void s78(); virtual void s79(); virtual void s80(); virtual void s81();
	virtual void s82(); virtual void s83(); virtual void s84();
	virtual void Set_User_Data(void *value, int recursive);
};

class BfmeGlobPB
{
public:
	virtual void bfmeSlotPB00();
	virtual void bfmeSlotPB01();
	virtual void Add_Render_Object(RenderObjClass *robj);
};
extern BfmeGlobPB *g_bfmeGlobPB;

static BfmeOverride *bfmeWalk(Drawable *draw)
{
	BfmeOverride *tmpl = ((BfmeThingView *)draw)->m_template;
	if (tmpl)
	{
		BfmeOverride *next = tmpl->m_nextOverride;
		if (next)
			tmpl = next->friend_getFinalOverride();
	}
	return tmpl;
}

// ??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DDefaultDraw::W3DDefaultDraw(Thing *thing, const ModuleData *moduleData)
	: DrawModule(thing, moduleData)
{
	*(RenderObjClass *volatile *)&m_renderObject = 0;
	*(Shadow *volatile *)&m_shadow = 0;

	if (!bfmeWalk(getDrawable())->getLTAName().isEmpty())
	{
		m_renderObject = Create_Render_Obj(
			bfmeWalk(getDrawable())->getLTAName().str(),
			getDrawable()->getScale(),
			0);

		BFMEShadowTypeInfo shadowInfo;
		shadowInfo.m_type = (int)SHADOW_VOLUME;
		shadowInfo.m_sizeX = 0;
		shadowInfo.m_sizeY = 0;
		shadowInfo.m_offsetX = 0;
		shadowInfo.m_offsetY = 0;
		shadowInfo.m_unused98 = 0;
		shadowInfo.m_extra9C = 20.0f;
		m_shadow = TheW3DShadowManager->addShadow(m_renderObject, (Shadow::ShadowTypeInfo *)&shadowInfo, 0);

		if (m_renderObject)
		{
			g_bfmeGlobPB->Add_Render_Object(m_renderObject);
			((BfmeRO *)m_renderObject)->Set_User_Data((char *)getDrawable() + 0x240, 0);
			Matrix3D transform(true);
			((BfmeRO *)m_renderObject)->Set_Transform(transform);
		}
	}
}

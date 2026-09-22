// ??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z
// cl: /DNDEBUG /MD /EHsc

// W3DDefaultDraw::W3DDefaultDraw, retail 0x007513C0, 568 bytes.
//
// The module registry row for W3DDefaultDraw carries 0x007513C0 in its
// constructor column, and its factory at 0x006BEFC0 builds the module. The body
// is Zero Hour's W3DDefaultDraw constructor with LOAD_TEST_ASSETS compiled in,
// so the reference source at
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDefaultDraw.cpp
// is the line-by-line model.
//
// BFME's render interfaces predate the Zero Hour headers, so the retail virtual
// slots and the extended shadow descriptor stay local to this translation unit,
// exactly as W3DDebrisDraw.cpp already keeps them.
//
// The override walk is the Zero Hour header's own recursive inline
// (reference/.../Code/GameEngine/Include/Common/Overridable.h): the compiler
// expands one level at each getTemplate() call and calls the out-of-line copy
// for the tail, which is what retail's 0x00087A80 walker is. Hand-expanding
// that level instead puts the merged pointer in EAX; letting MSVC inline it
// reproduces retail's xor ecx,ecx null arm and shared mov ecx,eax merge.

typedef unsigned char Bool;
typedef float Real;
typedef int Int;

class Thing;
class ModuleData;
class RenderObjClass;
class Drawable;

// The string payload BFME allocates, as
// Code/GameEngine/Source/Common/SmallGaps/lookupNameNoCase.cpp reads it: the
// length is a word at +4 and the characters start at +8.
struct BfmeStringData
{
	Int m_refs;
	unsigned short m_length;
	unsigned short m_alloc;
	char m_chars[1];
};

extern char Rva006A16B0Empty[];

template <class Character>
class BFMERetailStringBase
{
public:
	~BFMERetailStringBase() { releaseBuffer(); }

	Bool isEmpty() const { Int empty = (m_data == 0 || m_data->m_length == 0); return (Bool)empty; }
	const char *str() const { return m_data ? m_data->m_chars : Rva006A16B0Empty; }

private:
	void releaseBuffer();

	BfmeStringData *m_data;
};

// 0x00087A80. The override walk every Overridable shares.
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}


	unsigned int m_vfptr;
	Overridable *m_nextOverride;
};

// 0x00751390. The by-value copy of the string at +0x5C of the thing template,
// which is the template's LTA model name.
class Rva00751390Host
{
public:
	BFMERetailStringBase<char> copyStringAt5C();
};

class Drawable
{
public:
	Real getScale() const;

	Rva00751390Host *getTemplate() const
	{
		if (!m_template)
			return 0;
		return (Rva00751390Host *)m_template->getFinalOverride();
	}

	unsigned int m_vfptr;
	Overridable *m_template;
};

class Shadow
{
public:
	struct ShadowTypeInfo;
};

class W3DShadowManager
{
public:
	Shadow *addShadow( RenderObjClass *renderObject, Shadow::ShadowTypeInfo *info, Drawable *drawable );
};

extern W3DShadowManager *TheW3DShadowManager;

class SceneClass;

class W3DDisplay
{
public:
	static SceneClass *m_3DScene;
};

class BfmeSceneView
{
public:
	__forceinline void addRenderObject( RenderObjClass *renderObject )
	{
		typedef void (BfmeSceneView::*Method)( RenderObjClass * );
		(this->*(*(Method *)&(*(void ***)this)[2]))( renderObject );
	}
};

struct BfmeTransform
{
	Real m_cell[12];
};

class BfmeRenderObjectView
{
public:
	__forceinline void setTransform( const BfmeTransform &transform )
	{
		typedef void (BfmeRenderObjectView::*Method)( const BfmeTransform & );
		(this->*(*(Method *)&(*(void ***)this)[21]))( transform );
	}

	__forceinline void setUserData( void *value, Bool recursive )
	{
		typedef void (BfmeRenderObjectView::*Method)( void *, Bool );
		(this->*(*(Method *)&(*(void ***)this)[85]))( value, recursive );
	}
};

struct BfmeShadowTypeInfo
{
	char m_shadowNames[128];
	Int m_type;
	Bool m_allowUpdates;
	Bool m_allowWorldAlign;
	unsigned char m_padding86[2];
	Real m_sizeX;
	Real m_sizeY;
	Real m_offsetX;
	Real m_offsetY;
	Real m_unmodelled98;
	Real m_unmodelled9c;
	Bool m_unmodelleda0;
};

// 0x00901F80, the cdecl scaled and recoloured factory W3DDebrisDraw.cpp already
// calls under this name.
RenderObjClass *Create_Render_Obj( const char *name, Real scale, Int color );

class DrawableModule
{
public:
	DrawableModule( Thing *thing, const ModuleData *moduleData );
	virtual ~DrawableModule();

	Drawable *getDrawable() const { return m_drawable; }

private:
	unsigned int m_moduleData;
	Drawable *m_drawable;
};

class DrawModule : public DrawableModule
{
public:
	DrawModule( Thing *thing, const ModuleData *moduleData ) : DrawableModule( thing, moduleData ) { }
};

class W3DDefaultDraw : public DrawModule
{
public:
	W3DDefaultDraw( Thing *thing, const ModuleData *moduleData );

	virtual void doDrawModule( const BfmeTransform *transformMtx );
	virtual void setShadowsEnabled( Bool enable );
	virtual void setFullyObscuredByShroud( Bool fullyObscured );

private:
	RenderObjClass *m_renderObject;
	Shadow *m_shadow;
};

// ??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DDefaultDraw::W3DDefaultDraw( Thing *thing, const ModuleData *moduleData ) : DrawModule( thing, moduleData )
{
	m_renderObject = 0;
	m_shadow = 0;
	if (!getDrawable()->getTemplate()->copyStringAt5C().isEmpty())
	{
		BfmeShadowTypeInfo shadowInfo;

		m_renderObject = Create_Render_Obj( getDrawable()->getTemplate()->copyStringAt5C().str(),
			getDrawable()->getScale(), 0 );

		shadowInfo.m_unmodelled9c = 20.0f;
		shadowInfo.m_unmodelleda0 = false;
		shadowInfo.m_type = 2;
		shadowInfo.m_sizeX = 0;
		shadowInfo.m_sizeY = 0;
		shadowInfo.m_offsetX = 0;
		shadowInfo.m_offsetY = 0;
		shadowInfo.m_unmodelled98 = 0.0f;
		m_shadow = TheW3DShadowManager->addShadow( m_renderObject,
			(Shadow::ShadowTypeInfo *)&shadowInfo, 0 );

		if (m_renderObject)
		{
			BfmeTransform transform;

			((BfmeSceneView *)W3DDisplay::m_3DScene)->addRenderObject( m_renderObject );

			((BfmeRenderObjectView *)m_renderObject)->setUserData(
				(unsigned char *)getDrawable() + 0x240, false );

			transform.m_cell[0] = 1.0f;
			transform.m_cell[1] = 0.0f;
			transform.m_cell[2] = 0.0f;
			transform.m_cell[3] = 0.0f;
			transform.m_cell[4] = 0.0f;
			transform.m_cell[5] = 1.0f;
			transform.m_cell[6] = 0.0f;
			transform.m_cell[7] = 0.0f;
			transform.m_cell[8] = 0.0f;
			transform.m_cell[9] = 0.0f;
			transform.m_cell[10] = 1.0f;
			transform.m_cell[11] = 0.0f;
			((BfmeRenderObjectView *)m_renderObject)->setTransform( transform );
		}
	}
}

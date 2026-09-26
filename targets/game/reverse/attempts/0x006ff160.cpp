// ?d_006ff160@@YAXXZ
// partial score=0.08 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME-only Living World renderer initialization.  The full retail body also
// builds the lighting tables and loads livingworld.txt; this reconstruction
// preserves the identified entry sequence and field layout for continuation.

class RenderObjClass;
RenderObjClass *Create_Render_Obj( const char *name );

class BfmeLivingWorldFileName
{
public:
	BfmeLivingWorldFileName( const char *name );
	~BfmeLivingWorldFileName();
private:
	void *m_data;
};

void loadLivingWorldFile( BfmeLivingWorldFileName &name );

class BfmeLivingWorldName
{
public:
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
private:
	void *m_data;
};

struct BfmeLivingWorldConfiguration
{
	char m_prefix[ 0xC ];
	BfmeLivingWorldName m_worldRenderObjectName;
};

extern BfmeLivingWorldConfiguration *TheLivingWorldConfiguration;

class BfmeLivingWorldScene
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void addRenderObject( RenderObjClass *object );
};

class LivingWorldManager
{
public:
	void init();
	void initializeWorldGeometry();

private:
	char m_prefix[ 0x74 ];
	BfmeLivingWorldScene *m_scene;
	char m_betweenSceneAndObjects[ 0xC ];
	RenderObjClass *m_worldRenderObject;       // +0x84
	char m_betweenWorldAndSunRays[ 0xB0 ];
	RenderObjClass *m_sunRaysRenderObject;     // +0x138
};

struct BfmeGameClientFlags
{
	char m_prefix[ 0xDBC ];
	unsigned char m_livingWorldInitialized;
};

extern BfmeGameClientFlags *TheBfmeGameClientFlags;
extern unsigned char g_livingWorldRendererActive;

void LivingWorldManager::init()
{
	volatile char reconstructionWorkspace[ 0x16C ];
	g_livingWorldRendererActive = 1;
	TheBfmeGameClientFlags->m_livingWorldInitialized = 0;

	m_worldRenderObject = Create_Render_Obj(
		TheLivingWorldConfiguration->m_worldRenderObjectName.str() );
	m_sunRaysRenderObject = Create_Render_Obj( "LM_SunRays" );

	if( m_worldRenderObject )
	{
		m_scene->addRenderObject( m_worldRenderObject );
		initializeWorldGeometry();
	}

	BfmeLivingWorldFileName fileName( "livingworld.txt" );
	loadLivingWorldFile( fileName );
	reconstructionWorkspace[ 0 ] = 0;
}

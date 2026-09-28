// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// WaterRenderObjClass::~WaterRenderObjClass, retail 0x007A5D10 (784 bytes).
// The body stores the primary vtable 0x01128148 that the exact constructor
// (0x007A46E0) installs, and the scalar deleting destructor (0x007A60F0)
// reaches it through ILT 0x00032DCB.  Its 10-state unwind map is the
// constructor's in reverse: RenderObjClass base, the three texture handles at
// +0xe4/+0x24c/+0x2a8, the list at +0x2ac, the sky name at +0x2c8, the five
// names at +0x2cc and the six settings at +0x2e0, then the body and its DX8
// lock guard.  The body is the Zero Hour destructor (W3DWater.cpp) with BFME's
// additions: the TheSkyboxTextureSets entries are deleted after
// ReleaseResources, and the owned-object list at +0x2ac is emptied last.

void __cdecl operator delete[]( void * ) throw();
void __cdecl operator delete( void * ) throw();
#include <list>
#include <hash_map>

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	const T *str() const { return m_data ? m_data->data : ""; }
	void clear() { releaseBuffer(); }

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &src );
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString( const AsciiString &that ) : StringBase<char>( that ) {}
	~AsciiString() {}
};

namespace rts
{
	template <typename T> struct hash;
	template <typename T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		size_t operator()( AsciiString ast ) const
		{
			_STL::hash<const char *> tmp;
			return tmp( (const char *)ast.str() );
		}
	};

	template <> struct equal_to<AsciiString>
	{
		bool operator()( const AsciiString &left, const AsciiString &right ) const;
	};
}

class SkyboxTextureSet
{
public:
	virtual ~SkyboxTextureSet();
};

typedef _STL::hash_map< AsciiString, SkyboxTextureSet *, rts::hash<AsciiString>,
	rts::equal_to<AsciiString> > SkyboxTextureSetMap;

extern SkyboxTextureSetMap TheSkyboxTextureSets;

template <class T> class OVERRIDE
{
public:
	OVERRIDE &operator=( const T *overridable )
	{
		m_overridable = overridable;
		return *this;
	}
	const T *getNonOverloadedPointer() const { return m_overridable; }

private:
	const T *m_overridable;
};

class WaterTransparencySetting
{
public:
	virtual ~WaterTransparencySetting();
	void deleteInstance() { delete this; }
};

extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;

class WaterSetting
{
public:
	void *m_vtable;
	AsciiString m_skyTextureFile;
	AsciiString m_waterTextureFile;
	unsigned char m_rest[ 0x7c - 0x0c ];
};

extern WaterSetting WaterSettings[];

enum { WATER_SETTING_COUNT = 6 };

void W3DRadarResetLock( void );
void BFME_DX8_Thread_Assert( void );

class WaterDestructorGuard
{
public:
	~WaterDestructorGuard( void )
	{
		BFME_DX8_Thread_Assert();
	}
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() {}
};

class RefCountClass
{
public:
	virtual void Delete_This( void );

	void Release_Ref( void )
	{
		NumRefs--;
		if( NumRefs == 0 )
			Delete_This();
	}

	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass( void );

	void *ListNode;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~RenderObjClass( void );

	unsigned char m_renderObjData[ 0xc8 - 0x10 ];
};

class VertexMaterialClass : public RefCountClass
{
};

class LightClass : public RenderObjClass
{
};

class TextureClass
{
public:
	void Release_Ref( void );
};

// The handle the constructor zero-initialises at +0xe4, +0x24c and +0x2a8.
class BfmeHandleCX
{
public:
	~BfmeHandleCX( void )
	{
		if( m_handle )
			m_handle->Release_Ref();
	}

private:
	TextureClass *m_handle;
};

class WaterTracksRenderSystem
{
public:
	~WaterTracksRenderSystem( void );
};

class WaterGridRef;
class WaterComRef;
struct WaterMeshData;

struct ListSlot4
{
	void *dummy;
};

#define REF_PTR_RELEASE( x ) { if( x ) { x->Release_Ref(); x = 0; } }

class WaterRenderObjClass : public BfmeBaseVUQ, public RenderObjClass
{
public:
	struct Setting
	{
		~Setting( void );

		void *skyTexture;
		void *waterTexture;
		unsigned char m_pad[ 0x30 - 8 ];
	};

	virtual ~WaterRenderObjClass( void );

private:
	WaterGridRef *m_indexBuffer;					// +0xcc
	unsigned long m_d0;
	unsigned long m_d4;
	VertexMaterialClass *m_vertexMaterialClass;	// +0xd8
	VertexMaterialClass *m_meshVertexMaterialClass;	// +0xdc
	LightClass *m_meshLight;						// +0xe0
	BfmeHandleCX m_e4Handle;						// +0xe4
	unsigned char m_beforeReflection[ 0x24c - 0xe8 ];
	BfmeHandleCX m_reflectionHandle;				// +0x24c
	RenderObjClass *m_skyBox;						// +0x250
	WaterTracksRenderSystem *m_waterTrackSystem;	// +0x254
	WaterMeshData *m_meshData;						// +0x258
	int m_meshDataSize;								// +0x25c
	unsigned char m_before2a8[ 0x2a8 - 0x260 ];
	BfmeHandleCX m_2a8Handle;						// +0x2a8
	_STL::list<ListSlot4> m_at2ac;					// +0x2ac
	unsigned char m_before2c8[ 0x2c8 - 0x2b0 ];
	AsciiString m_sky;								// +0x2c8
	AsciiString m_names[ 5 ];						// +0x2cc
	Setting m_settings[ 6 ];						// +0x2e0
	int m_400;
	unsigned char m_tail[ 0x11c ];
};

// Two members are reached only through their ILT thunks, whose targets carry
// no usable ledger identity yet:
//  * 0x0004ADD1 -> 0x0079EFD0 releases the index/vertex buffers, bump and
//    reflection textures -- Zero Hour's ReleaseResources, called at the same
//    point of the destructor (the ledger row there is still filed as a
//    non-virtual ??1WaterRenderObjClass);
//  * 0x00028B8C -> 0x007A1330 unlinks every node of the +0x2ac list and
//    deletes its element through the virtual destructor.
extern void j_0004add1();
extern void j_00028b8c();

class Rva007A5D10Call
{
};

static __forceinline void callThunk( WaterRenderObjClass *object, void ( *thunk )() )
{
	typedef void ( Rva007A5D10Call::*Function )();
	union { void ( *raw )(); Function member; } fn;
	fn.raw = thunk;
	( reinterpret_cast<Rva007A5D10Call *>( object )->*fn.member )();
}

static __forceinline void releaseResources( WaterRenderObjClass *water )
{
	callThunk( water, j_0004add1 );
}

static __forceinline void clearList2ac( WaterRenderObjClass *water )
{
	callThunk( water, j_00028b8c );
}

// ??1WaterRenderObjClass@@UAE@XZ
WaterRenderObjClass::~WaterRenderObjClass( void )
{
	W3DRadarResetLock();
	WaterDestructorGuard guard;

	REF_PTR_RELEASE( m_meshVertexMaterialClass );
	REF_PTR_RELEASE( m_vertexMaterialClass );
	REF_PTR_RELEASE( m_meshLight );
	REF_PTR_RELEASE( m_skyBox );

	if( m_meshData )
		delete [] m_meshData;
	m_meshData = 0;
	m_meshDataSize = 0;

	// Release strings allocated inside global water settings.
	int i;
	for( i = 0; i < WATER_SETTING_COUNT; i++ )
	{
		WaterSettings[ i ].m_skyTextureFile.clear();
		WaterSettings[ i ].m_waterTextureFile.clear();
	}
	( (WaterTransparencySetting *)TheWaterTransparency.getNonOverloadedPointer() )->deleteInstance();
	TheWaterTransparency = 0;
	releaseResources( this );

	for( SkyboxTextureSetMap::iterator it = TheSkyboxTextureSets.begin();
		it != TheSkyboxTextureSets.end(); ++it )
		delete it->second;

	if( m_waterTrackSystem )
		delete m_waterTrackSystem;

	clearList2ac( this );
}

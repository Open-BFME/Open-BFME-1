// cl: /DNDEBUG /MD /EHsc
// Real C++ reconstruction of ??0RTS2DScene@@QAE@XZ (retail 0x00712590,
// 209 bytes).
//
// Identity is established by the two constructor-installed tables, not by
// adjacency: the primary table 0x01120A80 carries SimpleSceneClass's Add /
// Remove / iterator slots, and the secondary table 0x01120A50 carries
// SubsystemInterface::loadIniFilesFromLegend at slot 2.  W3DDisplay::init's
// NEW_REF(RTS2DScene) call is the named construction path.  The matched
// destructor independently fixes the second base at +0x108 and the two scene
// members at +0x110 / +0x114.
//
// The local string view deliberately keeps the canonical StringInline shape:
// StringBase owns one data pointer, while the AsciiString copy constructor and
// destructor remain inline forwarders.  setName needs the real out-of-line
// copy-assignment ABI as well, so the declaration below is TU-local rather than
// changing the shared helper.

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &other );
};

typedef bool Bool;

class SceneClass;

#define NEW_REF( C, P ) ( new C P )

// These are the real BFME data-bearing bases of RenderObjClass.  The
// constructor only needs their object size here, but keeping the proven field
// declarations makes the W3DStatusCircle allocation a normal C++ lifetime
// operation instead of a raw buffer/placement-new substitute.
class Vector3
{
public:
	float m_x, m_y, m_z;
};

class Vector4
{
public:
	float m_x, m_y, m_z, m_w;
};

class Matrix3D
{
public:
	Vector4 m_row[3];
};

class SphereClass
{
public:
	Vector3 m_center;
	float m_radius;
};

class AABoxClass
{
public:
	Vector3 m_center;
	Vector3 m_extent;
};

class RefCountClass
{
public:
	virtual void Delete_This();
	int m_numRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *m_listNode;
};

class RenderHookClass;

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	enum { CLASSID_UNKNOWN = -1 };
	virtual ~RenderObjClass();
	virtual int Class_ID() const;

	unsigned long m_bits;
	unsigned long m_unknown14;
	Matrix3D m_transform;
	float m_objectScale;
	unsigned int m_objectColor;
	SphereClass m_cachedBoundingSphere;
	AABoxClass m_cachedBoundingBox;
	float m_nativeScreenSize;
	bool m_isTransformIdentity;
	SceneClass *m_scene;
	RenderObjClass *m_container;
	void *m_userData;
	float m_unknown8c;
	unsigned long m_unknown90;
	unsigned long m_unknown94;
	float m_unknown98;
	RenderHookClass *m_renderHook;
	unsigned long m_unknownA0;
	bool m_unknownA4;
	unsigned char m_unknownA5[0x1f];
	bool m_unknownC4;
	unsigned char m_unknownC5[3];
};

// The retail body at 0x00944940 is the real SimpleSceneClass constructor: its
// final vptr is 0x0113CF48 and its slots 2/3/4 are the matched SimpleSceneClass
// Add, Remove and Create_Iterator bodies.  The opaque tail is the proven
// 0x108-byte scene subobject layout also used by the matched destructor.
class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
	virtual void Add_Render_Object( RenderObjClass *obj );
	virtual void Remove_Render_Object( RenderObjClass *obj );
	virtual void *Create_Iterator();

private:
	unsigned char m_sceneLayout[0x104];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() {}
	virtual Bool loadIniFilesFromLegend();
	virtual void postProcessLoad() {}
	virtual void reset() {}
	virtual void update() {}
	virtual void draw() {}

	void setName( AsciiString name )
	{
		AsciiString &nameSlot = m_name;
		nameSlot = name;
	}

private:
	AsciiString m_name;
};

class ShaderClass
{
public:
	unsigned int m_shaderBits;
	unsigned int m_bfmeReserved4;
	unsigned int m_bfmeReserved8;
	unsigned int m_bfmeReservedC;
};

class W3DStatusCircle : public RenderObjClass
{
public:
	W3DStatusCircle();

	int m_numTriangles;
	void *m_indexBuffer;
	ShaderClass m_shaderClass;
	void *m_vertexMaterialClass;
	void *m_vertexBufferCircle;
	void *m_vertexBufferScreen;
};

typedef char BfmeRenderObjClassSizeCheck[( sizeof( RenderObjClass ) == 0xc8 ) ? 1 : -1];
typedef char BfmeW3DStatusCircleSizeCheck[( sizeof( W3DStatusCircle ) == 0xec ) ? 1 : -1];

class RTS2DScene : public SimpleSceneClass, public SubsystemInterface
{
public:
	RTS2DScene();

private:
	RenderObjClass *m_status;
	void *m_camera;
};

// ??0RTS2DScene@@QAE@XZ
RTS2DScene::RTS2DScene()
{
	setName( AsciiString( "RTS2DScene" ) );

	m_status = NEW_REF( W3DStatusCircle, () );
	Add_Render_Object( m_status );
	m_camera = 0;
}

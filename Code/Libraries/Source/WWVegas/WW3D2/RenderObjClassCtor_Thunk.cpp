// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RenderObjClass's default constructor, lifted out of the byte dump
// into real C++.
//
// Layout evidence from the retail body @0x9204B0:
//   +0x00  primary vftable            (stored by THIS ctor, not by a base)
//   +0x04  RefCountClass::NumRefs = 1 (the base ctor's only surviving store --
//          its vptr store at +0 is dead because this ctor rewrites +0, and MSVC
//          drops the redundant PRIMARY vptr store while keeping the secondary
//          one at +8; that asymmetry is what pins RefCountClass as the first
//          base and forces it to be polymorphic)
//   +0x08  MultiListObjectClass vftable, then its rewrite by this ctor
//   +0x0c  MultiListObjectClass's link pointer = 0
// so both bases carry a vfptr; MSVC only reorders bases when the first one has
// none, and with RefCountClass polymorphic the declared order survives.
//
// Everything from +0x10 on is emitted in DECLARATION order, which is why the
// initialiser list below is written in address order rather than the order
// rendobj.cpp spells it.  The two byte stores at the tail come out +0xC4 before
// +0xA4, i.e. the higher offset first, so +0xA4 cannot be in the list -- it is a
// body assignment, which runs after every member initialiser.
//
// The WWMath types are reproduced in their retail shapes (Vector4::Set for the
// identity rows, SphereClass::Init, AABoxClass's Center/Extent copy-init): the
// interleaving of the 1.0f and zero stores inside Transform and CachedBoundingBox
// is the scheduler reacting to that exact expression shape, and hand-written
// field assignments schedule differently.

class Vector3
{
public:
	float X, Y, Z;

	Vector3(void) {}
	Vector3(const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 & operator = (const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

class Vector4
{
public:
	float X, Y, Z, W;

	Vector4(void) {}
	void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
};

class Matrix3D
{
public:
	Matrix3D(void) {}
	explicit Matrix3D(bool init) { if (init) Make_Identity(); }

	void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	Vector4 Row[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
public:
	SphereClass(void) {}
	SphereClass(const Vector3 & center, float radius) { Init(center, radius); }

	void Init(const Vector3 & pos, float radius) { Center = pos; Radius = radius; }

	Vector3	Center;
	float	Radius;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabox.h
class AABoxClass
{
public:
	AABoxClass(void) {}
	AABoxClass(const Vector3 & center, const Vector3 & extent) : Center(center), Extent(extent) {}

	Vector3 Center;
	Vector3 Extent;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass(void) : NumRefs(1) {}
	virtual void Delete_This(void);

	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	MultiListObjectClass(void) : ListNode(0) {}
	virtual ~MultiListObjectClass(void);

	void * ListNode;
};

class SceneClass;
class RenderHookClass;

// Get_Default_Native_Screen_Size is inlined to a straight load of the static at
// 0x12D6D7C -- retail reads it with an integer mov, never the x87 stack.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static float Get_Default_Native_Screen_Size(void) { return DefaultNativeScreenSize; }

	static float DefaultNativeScreenSize;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RenderObjClass(void);

	virtual int Class_ID(void) const;

	mutable unsigned long		Bits;					// +0x10, DEFAULT_BITS = 0x6001
	unsigned long				_bfme_unk_14;			// +0x14
	Matrix3D					Transform;				// +0x18
	float						ObjectScale;			// +0x48
	unsigned int				ObjectColor;			// +0x4c
	mutable SphereClass			CachedBoundingSphere;	// +0x50
	mutable AABoxClass			CachedBoundingBox;		// +0x60
	float						NativeScreenSize;		// +0x78
	mutable bool				IsTransformIdentity;	// +0x7c
	SceneClass *				Scene;					// +0x80
	RenderObjClass *			Container;				// +0x84
	void *						User_Data;				// +0x88
	float						_bfme_unk_8c;			// +0x8c
	unsigned long				_bfme_unk_90;			// +0x90
	int							_bfme_unk_94;			// +0x94
	float						_bfme_unk_98;			// +0x98
	RenderHookClass *			RenderHook;				// +0x9c
	int							_bfme_unk_a0;			// +0xa0
	bool						_bfme_unk_a4;			// +0xa4
	char						_bfme_pad_a5[0x1f];		// +0xa5, never written here
	bool						_bfme_unk_c4;			// +0xc4
	char						_bfme_pad_c5[3];		// keeps sizeof at 0xc8
};

// ??0RenderObjClass@@QAE@XZ
RenderObjClass::RenderObjClass(void) :
	Bits(0x6001),
	_bfme_unk_14(1),
	Transform(1),
	ObjectScale(1.0f),
	ObjectColor(0),
	CachedBoundingSphere(Vector3(0,0,0), 1.0f),
	CachedBoundingBox(Vector3(0,0,0), Vector3(1,1,1)),
	NativeScreenSize(WW3D::Get_Default_Native_Screen_Size()),
	IsTransformIdentity(false),
	Scene(0),
	Container(0),
	User_Data(0),
	_bfme_unk_8c(0.0f),
	_bfme_unk_90(0),
	_bfme_unk_94(-1),
	_bfme_unk_98(-1.0f),
	RenderHook(0),
	_bfme_unk_a0(-1),
	_bfme_unk_c4(false)
{
	_bfme_unk_a4 = false;
}

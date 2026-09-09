// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME constructor at RVA 0x00726000, 90 bytes. Narrow RenderObjClass
// view follows RTS2DScene_Ctor_Thunk.cpp. Both vptrs are compiler-generated;
// retail installs the primary table at VA 0x01121018 and secondary at 0x01121010.
// The shader word is at DC; the two preceding floats initialize to -1.
typedef bool Bool;
class SceneClass;
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
	RenderObjClass();
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


class BfmeCircleShader {
public:
 BfmeCircleShader() : bits(0x0010441b) {}
 unsigned int bits;
};
class W3DStatusCircle : public RenderObjClass {
public:
 W3DStatusCircle();
 virtual ~W3DStatusCircle();
 int fieldC8;
 int fieldCC;
 float fieldD0;
 float fieldD4;
 void *indexBuffer;
 BfmeCircleShader shader;
 void *material;
 void *circleBuffer;
 void *screenBuffer;
};
W3DStatusCircle::W3DStatusCircle()
 : fieldC8(0), fieldCC(0), fieldD0(-1.0f), fieldD4(-1.0f), indexBuffer(0)
{
 material=0;
 circleBuffer=0;
 screenBuffer=0;
}

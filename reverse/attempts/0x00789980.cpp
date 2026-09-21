// ?rva00789980@Rva00789900Init@@UAEXXZ
// partial score=0.45 date=2026-09-18
// ?rva00789980@Rva00789900Init@@UAEXXZ
// Retail RVA 0x00789980, 498 bytes.
//
// The owner is address-derived from the landed 0x00789900 constructor and
// 0x007897D0 destructor: vtable 0x01126CCC slot 1 routes through thunk
// 0x0001A893 to this body.  The body creates a SimpleSceneClass-derived
// 0x108-byte scene and a CameraClass, then installs the camera transform.

// cl: /DNDEBUG /MD /EHsc

extern "C" double sin(double value);
extern "C" double cos(double value);
#pragma intrinsic(sin, cos)

#define BfmeZeroRange (*(const float *)0x01075350)
#define Rva00789980NegPi (*(const double *)0x01126CF8)
#define Rva00789980PosPi (*(const double *)0x01126CE8)

struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

class GenBase00944940
{
public:
	GenBase00944940();
	virtual ~GenBase00944940() {}
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void Set_Ambient_Light(const Vector3 &color);
};

class Rva00789650 : public GenBase00944940
{
public:
	Rva00789650() {}

private:
	unsigned char m_body[0x104];
};

struct Matrix3D
{
	float Row[3][4];

	__forceinline explicit Matrix3D(bool init)
	{
		if (init)
		{
			Row[0][0] = 1.0f;
			Row[0][1] = 0.0f;
			Row[0][2] = 0.0f;
			Row[0][3] = 0.0f;
			Row[1][0] = 0.0f;
			Row[1][1] = 1.0f;
			Row[1][2] = 0.0f;
			Row[1][3] = 0.0f;
			Row[2][0] = 0.0f;
			Row[2][1] = 0.0f;
			Row[2][2] = 1.0f;
			Row[2][3] = 0.0f;
		}
	}

	__forceinline void Rotate_Y(double theta)
	{
		float s = (float)sin(theta);
		float c = (float)cos(theta);
		float tmp1;
		float tmp2;
		tmp1 = Row[0][0];
		tmp2 = Row[0][2];
		Row[0][0] = c * tmp1 - s * tmp2;
		Row[0][2] = c * tmp2 + s * tmp1;
		tmp1 = Row[1][0];
		tmp2 = Row[1][2];
		Row[1][0] = c * tmp1 - s * tmp2;
		Row[1][2] = c * tmp2 + s * tmp1;
		tmp1 = Row[2][0];
		tmp2 = Row[2][2];
		Row[2][0] = c * tmp1 - s * tmp2;
		Row[2][2] = c * tmp2 + s * tmp1;
	}

	__forceinline void Rotate_Z(double theta)
	{
		float c = (float)cos(theta);
		float s = (float)sin(theta);
		float tmp1;
		float tmp2;
		tmp1 = Row[0][0];
		tmp2 = Row[0][1];
		Row[0][0] = c * tmp1 + s * tmp2;
		Row[0][1] = c * tmp2 - s * tmp1;
		tmp1 = Row[1][0];
		tmp2 = Row[1][1];
		Row[1][0] = c * tmp1 + s * tmp2;
		Row[1][1] = c * tmp2 - s * tmp1;
		tmp1 = Row[2][0];
		tmp2 = Row[2][1];
		Row[2][0] = c * tmp1 + s * tmp2;
		Row[2][1] = c * tmp2 - s * tmp1;
	}
};

class CameraClass
{
public:
	CameraClass();
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void Set_Transform(const Matrix3D &transform);
	void Set_Clip_Planes(float nearZ, float farZ);
	void Set_View_Plane(float horizontalFOV, float verticalFOV);

private:
	unsigned char m_body[0x3bc];
};

class Rva00789900Init
{
public:
	virtual ~Rva00789900Init();
	virtual void rva00789980();

private:
	unsigned int m_04;
	unsigned int m_08;
	Rva00789650 *m_scene;
	CameraClass *m_camera;
};

void Rva00789900Init::rva00789980()
{
	m_scene = new Rva00789650();
	m_scene->Set_Ambient_Light(Vector3(0.5f, 0.5f, 0.5f));

	m_camera = new CameraClass();
	m_camera->Set_Clip_Planes(1.0f, 5000.0f);
	m_camera->Set_View_Plane(0.87266463f, -1.0f);

	Matrix3D transform(true);
	transform.Rotate_Y(-Rva00789980NegPi);
	transform.Rotate_Z(Rva00789980PosPi);

	m_camera->Set_Transform(transform);
}

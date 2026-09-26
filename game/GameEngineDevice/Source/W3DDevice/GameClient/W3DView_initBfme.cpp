// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME W3DView::init, retail 0x00742700.

struct Coord2D
{
	float x;
	float y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "ascii_string.h"

class Vector2
{
public:
	Vector2(float xValue, float yValue) : x(xValue), y(yValue) {}

	float x;
	float y;
};

class Vector3
{
public:
	Vector3(float xValue, float yValue, float zValue)
		: x(xValue), y(yValue), z(zValue) {}

	float x;
	float y;
	float z;
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
	virtual void slot21();
	virtual void Set_Position(const Vector3 &position);
	void Set_View_Plane(const Vector2 &min, const Vector2 &max);
	void Set_Clip_Planes(float nearZ, float farZ);

private:
	unsigned char m_body[0x3bc];
};

class Rva006DF250
{
public:
	virtual float minimum();
	virtual float maximum();
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
	virtual void resetState();
	void initialize();

private:
	unsigned char m_body[0x28];
};

struct GlobalData
{
	unsigned char m_body[0xb74];
	float m_scrollAmountCutoff;
};

extern GlobalData *TheWritableGlobalData;
extern void j_0002c458(void);
extern void j_000312a0(void);
extern void j_00001555(void);

class View
{
public:
	virtual void init();

private:
	unsigned char m_body[0xfc - 4];
};

class SubsystemInterface
{
public:
	virtual void init() = 0;
	void setName(AsciiString name) { m_name = name; }

protected:
	AsciiString m_name;
};

class W3DView : public View, public SubsystemInterface
{
public:
	virtual void init();

	private:
	CameraClass *m_3DCamera;
	CameraClass *m_2DCamera;
	unsigned char m_body10c[0x23f4 - 0x10c];
	float m_scrollAmountCutoff;
	unsigned char m_body23f8[0x240c - 0x23f8];
	bool m_cameraConstraintValid;
	unsigned char m_body240d[0x24b4 - 0x240d];
	int m_field24b4;
	Rva006DF250 m_zoomLimits;
	void setCameraTransform();
	void setPosition(const Coord3D &position)
	{
		*reinterpret_cast<Coord3D *>(reinterpret_cast<unsigned char *>(this) + 0x0c) = position;
	}
};

void W3DView::init()
{
	j_0002c458();
	setName("W3DView");

	Coord3D pos;
	pos.x = 87.0f;
	pos.y = 77.0f;
	pos.z = 0.0f;
	pos.x *= 10.0f;
	pos.y *= 10.0f;
	setPosition(pos);

	m_3DCamera = new CameraClass();
	Rva006DF250 *zoomLimits = reinterpret_cast<Rva006DF250 *>(reinterpret_cast<unsigned char *>(this) + 0x24b8);
	zoomLimits->resetState();
	setCameraTransform();

	m_2DCamera = new CameraClass();
	m_2DCamera->Set_Position(Vector3(0.0f, 0.0f, 1.0f));
	Vector2 min(-1.0f, -0.75f);
	Vector2 max(1.0f, 0.75f);
	m_2DCamera->Set_View_Plane(min, max);
	m_2DCamera->Set_Clip_Planes(0.995f, 2.0f);

	m_cameraConstraintValid = false;
	m_scrollAmountCutoff = TheWritableGlobalData->m_scrollAmountCutoff;
	m_field24b4 = 0;
	zoomLimits->initialize();
}

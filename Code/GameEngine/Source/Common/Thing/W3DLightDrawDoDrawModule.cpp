// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

#include "matrix3d.h"
#include "wwmath.h"

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Drawable
{
};

extern void j_0003ee55();

class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19();
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &transform);

	const Matrix3D &Get_Transform_No_Validity_Check() const { return m_transform; }

	unsigned char m_pad04[0x14];
	Matrix3D m_transform;
};

class W3DDynamicLight : public RenderObjClass
{
};

class W3DLightDrawModuleData
{
public:
	unsigned char m_pad[0x30];
	Real m_30;
	Real m_34;
	Real m_38;
	Real m_3c;
	Real m_40;
	Real m_44;
};

class DrawModule
{
public:
	virtual void doDrawModule(const Matrix3D *transform) = 0;

protected:
	W3DLightDrawModuleData *m_moduleData;
	Drawable *m_drawable;
};

class W3DLightDraw : public DrawModule
{
public:
	virtual void doDrawModule(const Matrix3D *transform);

private:
	W3DDynamicLight *m_light;
	Real m_phase;
	Real m_radius;
	Real m_angle;
	Real m_height;
};

// Vtable slot 9 at 0x00758890 identifies this body as W3DLightDraw::doDrawModule.
// The constructor at 0x007583A0 and destructor vtable at 0x01122B20 confirm the class layout.
void W3DLightDraw::doDrawModule(const Matrix3D *)
{
	Real phase = m_phase;
	W3DDynamicLight *light = m_light;
	phase += *(const Real *)0x01080bbc;
	m_phase = phase;
	if (light == 0)
		return;

	const W3DLightDrawModuleData *data = m_moduleData;
	if (data == 0)
		return;
	Drawable *drawable = m_drawable;
	volatile Real height;
	height = data->m_30;
	if (drawable != 0)
	{
		light->Validate_Transform();
		Matrix3D transform;
		volatile float *destination = (volatile float *)&transform;
		volatile const float *source = (volatile const float *)&light->Get_Transform_No_Validity_Check();
		destination[0] = source[0];
		destination[1] = source[1];
		destination[2] = source[2];
		destination[3] = source[3];
		destination[4] = source[4];
		destination[5] = source[5];
		destination[6] = source[6];
		destination[7] = source[7];
		destination[8] = source[8];
		destination[9] = source[9];
		destination[10] = source[10];
		destination[11] = source[11];
		const Coord3D *position = ((const Coord3D *(__fastcall *)(Drawable *))j_0003ee55)(drawable);
		Vector3 positionVector(position->x, position->y, position->z);
		transform.Set_Translation(positionVector);
		m_light->Set_Transform(transform);
	}

	if (data->m_34 > *(const Real *)0x01075350)
	{
		if (m_radius <= *(const Real *)0x01075350)
		{
			m_radius = *(const Real *)0x01075344 / data->m_38;
			Real minimum = -data->m_34;
			Real maximum = data->m_34;
			m_angle = ((WWMath::Random_Float() * (maximum - minimum) + minimum) + height - m_height) / m_radius;
		}
		m_radius -= *(const Real *)0x01075334;
		height = m_angle + m_height;
		m_height = height;
	}
	if (data->m_3c > *(const Real *)0x01075350)
		height = WWMath::Sin(m_phase * data->m_40 * *(const Real *)0x01087b10) * data->m_3c + height;
	*(unsigned int *)((char *)m_light + 0xd4) = *(const unsigned int *)&height;
}

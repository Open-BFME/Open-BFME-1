// cl: /DNDEBUG /MD /GX- /O2 /Ob2

#include <math.h>

#pragma intrinsic(sin, cos, atan2)

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	__forceinline Coord3D() {}
	__forceinline Coord3D(Real xValue, Real yValue, Real zValue)
		: x(xValue), y(yValue), z(zValue) {}

	Real x;
	Real y;
	Real z;
};

extern const Real BfmeZeroRange;

class Matrix3D
{
public:
	__forceinline Matrix3D(bool init)
	{
		if (init)
		{
			m_row[0][0] = 1.0f;
			m_row[0][1] = 0.0f;
			m_row[0][2] = 0.0f;
			m_row[0][3] = 0.0f;
			m_row[1][0] = 0.0f;
			m_row[1][1] = 1.0f;
			m_row[1][2] = 0.0f;
			m_row[1][3] = 0.0f;
			m_row[2][0] = 0.0f;
			m_row[2][1] = 0.0f;
			m_row[2][2] = 1.0f;
			m_row[2][3] = 0.0f;
		}
	}

	__forceinline void Rotate_Z(Real angle)
	{
		Real cosine = cos(angle);
		Real sine = sin(angle);
		Real xComponent = m_row[0][0];
		Real yComponent = m_row[0][1];
		m_row[0][0] = (Real)(cosine * xComponent + sine * yComponent);
		m_row[0][1] = (Real)(-sine * xComponent + cosine * yComponent);
		xComponent = m_row[1][0];
		yComponent = m_row[1][1];
		m_row[1][0] = (Real)(cosine * xComponent + sine * yComponent);
		m_row[1][1] = (Real)(-sine * xComponent + cosine * yComponent);
		xComponent = m_row[2][0];
		yComponent = m_row[2][1];
		m_row[2][0] = (Real)(cosine * xComponent + sine * yComponent);
		m_row[2][1] = (Real)(-sine * xComponent + cosine * yComponent);
	}

	Real m_row[3][4];
};

class FXList
{
public:
	Bool isEmpty() const;
};

class BfmeThingCOF
{
public:
	void bfmeRunCOF(void *position, void *matrix, void *speed, void *secondary);
};

class TerrainLogic
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;
};

extern TerrainLogic *TheTerrainLogic;

namespace FXParticleSystem
{

class ParticleSystem005FD380
{
public:
	char m_pad00[0x10];
	Real m_directionX;
	Real m_directionY;
	char m_pad18[4];
	Coord3D m_position;
	char m_pad28[0x40];
	int m_finished;
};

class ParticleTerrainCollisionOwner005FD380
{
public:
	virtual void ownerSlot();
	ParticleSystem005FD380 *m_system;
};

class ParticleTerrainCollisionFlags005FD380
{
public:
	virtual void flagSlot();
	unsigned char m_oneShot;
};

class ParticleTerrainCollisionData005FD380
{
public:
	virtual void dataSlot();
	Real m_heightOffset;
	::FXList *m_eventFX;
	unsigned char m_alignToDirection;
	char m_pad1d[3];
	unsigned char m_active;
};

class ParticleTerrainCollisionModule
	: public ParticleTerrainCollisionOwner005FD380,
	  public ParticleTerrainCollisionFlags005FD380,
	  public ParticleTerrainCollisionData005FD380
{
public:
	virtual void update();
};

// ?update@ParticleTerrainCollisionModule@FXParticleSystem@@UAEXXZ
void ParticleTerrainCollisionModule::update()
{
	if (m_active && m_eventFX)
	{
		ParticleSystem005FD380 *system = m_system;
		if (TheTerrainLogic->getGroundHeight(
			system->m_position.x, system->m_position.y, 0) >= system->m_position.z)
		{
			Matrix3D matrix(true);
			if (m_alignToDirection)
				matrix.Rotate_Z(atan2(m_system->m_directionY, m_system->m_directionX));

			Coord3D *sourcePosition = &m_system->m_position;
			Coord3D position;
			position.x = sourcePosition->x;
			::FXList *eventFX = m_eventFX;
			position.y = sourcePosition->y;
			position.z = sourcePosition->z + m_heightOffset;

			if (eventFX && !eventFX->isEmpty())
				((BfmeThingCOF *)eventFX)->bfmeRunCOF(
					&position, &matrix, 0, 0);

			m_active = 0;
			if (m_oneShot)
				m_system->m_finished = 1;
		}
	}
}

}

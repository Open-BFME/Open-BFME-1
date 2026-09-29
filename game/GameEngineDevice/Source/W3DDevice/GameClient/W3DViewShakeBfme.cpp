// ?shake@W3DView@@UAEXPBUCoord3D@@W4CameraShakeType@@@Z
// Retail 0x0073D2A0, reached through ILT 0x00016DD3 from the W3DView vtable
// slot at rdata 0x00D21948 (31 slots after setZoom).  The ZH body unchanged:
// a random shake angle, the intensity for the shake type, fall-off with the
// distance from the camera position, then the clamp to the maximum.
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CameraShakeType
{
	SHAKE_SUBTLE = 0,
	SHAKE_NORMAL,
	SHAKE_STRONG,
	SHAKE_SEVERE,
	SHAKE_CINE_EXTREME,
	SHAKE_CINE_INSANE,
	SHAKE_COUNT
};

struct Rva006C9270GlobalData
{
	unsigned char m_padding0000[0xC10];
	Real m_shakeSubtleIntensity;
	Real m_shakeNormalIntensity;
	Real m_shakeStrongIntensity;
	Real m_shakeSevereIntensity;
	Real m_shakeCineExtremeIntensity;
	Real m_shakeCineInsaneIntensity;
	Real m_maxShakeIntensity;
	Real m_maxShakeRange;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, int line);

class W3DView
{
public:
	virtual void shake(const Coord3D *epicenter, CameraShakeType shakeType);

private:
	unsigned char m_padding0004[0x08];
	Coord3D m_pos;
	unsigned char m_padding0018[0x120 - 0x18];
	Real m_shakeAngleCos;
	Real m_shakeAngleSin;
	Real m_shakeIntensity;
};

void W3DView::shake(const Coord3D *epicenter, CameraShakeType shakeType)
{
	Real angle = GetGameClientRandomValueReal(0, 2 * 3.14159265359f,
		"F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\W3DView.cpp", 0x15AA);

	m_shakeAngleCos = (Real)cos(angle);
	m_shakeAngleSin = (Real)sin(angle);

	Real intensity = 0.0f;
	switch (shakeType)
	{
		case SHAKE_SUBTLE:
			intensity = TheWritableGlobalData->m_shakeSubtleIntensity;
			break;

		case SHAKE_NORMAL:
			intensity = TheWritableGlobalData->m_shakeNormalIntensity;
			break;

		case SHAKE_STRONG:
			intensity = TheWritableGlobalData->m_shakeStrongIntensity;
			break;

		case SHAKE_SEVERE:
			intensity = TheWritableGlobalData->m_shakeSevereIntensity;
			break;

		case SHAKE_CINE_EXTREME:
			intensity = TheWritableGlobalData->m_shakeCineExtremeIntensity;
			break;

		case SHAKE_CINE_INSANE:
			intensity = TheWritableGlobalData->m_shakeCineInsaneIntensity;
			break;
	}

	// intensity falls off with distance
	const Coord3D *position = &m_pos;
	Coord3D dir;
	dir.x = epicenter->x - position->x;
	dir.y = epicenter->y - position->y;
	dir.z = 0.0f;
	Real dist = (Real)sqrt(dir.x * dir.x + dir.y * dir.y);

	if (dist > TheWritableGlobalData->m_maxShakeRange)
		return;

	intensity *= 1.0f - (dist / TheWritableGlobalData->m_maxShakeRange);

	// add intensity and clamp
	m_shakeIntensity += intensity;

	if (m_shakeIntensity > TheWritableGlobalData->m_maxShakeIntensity)
		m_shakeIntensity = TheWritableGlobalData->m_maxShakeIntensity;
}

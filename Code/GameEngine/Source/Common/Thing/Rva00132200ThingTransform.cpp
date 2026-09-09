// ?rva00132200@Thing@@QAEXPBVMatrix3D@@@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// The retail body at 0x00132200 is the old-transform callback variant used by
// Thing position setters.  Its surviving callers establish Thing ownership,
// while the distinct no-argument setter at 0x00132350 retains the published
// setTransformMatrix spelling.  Keep this method RVA-derived until the
// original lexical split is recovered.

#include "Lib/BaseType.h"
#include "WWMath/matrix3d.h"

class Thing
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void reactToTransformChange(const Matrix3D *oldMtx,
		const Coord3D *oldPos, Real oldAngle) = 0;

	void rva00132200(const Matrix3D *mx);

private:
	unsigned char m_pad04[4];
	Matrix3D m_transform;
	Coord3D m_cachedPos;
	Real m_cachedAngle;
	unsigned char m_pad48[0x14];
	unsigned int m_cacheFlags;
};

void Thing::rva00132200(const Matrix3D *mx)
{
	const Coord3D *cachedPos = &m_cachedPos;
	Real oldAngle = m_cachedAngle;
	Coord3D oldPos;
	oldPos.x = cachedPos->x;
	oldPos.y = cachedPos->y;
	oldPos.z = cachedPos->z;
	Matrix3D oldMtx = m_transform;

	m_transform = *mx;
	*(volatile Real *)&m_cachedPos.x = m_transform.Get_X_Translation();
	*(volatile Real *)&m_cachedPos.y = m_transform.Get_Y_Translation();
	*(volatile Real *)&m_cachedPos.z = m_transform.Get_Z_Translation();
	m_cachedAngle = m_transform.Get_Z_Rotation();
	m_cacheFlags = 0;

	reactToTransformChange(&oldMtx, &oldPos, oldAngle);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the dynamic-shroud decal animation to clean C++.

#include <math.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }

private:
	unsigned char m_unreconstructed_00[0x38];
	Coord3D m_cachedPos;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void setPosition(const Coord3D &);
	void setOpacity(float);

private:
	unsigned char m_unreconstructed_00[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdate
{
public:
	void animateGridDecals();

private:
	unsigned char m_unreconstructed_00[0x08];
	Object *m_object;
	unsigned char m_unreconstructed_0c[0x18];
	int m_stateCountDown;
	int m_totalFrames;
	unsigned char m_unreconstructed_2c[0x1c];
	float m_nativeClearingRange;
	float m_currentClearingRange;
	RadiusDecal m_gridDecal[30];
};

// ?animateGridDecals@DynamicShroudClearingRangeUpdate@@QAEXXZ
void DynamicShroudClearingRangeUpdate::animateGridDecals()
{
	const Coord3D *center = m_object->getPosition();
	Coord3D position;
	position.z = 0.0f;

	float radius = m_currentClearingRange + ((m_totalFrames - m_stateCountDown) * 2);
	float angle = 0.0f;
	float angleIncrement = (3.14159265358979323846f * 2.0f) / 30.0f;
	float opacity = 1.0f - (m_currentClearingRange / m_nativeClearingRange);

	for (int decal = 0; decal < 30; ++decal)
	{
		position.x = center->x + sinf(angle) * radius;
		position.y = center->y + cosf(angle) * radius;
		position.x -= ((int)position.x) % 23;
		position.y -= ((int)position.y) % 23;
		m_gridDecal[decal].setPosition(position);
		m_gridDecal[decal].setOpacity(opacity);
		angle += angleIncrement;
	}
}

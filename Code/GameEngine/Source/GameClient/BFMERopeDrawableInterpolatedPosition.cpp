// cl: /DNDEBUG /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeVector3
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	unsigned char m_unreconstructed_000[0x38];
	float m_interpolationFactor;
};

extern GameEngine *TheGameEngine;

extern BfmeVector3 *__stdcall bfmeVec3Hermite(
	BfmeVector3 *result,
	const Coord3D *position0,
	const Coord3D *tangent0,
	const Coord3D *position1,
	const Coord3D *tangent1,
	float factor);

class BFMERopeDrawableGetPositionShim
{
private:
	unsigned char m_unreconstructed_000[0x38];
	Coord3D m_basePosition;
	unsigned char m_unreconstructed_044[0x0FC - 0x044];
	void *m_object;
	unsigned char m_unreconstructed_100[0x230 - 0x100];
	Coord3D m_interpolatedPosition;
	unsigned char m_unreconstructed_23C[0x37C - 0x23C];
	Coord3D m_position0;
	Coord3D m_tangent0;
	Coord3D m_position1;
	Coord3D m_tangent1;
	unsigned char m_unreconstructed_3AC[0x3B4 - 0x3AC];
	bool m_interpolationReady;

	void bfmeRebuild(int force);

public:
	const Coord3D *get() const;
};

const Coord3D *BFMERopeDrawableGetPositionShim::get() const
{
	if (!m_object)
		return &m_basePosition;

	BFMERopeDrawableGetPositionShim *self =
		const_cast<BFMERopeDrawableGetPositionShim *>(this);
	if (!m_interpolationReady)
		self->bfmeRebuild(0);

	Coord3D interpolated;
	BfmeVector3 result;
	bfmeVec3Hermite(
		&result,
		&m_position0,
		&m_tangent0,
		&m_position1,
		&m_tangent1,
		TheGameEngine->m_interpolationFactor);

	interpolated.x = result.x;
	interpolated.y = result.y;
	interpolated.z = result.z;
	self->m_interpolatedPosition = interpolated;
	return &m_interpolatedPosition;
}

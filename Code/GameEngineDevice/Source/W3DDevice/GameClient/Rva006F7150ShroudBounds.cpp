// ?check@Rva006F7150@@QAEHH@Z
// Retail 0x006F7150: exact 398-byte shroud-boundary check. The volatile
// matrix X read preserves the observed x87 operand order at +0x51.
// RVA 0x006F7150: opaque shroud-boundary predicate with decoded ABI.
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
#include "matrix3d.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex,
		const Coord3D *position) const;
};

extern PartitionManager *TheShroudManager;

class BfmeCalc919G
{
public:
	int bfmeCalc919G();
};

static __forceinline void transformBounds(const Matrix3D &matrix, const Vector3 &input, Vector3 *output)
{
    Vector3 temporary;
    const Vector3 *value;
    if (output == &input) {
        temporary = input;
        value = &temporary;
    } else {
        value = &input;
    }
    output->X = (matrix[0][2] * value->Z + matrix[0][1] * value->Y) + (*(volatile const float *)&matrix[0][0]) * value->X + matrix[0][3];
    output->Y = matrix[1][0] * value->X + matrix[1][1] * value->Y + matrix[1][2] * value->Z + matrix[1][3];
    output->Z = matrix[2][0] * value->X + matrix[2][1] * value->Y + matrix[2][2] * value->Z + matrix[2][3];
}

class Rva006F7150
{
public:
	int check(int playerIndex);

private:
	Coord3D m_destination;
	float m_radius;
	Coord3D m_local;
	char m_padding1c[0x0c];
	BfmeCalc919G *m_matrixSource;
};

// ?check@Rva006F7150@@QAEHH@Z
int Rva006F7150::check(int playerIndex)
{
    if (TheShroudManager != 0)
    {
        if (m_matrixSource != 0)
        {
            transformBounds(*reinterpret_cast<const Matrix3D *>(m_matrixSource->bfmeCalc919G()), *reinterpret_cast<const Vector3 *>(&m_local), reinterpret_cast<Vector3 *>(&m_destination));
        }
        Coord3D sample;
        sample.x = m_destination.x;
        sample.y = m_destination.y;
        sample.z = m_destination.z;
        if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &sample) == CELLSHROUD_CLEAR)
            return 1;
        sample.x = m_radius + m_destination.x;
        sample.y = m_destination.y;
        sample.z = m_destination.z;
        if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &sample) == CELLSHROUD_CLEAR)
            return 1;
        sample.x = m_destination.x - m_radius;
        sample.y = m_destination.y;
        sample.z = m_destination.z;
        if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &sample) == CELLSHROUD_CLEAR)
            return 1;
        sample.x = m_destination.x;
        sample.y = m_radius;
        sample.y += m_destination.y;
        sample.z = m_destination.z;
        if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &sample) == CELLSHROUD_CLEAR)
            return 1;
        sample.x = m_destination.x;
        sample.y = m_destination.y - m_radius;
        sample.z = m_destination.z;
        if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &sample) == CELLSHROUD_CLEAR)
            return 1;
    }
    return 0;
}

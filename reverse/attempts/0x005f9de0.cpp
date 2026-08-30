// ?d_005f9de0@@YAXXZ
// partial score=0.94 date=2026-08-30
#include "System/game_client_random_variable.h"

struct BfmeVec1284
{
	BfmeVec1284(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

	float x;
	float y;
	float z;
};

class BfmeA1284
{
public:
	BfmeVec1284 bfmeSample1284(int, int);
	char m_bfmePad00[0x1c];
	GameClientRandomVariable m_x;
	GameClientRandomVariable m_y;
	GameClientRandomVariable m_z;
};

BfmeVec1284 BfmeA1284::bfmeSample1284(int, int)
{
	float x = m_x.getValue();
	float y = m_y.getValue();
	float z = m_z.getValue();
	return BfmeVec1284(x, y, z);
}

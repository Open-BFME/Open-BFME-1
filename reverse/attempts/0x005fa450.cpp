// ?d_005fa450@@YAXXZ
// partial score=0.91 date=2026-09-17
// Retail proves a __stdcall helper with three float ABI arguments. It fills
// two native Coord3D values, raises one Z value by the double at RVA
// 0x00C7FD90, and calls the tactical-view vtable at slot 11 with the color
// 0xCCAAFFFF and a zero flag.
// The address-derived name remains intentional because no named caller or
// owning class proves the identity.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Coord3D : public Coord3DBase
{
public:
	Coord3D() {}
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	~Coord3D() {}
};

class TacticalViewRva005FA450
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void drawLine(Coord3D *from, Coord3D *to,
		unsigned int colour, int flag);
};

extern TacticalViewRva005FA450 *TheTacticalViewRva005FA450;
extern const double g_liftK;

void __stdcall Rva005FA450DrawLine(float x, float y, float z)
{
	Coord3D lifted;
	Coord3D ground;

	ground.x = x;
	ground.y = y;
	ground.z = z;

	lifted.x = x;
	lifted.y = y;
	lifted.z = (float)(z + g_liftK);

	TheTacticalViewRva005FA450->drawLine(&ground, &lifted,
		0xccaaffff, 0);
}

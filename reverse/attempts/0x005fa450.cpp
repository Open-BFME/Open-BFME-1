// ?Rva005FA450Draw@PointEmissionVolumeModule@FXParticleSystem@@UAEXMMM@Z
// partial score=0.91 date=2026-09-17
// The primary PointEmissionVolumeModule vtable at 0x011122E0 carries the
// 0x0001E22C ILT in slot 4; vtable_lookup ties that table to the Point module
// constructor and initializePointEmissionVolumeModule.  The method name is
// address-derived because no historical semantic name is proven.  The
// constructor witnesses a 0x24-byte object with secondary tables at +0x14,
// +0x18, and +0x1c, but this body reads no module member.
namespace FXParticleSystem {

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

class View
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28();
	virtual void Rva0045BA00Slot(const Coord3D *from, const Coord3D *to,
		unsigned int colour, unsigned int flags);
};

class PointEmissionVolumeModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void Rva005FA450Draw(float x, float y, float z);
	virtual void slot05();
	virtual void slot06();

private:
	// The constructor witness makes the primary view 0x24 bytes.  The
	// secondary vptrs at +0x14/+0x18/+0x1c are intentionally not modelled in
	// this method-only ABI view because the body never dereferences this.
	unsigned char opaquePrimaryTail[0x20];
};

extern View *TheTacticalView;
extern const double g_liftK;

void PointEmissionVolumeModule::Rva005FA450Draw(float x, float y, float z)
{
	Coord3D lifted;
	Coord3D ground;

	ground.x = x;
	ground.y = y;
	ground.z = z;

	lifted.x = x;
	lifted.y = y;
	lifted.z = (float)(z + g_liftK);

	TheTacticalView->Rva0045BA00Slot(&ground, &lifted,
		0xccaaffff, 0);
}

} // namespace FXParticleSystem

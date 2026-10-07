// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x005FAC90. Fills a local Coord3D through virtual slot four, then
// scales it component by component and returns the result through the hidden
// struct-return pointer (eax holds it at the ret, as ParticleSystem::
// computeParticleVelocity relies on). Nothing names the owning class, so it is address-derived.

struct Coord3D
{
	Coord3D() {}
	Coord3D(float xValue, float yValue, float zValue) : x(xValue), y(yValue), z(zValue) {}

	float x;
	float y;
	float z;
};

class Rva005FAC90Owner
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void sample(Coord3D *out, void *context, void *extra);

	Coord3D scale(void *context, const Coord3D *factors, float amount, void *extra);
};

Coord3D Rva005FAC90Owner::scale(void *context, const Coord3D *factors,
	float amount, void *extra)
{
	volatile Coord3D local;

	sample((Coord3D *)&local, context, extra);

	float x = local.x * factors->x * amount;
	float y = local.y * factors->y * amount;
	float z = local.z * factors->z * amount;

	return Coord3D(x, y, z);
}

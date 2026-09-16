// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x005FAC90. Fills a local Coord3D through virtual slot four, then
// scales it component by component and writes the result through the first
// argument. Nothing names the owning class, so it is address-derived.

struct Coord3D
{
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

	void scale(Coord3D *out, void *context, const Coord3D *factors, float amount,
		void *extra);
};

void Rva005FAC90Owner::scale(Coord3D *out, void *context, const Coord3D *factors,
	float amount, void *extra)
{
	volatile Coord3D local;

	sample((Coord3D *)&local, context, extra);

	float x = local.x * factors->x * amount;
	float y = local.y * factors->y * amount;
	float z = local.z * factors->z * amount;

	out->x = x;
	out->y = y;
	out->z = z;
}

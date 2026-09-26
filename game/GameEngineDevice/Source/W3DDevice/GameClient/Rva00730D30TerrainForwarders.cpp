// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Address-derived wrappers at 0x00730D30, 0x00730D50 and 0x00730D70.
// Each reads its own receiver's +0x10 slot. The owners are address-derived;
// the parameter types come from each independently decoded callee contract.

struct Coord3D;
class GeometryInfo;

class Rva006C8890Target
{
public:
	void forward(const Coord3D *point, float radius, void *context);
};

// BODY pin proposal for Rva006C8890Target::forward: 0x006C8890. Its retail
// body reads all three incoming words, passes point/radius to the 0x007023C0
// consumer, and passes point/radius/context to 0x00720C20. The latter's
// matched scan contract is (const Rva00720C20Coord3D &, float, void *); the
// former's matched body dereferences pointBits and interprets radiusBits as a
// float. These downstream contracts establish the argument ABI without
// retaining the legacy integer parameter declarations at that address.

class Rva00730D30Owner
{
public:
	void forward(const Coord3D *point, float radius, void *context);

private:
	char m_pad[0x10];
	Rva006C8890Target *m_target;
};

void Rva00730D30Owner::forward(const Coord3D *point, float radius,
	void *context)
{
	if (m_target)
		m_target->forward(point, radius, context);
}

class BfmeBaseHeightMapRenderObjClass
{
public:
	void removeTreesAndPropsForConstruction(const Coord3D *pos,
		const GeometryInfo &geom, float angle);
};

class Rva00730D50Owner
{
public:
	void forward(const Coord3D *pos, const GeometryInfo &geom, float angle);

private:
	char m_pad[0x10];
	BfmeBaseHeightMapRenderObjClass *m_target;
};

void Rva00730D50Owner::forward(const Coord3D *pos,
	const GeometryInfo &geom, float angle)
{
	if (m_target)
		m_target->removeTreesAndPropsForConstruction(pos, geom, angle);
}

class BaseHeightMapRenderObjClass
{
public:
	void removeTreesAndPropsForConstruction(const Coord3D *pos,
		const GeometryInfo &geom, float angle);
};

class Rva00730D70Owner
{
public:
	void forward(const Coord3D *pos, const GeometryInfo &geom, float angle);

private:
	char m_pad[0x10];
	BaseHeightMapRenderObjClass *m_target;
};

void Rva00730D70Owner::forward(const Coord3D *pos,
	const GeometryInfo &geom, float angle)
{
	if (m_target)
		m_target->removeTreesAndPropsForConstruction(pos, geom, angle);
}

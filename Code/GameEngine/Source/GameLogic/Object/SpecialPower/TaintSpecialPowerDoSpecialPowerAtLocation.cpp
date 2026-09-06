// cl: /DNDEBUG /MD
//
// TaintSpecialPowerInterface::doSpecialPowerAtLocation, retail RVA 0x0026BF40.
//
// Identity: ??0TaintSpecialPower@@ stores vftable 0x00CB83E0 at object offset
// +0x10, and this body is that table's doSpecialPowerAtLocation slot -- the one
// the shared base body 0x0026A620 fills in every power that does not override
// it, and no other power's table points here.  `this` is the
// SpecialPowerModuleInterface sub-object; -0x10 reaches the TaintSpecialPower
// module, where +4 is the module data and +8 the object.
//
// The override refuses while the object is disabled, without a location, or
// while the module data's name field at +0x210 is empty, then runs the base
// doSpecialPowerAtLocation and one further module call at 0x0026B9D0 that has
// no identity yet.


typedef unsigned int UnsignedInt;

class Coord3D;

class SpecialPowerModuleInterface
{
public:
	void doSpecialPowerAtLocation(const Coord3D *loc, UnsignedInt commandOptions);
};

struct TaintNameString
{
	unsigned short *m_data;
};

struct TaintSpecialPowerModuleData
{
	char m_pad[0x210];
	TaintNameString m_name;
};

class TaintSpecialPower
{
public:
	void after(const Coord3D *loc);

	char m_pad00[4];
	TaintSpecialPowerModuleData *m_moduleData;
	void **m_object;
	char m_pad0C[4];
};

class TaintSpecialPowerInterface
{
public:
	void doSpecialPowerAtLocation(const Coord3D *loc, UnsignedInt commandOptions);
};

static TaintSpecialPower *taintSpecialPower(TaintSpecialPowerInterface *self)
{
	return (TaintSpecialPower *)((char *)self - 0x10);
}

void TaintSpecialPowerInterface::doSpecialPowerAtLocation(const Coord3D *loc, UnsignedInt commandOptions)
{
	if (taintSpecialPower(this)->m_object[0x1a4 / 4] != 0)
		return;
	if (loc == 0)
		return;
	TaintNameString *name = &taintSpecialPower(this)->m_moduleData->m_name;
	if (name->m_data == 0)
		return;
	if (name->m_data[2] == 0)
		return;
	((SpecialPowerModuleInterface *)this)->doSpecialPowerAtLocation(loc, commandOptions);
	taintSpecialPower(this)->after(loc);
}

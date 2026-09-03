// cl: /DNDEBUG /MD

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class Object;
class Coord3D;
class Waypoint;

class SpecialPowerModule
{
public:
	Bool initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos, const Waypoint *way, UnsignedInt commandOptions);
	void finishSpecialPower(UnsignedInt arg);
};

class Rva0026A620Owner
{
public:
	void apply(const Coord3D *loc, UnsignedInt commandOptions);

private:
	char m_pad00[8];
	Int m_count08;
};

struct Rva0026A620Primary
{
	char m_pad00[4];
	unsigned char *m_flagHost;
	void **m_gate;
	char m_pad0C[4];
	Rva0026A620Owner m_owner;
};

static Rva0026A620Primary *rva0026A620Primary(Rva0026A620Owner *self)
{
	return (Rva0026A620Primary *)((char *)self - 0x10);
}

// ?apply@Rva0026A620Owner@@QAEXPBUCoord3D@@I@Z
void Rva0026A620Owner::apply(const Coord3D *loc, UnsignedInt commandOptions)
{
	if ((commandOptions & 0x40000) == 0)
	{
		if (m_count08 > 0)
			return;
		if (rva0026A620Primary(this)->m_gate[0x1a4 / 4] != 0)
			return;
	}
	SpecialPowerModule *mod = (SpecialPowerModule *)rva0026A620Primary(this);
	mod->initiateIntentToDoSpecialPower(0, loc, (const Waypoint *)commandOptions, 0);
	if (rva0026A620Primary(this)->m_flagHost[0xc] == 0)
		mod->finishSpecialPower((UnsignedInt)loc);
}

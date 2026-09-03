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

class Rva0026A5B0Owner
{
public:
	void apply(Object *target, UnsignedInt commandOptions);

private:
	char m_pad00[8];
	Int m_count08;
};

struct Rva0026A5B0Primary
{
	char m_pad00[4];
	unsigned char *m_flagHost;
	void **m_gate;
	char m_pad0C[4];
	Rva0026A5B0Owner m_owner;
};

static Rva0026A5B0Primary *rva0026A5B0Primary(Rva0026A5B0Owner *self)
{
	return (Rva0026A5B0Primary *)((char *)self - 0x10);
}

// ?apply@Rva0026A5B0Owner@@QAEXPAVObject@@I@Z
void Rva0026A5B0Owner::apply(Object *target, UnsignedInt commandOptions)
{
	if ((commandOptions & 0x40000) == 0)
	{
		if (m_count08 > 0)
			return;
		if (rva0026A5B0Primary(this)->m_gate[0x1a4 / 4] != 0)
			return;
	}
	SpecialPowerModule *mod = (SpecialPowerModule *)rva0026A5B0Primary(this);
	mod->initiateIntentToDoSpecialPower(target, 0, (const Waypoint *)commandOptions, 0);
	if (rva0026A5B0Primary(this)->m_flagHost[0xc] == 0)
		mod->finishSpecialPower((UnsignedInt)target + 0x38);
}

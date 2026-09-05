// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5 candidate for 0x000E5B30 (202B). stdcall (object*, Coord3D*).
// Module at Object+0x204; helper from vcall +0x144; bool vcall +0x18;
// Coord3D vcall +0x40 else Object+0x38; float vcall +0x28; TheTerrainLogic
// thiscall query at ILT 0x0001DFED (body 0x001A6320).
// Query callback 0x001A3280 stores a pointer to the selected 48-byte record;
// its first member is the position. No vtables are instantiated by this TU.

struct Coord3D
{
	float x;
	float y;
	float z;
};

#define VDECL(N) virtual void *slot##N();

class BfmeE5B30Helper
{
public:
	VDECL(0) VDECL(1) VDECL(2) VDECL(3) VDECL(4) VDECL(5)
	virtual bool gate();					// +0x18  slot 6
	VDECL(7) VDECL(8) VDECL(9)
	virtual float radius();					// +0x28  slot 10
	VDECL(11) VDECL(12) VDECL(13) VDECL(14) VDECL(15)
	virtual bool tryPos(Coord3D *out);			// +0x40  slot 16
};

class BfmeE5B30Module
{
public:
	VDECL(0) VDECL(1) VDECL(2) VDECL(3) VDECL(4) VDECL(5) VDECL(6) VDECL(7)
	VDECL(8) VDECL(9) VDECL(10) VDECL(11) VDECL(12) VDECL(13) VDECL(14) VDECL(15)
	VDECL(16) VDECL(17) VDECL(18) VDECL(19) VDECL(20) VDECL(21) VDECL(22) VDECL(23)
	VDECL(24) VDECL(25) VDECL(26) VDECL(27) VDECL(28) VDECL(29) VDECL(30) VDECL(31)
	VDECL(32) VDECL(33) VDECL(34) VDECL(35) VDECL(36) VDECL(37) VDECL(38) VDECL(39)
	VDECL(40) VDECL(41) VDECL(42) VDECL(43) VDECL(44) VDECL(45) VDECL(46) VDECL(47)
	VDECL(48) VDECL(49) VDECL(50) VDECL(51) VDECL(52) VDECL(53) VDECL(54) VDECL(55)
	VDECL(56) VDECL(57) VDECL(58) VDECL(59) VDECL(60) VDECL(61) VDECL(62) VDECL(63)
	VDECL(64) VDECL(65) VDECL(66) VDECL(67) VDECL(68) VDECL(69) VDECL(70) VDECL(71)
	VDECL(72) VDECL(73) VDECL(74) VDECL(75) VDECL(76) VDECL(77) VDECL(78) VDECL(79)
	VDECL(80)
	virtual BfmeE5B30Helper *getHelper();			// +0x144 slot 81
};

class BfmeE5B30Object
{
public:
	unsigned char m_head[0x38];
	Coord3D m_pos;						// +0x38
	unsigned char m_mid[0x204 - 0x44];
	BfmeE5B30Module *m_module;				// +0x204
};

struct Bfme1A6320Record
{
	Coord3D position;
	unsigned char remainder[0x30 - sizeof(Coord3D)];
};

class TerrainLogic
{
public:
	Bfme1A6320Record *query1A6320(BfmeE5B30Object *obj, Coord3D *pos, float value);
};

extern TerrainLogic *TheTerrainLogic;

bool __stdcall rva000E5B30(BfmeE5B30Object *obj, Coord3D *out)
{
	if (obj)
	{
		BfmeE5B30Module *mod = obj->m_module;
		if (mod)
		{
			BfmeE5B30Helper *helper = mod->getHelper();
			if (helper)
			{
				if (helper->gate())
				{
					Coord3D pos;
					Coord3D tmp;
					if (helper->tryPos(&tmp))
						pos = tmp;
					else
						pos = obj->m_pos;

					Bfme1A6320Record *got = TheTerrainLogic->query1A6320(obj, &pos, helper->radius());
					if (!got)
						return false;
					*out = got->position;
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

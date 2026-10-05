// cl: /O2 /DNDEBUG /MD

// Open-BFME7: near-twin of Rva008A48D0ReleaseGlobals.cpp (0x008A48D0, 131 B),
// same shape (release each ref-counted global through vtable slot +4, then
// null it), but with eight globals instead of six and a caller (0x00894A90,
// proven in an earlier attempt) at retail 0x008A47B0, 173 bytes. The eighth
// global (0x01337A88) sits out of address order at the end, matching the
// retail call order exactly.

class Rva00899FC0;
extern Rva00899FC0 *Va01337A7C;
class Rva00899FC0;
extern Rva00899FC0 *Va01337A80;
class Rva00899FC0;
extern Rva00899FC0 *Va01337A84;
class Rva00899FC0;
extern Rva00899FC0 *Va01337A88;
class Rva00899FC0;
extern Rva00899FC0 *Va01337A8C;
class Rva00899FC0;
extern Rva00899FC0 *Va01337A90;
class Rva00899FC0;
extern Rva00899FC0 *Va01337A94;
class Rva00899FC0;
extern Rva00899FC0 *Va01337A98;

class Rva008A47B0Item
{
public:
	virtual void unused0();
	virtual void release();
};










void rva008A47B0ReleaseGlobals()
{
	Rva008A47B0Item *z = 0;
	if (((Rva008A47B0Item *&)Va01337A7C) != z)
	{
		((Rva008A47B0Item *&)Va01337A7C)->release();
		((Rva008A47B0Item *&)Va01337A7C) = z;
	}
	if (((Rva008A47B0Item *&)Va01337A80) != z)
	{
		((Rva008A47B0Item *&)Va01337A80)->release();
		((Rva008A47B0Item *&)Va01337A80) = z;
	}
	if (((Rva008A47B0Item *&)Va01337A84) != z)
	{
		((Rva008A47B0Item *&)Va01337A84)->release();
		((Rva008A47B0Item *&)Va01337A84) = z;
	}
	if (((Rva008A47B0Item *&)Va01337A8C) != z)
	{
		((Rva008A47B0Item *&)Va01337A8C)->release();
		((Rva008A47B0Item *&)Va01337A8C) = z;
	}
	if (((Rva008A47B0Item *&)Va01337A90) != z)
	{
		((Rva008A47B0Item *&)Va01337A90)->release();
		((Rva008A47B0Item *&)Va01337A90) = z;
	}
	if (((Rva008A47B0Item *&)Va01337A94) != z)
	{
		((Rva008A47B0Item *&)Va01337A94)->release();
		((Rva008A47B0Item *&)Va01337A94) = z;
	}
	if (((Rva008A47B0Item *&)Va01337A98) != z)
	{
		((Rva008A47B0Item *&)Va01337A98)->release();
		((Rva008A47B0Item *&)Va01337A98) = z;
	}
	if (((Rva008A47B0Item *&)Va01337A88) != z)
	{
		((Rva008A47B0Item *&)Va01337A88)->release();
		((Rva008A47B0Item *&)Va01337A88) = z;
	}
}

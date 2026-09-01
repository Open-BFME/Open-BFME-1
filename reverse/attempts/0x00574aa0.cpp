// ?BfmeLess00574AA0@S4SortElem8@@QBE_NABU1@@Z
// partial score=0.94 date=2026-09-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString
{
public:
	~AsciiString();
	int bfmeCompare(AsciiString const &other) const;

private:
	char *Data;
};

class LivingWorldArmy
{
public:
	AsciiString getName() const;

	unsigned char Prefix[0x44];
	int SortKey;
};

class LivingWorldArmyState
{
public:
	unsigned char Prefix[0xD0];
	unsigned Unused : 25;
	unsigned Special : 1;
};

struct S4SortElem8
{
	LivingWorldArmy *Army;
	LivingWorldArmyState *State;

	bool BfmeLess00574AA0(S4SortElem8 const &other) const;
};

bool S4SortElem8::BfmeLess00574AA0(S4SortElem8 const &other) const
{
	if (State->Special != other.State->Special)
		return State->Special != 0;
	if (Army->SortKey != other.Army->SortKey)
		return Army->SortKey > other.Army->SortKey;
	return Army->getName().bfmeCompare(other.Army->getName()) < 0;
}

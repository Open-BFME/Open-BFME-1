// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// MapObject::verifyValidTeam, retail RVA 0x000889A0, 157 bytes.
// The BFME dictionary and StringBase ABI are distinct from the Zero Hour
// headers used by WorldHeightMap.cpp; StringInline.h supplies the existing
// one-pointer by-value string model and its proven StringBase forwarding
// constructors without redeclaring a covered string type here.

#include "StringInline.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern const StaticNameKey TheKey_originalOwner;

class Dict
{
public:
	AsciiString getAsciiString(NameKeyType key, bool *exists = 0) const;
	bool remove(NameKeyType key);
};

class MapObject
{
public:
	Dict *getProperties()
	{
		return &m_properties;
	}

	void verifyValidTeam();

private:
	char m_prefix[0x24];
	Dict m_properties;
};

class Rva0019C520Owner
{
public:
	int forward(AsciiString name, int extra);
};

// Canonical retail type of the 0x012EF428 singleton; pointee only, so a forward
// declaration is enough.  The definition lives in
// game/GameEngine/Source/Common/System/game_engine_subsystems.h.
class SidesList;

// Retail global at 0x012EF428, ?TheSidesList@@3PAVSidesList@@A.  The member
// call shape is taken through the TU-local ABI view below.
extern SidesList *TheSidesList;

void MapObject::verifyValidTeam()
{
	bool exists;
	AsciiString teamName = getProperties()->getAsciiString(
		TheKey_originalOwner.key(), &exists);
	if (exists)
	{
		if (!((Rva0019C520Owner *)TheSidesList)->forward(teamName, 0))
			getProperties()->remove(TheKey_originalOwner.key());
	}
}

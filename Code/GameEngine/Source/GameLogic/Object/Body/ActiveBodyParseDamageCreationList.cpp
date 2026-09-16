// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x00211940, 182 bytes.  The INI field parser for DamageCreationList.
//
// IDENTITY.  The only reference to this body in the image is the FieldParse row
// at VA 0x010A7B78, whose name pointer reads DamageCreationList.  That row sits
// in the table starting at VA 0x010A7AA8, which opens with MaxHealth,
// MaxHealthDamaged, InitialHealth and RecoveryTime and goes on to GrabObject,
// GrabFX and CheerRadius, so the table is the body module data one and the
// parser goes beside the other converted ActiveBody bodies.  The table is
// handed to the registrar by the forwarder at 0x00211A30.
//
// WHAT IT PARSES.  One object creation list through the matched
// ?parseObjectCreationList@INI@@SAXPAV1@PAX1PBX@Z at 0x000B8F10, then two
// optional index tokens.  The name lists the two scanIndexList calls carry are
// the retail arrays at VA 0x012AE2C4 and VA 0x012AE2D4, read straight out of
// the image.  The three values go into one 12-byte record appended to the
// vector at instance+0x50.  The record type is spelled State::TransitionInfo
// because that is the element type retail's own
// vector<State::TransitionInfo>::_M_insert_overflow symbol carries at the
// overflow call.

#include <vector>

class ObjectCreationList;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	static int scanIndexList(const char *token, const char *const *names);
	static void parseObjectCreationList(INI *, void *, void *, const void *);

private:
	char m_unreconstructed_000[0x41c];
};

class State
{
public:
	struct TransitionInfo
	{
		const ObjectCreationList *ocl;
		int rock;
		int side;
	};
};

class BfmeDamageModuleData
{
public:
	char m_unreconstructed_000[0x50];
	_STL::vector<State::TransitionInfo> m_damageCreationList;	// +0x50
};

static const char *const theRockNames[] =
{
	"NONE", "CATAPULT_ROCK", "TREBUCHET_ROCK", 0
};

static const char *const theDamageSideNames[] =
{
	"NONE", "FRONT_DESTROYED", "RIGHT_DESTROYED", "BACK_DESTROYED",
	"LEFT_DESTROYED", 0
};

// ?parseDamageCreationList@@YAXPAVINI@@PAX1PBX@Z
void parseDamageCreationList(INI *ini, void *instance, void *store,
	const void *userData)
{
	State::TransitionInfo info;

	INI::parseObjectCreationList(ini, instance, &info.ocl, 0);

	const char *token = ini->getNextTokenOrNull(0);
	info.rock = token ? INI::scanIndexList(token, theRockNames) : 0;

	token = ini->getNextTokenOrNull(0);
	info.side = token ? INI::scanIndexList(token, theDamageSideNames) : 0;

	((BfmeDamageModuleData *)instance)->m_damageCreationList.push_back(info);
}

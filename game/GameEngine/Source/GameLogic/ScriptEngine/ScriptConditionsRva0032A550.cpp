// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0032A550, 348 bytes: 0x144 bytes of code, then the 24-byte
// comparison jump table (the old 252-byte ledger extent stopped inside the code).
//
// Identity: reached only from the matched condition dispatcher Rva0032D720::evaluate
// through ILT j_00004066 with five Parameters. It builds an object-distance context
// (center from ScriptEngine slot 26 resolveUnit, squared radius clamped to
// BfmeZeroRange), lets Player::iterateObjects run the visitor at 0x0032A490 for each
// player in the mask until the count passes the limit, then compares the count with
// the comparison parameter. No Zero Hour name fits, so the name keeps the address token.

typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern const float BfmeZeroRange;

class Object;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// The constructor lives at retail 0x00324540 (R3ScalarFieldConstructors.cpp).
struct Rva00324540
{
	Rva00324540();

	Coord3D m_center;
	Real m_radiusSquared;
	Int m_count;
	Int m_maxCount;
};

int rva0032a490(Object *object, Rva00324540 *context);

class Parameter
{
public:
	Int getInt() const { return m_int; }
	Real getReal() const { return m_real; }

	unsigned char m_pad00[0x08];
	Int m_int;
	Real m_real;
};

class Rva0032A550Position
{
public:
	unsigned char m_before[0x38];
	Coord3D m_position;
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual Rva0032A550Position *resolveUnit(Parameter *parameter);	// vtable+0x68

	UnsignedShort unidentified_0034DB40(Parameter *parameter);
};
extern ScriptEngine *TheScriptEngine;

typedef void (*ObjectIterateFunc)(Object *, void *);

class Player
{
public:
	void iterateObjects(ObjectIterateFunc routine, void *state) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &maskToAdjust);
};
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool rva0032A550(Parameter *pPlayerParm, Parameter *pComparisonParm,
		Parameter *pCountParm, Parameter *pDistanceParm, Parameter *pUnitParm);
};

Bool ScriptConditions::rva0032A550(Parameter *pPlayerParm, Parameter *pComparisonParm,
	Parameter *pCountParm, Parameter *pDistanceParm, Parameter *pUnitParm)
{
	UnsignedShort playerMask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	Int limit = pCountParm->getInt();
	Rva00324540 context;

	Real distance = pDistanceParm->getReal();
	if (distance < BfmeZeroRange)
		distance = BfmeZeroRange;
	context.m_maxCount = limit;
	context.m_radiusSquared = distance * distance;

	Rva0032A550Position *unit = TheScriptEngine->resolveUnit(pUnitParm);
	if (unit)
	{
		context.m_center = unit->m_position;
	}
	else
	{
		context.m_center.x = 0;
		context.m_center.y = 0;
		context.m_center.z = 0;
		context.m_radiusSquared = -1.0f;
	}

	while (playerMask && context.m_count <= limit)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player)
			player->iterateObjects((ObjectIterateFunc)rva0032a490, &context);
	}

	Int count = context.m_count;
	Bool result;
	switch (pComparisonParm->getInt())
	{
	case 0: result = count < limit; break;
	case 1: result = count <= limit; break;
	case 2: result = count == limit; break;
	case 3: result = count >= limit; break;
	case 4: result = count > limit; break;
	case 5: result = count != limit; break;
	default: result = false; break;
	}
	return result;
}

// cl: /O2 /DNDEBUG /DWIN32 /MD
//
// Weapon-nugget helper that fills a DamageInfo from a source-id record, a
// Thing with a position at +0x38, and this nugget's stored scalars.  Sibling
// of the banked 0x002DC8B0 attempt (same dest layout, same fabs-epsilon Z
// fixup, same 1<<playerIndex mask).  Address-derived name: no recovered owner.

extern "C" float fabs(float value);
extern "C" float sqrt(float value);
#pragma intrinsic(fabs, sqrt)

extern const float BfmeZeroRange;
extern const float Rva0109BF40ZeroRange;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct IdRecord002DD390
{
	unsigned char m_unreconstructed00[8];
	int m_id;
};

struct BFMEDamageInfo
{
	unsigned char m_unreconstructed00[8];
	int m_sourceID;
	unsigned short m_sourcePlayerMask;
	unsigned char m_unreconstructed0e[0x24 - 0x0e];
	float m_distance24;
	unsigned char m_unreconstructed28[4];
	int m_sourceObjectID2c;
	Coord3D m_delta30;
	int m_ownerValue3c;
	int m_ownerValue40;
	int m_ownerValue44;
	int m_ownerValue48;
};

class Player
{
public:
	unsigned char m_unreconstructed00[0x24];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;

	unsigned char m_gap00[0x38];
	Coord3D m_position;
	unsigned char m_gap44[0x74 - 0x44];
	int m_id;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class FillDamageInfo002DD390
{
public:
	bool fill(IdRecord002DD390 *record, Object *thing, BFMEDamageInfo *dest);

	unsigned char m_gap00[0x58];
	int m_value58;
	int m_value5c;
	int m_value60;
	int m_value64;
	float m_value68;
	int m_value6c;
	unsigned int m_value70;
	unsigned char m_flag74;
};

bool FillDamageInfo002DD390::fill(IdRecord002DD390 *record, Object *thing, BFMEDamageInfo *dest)
{
	IdRecord002DD390 *rec = record;
	Coord3D delta;
	if (rec == 0 || thing == 0)
		return false;

	Object *source = TheGameLogic->findObjectByID(rec->m_id);
	if (source == 0)
		return false;

	BFMEDamageInfo *out = dest;
	out->m_ownerValue3c = m_value58;

	if (!m_flag74)
	{
		delta.x = thing->m_position.x;
		delta.y = thing->m_position.y;
		delta.z = thing->m_position.z;
		delta.x -= source->m_position.x;
		delta.y -= source->m_position.y;
		delta.z -= source->m_position.z;
	}
	else
	{
		delta.x = source->m_position.x;
		delta.y = source->m_position.y;
		delta.z = source->m_position.z;
		delta.x -= thing->m_position.x;
		delta.y -= thing->m_position.y;
		delta.z -= thing->m_position.z;
	}

	if (fabs(delta.x) < Rva0109BF40ZeroRange &&
		fabs(delta.y) < Rva0109BF40ZeroRange &&
		fabs(delta.z) < Rva0109BF40ZeroRange)
		delta.z = 1.0f;

	out->m_delta30 = delta;
	out->m_ownerValue40 = m_value5c;
	out->m_ownerValue44 = m_value64;
	out->m_ownerValue48 = m_value6c;

	out->m_distance24 = (float)m_value70;
	if (m_value68 > BfmeZeroRange)
	{
		out->m_distance24 =
			sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) /
			m_value68 + out->m_distance24;
	}

	out->m_sourceObjectID2c = source->m_id;

	Player *player = source->getControllingPlayer();
	if (player != 0)
	{
		player = source->getControllingPlayer();
		out->m_sourcePlayerMask =
			(unsigned short)(1 << player->m_playerIndex);
	}

	out->m_sourceID = rec->m_id;
	player = source->getControllingPlayer();
	out->m_sourcePlayerMask =
		(unsigned short)(1 << player->m_playerIndex);
	return true;
}

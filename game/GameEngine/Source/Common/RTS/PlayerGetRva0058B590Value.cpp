// cl: /O2 /Ob1
// stlport
//
// Player::getRva0058B590Value, 0x000D6100, 236 bytes (ret 4 at +0xE9).
// Identity: the matched Rva0058B590Value::get (0x0058B590) calls this through
// ILT 0x0001D287 with ECX = player and its data's +0x70 key on the unscaled
// path. The body walks the player's +0x640 entry list, keeps entries whose
// object (looked up by id in TheGameLogic's +0xB0 object hash) is live (status
// bit 3 clear) and whose key matches, and takes the n-th such entry's n-th
// value. The result is then scaled and floored exactly as the wrapper's scaled
// path does. The method name keeps the wrapper's address token.

#include <hash_map>
#include <vector>

#ifndef NULL
#define NULL 0
#endif

extern "C" __declspec(dllimport) double __cdecl floor( double );

#include "../../../Include/Common/ScalarTypes.h"



extern const float g_rva01075350;		// VA 0x01075350, 0.0f

extern const float g_rva0107533C;

__forceinline long rva0058B590FloatToLong( float value )
{
	volatile long result;
	__asm {
		fld value
		fistp result
	}
	return result;
}

class Object
{
public:
	unsigned char m_pad00[0x118];
	unsigned char m_status;					// +0x118
};

typedef _STL::hash_map<int, Object*, _STL::hash<int>, _STL::equal_to<int> > ObjectHash;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad00[0xb0];
	ObjectHash m_objectHash;				// +0xB0
};

extern GameLogic *TheGameLogic;

struct PlayerValueEntry0058B590
{
	Int *m_key;						// +0x00
	_STL::vector<Real> m_values;				// +0x04
	UnsignedInt m_objectID;					// +0x10
};

struct PlayerValueNode0058B590
{
	PlayerValueNode0058B590 *m_next;
	PlayerValueNode0058B590 *m_prev;
	PlayerValueEntry0058B590 *m_value;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	long getRva0058B590Value( int value ) const;

private:
	unsigned char m_pad00[0x640];
	PlayerValueNode0058B590 *m_valueList;			// +0x640
};

long Player::getRva0058B590Value( int value ) const
{
	Real result = g_rva01075350;
	UnsignedInt valueIndex = 0;
	PlayerValueNode0058B590 *anchor = m_valueList;
	PlayerValueNode0058B590 *node = anchor->m_next;

	if (node != anchor)
	{
		while (node != anchor)
		{
			PlayerValueEntry0058B590 *entry = node->m_value;
			if (entry->m_objectID != 0)
			{
				ObjectHash::iterator found = TheGameLogic->m_objectHash.find(entry->m_objectID);
				if (found != TheGameLogic->m_objectHash.end())
				{
					Object *object = found->second;
					if (object != NULL && (object->m_status & 8) == 0)
					{
						if (*entry->m_key == value)
						{
							UnsignedInt count = entry->m_values.size();
							if (valueIndex < count)
								result = entry->m_values[valueIndex];
							++valueIndex;
						}
					}
				}
			}
			node = node->m_next;
		}
	}

	result *= 100.0f;
	result = g_rva0107533C - result;
	return rva0058B590FloatToLong( (float)floor( (double)result ) );
}

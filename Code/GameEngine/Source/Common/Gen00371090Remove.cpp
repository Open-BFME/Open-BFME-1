// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB
// Keyed removal body at retail 0x00371090.  The owner contains an STLport
// map<NameKeyType, Real> at +0xF4; the incoming object supplies the key at
// +0x74 and is notified before the map iterator is erased.

// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <set>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
typedef float Real;

enum ModelConditionFlagType
{
	MODEL_CONDITION_FLAG_UNUSED = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void clearModelConditionState(ModelConditionFlagType flag);
};

class BfmeKeyThing
{
public:
	NameKeyType getKey() const
	{
		return m_key;
	}

private:
	unsigned char m_pad00[0x74];
	NameKeyType m_key;
};

typedef _STL::set<NameKeyType> BfmeKeySet;
typedef _STL::map<NameKeyType, Real> BfmeKeyFindMap;

class Gen_00371090
{
public:
	void bfmeRemove(BfmeKeyThing *value);

	private:
	unsigned char m_pad00[0xF4];
	BfmeKeySet m_map;
};

// ?bfmeRemove@Gen_00371090@@QAEXPAVBfmeKeyThing@@@Z
void Gen_00371090::bfmeRemove(BfmeKeyThing *value)
{
	if (value != 0)
	{
		BfmeKeyFindMap *findMap = (BfmeKeyFindMap *)&m_map;
		BfmeKeyFindMap::iterator found = findMap->find(value->getKey());
		if (found != findMap->end())
		{
			((Object *)value)->clearModelConditionState(
				(ModelConditionFlagType)0x54);
			BfmeKeySet::iterator erasePosition =
				*(BfmeKeySet::iterator *)(void *)&found;
			m_map.erase(erasePosition);
		}
	}
}

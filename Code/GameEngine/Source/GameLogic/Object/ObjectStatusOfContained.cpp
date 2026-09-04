// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: ObjectStatusOfContained INI callback, retail 0x00227430, 78 bytes.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;

class INI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags() { }
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class ObjectStatusOfContainedFields
{
private:
	unsigned char m_padding[0x156];

public:
	Bool m_objectStatusOfContained;
};

void parseObjectStatusOfContained(INI *ini, void *instance, void *store, const void *userData)
{
	ObjectStatusMaskType status;
	BitFlags<45>::parseFromINI(ini, instance, &status, 0);
	*(ObjectStatusMaskType *)store = status;
	((ObjectStatusOfContainedFields *)instance)->m_objectStatusOfContained = true;
}

// ?Rva0036E650BuildListDispatch@@YAXPAVRva0036E650Owner@@PAX1@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/namekeygenerator /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: retail 0x0036E650, 433 bytes.
//
// The owning type is not identified by a direct caller.  Its proven layout is
// the vector-like range at +0x54 and the STLport map at +0x6c.  The map value
// is the narrow string whose data is read at node+0x14; the other range carries
// the same string plus the observed four-byte companion at +4.

#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include "Common/AsciiString.h"

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0, NAMEKEY_MIN = (-2147483647 - 1), NAMEKEY_MAX = 2147483647
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AsciiStringBN
{
public:
	AsciiString m_name;
	Int m_index;
};

class ThingTemplate;
class ThingFactory
{
public:
    ThingTemplate *findTemplate(const AsciiString &name);
};
class BfmeOtherBN;

extern BfmeOtherBN *g_bfmeOtherBN;

class BfmeResGH
{
public:
	void bfmeTwoGH(void *first, void *second);
};

struct BfmeIndexedMapRecord
{
	char m_data[140];
};

class BfmeIndexedMapConsumer
{
public:
	void bfmeUse(BfmeIndexedMapRecord *record);
};

class BfmeIndexedMapOwner
{
public:
	bool bfmeFindAndUse(Int key, Int index, BfmeIndexedMapConsumer *consumer);
};

class Rva0036E650Owner;
void Rva0036E650BuildListDispatch(
	Rva0036E650Owner *owner,
	void *first,
	void *second);

class BuildListInfo
{
public:
	BuildListInfo();
	__declspec(noinline) AsciiString getTemplateName() const { return m_templateName; }

private:
	AsciiString m_buildingName;
	AsciiString m_templateName;
	char m_tail[0x80];

protected:
	virtual ~BuildListInfo();

	friend void Rva0036E650BuildListDispatch(
		Rva0036E650Owner *owner,
		void *first,
		void *second);
};

class SidesList
{
};

extern SidesList *TheSidesList;

typedef _STL::map<Int, AsciiString> Rva0036E650NameMap;

class Rva0036E650Owner
{
public:
	char m_prefix[0x54];
	AsciiStringBN *m_begin;
	AsciiStringBN *m_end;
	char m_gap[0x10];
	Rva0036E650NameMap m_names;
};

void Rva0036E650BuildListDispatch(
	Rva0036E650Owner *owner,
	void *first,
	void *second)
{
	for (Rva0036E650NameMap::iterator it = owner->m_names.begin();
		it != owner->m_names.end(); ++it)
	{
		NameKeyType key = TheNameKeyGenerator->nameToKey(it->second.str());
		Int index = 0;
		BuildListInfo info;
		while (reinterpret_cast<BfmeIndexedMapOwner *>(TheSidesList)->bfmeFindAndUse(
			key, index, reinterpret_cast<BfmeIndexedMapConsumer *>(&info)))
		{
			++index;
			AsciiString name = info.getTemplateName();
			ThingTemplate *found = reinterpret_cast<ThingFactory *>(g_bfmeOtherBN)->findTemplate(name);
			if (found)
				reinterpret_cast<BfmeResGH *>(found)->bfmeTwoGH(first, second);
		}
	}

	unsigned count = (unsigned)(owner->m_end - owner->m_begin);
	for (unsigned index = 0; index < count; ++index)
	{
		const unsigned int begin = (unsigned int)owner->m_begin;
		AsciiStringBN name = *(const AsciiStringBN *)(begin + index * sizeof(AsciiStringBN));
		ThingTemplate *found = reinterpret_cast<ThingFactory *>(g_bfmeOtherBN)->findTemplate(name.m_name);
		if (found)
			reinterpret_cast<BfmeResGH *>(found)->bfmeTwoGH(first, second);
	}
}

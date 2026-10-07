// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame
// stlport

// The body calls the matched NAMEKEY helper at RVA 0x000A3AB0.
// Rename the inline header wrapper so this TU preserves that call.
#define NAMEKEY Rva0036EF70InlineNAMEKEY
#include "PreRTS.h"
#include "Libraries/Source/WWVegas/WWLib/string_base.h"
#include <map>
#include "Common/NameKeyGenerator.h"
#include "GameLogic/Object.h"
#undef NAMEKEY

NameKeyType NAMEKEY(const AsciiString &s);

typedef StringBase<char> Rva0036EF70String;

struct CastleUnpackCost
{
	Int m_unmodelled_00;
	UnsignedInt m_cost;
	Int m_minimumMoney;
};

class Rva0036EF70Sub
{
public:
	char m_pad00[0x6c];
	_STL::map<NameKeyType, CastleUnpackCost> m_bfme6c;
};

class Rva0036EF70Owner
{
public:
	NameKeyType d_0036ef70Method(void);

private:
	char m_unmodelled00[4];
	Rva0036EF70Sub *m_04;
	Object *m_08;
};

NameKeyType Rva0036EF70Owner::d_0036ef70Method(void)
{
	Rva0036EF70Sub *sub = m_04;
	NameKeyType resultKey = TheNameKeyGenerator->nameToKey("kq");

	Object *obj = m_08;
	if (obj)
	{
		Player *player = obj->getControllingPlayer();
		if (player)
		{
			// getControllingPlayer returns the witnessed Player type.
			// No BFME evidence names its member at +0x28.
			AsciiString name(*reinterpret_cast<const AsciiString *>(
				reinterpret_cast<const char *>(player) + 0x28));
			char *nameData = *reinterpret_cast<char **>(&name);
			const char *p = nameData ?
				nameData + 8 : "";	// retail "" at 0x0107388B
			NameKeyType lookupKey = TheNameKeyGenerator->nameToKey(p);

			_STL::map<NameKeyType, CastleUnpackCost>::iterator it =
				sub->m_bfme6c.find(lookupKey);

			if (it != sub->m_bfme6c.end())
			{
				AsciiString hit(*reinterpret_cast<const AsciiString *>(
					&it->second));
				resultKey = NAMEKEY(hit);
			}
		}
	}

	return resultKey;
}

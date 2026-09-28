// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0024A350 / 413 bytes / ret at +0x19c.
// HordeSiegeEngineContain createPayload: inherited TransportContain payload loop
// plus payload-template field +0x2f4 scaled by retail 5.0 and owner-name suffix.
// Three-word BitFlags<86> is constructed per iteration (ThingFactory ABI).
// The temporary AsciiString is the setName argument and dies at that statement.
// Name retained from preferred stash. Callee shim substitutions are proven by
// matched ThingFactoryFindTemplate / ThingFactory_newObject / Object.cpp /
// TransportContain.cpp and dispatch pin evidence at RVA 001BE220.
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
template <> inline StringBase<char>::~StringBase() { releaseBuffer(); }

#define __PLACEMENT_VEC_NEW_INLINE
#define ASCIISTRING_H
#include "Common/BitFlags.h"

typedef BitFlags<86> ObjectStatusMaskType;
typedef bool Bool;
extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);

class Player;
#define BFME_HAVE_ASCIISTRING 1
#define OBJECT_TU_MEMBERS const AsciiString &getName() const { return m_name; } void setName(const AsciiString &name) { m_name = name; } Player *getControllingPlayer() const;
#include "../object.h"
class Player;
class Team;
class ThingTemplate;

// Callee identities and ABI are established by the byte-matched bodies.
class BfmeThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
class ThingFactory { public: Object *newObject(const ThingTemplate *, Team *, const ObjectStatusMaskType &, unsigned int); };
class Rva001BE220Receiver { public: void dispatch(int condition, unsigned int duration); };
extern void j_00004d63();
class Rva0024A350MapCall { public: void invoke(Object *object) { union { void (*entry)(); void (Rva0024A350MapCall::*method)(Object *); } call; call.entry=j_00004d63; (this->*call.method)(object); } };
class TransportContain { friend class HordeSiegeEngineContain; protected: virtual void createPayload(); };

#define CONTAIN_SLOT(n) virtual void slot##n();
class ContainModuleInterface
{
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32)
	virtual Bool isValidContainerFor(const Object *object, Bool checkCapacity);
	CONTAIN_SLOT(34) CONTAIN_SLOT(35) CONTAIN_SLOT(36) CONTAIN_SLOT(37)
	CONTAIN_SLOT(38) CONTAIN_SLOT(39) CONTAIN_SLOT(40) CONTAIN_SLOT(41)
	CONTAIN_SLOT(42) CONTAIN_SLOT(43) CONTAIN_SLOT(44) CONTAIN_SLOT(45)
	CONTAIN_SLOT(46) CONTAIN_SLOT(47) CONTAIN_SLOT(48) CONTAIN_SLOT(49)
	CONTAIN_SLOT(50) CONTAIN_SLOT(51) CONTAIN_SLOT(52) CONTAIN_SLOT(53)
	CONTAIN_SLOT(54) CONTAIN_SLOT(55) CONTAIN_SLOT(56) CONTAIN_SLOT(57)
	CONTAIN_SLOT(58) CONTAIN_SLOT(59) CONTAIN_SLOT(60) CONTAIN_SLOT(61)
	CONTAIN_SLOT(62) CONTAIN_SLOT(63) CONTAIN_SLOT(64) CONTAIN_SLOT(65)
	CONTAIN_SLOT(66) CONTAIN_SLOT(67) CONTAIN_SLOT(68) CONTAIN_SLOT(69)
	CONTAIN_SLOT(70) CONTAIN_SLOT(71) CONTAIN_SLOT(72) CONTAIN_SLOT(73)
	CONTAIN_SLOT(74) CONTAIN_SLOT(75) CONTAIN_SLOT(76) CONTAIN_SLOT(77)
	virtual void enableLoadSounds(Bool enable);
};
#undef CONTAIN_SLOT

class HordeSiegeEngineContain
{
protected:
	virtual void createPayload();
};

// ?createPayload@HordeSiegeEngineContain@@MAEXXZ
void HordeSiegeEngineContain::createPayload()
{
	char *self = (char *)this;
	char *moduleData = *(char **)(self + 4);
	int count = *(int *)(moduleData + 0x230);

	const ThingTemplate *payloadTemplate =
		(*(BfmeThingFactory **)0x012EF1D8)->findTemplate(*(AsciiString *)(moduleData + 0x22c));
	Object *owner = *(Object **)(self + 8);
	ContainModuleInterface *contain = owner->m_contain;
	if (contain)
	{
		contain->enableLoadSounds(false);
		for (int i = 0; i < count; ++i)
		{
			ObjectStatusMaskType status;
			Player *player = owner->getControllingPlayer();
			Team *team = *(Team **)((char *)player + 0x230);
			Object *payload = (*(ThingFactory **)0x012EF1D8)->newObject(payloadTemplate, team, status, 0);
			if (contain->isValidContainerFor(payload, true))
			{
				int scaledCount = (int)(*(float *)((char *)payloadTemplate + 0x2f4) * 5.0f);
				if (scaledCount > 0)
					((Rva001BE220Receiver *)payload)->dispatch(0xcf, scaledCount);

				if (!owner->getName().isEmpty())
				{
					const char *text = owner->getName().str();
					char formattedName[256];
					sprintf(formattedName, "%s%d", text, i);
					payload->setName(formattedName);
				}
				((Rva0024A350MapCall *)((char *)this + 0x20))->invoke(payload);
			}
		}
		contain->enableLoadSounds(true);
	}
	((TransportContain *)this)->TransportContain::createPayload();
}

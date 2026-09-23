// ?createPayload@HordeSiegeEngineContain@@MAEXXZ
// partial score=0.23 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// First complete source hypothesis for retail 0x0024A350.
#include <Common/AsciiString.h>
#include <Common/ObjectStatusTypes.h>

typedef bool Bool;
extern "C" int __cdecl sprintf(char *, const char *, ...);

class Object;
class Player;
class Team;
class ThingTemplate;

class Rva0024A350Factory
{
public:
	const ThingTemplate *find(const AsciiString &name);
	Object *newObject(const ThingTemplate *thingTemplate, Team *team,
		const ObjectStatusMaskType &status, unsigned int flags);
};

#pragma comment(linker, "/alternatename:?find@Rva0024A350Factory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:?newObject@Rva0024A350Factory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z=?j_0004494a@@YAXXZ")

class Rva0024A350ObjectCall
{
public:
	Player *getControllingPlayer() const;
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@Rva0024A350ObjectCall@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

class Rva0024A350ControlCall
{
public:
	void invoke(int code, int count);
};

#pragma comment(linker, "/alternatename:?invoke@Rva0024A350ControlCall@@QAEXHH@Z=?j_0002852e@@YAXXZ")

class Rva0024A350MapCall
{
public:
	void invoke(Object *object);
};

#pragma comment(linker, "/alternatename:?invoke@Rva0024A350MapCall@@QAEXPAVObject@@@Z=?j_00004d63@@YAXXZ")

class Rva0024A350TransportBase
{
public:
	void createPayload();
};

#pragma comment(linker, "/alternatename:?createPayload@Rva0024A350TransportBase@@QAEXXZ=?j_0003a355@@YAXXZ")

class Rva0024A350NameField
{
public:
	void set(const Rva0024A350NameField &source);
};

#pragma comment(linker, "/alternatename:?set@Rva0024A350NameField@@QAEXABV1@@Z=?set@UnicodeString@@QAEXABV1@@Z")

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();
private:
	void *m_data;
};

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
	Object *owner = *(Object **)(self + 8);
	int count = *(int *)(moduleData + 0x230);

	const ThingTemplate *payloadTemplate =
		(*(Rva0024A350Factory **)0x012EF1D8)->find(*(AsciiString *)(moduleData + 0x22c));
	ContainModuleInterface *contain = *(ContainModuleInterface **)((char *)owner + 0x1fc);
	if (contain)
	{
		contain->enableLoadSounds(false);
		if (count > 0)
		{
			ObjectStatusMaskType status;
			Player *player = ((Rva0024A350ObjectCall *)owner)->getControllingPlayer();
			Team *team = *(Team **)((char *)player + 0x230);
			for (int i = 0; i < count; ++i)
			{
				Object *payload = (*(Rva0024A350Factory **)0x012EF1D8)->newObject(payloadTemplate, team, status, 0);
				if (contain->isValidContainerFor(payload, true))
				{
					int scaledCount = (int)(*(float *)(moduleData + 0x2f4) * *(float *)0x01075344);
					if (scaledCount > 0)
						((Rva0024A350ControlCall *)payload)->invoke(0xcf, scaledCount);

					void *nameData = *(void **)((char *)owner + 0x84);
					if (nameData && *(unsigned short *)((char *)nameData + 4))
					{
						const char *text = nameData
							? (const char *)nameData + 8 : (const char *)0x0107388b;
						char formattedName[248];
						sprintf(formattedName, (const char *)0x01085e68, text, i);
						{
							BFMERetailAsciiString temporary(formattedName);
							((Rva0024A350NameField *)((char *)payload + 0x84))->set(
								*(const Rva0024A350NameField *)&temporary);
						}
					}
					((Rva0024A350MapCall *)((char *)this + 0x20))->invoke(payload);
				}
			}
		}
		contain->enableLoadSounds(true);
	}
	((Rva0024A350TransportBase *)this)->createPayload();
}

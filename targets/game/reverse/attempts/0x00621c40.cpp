// ?ParseAsciiStringToGameInfo@@YA_NPAVGameInfo@@VAsciiString@@_N@Z
// partial score=0.263345 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/gameinfo /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Canonical by-value string models for BFME bodies -- the shape that byte-matches.
//
// Use this when a body takes or builds an AsciiString / UnicodeString BY VALUE
// (in-place construction: `mov ecx,esp` + call). Two rules it encodes, both
// proven byte-exact (docs/lessons.md):
//   1. The string class must NOT be trivially copyable, or MSVC builds a local
//      and pushes a copy instead of constructing in the argument slot.
//   2. Its copy ctor and dtor must be INLINE FORWARDERS to a StringBase<T> base
//      that owns the out-of-line bodies. Declaring them out of line on the
//      string class transposes the EH saved-esp store and the ctor `this`
//      (`mov [esp+N],esp` / `mov ecx,esp`) on every flag combination.
// Retail callees: char  copy ctor 0x00887B60, dtor 0x00887940 (StringBase<char>);
//                 wide  StringBase<unsigned short> bodies are pinned likewise.
// Add only the members the body needs; keep the layout a single data pointer.

#ifndef BFME_STRING_INLINE_H
#define BFME_STRING_INLINE_H

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	int getLength() const;
	const T *str() const;
	int compare(const StringBase<T> &other) const;
	int compare(const T *text) const;
	int compareNoCase(const StringBase<T> &other) const;
	int compareNoCase(const T *text) const;
	void concat(const StringBase<T> &other);
	void concat(const T *text);
	void concat(T value);
	bool nextToken(StringBase<T> *out, const T *delimiters);
	void set(const StringBase<T> &other);
	void set(const T *text);
	void toLower();

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
	int getLength() const { return StringBase<char>::getLength(); }
	AsciiString &operator=(const AsciiString &other) { StringBase<char>::set(*(const StringBase<char> *)&other); return *this; }
	bool isEmpty() const { return getLength() == 0; }
	void toLower() { StringBase<char>::toLower(); }
	int compare(const char *text) const { return StringBase<char>::compare(text); }
	int compare(const AsciiString &other) const { return StringBase<char>::compare(*(const StringBase<char> *)&other); }
	int compareNoCase(const char *text) const { return StringBase<char>::compareNoCase(text); }
	int compareNoCase(const AsciiString &other) const { return StringBase<char>::compareNoCase(*(const StringBase<char> *)&other); }
	void concat(const char *text) { StringBase<char>::concat(text); }
	void concat(char value) { StringBase<char>::concat(value); }
	void concat(const AsciiString &other) { StringBase<char>::concat(*(const StringBase<char> *)&other); }
	bool nextToken(AsciiString *out, const char *delimiters) { return StringBase<char>::nextToken((StringBase<char> *)out, delimiters); }
	static AsciiString TheEmptyString;
	void format( const char *format, ... );
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other) { StringBase<unsigned short>::set(*(const StringBase<unsigned short> *)&other); return *this; }
	void __cdecl format( UnicodeString format, ... );
	const unsigned short *str( void ) const { return (const unsigned short *)StringBase<unsigned short>::str(); }
	int getLength() const { return StringBase<unsigned short>::getLength(); }
	bool isEmpty() const { return getLength() == 0; }
	int compareNoCase(const UnicodeString &other) const { return StringBase<unsigned short>::compareNoCase(*(const StringBase<unsigned short> *)&other); }
	void set(const unsigned short *text) { StringBase<unsigned short>::set(text); }
	void translate(const AsciiString &other);
	void set(const UnicodeString &other) { StringBase<unsigned short>::set(*(const StringBase<unsigned short> *)&other); }
	static UnicodeString TheEmptyString;
};

#endif

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compareNoCase(right) == 0;
}
inline bool operator==(const UnicodeString &left, const UnicodeString &right)
{
	return left.compareNoCase(right) == 0;
}
inline bool operator<(const AsciiString &left, const AsciiString &right)
{
	return left.compareNoCase(right) < 0;
}

#define ASCIISTRING_H
#define UNICODESTRING_H
#include "PreRTS.h"
#include "Common/CRCDebug.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameState.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"
#include "Common/MultiplayerSettings.h"
#include "Common/PlayerTemplate.h"
#include "Common/Xfer.h"
#include "GameNetwork/FileTransfer.h"
#include "GameNetwork/GameInfo.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"
#include "GameNetwork/GameSpy/StagingRoomGameInfo.h"
#include "GameNetwork/LANAPI.h"
#include "GameNetwork/LANAPICallbacks.h"
#include "strtok_r.h"

extern char * __cdecl BFMEDuplicateString(const char *text);
extern AsciiString _Rva00621350GameInfoMapPath(const AsciiString &input, Bool option);

static const char slotListID = 'S';

static Int grabHexInt(const char *s)
{
	char tmp[5] = "0xff";
	tmp[2] = s[0];
	tmp[3] = s[1];
	Int b = strtol(tmp, NULL, 16);
	return b;
}
Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, Bool includeSlots)
{
	// Parse game options
	char *buf = BFMEDuplicateString(options.str());
	char *bufPtr = buf;
	char *strPos, *keyValPair;
	GameSlot newSlot[MAX_SLOTS];
	UnicodeString oldNames[MAX_SLOTS];
	typedef char GameSlotRetailStrideCheck[sizeof(GameSlot) == 0x44 ? 1 : -1];
	typedef char UnicodeStringRetailStrideCheck[sizeof(UnicodeString) == 4 ? 1 : -1];
	if (!includeSlots)
	{
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			oldNames[i] = game->getSlot(i)->getName();
		}
	}
	Bool optionsOk = true;
	AsciiString mapName;
	Int mapContentsMask;
	UnsignedInt mapCRC, mapSize;
	Int seed = 0;
	Int crc = 100;
	Bool sawCRC = FALSE;
  Bool oldFactionsOnly = FALSE;
	Int useStats = TRUE;
  Money startingCash = TheGlobalData->m_defaultStartingCash;
  UnsignedShort restriction = 0; // Always the default
  
	Bool sawMap, sawMapCRC, sawMapSize, sawSeed, sawSlotlist, sawUseStats, sawSuperweaponRestriction, sawStartingCash, sawOldFactions;
	sawMap = sawMapCRC = sawMapSize = sawSeed = sawSlotlist = sawUseStats = sawSuperweaponRestriction = sawStartingCash = sawOldFactions = FALSE;

	//DEBUG_LOG(("Saw options of %s\n", options.str()));
	DEBUG_LOG(("ParseAsciiStringToGameInfo - parsing [%s]\n", options.str()));


	while ( (keyValPair = strtok_r(bufPtr, ";", &strPos)) != NULL )
	{
		bufPtr = NULL; // strtok within the same string

		AsciiString key, val;
		char *pos = NULL;
		char *keyPtr, *valPtr;
		keyPtr = (strtok_r(keyValPair, "=", &pos));
		valPtr = (strtok_r(NULL, "\n", &pos));
		if (keyPtr)
			key = keyPtr;
		if (valPtr)
			val = valPtr;

		if (val.isEmpty())
		{
			optionsOk = false;
			DEBUG_LOG(("ParseAsciiStringToGameInfo - saw empty value, quitting\n"));
			break;
		}

		if (key.compare("US") == 0)
		{
			useStats = atoi(val.str());
			sawUseStats = true;
		}
		else
		if (key.compare("M") == 0)
		{
			if (val.getLength() < 3)
			{
				optionsOk = FALSE;
				DEBUG_LOG(("ParseAsciiStringToGameInfo - saw bogus map; quitting\n"));
				break;
			}
			mapContentsMask = grabHexInt(val.str());
			AsciiString tempstr;
			tempstr = val.str()+2;
			mapName = _Rva00621350GameInfoMapPath(tempstr, FALSE);
			sawMap = true;
			DEBUG_LOG(("ParseAsciiStringToGameInfo - map name is %s\n", mapName.str()));
		}
		else if (key.compare("MC") == 0)
		{
			mapCRC = 0;
			sscanf(val.str(), "%X", &mapCRC);
			sawMapCRC = true;
		}
		else if (key.compare("MS") == 0)
		{
			mapSize = atoi(val.str());
			sawMapSize = true;
		}
		else if (key.compare("SD") == 0)
		{
			seed = atoi(val.str());
			sawSeed = true;
//			DEBUG_LOG(("ParseAsciiStringToGameInfo - random seed is %d\n", seed));
		}
		else if (key.compare("C") == 0)
		{
			crc = atoi(val.str());
			sawCRC = TRUE;
		}
    else if (key.compare("SR") == 0 )
    {
      restriction = (UnsignedShort)atoi(val.str());
      sawSuperweaponRestriction = TRUE;
    }
    else if (key.compare("SC") == 0 )
    {
      UnsignedInt startingCashAmount = strtoul( val.str(), NULL, 10 );
      startingCash.init();
      startingCash.deposit( startingCashAmount, FALSE );
      sawStartingCash = TRUE;
    }
    else if (key.compare("O") == 0 )
    {
      oldFactionsOnly = ( val.compareNoCase( "Y" ) == 0 );
      sawOldFactions = TRUE;
    }
		else if (key.getLength() == 1 && *key.str() == slotListID)
		{
			sawSlotlist = true;
			/// @TODO: Need to read in all the slot info... big mess right now.
			char *rawSlotBuf = BFMEDuplicateString(val.str());
			char *freeMe = NULL;
			AsciiString rawSlot;
//			Bool slotsOk = true;	//flag that lets us know whether or not the slot list is good.

//			DEBUG_LOG(("ParseAsciiStringToGameInfo - Parsing slot list\n"));
			for (int i=0; i<MAX_SLOTS; ++i)
				{
					rawSlot = strtok_r(rawSlotBuf,":",&pos);
					if( rawSlotBuf )
						freeMe = rawSlotBuf;
					rawSlotBuf = NULL;
					switch (*rawSlot.str())
					{
						case 'H':
						{
//							DEBUG_LOG(("ParseAsciiStringToGameInfo - Human player\n"));
							char *slotPos = NULL;
							//Parse out the Name																
							AsciiString slotValue(strtok_r((char *)rawSlot.str(),",",&slotPos));
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue name is empty, quitting\n"));
								break;
							}
							UnicodeString name;
              				name.set((const unsigned short *)MultiByteToWideCharSingleLine(slotValue.str() + 1).c_str());
				if (!includeSlots && name.isEmpty())
					name = oldNames[i];

							//DEBUG_LOG(("ParseAsciiStringToGameInfo - name is %s\n", slotValue.str()+1));
							
							//Parse out the IP
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue IP address is empty, quitting\n"));
								break;
							}
							UnsignedInt playerIP = 0;
							sscanf(slotValue.str(),"%x", &playerIP);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - IP address is %x\n", playerIP));
							
							//set the state of the slot
							newSlot[i].setState(SLOT_PLAYER, name);
						newSlot[i].setIP(playerIP);

							// parse out the port
							slotValue = strtok_r(NULL, ",", &slotPos);
							if (slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue port is empty, quitting\n"));
								break;
							}
							UnsignedInt playerPort = 0;
							sscanf(slotValue.str(), "%d", &playerPort);
							newSlot[i].setPort(playerPort);
							DEBUG_LOG(("ParseAsciiStringToGameInfo - port is %d\n", playerPort));

							//Read if it's accepted or not
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.getLength() != 2)
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue accepted is mis-sized, quitting\n"));
								break;
							}
							const char *svs = slotValue.str();
							if(*svs == 'T') {
								newSlot[i].setAccept();
								//DEBUG_LOG(("ParseAsciiStringToGameInfo - player has accepted\n"));
							} else if (*svs == 'F') {
								newSlot[i].unAccept();
								//DEBUG_LOG(("ParseAsciiStringToGameInfo - player has not accepted\n"));
							}
							++svs;
							if(*svs == 'T') {
								newSlot[i].setMapAvailability(TRUE);
								//DEBUG_LOG(("ParseAsciiStringToGameInfo - player has map\n"));
							} else {
								newSlot[i].setMapAvailability(FALSE);
								//DEBUG_LOG(("ParseAsciiStringToGameInfo - player does not have map\n"));
							}

							//Read color index
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue color is empty, quitting\n"));
								break;
							}
							Int color = atoi(slotValue.str());
							if (color < -1 || color >= TheMultiplayerSettings->getNumColors())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - player color was invalid, quitting\n"));
								break;
							}
							newSlot[i].setColor(color);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - player color set to %d\n", color));

							//Read playerTemplate index
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue player template is empty, quitting\n"));
								break;
							}
							Int playerTemplate = atoi(slotValue.str());
							if (playerTemplate < PLAYERTEMPLATE_MIN || playerTemplate >= ThePlayerTemplateStore->getPlayerTemplateCount())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - player template value is invalid, quitting\n"));
								break;
							}
							newSlot[i].setPlayerTemplate(playerTemplate);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - player template is %d\n", playerTemplate));

							//Read start position index
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue start position is empty, quitting\n"));
								break;
							}
							Int startPos = atoi(slotValue.str());
							if (startPos < -1 || startPos >= MAX_SLOTS)
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - player start position is invalid, quitting\n"));
								break;
							}
							newSlot[i].setStartPos(startPos);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - player start position is %d\n", startPos));

							//Read team index
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue team number is empty, quitting\n"));
								break;
							}
							Int team = atoi(slotValue.str());
							if (team < -1 || team >= MAX_SLOTS/2)
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - team number is invalid, quitting\n"));
								break;
							}
							newSlot[i].setTeamNumber(team);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - team number is %d\n", team));

							// Read the NAT behavior
							slotValue = strtok_r(NULL, ",",&slotPos);
							if (slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - NAT behavior is empty, quitting\n"));
								break;
							}
							FirewallHelperClass::FirewallBehaviorType NATType = (FirewallHelperClass::FirewallBehaviorType)atoi(slotValue.str());
							if ((NATType < FirewallHelperClass::FIREWALL_MIN) ||
									(NATType > FirewallHelperClass::FIREWALL_MAX)) {
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - NAT behavior is invalid, quitting\n"));
								break;
							}
							newSlot[i].setNATBehavior(NATType);
							DEBUG_LOG(("ParseAsciiStringToGameInfo - NAT behavior is %X\n", NATType));
						}// case 'H':
						break;
						case 'C':
						{
            	DEBUG_LOG(("ParseAsciiStringToGameInfo - AI player\n"));
							char *slotPos = NULL;
							//Parse out the Name																
							AsciiString slotValue(strtok_r((char *)rawSlot.str(),",",&slotPos));
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue AI Type is empty, quitting\n"));
								break;
							}
              
							switch(*(slotValue.str() + 1))
							{
								case 'E':
								{
									newSlot[i].setState(SLOT_EASY_AI);
									//DEBUG_LOG(("ParseAsciiStringToGameInfo - Easy AI\n"));
								}
								break;
								case 'M':
								{
									newSlot[i].setState(SLOT_MED_AI);
									//DEBUG_LOG(("ParseAsciiStringToGameInfo - Medium AI\n"));
								}
								break;
								case 'H':
								{
									newSlot[i].setState(SLOT_BRUTAL_AI);
									//DEBUG_LOG(("ParseAsciiStringToGameInfo - Brutal AI\n"));
								}
								break;
								default:
								{
									optionsOk = false;
									DEBUG_LOG(("ParseAsciiStringToGameInfo - Unknown AI, quitting\n"));
								}
								break;
							}//switch(*rawSlot.str()+1)
              
							//Read color index
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue color is empty, quitting\n"));
								break;
							}
							Int color = atoi(slotValue.str());
							if (color < -1 || color >= TheMultiplayerSettings->getNumColors())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - player color was invalid, quitting\n"));
								break;
							}
							newSlot[i].setColor(color);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - player color set to %d\n", color));

							//Read playerTemplate index
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue player template is empty, quitting\n"));
								break;
							}
							Int playerTemplate = atoi(slotValue.str());
							if (playerTemplate < PLAYERTEMPLATE_MIN || playerTemplate >= ThePlayerTemplateStore->getPlayerTemplateCount())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - player template value is invalid, quitting\n"));
								break;
							}
							newSlot[i].setPlayerTemplate(playerTemplate);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - player template is %d\n", playerTemplate));

							//Read start pos
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue start pos is empty, quitting\n"));
								break;
							}
							Int startPos = atoi(slotValue.str());
							Bool isStartPosBad = FALSE;
							if (startPos < -1 || startPos >= MAX_SLOTS)
							{
								isStartPosBad = TRUE;
							}
							for (Int j=0; j<i; ++j)
							{
								if (startPos >= 0 && startPos == newSlot[i].getStartPos())
								{
									isStartPosBad = TRUE; // can't have multiple people using the same start pos
								}
							}
							if (isStartPosBad)
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - start pos is invalid, quitting\n"));
								break;
							}
							newSlot[i].setStartPos(startPos);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - start spot is %d\n", startPos));

							//Read team index
							slotValue = strtok_r(NULL,",",&slotPos);
							if(slotValue.isEmpty())
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - slotValue team number is empty, quitting\n"));
								break;
							}
							Int team = atoi(slotValue.str());
							if (team < -1 || team >= MAX_SLOTS/2)
							{
								optionsOk = false;
								DEBUG_LOG(("ParseAsciiStringToGameInfo - team number is invalid, quitting\n"));
								break;
							}
							newSlot[i].setTeamNumber(team);
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - team number is %d\n", team));

						}//case 'C':
						break;
						case 'O':
						{
							newSlot[i].setState( SLOT_OPEN );
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - Slot is open\n"));
						}// case 'O':
						break;
						case 'X':
						{
							newSlot[i].setState( SLOT_CLOSED );
							//DEBUG_LOG(("ParseAsciiStringToGameInfo - Slot is closed\n"));
						}// case 'X':
						break;
						default:
						{								
							optionsOk = false;
							DEBUG_LOG(("ParseAsciiStringToGameInfo - unrecognized slot entry, quitting\n"));
						}
						break;
					}
				}
		if(freeMe)
			free(freeMe);
		}
		else
		{
			optionsOk = false;
			break;
		}
	}
	if( buf )
		free(buf);

	//DEBUG_LOG(("Options were ok == %d\n", optionsOk));
	if (optionsOk && sawMap && sawMapCRC && sawMapSize && sawSeed && sawSlotlist && sawCRC && sawUseStats && sawSuperweaponRestriction && sawStartingCash && sawOldFactions )
	{
		// We were setting the Global Data directly here, but Instead, I'm now 
		// first setting the data in game.  We'll set the global data when
		// we start a game.
		if (!game)
			return true;

		//DEBUG_LOG(("ParseAsciiStringToGameInfo - game options all good, setting info\n"));

		for(Int i = 0; i<MAX_SLOTS; i++)
			game->setSlot(i,newSlot[i]);

		game->setMap(mapName);
		game->setMapCRC(mapCRC);
		game->setMapSize(mapSize);
		game->setMapContentsMask(mapContentsMask);
		game->setSeed(seed);
		game->setCRCInterval(crc);
		game->setUseStats(useStats);
    game->setSuperweaponRestriction(restriction);
    game->setStartingCash( startingCash );
    game->setOldFactionsOnly( oldFactionsOnly );

		return true;
	}

	DEBUG_LOG(("ParseAsciiStringToGameInfo - game options messed up\n"));
	return false;
}



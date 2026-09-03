// cl: /DNDEBUG /MD /EHsc
// stlport
// ?bfmePopulateGameReport@GameLogic@@QAEXPAVGameInfo@@PAH@Z
// Retail 0x00393880, 2022 bytes.  BFME's start-game report helper.

#include <vector>

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

	private:
	struct Header
	{
		unsigned short m_refCount;
		unsigned short m_numCharsAllocated;
		unsigned short m_length;
		unsigned short m_pad;
		T m_data[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	public:
	void concat( const T *text, Int length );
	void set( const StringBase<T> &other );

	private:
	Header *m_data;
};

class UnicodeString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void format( AsciiString format, ... );
	void translate( const UnicodeString &text );
	AsciiString &operator=( const UnicodeString &text );

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}

	Int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	void concat( const char *text, Int length )
	{
		StringBase<char>::concat( text, length );
	}

	void set( const AsciiString &other )
	{
		StringBase<char>::set( *(const StringBase<char> *)&other );
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset();

	unsigned char m_unreconstructed_04[0x0C];
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;

	UnicodeString getName() const;
	Bool isHuman() const;
	Bool isAI() const;

	Int getStartPos() const { return m_startPos; }
	Int getPlayerTemplate() const { return m_playerTemplate; }
	Int getTeamNumber() const { return m_teamNumber; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual Int getLocalSlotNum() const;
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual Bool isSkirmish();
	virtual Bool isMultiplayer();
	virtual Bool isSandBox();
	virtual Bool isSinglePlayerSkirmish();

	GameSlot *getSlot( Int slot );
    Int getSlotNum( const AsciiString userName ) const;
	AsciiString getMap() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	UnicodeString getDisplayName() const;
	AsciiString getName() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate( Int index ) const;
};

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual void vfn09();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct GlobalData
{
	unsigned char m_unreconstructed_0000[0x0A6C];
	Bool m_audioOn;
	Bool m_musicOn;
	unsigned char m_unreconstructed_0A6E[0x11EC - 0x0A6E];
	Bool m_fastGamePlay;
	unsigned char m_unreconstructed_11ED[3];
	Int m_startingMoney;
};

struct PlayerLeaveStatus
{
	unsigned char m_unreconstructed_00[0x10];
	Bool m_notPresent;
	unsigned char m_unreconstructed_11[3];
	Int m_isHuman;
	AsciiString m_playerName;
};

extern GameInfo *TheGameInfo;
extern PlayerTemplateStore *ThePlayerTemplateStore;
extern GameTextInterface *TheGameText;
extern GlobalData *TheWritableGlobalData;

extern Bool g_xObjectCRC;
extern Bool g_xPartitionCRC;
extern Bool g_xCollisionCRC;
extern Bool g_xShroudCRC;
extern Bool g_xTaintCRC;
extern Bool g_xTerrainLogicCRC;
extern Bool g_xPlayerCRC;
extern Bool g_xAICRC;
extern Bool g_verifyClientCRC;
extern Bool g_deepCRC;
extern Bool g_liteCRC;
extern Bool g_binaryDeepCRC;
extern Int g_netCRCInterval;
extern Int g_debugCRCFromFrame;
extern Int g_debugCRCUntilFrame;
extern const char *g_crcLogFile;

extern UnsignedByte Rva00882F40GetFlag( void );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void bfmePopulateGameReport( GameInfo *game, Int *localSlot );

	unsigned char m_unreconstructed_0000[0x50];
	AsciiString m_gameReport;
	std::vector<AsciiString> m_gameReportDetails;
	AsciiString m_commandLineArguments;
	AsciiString m_gameReportTrailer;
	Bool m_gameReportReady;
	unsigned char m_unreconstructed_0069[0x1B0 - 0x69];
	PlayerLeaveStatus m_playerLeaveStatus[8];
};

#define self this

void GameLogic::bfmePopulateGameReport( GameInfo *game, Int *localSlot )
{
	if ( game == 0 || localSlot == 0 )
		return;

	self->m_gameReportReady = false;
	AsciiString line;

	self->m_gameReport.format( (AsciiString)"---------------------------------------------------------\nGAME REPORT:\n---------------------------------------------------------\n" );

	line.format( (AsciiString)"  BuildType: RELEASE\n" );
	self->m_gameReport.concat( line.str(), line.getLength() );

	AsciiString report;
	report.format( (AsciiString)"  Session Game #%d\n    Map Name: %s\n",
		(int)( self->m_gameReportDetails.size() + 1 ), game->getMap().str() );

	line.format( (AsciiString)"    GameMode: isSkirmish:%d, isMultiplayer:%d, isSandBox:%d, isSinglePlayerSkirmish:%d\n    Player List:\n",
		TheGameInfo->isSkirmish(), TheGameInfo->isMultiplayer(),
		TheGameInfo->isSandBox(), TheGameInfo->isSinglePlayerSkirmish() );
	report.concat( line.str(), line.getLength() );

	*localSlot = 0;
	AsciiString *statusName;
	statusName = &self->m_playerLeaveStatus[0].m_playerName;

    for ( Int slotIndex = 0; slotIndex < 8;
        ++slotIndex, statusName = (AsciiString *)( (char *)statusName + 0x1C ) )
    {
        GameSlot *slot = game->getSlot( slotIndex );
        AsciiString slotNameAscii;
        slotNameAscii.translate( slot->getName() );

        if ( slot->isHuman() && game->getSlotNum( slotNameAscii ) == game->getLocalSlotNum() )
			*localSlot = slotIndex;

        AsciiString displayName;
        const PlayerTemplate *playerTemplate;
            if ( !slot->isHuman() && !slot->isAI() )
			{
                line.format( (AsciiString)"      Slot %d: %s\n", slotIndex, slotNameAscii.str() );
			}
			else
			{
				playerTemplate =
                    ThePlayerTemplateStore->getNthPlayerTemplate( slot->getPlayerTemplate() );

                if ( slot->getPlayerTemplate() == -1 )
                    displayName = TheGameText->fetch( "GUI:Random" );
                else if ( slot->getPlayerTemplate() == -2 )
					displayName = TheGameText->fetch( "GUI:Observer" );
				else
                    displayName = ThePlayerTemplateStore->getNthPlayerTemplate( slot->getPlayerTemplate() )->getDisplayName();

				line.format( (AsciiString)"      Slot %d: %s(%s), %s %s, Team:%d, StartPos:%d\n",
                    slotIndex, slotNameAscii.str(),
					displayName.str(),
					playerTemplate ? playerTemplate->getName().str() : "n/a",
                    slot->isHuman() ? "Human" : "AI",
                    slot->getTeamNumber(), slot->getStartPos() );

                Int humanStatus = slot->isHuman() ? 0 : 1;
				if ( slotIndex >= 0 && slotIndex < 8 )
				{
					*(Bool *)( (char *)statusName - 8 ) = false;
                    statusName->set( slotNameAscii );
					*(Int *)( (char *)statusName - 4 ) = humanStatus;
				}
			}
        report.concat( line.str(), line.getLength() );
    }

	self->m_gameReportDetails.push_back( report );

	self->m_commandLineArguments.format( (AsciiString)"  Important CommandLine Arguments:\n    System:" );
	if ( Rva00882F40GetFlag() )
		self->m_commandLineArguments.concat( " zeroFillMemory:ON", 0x12 );
	else
		self->m_commandLineArguments.concat( " zeroFillMemory:OFF", 0x13 );
	if ( !TheWritableGlobalData->m_audioOn )
		self->m_commandLineArguments.concat( " -noAudio", 9 );
	if ( !TheWritableGlobalData->m_musicOn )
		self->m_commandLineArguments.concat( " -noMusic", 9 );
	self->m_commandLineArguments.concat( "\n    GamePlay:", 0x0E );
	if ( TheWritableGlobalData->m_fastGamePlay )
		self->m_commandLineArguments.concat( " -fastGamePlay", 0x0E );
	if ( TheWritableGlobalData->m_startingMoney )
	{
		line.format( (AsciiString)" -startingMoney %d", TheWritableGlobalData->m_startingMoney );
		self->m_commandLineArguments.concat( line.str(), line.getLength() );
	}

	self->m_commandLineArguments.concat( "\n    Network:", 0x0D );
	if ( g_xObjectCRC ) self->m_commandLineArguments.concat( " -xObjectCRC", 0x0C );
	if ( g_xPartitionCRC ) self->m_commandLineArguments.concat( " -xPartitionCRC", 0x0F );
	if ( g_xCollisionCRC ) self->m_commandLineArguments.concat( " -xCollisionCRC", 0x0F );
	if ( g_xShroudCRC ) self->m_commandLineArguments.concat( " -xShroudCRC", 0x0C );
	if ( g_xTaintCRC ) self->m_commandLineArguments.concat( " -xTaintCRC", 0x0B );
	if ( g_xTerrainLogicCRC ) self->m_commandLineArguments.concat( " -xTerrainLogicCRC", 0x12 );
	if ( g_xPlayerCRC ) self->m_commandLineArguments.concat( " -xPlayerCRC", 0x0C );
	if ( g_xAICRC ) self->m_commandLineArguments.concat( " -xAICRC", 8 );
	if ( g_verifyClientCRC ) self->m_commandLineArguments.concat( " -verifyClientCRC", 0x11 );
	if ( g_deepCRC ) self->m_commandLineArguments.concat( " -deepCRC", 9 );
	if ( g_liteCRC ) self->m_commandLineArguments.concat( " -liteCRC", 9 );
	if ( g_binaryDeepCRC ) self->m_commandLineArguments.concat( " -binaryDeepCRC", 0x0F );
	if ( g_debugCRCFromFrame != -1 )
	{
		line.format( (AsciiString)" -debugCRCFromFrame %d", g_debugCRCFromFrame );
		self->m_commandLineArguments.concat( line.str(), line.getLength() );
	}
	if ( g_debugCRCUntilFrame != -1 )
	{
		line.format( (AsciiString)" -debugCRCUntilFrame %d", g_debugCRCUntilFrame );
		self->m_commandLineArguments.concat( line.str(), line.getLength() );
	}

	line.format( (AsciiString)"\n    NetCRCInterval: %d\n", g_netCRCInterval );
	self->m_commandLineArguments.concat( line.str(), line.getLength() );

	self->m_gameReportTrailer.format( (AsciiString)"---------------------------------------------------------\n" );
}

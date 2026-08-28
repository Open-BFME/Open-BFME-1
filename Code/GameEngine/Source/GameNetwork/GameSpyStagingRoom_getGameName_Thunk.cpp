// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GameSpyStagingRoom::getGameName, retail 0x004CE820.
//
// The one-line accessor. It returns UnicodeString by value, so the body is
// mostly the return-slot protocol: reserve four bytes, take &m_gameName as
// this+0x3a0, clear the unwind state slot, and copy-construct into the hidden
// return pointer.
//
// The offset is the only thing here that is not boilerplate: m_gameName sits
// at this+0x3a0.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const UnicodeString &that);		///< ILT 0x00888400
	~UnicodeString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom
{
public:
	UnicodeString getGameName(void) const;

private:
	char m_unreconstructed_00[0x3a0];
	UnicodeString m_gameName;						///< retail this+0x3a0
};

// ?getGameName@GameSpyStagingRoom@@QBE?AVUnicodeString@@XZ
UnicodeString GameSpyStagingRoom::getGameName(void) const
{
	return m_gameName;
}

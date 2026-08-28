// cl: /DNDEBUG /MD /EHsc
// readable body of ?getSaveDirectory@GameState@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp

// Open-BFME5: GameState::getSaveDirectory, retail 0x0010DC70, 131 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it.
//
// The user-data path comes back from TheWritableGlobalData by value, five more
// characters are concatenated onto it, and the result is copied into the
// caller's return buffer before the local is destroyed.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_bfmeData = 0; }
	AsciiString(const AsciiString &other);			// retail 0x00887B60
	~AsciiString();						// retail 0x00887940

	void concat(const char *text, Int length);		// retail 0x00887D60

private:
	char *m_bfmeData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	AsciiString getPath_UserData(void) const;		// ILT 0x000106EA
};

extern GlobalData *TheWritableGlobalData;			// 0x012ED5C8

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
public:
	AsciiString getSaveDirectory(void) const;
};

// ?getSaveDirectory@GameState@@QBE?AVAsciiString@@XZ
AsciiString GameState::getSaveDirectory(void) const
{
	AsciiString directory = TheWritableGlobalData->getPath_UserData();

	directory.concat("Save\\", 5);

	return directory;
}

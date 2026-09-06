// cl: /DNDEBUG /MD /EHsc
// readable body of ?getSaveDirectory@GameState@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// readable body of ?getFilePathInSaveDirectory@GameState@@QBE?AVAsciiString@@ABV2@@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// readable body of ?getMapLeafName@GameState@@QBE?AVAsciiString@@ABV2@@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// readable body of ?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// readable body of ?clearAvailableGames@GameState@@AAEXXZ: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp

// The save-game directory: the paths into it, the existence check they feed,
// and the teardown of the list of what was found there.
//
//   getSaveDirectory          0x0010DC70   user data + "Save\"
//   getFilePathInSaveDirectory 0x0010F120  that + a leaf name
//   getMapLeafName            0x0010F1C0   the last component of a map path
//   doesSaveGameExist         0x0010DD00   the resolved path, asked of the FileSystem
//   clearAvailableGames       0x0010DBF0   free the scanned-game list at +0x50
//
// Four of the five build or take apart an AsciiString, and they used to carry
// four different accounts of it: one keeping only the buffer pointer, one
// spelling the header out as a struct to reach the length, one indexing the
// characters as m_data + 8, one as m_data + 1 over an eight-byte header. They
// are the same object, and the one declaration below says so once: an eight-byte
// header with the characters immediately behind it. The out-of-line members are
// retail's own -- the copy constructor at 0x00887B60, the destructor at
// 0x00887940 and the counted concat at 0x00887D60.

#include <string.h>

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned short m_refCount;				// +0x00
	unsigned short m_numCharsAllocated;			// +0x02
	unsigned short m_len;					// +0x04
	unsigned short m_pad;
	// the characters follow at +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);			// retail 0x00887B60
	~AsciiString();						// retail 0x00887940

	void concat(const char *text, Int length);		// retail 0x00887D60

	// The inline forwarder: length and text pulled out of the argument with the
	// null guards, then the counted concat.
	void concat(const AsciiString &other)
	{
		const Int len = other.m_data ? other.m_data->m_len : 0;
		const char *data = other.m_data ? (const char *)(other.m_data + 1) : "";
		concat(data, len);
	}

	const char *str() const
	{
		static const char empty = 0;
		return m_data ? (const char *)(m_data + 1) : &empty;
	}

private:
	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	AsciiString getPath_UserData(void) const;		// ILT 0x000106EA
};

extern GlobalData *TheWritableGlobalData;			// 0x012ED5C8

class FileSystem
{
public:
	bool doesFileExist(const char *) const;
};

extern FileSystem *TheFileSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
struct AvailableGameInfo
{
	char m_data[0x34];
	AvailableGameInfo *next;
	~AvailableGameInfo();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
public:
	AsciiString getSaveDirectory(void) const;		// ILT 0x0001F203, returns by value
	AsciiString getFilePathInSaveDirectory(const AsciiString &leaf) const;
	AsciiString getMapLeafName(const AsciiString &path) const;
	bool doesSaveGameExist(AsciiString filename);

private:
	void clearAvailableGames();

	char m_bfmeLayout[0x50];
	AvailableGameInfo *m_availableGames;			// this+0x50
};

// ?getSaveDirectory@GameState@@QBE?AVAsciiString@@XZ
// The user-data path comes back from TheWritableGlobalData by value, five more
// characters are concatenated onto it, and the result is copied into the
// caller's return buffer before the local is destroyed.
AsciiString GameState::getSaveDirectory(void) const
{
	AsciiString directory = TheWritableGlobalData->getPath_UserData();

	directory.concat("Save\\", 5);

	return directory;
}

// ?getFilePathInSaveDirectory@GameState@@QBE?AVAsciiString@@ABV2@@Z
AsciiString GameState::getFilePathInSaveDirectory(const AsciiString& leaf) const
{
	AsciiString tmp = getSaveDirectory();
	tmp.concat(leaf);
	return tmp;
}

// ?getMapLeafName@GameState@@QBE?AVAsciiString@@ABV2@@Z
AsciiString GameState::getMapLeafName(const AsciiString &path) const
{
	char *separator = strrchr((char *)path.str(), '\\');
	if (separator)
	{
		++separator;
		return separator;
	}
	return path;
}

// ?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z
// BFME checks the resolved save path through FileSystem directly.
bool GameState::doesSaveGameExist(AsciiString filename)
{
	AsciiString filepath = getFilePathInSaveDirectory(filename);
	return TheFileSystem->doesFileExist(filepath.str());
}

// ?clearAvailableGames@GameState@@AAEXXZ
void GameState::clearAvailableGames()
{
	while (m_availableGames)
	{
		AvailableGameInfo *next = m_availableGames->next;
		delete m_availableGames;
		m_availableGames = next;
	}
}

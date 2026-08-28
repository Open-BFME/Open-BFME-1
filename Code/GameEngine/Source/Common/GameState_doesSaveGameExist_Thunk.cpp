// cl: /DNDEBUG /MD /EHsc
// readable body of ?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// Open-BFME5: BFME checks the resolved save path through FileSystem directly.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
	struct AsciiStringData
	{
		unsigned short m_refCount;
		unsigned short m_numCharsAllocated;
		unsigned int m_bfmeHeader;
	};

	AsciiStringData *m_data;

public:
	~AsciiString();

	const char *str() const
	{
		static const char empty = 0;
		return m_data != 0 ? reinterpret_cast<const char *>(m_data + 1) : &empty;
	}
};

class FileSystem
{
public:
	bool doesFileExist(const char *) const;
};

extern FileSystem *TheFileSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
public:
	AsciiString getFilePathInSaveDirectory(const AsciiString &) const;
	bool doesSaveGameExist(AsciiString);
};

// ?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z
bool GameState::doesSaveGameExist(AsciiString filename)
{
	AsciiString filepath = getFilePathInSaveDirectory(filename);
	return TheFileSystem->doesFileExist(filepath.str());
}

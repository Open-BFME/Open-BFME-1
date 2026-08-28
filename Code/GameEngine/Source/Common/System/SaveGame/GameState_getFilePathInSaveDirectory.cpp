// cl: /DNDEBUG /MD /EHsc
// readable body of ?getFilePathInSaveDirectory@GameState@@QBE?AVAsciiString@@ABV2@@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// Open-BFME: GameState::getFilePathInSaveDirectory, retail 0x0010F120,
// 151 bytes.
//
// The reference's three lines. getSaveDirectory() hands its string back BY
// VALUE into the local, the concat is the string's own inline forwarder --
// length and text pulled out of the argument with the null guards, then the
// out-of-line concat(const char *, int) -- and the return is a copy of the
// local, which is then destroyed.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &src);			// 0x00887B60
	~AsciiString();						// 0x00887940

	void concat(const char *str, Int len);			// 0x00887D60

	void concat(const AsciiString &str)
	{
		const Int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		concat(data, len);
	}

private:
	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
public:
	AsciiString getFilePathInSaveDirectory(const AsciiString& leaf) const;
	AsciiString getSaveDirectory(void) const;		// ILT 0x0001F203, returns by value
};

AsciiString GameState::getFilePathInSaveDirectory(const AsciiString& leaf) const
{
	AsciiString tmp = getSaveDirectory();
	tmp.concat(leaf);
	return tmp;
}

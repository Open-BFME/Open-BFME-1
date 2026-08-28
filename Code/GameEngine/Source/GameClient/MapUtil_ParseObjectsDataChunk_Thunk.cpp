// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the ParseObjectsDataChunk MASM dump to clean C++.
//
// Zero Hour's version is MapUtil.cpp:178 and BFME kept the shape, but changed
// registerParser: retail passes `info` itself and a trailing zero where the
// reference passes info->label and stops at three arguments.
//
// MSVC reuses the dead first-parameter slot for the AsciiString temporary, which
// is why the constructor's `this` and the later destructor both point at the
// incoming argument area rather than at fresh stack.

class DataChunkInput;
struct DataChunkInfo;
class AsciiString;

template <class T>
class StringBase
{
private:
	friend class AsciiString;

	StringBase(const char *s);					///< body at 0x00888BC0
	~StringBase();								///< body at 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	~AsciiString() {}
};

typedef bool (*DataChunkParser)(DataChunkInput &file, DataChunkInfo *info, void *userData);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
public:
	void registerParser(const AsciiString &name, DataChunkInfo *info, DataChunkParser parser, int flags);
	bool parse(void *userData);

	unsigned char m_unreconstructed_00[0x20];
	void *m_currentObject;						///< retail this+0x20
};

bool ParseObjectDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);

// ?ParseObjectsDataChunk@@YA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
bool ParseObjectsDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	file.m_currentObject = 0;
	file.registerParser(AsciiString("Object"), info, ParseObjectDataChunk, 0);

	return file.parse(userData);
}

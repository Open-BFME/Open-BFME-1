// cl: /DNDEBUG /MD /EHsc
// readable body of ?writeAsciiString@DataChunkOutput@@QAEXABVAsciiString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// Open-BFME: DataChunkOutput::writeAsciiString, retail 0x00102C80, 97 bytes.
//
// The reference's three lines unchanged: the length as a halfword, then that
// many characters, both through fwrite on the temporary file at this+0x04.
//
// Both accessors are inlined, which is where the length and the buffer offsets
// come from -- the halfword at the buffer's +4 and the characters from +8,
// with an empty string standing in for a null buffer. fwrite is imported and
// its address is loaded once for the two calls.

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buffer, unsigned int size, unsigned int count, void *stream);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void writeAsciiString(const AsciiString &theString);

private:
	char m_slice_pad[4];					// retail this+0x00, untouched
	void *m_tmp_file;					// this+0x04
};

void DataChunkOutput::writeAsciiString( const AsciiString& theString )
{
	UnsignedShort len = theString.getLength();
	fwrite( (const char *)&len, sizeof(UnsignedShort) , 1, m_tmp_file );
	fwrite( theString.str(), len , 1, m_tmp_file );
}

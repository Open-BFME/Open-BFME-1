// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the Parameter::WriteParameter naked dump to clean C++.
//
// Zero Hour's Scripts.cpp body. Two things are inlined that ZH writes as calls.
//
// getNameFromSingleBit becomes a bounds-checked table lookup: retail rejects a
// negative index or one at or past 0xB5 and otherwise reads the name pointer
// out of the array at 0x012AA068, so the mask has 181 named bits.
//
// The assignment of that name into the string member is a two-argument setter
// taking pointer and length, with the length computed by an inline strlen that
// is skipped entirely when the pointer is null -- so a null name still calls the
// setter, with zero.
//
// Retail pins the layout: the parameter type is at this+0x00, the int at +0x08,
// the real at +0x0C, the string at +0x10 and the coordinate at +0x14 through
// +0x1C.

typedef int Int;
typedef float Real;

extern "C" unsigned int __cdecl strlen(const char *);

enum { COORD3D = 0x10, KIND_OF_PARAM = 0x1B };

// 181 named bits; only the bound is proven, the contents are not read here.
extern const char *TheKindOfBitNames[0xB5];				///< retail [0x012AA068]

class KindOfMaskType
{
public:
	static const char *getNameFromSingleBit(Int bit)
	{
		// the bound comes from the array's own size, so it is unsigned and the
		// comparison is `jae` rather than `jge` -- a literal 0xB5 would be signed
		if (bit < 0 || bit >= sizeof(TheKindOfBitNames)/sizeof(TheKindOfBitNames[0]))
			return 0;
		return TheKindOfBitNames[bit];
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set(const char *s, Int len);					///< retail body at 0x00487D20

	AsciiString &operator=(const char *s)
	{
		set(s, s ? (Int)strlen(s) : 0);
		return *this;
	}

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkOutput
{
public:
	void writeInt(Int value);							///< ILT thunk at 0x000092B4
	void writeReal(Real value);							///< ILT thunk at 0x00014894
	void writeAsciiString(const AsciiString &value);	///< ILT thunk at 0x0001EBBE
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	void WriteParameter(DataChunkOutput &chunkWriter);

private:
	Int m_paramType;									///< retail this+0x00
	unsigned char m_unreconstructed_04[4];
	Int m_int;											///< retail this+0x08
	Real m_real;										///< retail this+0x0C
	AsciiString m_string;								///< retail this+0x10
	Coord3D m_coord;									///< retail this+0x14
};

// ?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z
void Parameter::WriteParameter(DataChunkOutput &chunkWriter)
{

	/**********Parameter  DATA ***********************/
	chunkWriter.writeInt(m_paramType);
	if (m_paramType == KIND_OF_PARAM) {
		// To get the proper kindof string stored.
		m_string = KindOfMaskType::getNameFromSingleBit(m_int);
	}
	if (m_paramType == COORD3D) {
		chunkWriter.writeReal(m_coord.x);
		chunkWriter.writeReal(m_coord.y);
		chunkWriter.writeReal(m_coord.z);
	} else {
		chunkWriter.writeInt(m_int);
		chunkWriter.writeReal(m_real);
		chunkWriter.writeAsciiString(m_string);
	}
}

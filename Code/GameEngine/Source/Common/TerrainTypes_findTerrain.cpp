// cl: /DNDEBUG /MD /EHsc
// readable body of ?findTerrain@TerrainTypeCollection@@: Code/GameEngine/Source/Common/TerrainTypes.cpp
// Open-BFME: TerrainTypeCollection::findTerrain, retail 0x000A7AF0, 246 bytes.
//
// The reference's loop unchanged -- walk the list from m_terrainList at
// this+0x08 through friend_getNext at +0x20 and stop on the first name that
// matches -- with the name comparison inlined, which is most of the 246 bytes.
//
// What it inlines is AsciiString's own compare, and the bytes give its shape
// exactly: the length is the halfword at the buffer's +4 and the characters
// start at +8, an empty string standing in for a null buffer; the two lengths
// pick a minimum; memcmp expands to `repe cmpsb` with the usual sbb/sbb pair
// turning the flags into -1 or 1; and only when that is zero does the length
// difference decide. The result is carried in bl across the temporary's
// destructor, which is what `sete bl` ahead of the call is doing.
//
// The argument side is read before the object side -- retail reloads the
// incoming name's buffer at the top of every iteration rather than hoisting it
// -- and that ordering is load-bearing: written the other way round the
// compiler hoists it, runs out of registers and spills the list pointer,
// costing the frame another four bytes.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

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
	AsciiString(const AsciiString &that);
	~AsciiString();

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff == 0)
			diff = lenThis - lenOther;

		return diff;
	}

	Bool operator==(const AsciiString &rhs) const { return compare(rhs) == 0; }

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TerrainTypes.h
class TerrainType
{
public:
	AsciiString getName(void) const;			// ILT 0x00031985

	TerrainType *friend_getNext(void) { return m_next; }

private:
	char m_slice_pad[0x20];					// retail this+0x00 .. +0x1F, untouched
	TerrainType *m_next;					// this+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TerrainTypes.h
class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);

private:
	char m_slice_pad[8];					// retail this+0x00 .. +0x07, untouched
	TerrainType *m_terrainList;				// this+0x08
};

TerrainType *TerrainTypeCollection::findTerrain( AsciiString name )
{
	TerrainType *terrain;

	for( terrain = m_terrainList; terrain; terrain = terrain->friend_getNext() )
	{

		if( terrain->getName() == name )
			return terrain;

	}  // end for terrain

	// not found
	return 0;

}  // end findTerrain

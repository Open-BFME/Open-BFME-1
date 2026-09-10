// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of TerrainLogic::loadMap.
//
// The retail entry consumes a filename, stream, tail flag, and query flag.
// The decorated name records only the filename and query flag, so this TU
// keeps the two additional observed stack words in an ABI helper.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class ChunkInputStream;

template <typename T>
class StringBase
{
public:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase &other);
	void set(const StringBase &other);

private:
	friend class AsciiString;
	StringBase(const T *text);

protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text);
	~AsciiString();

	Bool isEmpty(void) const
	{
		return m_data == 0 ||
			*reinterpret_cast<const UnsignedShort *>(
				reinterpret_cast<const char *>(m_data) + 4) == 0;
	}

	const char *str(void) const
	{
		static const char empty = 0;
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : &empty;
	}

	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}

	static AsciiString TheEmptyString;
};

class MapObject
{
public:
	MapObject *getNext(void) const
	{
		return *reinterpret_cast<MapObject *const *>(
			reinterpret_cast<const char *>(this) + 4);
	}

	Bool isWaypoint(void) const
	{
		const Int runtimeFlags = *reinterpret_cast<const Int *>(
			reinterpret_cast<const char *>(this) + 0x44);
		return ((static_cast<UnsignedInt>(runtimeFlags) >> 2) & 1) != 0;
	}
};

static MapObject ***const TheMapObjectListPtr =
	reinterpret_cast<MapObject ***>(0x012ED5DC);

class ChunkInputStream
{
public:
	virtual Int read(void *data, Int bytes);
	virtual Int tell(void);
	virtual void absoluteSeek(Int position);
	virtual Bool eof(void);
};

class DataChunkInput;
struct DataChunkInfo;
typedef Bool (__cdecl *DataChunkParserPtr)(DataChunkInput &, DataChunkInfo *, void *);

class UserParser;
class DataChunkInput
{
public:
	DataChunkInput(ChunkInputStream *stream);
	~DataChunkInput(void);
	Bool isValidFileType(void);
	UserParser *registerParser(const AsciiString &label,
		const AsciiString &parentLabel, DataChunkParserPtr parser,
		void *userData = 0);
	Bool parse(void *userData = 0);

private:
	char m_layout[0x28];
};

class TerrainLogic;
extern void j_000241e5(void);
extern void j_00026940(void);
extern void j_0000299b(void);

class TerrainVisual
{
public:
	virtual void _slot00(void) = 0;
	virtual void _slot04(void) = 0;
	virtual void _slot08(void) = 0;
	virtual void _slot0c(void) = 0;
	virtual void _slot10(void) = 0;
	virtual Bool load(AsciiString filename) = 0;
};

static TerrainVisual *const TheTerrainVisual =
	reinterpret_cast<TerrainVisual *>(0x012F7014);

class __declspec(novtable) TerrainLogic
{
public:
	virtual void _slot00(void) = 0;
	virtual void _slot04(void) = 0;
	virtual void _slot08(void) = 0;
	virtual void _slot0c(void) = 0;
	virtual void _slot10(void) = 0;
	virtual void _slot14(void) = 0;
	virtual void _slot18(void) = 0;
	virtual void _slot1c(void) = 0;
	virtual void _slot20(void) = 0;
	virtual void _slot24(void) = 0;
	virtual void _slot28(void) = 0;
	virtual void _slot2c(void) = 0;
	virtual void _slot30(void) = 0;
	virtual void _slot34(void) = 0;
	virtual void _slot38(void) = 0;
	virtual void _slot3c(void) = 0;
	virtual void _slot40(void) = 0;
	virtual AsciiString getSourceFilename(ChunkInputStream *stream);

	Bool loadMapAbi(AsciiString filename, ChunkInputStream *stream,
		Bool tailFlag, Bool query);

private:
	char m_prefix[0x3c];
	AsciiString m_filenameString;
};

Bool TerrainLogic::loadMapAbi(AsciiString filename, ChunkInputStream *stream,
	Bool tailFlag, Bool query)
{
	if (filename.isEmpty())
		return false;

	m_filenameString = filename;

	if (query) {
		MapObject *object = **TheMapObjectListPtr;
		while (object != 0) {
			if (object->isWaypoint()) {
				typedef void (TerrainLogic::*AddWaypointCall)(MapObject *);
				union
				{
					void (*generic)(void);
					AddWaypointCall typed;
				} addWaypoint;
				addWaypoint.generic = j_00026940;
				(this->*addWaypoint.typed)(object);
			}
			object = object->getNext();
		}
	}

	try {
		stream->absoluteSeek(0);
		DataChunkInput file(stream);
		typedef Bool (DataChunkInput::*IsValidFileTypeCall)(void);
		union
		{
			void (*generic)(void);
			IsValidFileTypeCall typed;
		} isValidFileType;
		isValidFileType.generic = j_0000299b;
		if ((file.*isValidFileType.typed)()) {
			{
				AsciiString label("WaypointsList");
				file.registerParser(label,
					AsciiString::TheEmptyString,
					reinterpret_cast<DataChunkParserPtr>(j_000241e5),
					0);
			}
			if (!file.parse(this))
				return false;
		}
	} catch (...) {
	}

	if (!tailFlag)
		TheTerrainVisual->load(getSourceFilename(stream));

	return true;
}

#pragma comment(linker, "/alternatename:?loadMap@TerrainLogic@@UAE_NVAsciiString@@_N@Z=?loadMapAbi@TerrainLogic@@QAE_NVAsciiString@@PAVChunkInputStream@@_N2@Z")

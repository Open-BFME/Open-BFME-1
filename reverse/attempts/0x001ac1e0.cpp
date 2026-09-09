// ?loadMap@TerrainLogic@@UAE_NVAsciiString@@_N@Z
// partial score=0.95 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: clean C++ reconstruction of TerrainLogic::loadMap.
//
// The ZH donor is TerrainLogic.cpp::loadMap.  The BFME body keeps the same
// empty-name guard, waypoint import, and DataChunk parser path.  Its vtable
// call to getSourceFilename and the TerrainVisual load are retained below;
// only the used ABI slices are declared in this TU.

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

// BFME's AsciiString object is one StringBase pointer.  The pointed-to
// StringBase header keeps its character count at +4 and its text at +8.
class AsciiString : public StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	// This is the existing out-of-line BFME constructor at 0x00888BC0.
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

// The map-object list head is MapObject::TheMapObjectListPtr at this BFME
// address.  It is read directly here because the exported data row is not
// part of this TU's source family.
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
	// The retail slot is entered with the observed stream word before the
	// hidden AsciiString return buffer; the parameter name is not asserted.
	virtual AsciiString getSourceFilename(ChunkInputStream *stream);
	virtual Bool loadMap(AsciiString filename, Bool query);

	// The named loadMap row's retail ABI consumes four stack words although
	// its decorated name records only the filename and bool.  This helper keeps
	// the two observed, unnamed words explicit; the ledger maps the proven body
	// to it with object-symbol= rather than inventing their semantics.
	Bool loadMapAbi(AsciiString filename, ChunkInputStream *stream,
		Bool tailFlag, Bool query);

private:
	char m_prefix[0x3c];
	AsciiString m_filenameString;
};

// ?loadMap@TerrainLogic@@UAE_NVAsciiString@@_N@Z
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

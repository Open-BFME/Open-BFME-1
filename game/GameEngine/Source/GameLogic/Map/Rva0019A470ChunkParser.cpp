// cl: /DNDEBUG /MD /EHsc
// Retail 0x0019A470: address-derived DataChunk callback with BuildListInfo payloads.

typedef int Int;
typedef bool Bool;
typedef unsigned char Byte;
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

struct DataChunkInfo;
class Rva0019A470Owner;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	float x;
	float y;
	float z;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}
	void set(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

class DataChunkInput
{
public:
	Int readInt();
	NameKeyType readNameKey();
	AsciiString readAsciiString();
	float readReal();
	Byte bfmeReadByte();
};

class BuildListInfo
{
public:
	BuildListInfo();
	friend class Rva0019A470Owner;
	protected:
	virtual ~BuildListInfo();

	public:
	AsciiString m_buildingName;
	AsciiString m_templateName;
	Coord3D m_location;
	unsigned char m_rallyPointOffset[8];
	float m_angle;
	Bool m_isInitiallyBuilt;
	unsigned char m_padding25[3];
	Int m_numRebuilds;
	BuildListInfo *m_nextBuildList;
	AsciiString m_script;
	Int m_health;
	Bool m_whiner;
	Bool m_unsellable;
	Bool m_repairable;
	unsigned char m_padding3b[0x51];

	void setBuildingName(AsciiString name) { m_buildingName.set(name); }
	void setTemplateName(AsciiString name) { m_templateName.set(name); }
	void setLocation(Coord3D location) { m_location = location; }
	void setAngle(float angle) { m_angle = angle; }
	void setInitiallyBuilt(Bool built) { m_isInitiallyBuilt = built; }
	void setNumRebuilds(Int rebuilds) { m_numRebuilds = rebuilds; }
	void setScript(AsciiString script) { m_script.set(script); }
	void setHealth(Int health) { m_health = health; }
	void setWhiner(Bool whiner) { m_whiner = whiner; }
	void setUnsellable(Bool unsellable) { m_unsellable = unsellable; }
	void setRepairable(Bool repairable) { m_repairable = repairable; }
};

struct Rva001999C0Element
{
	char m_body[140];
};

class Rva0019A2D0Table
{
public:
	void appendKeyed(NameKeyType key, const Rva001999C0Element *element, Int list);
};

class Rva0019A470Owner
{
public:
	Bool parse(DataChunkInput &file, DataChunkInfo *info, Int list);
};

// ?parse@Rva0019A470Owner@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@H@Z
Bool Rva0019A470Owner::parse(DataChunkInput &file, DataChunkInfo *info, Int list)
{
	Int count = file.readInt();
	for (Int i = 0; i < count; ++i)
	{
		if (i >= 0x20)
			break;

		NameKeyType key = file.readNameKey();
		{
		Coord3D location;
		BuildListInfo record;
		Int innerCount = file.readInt();
		while (innerCount > 0)
		{
			record.setBuildingName(file.readAsciiString());
			record.setTemplateName(file.readAsciiString());

			location.x = file.readReal();
			location.y = file.readReal();
			location.z = file.readReal();
			record.setLocation(location);
			record.setAngle(file.readReal());

			record.setInitiallyBuilt(file.bfmeReadByte());
			record.setNumRebuilds(file.readInt());
			record.setScript(file.readAsciiString());
			record.setHealth(file.readInt());
			record.setWhiner(file.bfmeReadByte());
			record.setUnsellable(file.bfmeReadByte());
			record.setRepairable(file.bfmeReadByte());

			reinterpret_cast<Rva0019A2D0Table *>(this)->appendKeyed(
				key, reinterpret_cast<const Rva001999C0Element *>(&record), list);
			--innerCount;
		}
		}
	}

	return true;
}

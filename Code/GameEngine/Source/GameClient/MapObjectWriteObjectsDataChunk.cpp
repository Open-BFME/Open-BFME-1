// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Shared BFME map-object chunk writer.  The retail strings and field order
// match the canonical WorldBuilder map writer: location, angle, flags, name,
// and the object's property dictionary.

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
private:
	void *m_data;
};

class Dict
{
private:
	unsigned char m_data[1];
};

class MapObject
{
public:
	const Coord3D *getLocation() const { return &m_location; }

	void *m_vftable;
	MapObject *m_nextMapObject;
	Coord3D m_location;
	AsciiString m_objectName;
	void *m_thingTemplate;
	Real m_angle;
	Int m_flags;
	Dict m_properties;
};

class MapObjectWriterFilter
{
public:
	virtual void bfmeFilterDestructorSlot();
	virtual Bool shouldWrite(MapObject *object);
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void closeDataChunk();
	void writeReal(Real value);
	void writeInt(Int value);
	void writeAsciiString(const AsciiString &value);
	void writeDict(const Dict &value);
};

void bfmeWriteObjectsDataChunk00087610(MapObject *objects, DataChunkOutput *output,
	MapObjectWriterFilter *filter)
{
	output->openDataChunk("ObjectsList", 3);

	for (MapObject *object = objects; object; object = object->m_nextMapObject)
	{
		if (!filter->shouldWrite(object))
			continue;

		output->openDataChunk("Object", 3);
		Coord3D location;
		location.x = object->getLocation()->x;
		location.y = object->getLocation()->y;
		location.z = object->getLocation()->z;
		output->writeReal(location.x);
		output->writeReal(location.y);
		output->writeReal(location.z);
		output->writeReal(object->m_angle);
		output->writeInt(object->m_flags);
		output->writeAsciiString(object->m_objectName);
		output->writeDict(object->m_properties);
		output->closeDataChunk();
	}

	output->closeDataChunk();
}

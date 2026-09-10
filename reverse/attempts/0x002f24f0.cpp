// ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
// partial score=0.95 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ScriptActions::doMoveCameraTo, retail 0x002F24F0.

typedef float Real;
typedef bool Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template <typename T> class StringBase
{
public:
	StringBase(const StringBase &);
protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString();
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	unsigned char m_pad000[0x0c];
	Coord3D m_location;
};

struct CameraMarker
{
	const Coord3D *getLocation() const { return &m_location; }
	unsigned char m_pad000[8];
	Coord3D m_location;
};

class CameraMarkerList
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void moveCameraTo(const Coord3D *destination, const CameraMarker *marker,
		int milliseconds, Bool orient, Real easeInMilliseconds, Real easeOutMilliseconds);
	CameraMarker *find(const AsciiString &name) const;
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Waypoint *getWaypointByName(AsciiString name);
};

class View : public CameraMarkerList
{
};

extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void doMoveCameraTo(const AsciiString &waypoint, Real sec,
		Real cameraStutterSec, Real easeIn, Real easeOut);
};

// ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z
void ScriptActions::doMoveCameraTo(const AsciiString &waypoint, Real sec,
	Real, Real easeIn, Real easeOut)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
	CameraMarker *marker = TheTacticalView->find(waypoint);
	if (way == 0 && marker == 0)
		return;

	Coord3D destination;
	if (way != 0)
		destination = *way->getLocation();
	if (marker != 0)
		destination = *marker->getLocation();

	TheTacticalView->moveCameraTo(&destination, marker, (int)(sec * 1000.0f), true,
		easeIn * 1000.0f, easeOut * 1000.0f);
}

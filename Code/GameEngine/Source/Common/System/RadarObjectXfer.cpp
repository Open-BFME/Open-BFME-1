// cl: /DNDEBUG /MD /EHsc
// RadarObject::xfer, retail 0x001085E0 (170 bytes).
//
// Identity: slot 3 of vftable 0x01088838, which the RadarObject constructor
// inlined in the matched xferRadarObjectList (0x00108A90) installs, and the
// body is the Zero Hour RadarObject::xfer line for line: version 1, the object
// ID through the shared ObjectID xfer helper, on load find the object or throw
// the BFME xfer exception (tag 5, as the matched list helper does) and point
// the object back at this node, then the color.  BFME first returns early when
// the xfer is a light CRC pass, and the object's back-pointer is the
// store at Object+0x20C (the Zero Hour friend_setRadarData inline).

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef Int Color;
typedef bool Bool;

#define NULL 0

struct XferVersion
{
	UnsignedByte current;
	UnsignedByte minimum;
};

struct XferException
{
	char *text;
	Int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading() const;
	virtual Bool isSaving() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(Int *value);
};

void xferObjectID0010C3C0(Xfer *xfer, UnsignedInt *objectID);

class RadarObject;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	UnsignedInt getID() const { return m_id; }

	void friend_setRadarData(RadarObject *radarData) { m_field20C = radarData; }

private:
	unsigned char m_pad00[0x74];
	UnsignedInt m_id;
	unsigned char m_pad78[0x20c - 0x78];
	RadarObject *m_field20C;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

class Snapshot
{
public:
	virtual ~Snapshot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class RadarObject : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);

	Object *m_object;
	RadarObject *m_next;
	Color m_color;
};

// ?xfer@RadarObject@@MAEXPAVXfer@@@Z
void RadarObject::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	XferVersion version;
	version.current = 1;
	version.minimum = 1;
	xfer->xferVersion(&version);

	UnsignedInt objectID = m_object ? m_object->getID() : 0;
	xferObjectID0010C3C0(xfer, &objectID);
	if (xfer->isLoading())
	{
		m_object = TheGameLogic->findObjectByID(objectID);
		if (m_object == NULL)
		{
			XferException error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}

		m_object->friend_setRadarData(this);
	}

	xfer->xferInt(&m_color);
}

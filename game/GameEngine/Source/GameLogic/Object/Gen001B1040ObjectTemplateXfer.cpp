// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME 0x001B1040: transfer an object/drawable reference and its template name.
// The dump is the small save/load helper beside the proven BFME Xfer bodies.

typedef unsigned char UnsignedByte;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();
	void set(const AsciiString &text);
	char *m_data;
};

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual void slot03();
	virtual bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &version);
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
	virtual void xferAsciiString(AsciiString &text);
};

void friend_xferObjectID(Xfer *xfer, ObjectID *id);

class Drawable;

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable() const;

	unsigned char m_pad[0x70];
	ObjectID m_id;
};

class Drawable
{
public:
	unsigned char m_pad[0xfc];
	Object *m_object;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class ThingTemplate
{
public:
	unsigned char m_pad[0x20];
	AsciiString m_name;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern GameLogic *TheGameLogic;
extern ThingFactory *TheThingFactory;
extern const char g_Rva0107301CEmptyString[];

class Gen_001B1040
{
public:
	void xfer(Xfer *xfer);

private:
	Drawable *m_drawable;
	ThingTemplate *m_template;
};

void Gen_001B1040::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	{
		XferVersion version(1, 1);
		xfer->xferVersion(version);
	}

	if (xfer->IsLoading())
	{
		ObjectID objectID = INVALID_OBJECT_ID;
		AsciiString name(g_Rva0107301CEmptyString);
		friend_xferObjectID(xfer, &objectID);
		xfer->xferAsciiString(name);

		if (objectID != 0)
		{
			Object *object = TheGameLogic->findObjectByID(objectID);
			if (object != 0)
				m_drawable = object->getDrawable();
		}

		if (name.m_data != 0 && *((unsigned short *)(name.m_data + 4)) != 0)
			m_template = TheThingFactory->findTemplate(name);
	}
	else if (xfer->IsStoring())
	{
		ObjectID objectID = INVALID_OBJECT_ID;
		if (m_drawable != 0)
		{
			Object *object = m_drawable->m_object;
			if (object != 0)
				objectID = object->m_id;
		}

		AsciiString name(g_Rva0107301CEmptyString);
		if (m_template != 0)
			name.set(m_template->m_name);

		friend_xferObjectID(xfer, &objectID);
		xfer->xferAsciiString(name);
	}
}

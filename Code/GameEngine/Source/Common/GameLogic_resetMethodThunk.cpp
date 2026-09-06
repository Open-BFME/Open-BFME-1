// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString(const char *);
	~AsciiString();
	int compare(const char *) const;

private:
	char *m_data;
};

class ThingTemplate;

class MapObject
{
public:
	AsciiString &getName() { return m_name; }
	void setName(const AsciiString &);
	void setThingTemplate(const ThingTemplate *);

private:
	char m_pad00[0x14];
	AsciiString m_name;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &);
};

extern ThingFactory *TheThingFactory;

// ?handleNameChange@@YAXPAVMapObject@@@Z
void handleNameChange(MapObject *mapObj)
{
	if (!mapObj->getName().compare("AmericaTankLeopard"))
	{
		mapObj->setName("AmericaTankCrusader");
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(mapObj->getName());
		mapObj->setThingTemplate(thingTemplate);
	}
	if (!mapObj->getName().compare("AmericaVehicleHumVee"))
	{
		mapObj->setName("AmericaVehicleHumvee");
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(mapObj->getName());
		mapObj->setThingTemplate(thingTemplate);
	}
}

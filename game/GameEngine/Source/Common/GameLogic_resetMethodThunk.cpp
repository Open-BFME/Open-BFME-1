// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

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
};

// Retail's factory lookup is BfmeThingFactory::findTemplate (0x00137E80); it
// returns a const ThingTemplate and takes the name by const reference.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &);
};

extern ThingFactory *TheThingFactory;

// ?handleNameChange@@YAXPAVMapObject@@@Z
void handleNameChange(MapObject *mapObj)
{
	if (!mapObj->getName().compare("AmericaTankLeopard"))
	{
		mapObj->setName("AmericaTankCrusader");
		const ThingTemplate *thingTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate(mapObj->getName());
		mapObj->setThingTemplate(thingTemplate);
	}
	if (!mapObj->getName().compare("AmericaVehicleHumVee"))
	{
		mapObj->setName("AmericaVehicleHumvee");
		const ThingTemplate *thingTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate(mapObj->getName());
		mapObj->setThingTemplate(thingTemplate);
	}
}

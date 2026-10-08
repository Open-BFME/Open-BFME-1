// cl: /DNDEBUG /MD /EHsc

class AsciiString;
class Player;

// Retail ILT 0x0000DA8A lands on ThingTemplate::calcCostToBuild (0x0013E390).
class ThingTemplate
{
public:
	int calcCostToBuild(const Player *player, int index) const;
};

// Retail ILT 0x00028560 lands on BfmeThingFactory::findTemplate (0x00137E80).
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// Retail global 0x012EF1D8 is EA's ThingFactory singleton, defined once in
// Common/Thing/ThingFactory.cpp; this TU keeps its own factory view of it.
class ThingFactory;

extern ThingFactory *TheThingFactory;

class Rva000F9270FactoryLookup
{
public:
	void *evaluate(void *argument);

private:
	unsigned char m_unmodelled_000[0x2c];
	void *m_context;
};

void *Rva000F9270FactoryLookup::evaluate(void *argument)
{
	const ThingTemplate *product = ((BfmeThingFactory *)TheThingFactory)->findTemplate(*(const AsciiString *)this);
	if (product)
		return (void *)product->calcCostToBuild((const Player *)argument, (int)m_context);
	return 0;
}

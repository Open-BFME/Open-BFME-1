// cl: /DNDEBUG /MD /EHsc

class BfmeUseB980
{
public:
	void *bfmeApply980B(int argument, int context);
};

class AsciiString;
class ThingTemplate;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// Retail global 0x012EF1D8 is EA's ThingFactory singleton, defined once in
// Common/Thing/ThingFactory.cpp; this TU keeps its own factory view of it.
class ThingFactory;

extern ThingFactory *TheThingFactory;

class Rva000F92B0FactoryLookup
{
public:
	void *evaluate(void *argument);

private:
	unsigned char m_unmodelled_000[0x34];
	void *m_context;
};

void *Rva000F92B0FactoryLookup::evaluate(void *argument)
{
	BfmeUseB980 *product = (BfmeUseB980 *)((BfmeThingFactory *)TheThingFactory)->findTemplate(*reinterpret_cast<const AsciiString *>(this));
	if (product)
		return product->bfmeApply980B((int)argument, (int)m_context);
	return 0;
}

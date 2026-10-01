// cl: /DNDEBUG /MD /EHsc

class Rva000F9270Product
{
public:
	void *evaluate(void *argument, void *context);
};

class Rva000F9270Factory
{
public:
	Rva000F9270Product *find(void *key);
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
	Rva000F9270Product *product = ((Rva000F9270Factory *)TheThingFactory)->find(this);
	if (product)
		return product->evaluate(argument, m_context);
	return 0;
}

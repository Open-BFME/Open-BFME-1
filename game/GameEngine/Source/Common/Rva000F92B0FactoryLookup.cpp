// cl: /DNDEBUG /MD /EHsc

class Rva000F92B0Product
{
public:
	void *evaluate(void *argument, void *context);
};

class Rva000F92B0Factory
{
public:
	Rva000F92B0Product *find(void *key);
};

extern Rva000F92B0Factory *TheRva000F92B0Factory;

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
	Rva000F92B0Product *product = TheRva000F92B0Factory->find(this);
	if (product)
		return product->evaluate(argument, m_context);
	return 0;
}

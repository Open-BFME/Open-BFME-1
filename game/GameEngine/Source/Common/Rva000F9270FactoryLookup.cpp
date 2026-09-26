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

extern Rva000F9270Factory *TheRva000F9270Factory;

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
	Rva000F9270Product *product = TheRva000F9270Factory->find(this);
	if (product)
		return product->evaluate(argument, m_context);
	return 0;
}

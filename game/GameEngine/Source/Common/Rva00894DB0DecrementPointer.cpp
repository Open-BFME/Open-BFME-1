class Rva00894DB0Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

unsigned int Rva00894DB0Accessor::decrement(unsigned int *value)
{
	return --*value;
}

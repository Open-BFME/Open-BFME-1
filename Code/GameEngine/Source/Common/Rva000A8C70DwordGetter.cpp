class Rva000A8C70DwordGetter
{
public:
	int get(void) const;
};

int Rva000A8C70DwordGetter::get(void) const
{
	return *((int *)((char *)this + 4));
}

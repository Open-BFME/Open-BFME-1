// cl: /O2 /Ob1 /EHsc

class Rva00321F90
{
public:
	void *getFieldAt4(void);
};

void *Rva00321F90::getFieldAt4(void)
{
	return *(void **)((char *)this + 4);
}

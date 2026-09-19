// cl: /O2 /Ob1 /EHsc

// Retail 0x0026B490 returns the dword at this-relative offset four.  The
// thunk caller does not prove a semantic owner, so the method keeps its RVA.

class Rva0026B490DwordGetter
{
public:
	void *getFieldAt4() const;
};

void *Rva0026B490DwordGetter::getFieldAt4() const
{
	return *(void **)((const char *)this + 4);
}

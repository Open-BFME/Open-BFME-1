struct RvaC4390First;
struct RvaC4390Second;

struct RvaC4390Interface
{
	virtual void slot0();
	virtual void slot1();
	virtual unsigned char accepts(RvaC4390Second *value);
};

struct RvaC4390First
{
	RvaC4390Interface *getInterface();
};

struct RvaC4390Second
{
	RvaC4390First *resolve(int mode);
};

unsigned char __stdcall rvaC4390RelationCheck(
	RvaC4390First *first,
	RvaC4390Second *second,
	void *)
{
	if (first != 0 && second != 0) {
		if (first != second->resolve(0)) {
			RvaC4390Interface *interfaceValue = first->getInterface();
			if (interfaceValue != 0) {
				return interfaceValue->accepts(second) != 0;
			}
		}
	}
	return false;
}

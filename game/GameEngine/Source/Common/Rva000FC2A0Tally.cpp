struct BfmeThingEJ;
int bfmeFindEJ(BfmeThingEJ *object);

struct Rva000FC2A0VirtualResult
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual int read(int value);
};

struct Rva000FC2A0Tally
{
	int total;
	int argument;
};

int __cdecl rva000fc2a0Tally(BfmeThingEJ *object, Rva000FC2A0Tally *tally)
{
	Rva000FC2A0VirtualResult *result = (Rva000FC2A0VirtualResult *)bfmeFindEJ(object);
	if (result)
		tally->total += result->read(tally->argument);
	return true;
}

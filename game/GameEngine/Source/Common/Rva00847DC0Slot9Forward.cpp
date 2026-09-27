// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-
// Retail 0x00847DC0 calls virtual slot 9 with the argument and returns it.
// The address-derived owner preserves the observed ABI without claiming a class identity.

class Rva00847DC0Owner
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void invoke(void *argument) = 0;
	void *dispatch(void *argument);
};

void *Rva00847DC0Owner::dispatch(void *argument)
{
	invoke(argument);
	return argument;
}

// cl: /DNDEBUG /MD /O2 /EHsc

// The carved boundary at 0x006435B0 contains only a return. The address-derived
// class keeps that opaque identity without claiming a semantic owner.
class Rva006435B0Noop
{
public:
	void run();
};

void Rva006435B0Noop::run()
{
}

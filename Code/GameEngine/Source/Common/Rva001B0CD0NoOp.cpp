// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail 0x001B0CD0 contains only ret 4. The carved boundary and its
// incremental-link jump prove one unused four-byte argument, but not the
// semantic owner.
class Rva001B0CD0Owner
{
public:
	void reset(unsigned int value);
};

void Rva001B0CD0Owner::reset(unsigned int value)
{
}

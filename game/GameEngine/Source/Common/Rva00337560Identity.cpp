// cl: /DNDEBUG /MD /EHsc

// The carved body returns this unchanged. The ILT thunk proves the address,
// but no caller proves a semantic owner or method name.
class Rva00337560Identity
{
public:
	void *identity();
};

void *Rva00337560Identity::identity()
{
	return this;
}

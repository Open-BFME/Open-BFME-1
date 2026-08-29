// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// The surrounding 23-byte wrappers establish this as the shared two-argument
// byte predicate.  The retail body forwards only the first argument to its
// one-argument worker and normalises the returned byte to zero or one.
class Rva002DF100
{
public:
	unsigned char test(void *first, void *second);
	unsigned char testOne(void *value);
};

unsigned char Rva002DF100::test(void *first, void *)
{
	return testOne(first) != 0;
}

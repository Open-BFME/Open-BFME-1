// cl: /DNDEBUG /MD /EHsc

struct Gen_uwt_0002aaa9;
extern Gen_uwt_0002aaa9 *g_Va0135282C;
void *operator new(unsigned int, Gen_uwt_0002aaa9 *);
void operator delete(void *, Gen_uwt_0002aaa9 *);

struct Rva00C62070Object
{
	Rva00C62070Object(int value);
};

// This function is a stub that exists only to make MSVC emit the 19-byte
// placement-cleanup funclet at retail 0x00C62070. Nothing identifies the
// function retail compiled to emit that funclet, so the ledger row records no
// parent. Do not read the name below as retail's.
Rva00C62070Object *Rva00C62070Parent()
{
	char pad[12];
	return new (g_Va0135282C) Rva00C62070Object(0);
}

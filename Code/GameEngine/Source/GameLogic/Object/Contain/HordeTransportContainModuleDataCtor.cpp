// cl: /DNDEBUG /MD /EHsc

// The disputed ICF-shared constructor at retail 0x0024D190. Eighteen bytes: the
// base's constructor and then this class's own vftable pointer, nothing else.
//
// The name used to sit on 0x00852130, which is INI::initFromINIMultiProc - a
// seventy-nine byte function that clears two sixteen-entry tables and is not a
// module-data constructor at all. It was one of seven names aliased onto those
// bytes; that claim is retracted here.

class Rva0024D190Base
{
public:
	Rva0024D190Base();

	virtual void moduleDataAnchor();
};

class Rva0024D190 : public Rva0024D190Base
{
public:
	Rva0024D190();
};

Rva0024D190::Rva0024D190()
{
}

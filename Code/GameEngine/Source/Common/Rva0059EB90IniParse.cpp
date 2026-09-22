// cl: /DNDEBUG /MD /EHsc

struct FieldParse;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BfmeC1137
{
public:
	BfmeC1137();

private:
	unsigned char m_pad[0x40];
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *fieldParse);
};

class Gen_00489270
{
public:
	void m(int value);
};

extern const FieldParse TheRva0059EB90FieldParse[];

// ?rva0059EB90@@YAXPAVINI@@PAVGen_00489270@@@Z
void rva0059EB90(INI *ini, Gen_00489270 *store)
{
	BfmeC1137 *item = new BfmeC1137;
	ini->initFromINI(item, TheRva0059EB90FieldParse);
	store->m((int)item);
}

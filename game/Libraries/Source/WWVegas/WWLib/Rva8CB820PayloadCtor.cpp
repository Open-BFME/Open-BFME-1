// ??0Rva8CB820Derived@@QAE@HHHHHHHHHHHHH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable 13-argument derived constructor, retail 0x008CB820 (145 bytes).

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	char _bfme_base_slice[0x1c];
};

class Rva8CB820Payload
{
public:
	Rva8CB820Payload(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		int a8, int a9, int a10, int a11, int a12, int a13);
	~Rva8CB820Payload();
};

class Rva8CB820Derived : public Rva899F00Base, public Rva8CB820Payload
{
public:
	Rva8CB820Derived(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		int a8, int a9, int a10, int a11, int a12, int a13);

};

Rva8CB820Derived::Rva8CB820Derived(int a1, int a2, int a3, int a4, int a5,
	int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13) :
	Rva899F00Base(reinterpret_cast<const char *>(0x24), 8),
	Rva8CB820Payload(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13)
{
}

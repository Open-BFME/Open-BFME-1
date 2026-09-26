// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0051D990
{
public:
	void first();
	void wrap(int a);
};

void Rva0051D990Second(int, int, int);

void Rva0051D990::wrap(int)
{
	first();
	Rva0051D990Second(2, 3, 0);
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00519C90
{
public:
	void first();
	void wrap(int a);
};

void Rva00519C90Second(int, int);

void Rva00519C90::wrap(int)
{
	first();
	Rva00519C90Second(0, 0);
}

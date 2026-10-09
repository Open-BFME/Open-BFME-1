// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeQ1078
{
public:
	void bfmeGo1078A();
};

class Rva00519C90
{
public:
	void wrap(int a);
};

void _bfme_showOptions(int, int);

void Rva00519C90::wrap(int)
{
	reinterpret_cast<BfmeQ1078 *>(this)->bfmeGo1078A();
	_bfme_showOptions(0, 0);
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0051D590
{
public:
	void first();
};

class Rva0051DCE0
{
public:
	void wrap(int a);
};

void _bfme_showSkirmish();

void Rva0051DCE0::wrap(int)
{
	reinterpret_cast<Rva0051D590 *>(this)->first();
	_bfme_showSkirmish();
}

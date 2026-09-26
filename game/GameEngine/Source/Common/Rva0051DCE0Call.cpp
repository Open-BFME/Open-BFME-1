// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0051DCE0
{
public:
	void first();
	void wrap(int a);
};

void Rva0051DCE0Second();

void Rva0051DCE0::wrap(int)
{
	first();
	Rva0051DCE0Second();
}

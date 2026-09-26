// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0051DB00
{
public:
	void first();
	void wrap(int a);
};

void Rva0051DB00Second();

void Rva0051DB00::wrap(int)
{
	first();
	Rva0051DB00Second();
}

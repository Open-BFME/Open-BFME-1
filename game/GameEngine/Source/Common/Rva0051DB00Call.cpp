// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0051D590
{
public:
	void first();
};

class Rva0051DB00
{
public:
	void wrap(int a);
};

void _bfme_showLanLobby();

void Rva0051DB00::wrap(int)
{
	reinterpret_cast<Rva0051D590 *>(this)->first();
	_bfme_showLanLobby();
}

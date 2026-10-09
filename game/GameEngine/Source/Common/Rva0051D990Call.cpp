// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0051D590
{
public:
	void first();
};

class Rva0051D990
{
public:
	void wrap(int a);
};

void showAptSaveLoad(void *, int, char);

void Rva0051D990::wrap(int)
{
	reinterpret_cast<Rva0051D590 *>(this)->first();
	showAptSaveLoad(reinterpret_cast<void *>(2), 3, 0);
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail ILTs 00005F88 -> 0051D590 and 0001D561 -> 0055E290 name
// the matched niladic thiscall member and two-int cdecl options function.
class Rva0051D590
{
public:
	void first();
};

class Rva0051D9B0
{
public:
	void wrap(int a);
};

void _bfme_showOptions(int, int);

void Rva0051D9B0::wrap(int)
{
	((Rva0051D590 *)this)->first();
	_bfme_showOptions(0, 1);
}

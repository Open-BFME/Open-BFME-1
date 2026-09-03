// ?erase@Rva0081CED0Vec@@QAEPAURva0081CED0Elem@@PAU2@@Z
// partial score=0.82 date=2026-09-03
// cl: /O2
// partial 59/59 register wall: pos in edx not edi; sub ecx,0x1C not add eax,-0x1C

struct Rva0081CED0Elem
{
	~Rva0081CED0Elem();
	char m_pad[0x1C];
};

Rva0081CED0Elem *__cdecl bfmeCopyVIA5(
	Rva0081CED0Elem *first,
	Rva0081CED0Elem *last,
	Rva0081CED0Elem *dest,
	Rva0081CED0Elem **hint,
	int flag);

class Rva0081CED0Vec
{
public:
	Rva0081CED0Elem *erase(Rva0081CED0Elem *pos);

	Rva0081CED0Elem *_M_start;
	Rva0081CED0Elem *_M_finish;
	Rva0081CED0Elem *_M_end_of_storage;
};

// ?erase@Rva0081CED0Vec@@QAEPAURva0081CED0Elem@@PAU2@@Z
Rva0081CED0Elem *Rva0081CED0Vec::erase(Rva0081CED0Elem *pos)
{
	Rva0081CED0Elem *finish = _M_finish;
	Rva0081CED0Elem *next = pos + 1;
	if (next != finish)
		bfmeCopyVIA5(next, finish, pos, &pos, 0);
	finish = _M_finish;
	finish += -1;
	_M_finish = finish;
	finish->~Rva0081CED0Elem();
	return pos;
}

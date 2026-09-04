// ?gen002EADF0@@YAXPAX0H0@Z
// cl: /O2 /Ob0
// Lever: the by-value temp's EH saved-esp is parked in a DEAD incoming-argument
// slot; retail used the 4th argument's, ours the 2nd's. Referencing b in each
// expression (no local) keeps b's slot live past the temp, so the 4th is chosen
// (docs/shape_levers.md, 'EH saved-esp in a parameter slot').

class Rva002E8FC0
{
public:
	Rva002E8FC0(const Rva002E8FC0 &);
	~Rva002E8FC0();

private:
	char m_bfmeBody[20];
};

void gen002EADF0Helper(void *a, Rva002E8FC0 *p, Rva002E8FC0 *q,
	Rva002E8FC0 val, void *c, int zero);

void gen002EADF0(void *a, void *b, int, void *c)
{
	gen002EADF0Helper(a, (Rva002E8FC0 *)b - 1, (Rva002E8FC0 *)b - 1, *((Rva002E8FC0 *)b - 1), c, 0);
}

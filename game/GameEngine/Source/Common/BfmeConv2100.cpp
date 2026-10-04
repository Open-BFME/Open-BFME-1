extern void j_0001815b();

struct Rva0069F740Ref
{
	Rva0069F740Ref(int v) : m_bfmeVYM(v) {}

	int m_bfmeVYM;
};

class Rva0069F740Owner
{
public:
	Rva0069F740Ref *bfmeGetYM(Rva0069F740Ref *out, int a, int b);
};

Rva0069F740Ref *Rva0069F740Owner::bfmeGetYM(Rva0069F740Ref *out, int a, int b)
{
	typedef Rva0069F740Ref (Rva0069F740Owner::*GetSlot)(int, int);
	union { void (*fn)(); GetSlot call; } getSlot = { j_0001815b };
	*out = (this->*getSlot.call)(a, b);

	return out;
}

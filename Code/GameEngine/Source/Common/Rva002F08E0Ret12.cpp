// cl: /O2 /DNDEBUG /MD

// Retail 0x002F08E0 contains only ret 0xc. The carved boundary proves an
// empty thiscall body with three stack arguments, but no semantic owner.
class Rva002F08E0Owner
{
public:
	void ret12(int, int, int);
};

void Rva002F08E0Owner::ret12(int, int, int)
{
}

class Rva002F0900Owner
{
public:
	void ret12(int, int, int);
};

void Rva002F0900Owner::ret12(int, int, int)
{
}

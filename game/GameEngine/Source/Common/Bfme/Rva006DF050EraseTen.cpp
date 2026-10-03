// cl: /O2 /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x006DF050 (44 bytes).
// Ten 12-byte map/tree slots at this+0x94; if the int key is nonzero, erase
// it from each. The callee is STLport _Rb_tree<int,...>::erase at 0x006DEFC0
// (thunk 0x0002F0EA). Named caller: BfmeThingELGa::bfmeGoELGa.

// The ILT thunk at 0x0002F0EA is the retail body at this call site
// (targets/game/reverse/functions.csv ?j_0002f0ea@@YAXXZ, 5 bytes, tail
// jmp to 0x00ADefc0).  Retail calls it thiscall on each 12-byte slot with the
// key address in the stack slot, so the route is a member-pointer union over
// the defined thunk symbol instead of a TU-local placeholder method.
extern void j_0002f0ea();

class Rva006DF050Slot
{
private:
	unsigned char m_bytes[12];
};

class Rva006DF050
{
public:
	void eraseKey(int key);

private:
	unsigned char m_unmodelled_000[0x94];
	Rva006DF050Slot m_slots[10];
};

void Rva006DF050::eraseKey(int key)
{
	union
	{
		void (*raw)();
		unsigned (Rva006DF050Slot::*member)(const int &);
	} route;

	if (key)
	{
		route.raw = j_0002f0ea;
		Rva006DF050Slot *slot = m_slots;
		int n = 10;
		do
		{
			(slot->*route.member)(key);
			++slot;
			--n;
		} while (n);
	}
}

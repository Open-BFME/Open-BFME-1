// cl: /O2 /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x006DF050 (44 bytes).
// Ten 12-byte map/tree slots at this+0x94; if the int key is nonzero, erase
// it from each. The callee is STLport _Rb_tree<int,...>::erase at 0x006DEFC0
// (thunk 0x0002F0EA). Named caller: BfmeThingELGa::bfmeGoELGa.

class Rva006DF050Slot
{
public:
	unsigned erase(const int &key);

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
	if (key)
	{
		Rva006DF050Slot *slot = m_slots;
		int n = 10;
		do
		{
			slot->erase(key);
			++slot;
			--n;
		} while (n);
	}
}

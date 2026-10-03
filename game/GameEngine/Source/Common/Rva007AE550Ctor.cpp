// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The class owns the vftable at 0x011283D4 that this constructor seats.  Slot 0
// of that vftable is ILT thunk 0x00033938, which tail-jumps to retail 0x007AE5A0
// -- the thirty-one-byte scalar deleting destructor that re-seats 0x011283D4.
// So the class has a virtual destructor, not a plain `void dummy()`: declaring
// one empty here makes MSVC emit exactly those thirty-one bytes as this class's
// own `??_G` COMDAT, which is the same body retail carries at 0x007AE5A0.
// The named `dummy` had no definition anywhere and left the vftable slot 1 of
// the emitted table unresolved (LNK2001 ?dummy@Rva007AE550Base@@UAEXXZ).
class Rva007AE550Base
{
public:
	Rva007AE550Base(int value);
	virtual ~Rva007AE550Base() {}

	int m_value;
};

Rva007AE550Base::Rva007AE550Base(int value)
{
	m_value = value;
}

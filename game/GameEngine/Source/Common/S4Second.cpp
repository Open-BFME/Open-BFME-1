// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: s4Second, retail 0x005F40C0, 87 bytes. The body carried only a
// machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name with
// identity=real.
//
// The whole function is one function-local static: a single byte of object at
// 0x012F6DDB with the guard word immediately after it at 0x012F6DDC. The first
// call through sets bit 1 of the guard, runs the constructor, and hands the
// compiler's destructor helper to atexit; every later call finds the bit set
// and does nothing at all.
//
// The frame is there for the constructor -- the unwind state is written just
// before it, so the guard bit is undone if it throws.

class Gen005F3EE0
{
public:
	Gen005F3EE0();						// ILT 0x0000B62C
	~Gen005F3EE0();

private:
	char m_bfmeByte;
};

// ?s4Second@@YAXXZ
void s4Second(void)
{
	static Gen005F3EE0 s_bfmeOnce;
}

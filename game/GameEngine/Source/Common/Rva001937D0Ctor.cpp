// cl: /O2 /Ob0

// 0x0001AB86 is retail's 5-byte ILT thunk (?j_0001ab86@@YAXXZ), defined only
// as j_0001ab86 in game/gen_small/thunks_012.cpp; the base copy is therefore
// routed through the thunk's own address.  Same shape as
// Rva0033A4C0Copy.cpp.
void j_0001ab86();

class Rva0033CopyBase
{
private:
	char m_pad[8];
};

class Rva001937D0 : public Rva0033CopyBase
{
	int m_08;

public:
	Rva001937D0(const Rva0033CopyBase &other, const int *extra);
};

Rva001937D0::Rva001937D0(const Rva0033CopyBase &other, const int *extra)
{
	typedef void (Rva0033CopyBase::*CopyCall)(const Rva0033CopyBase &);
	union { void (*address)(); CopyCall member; } copy = { j_0001ab86 };
	(static_cast<Rva0033CopyBase *>(this)->*copy.member)(other);
	m_08 = *extra;
}

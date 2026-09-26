// Four neighbouring members from 0x00841540-0x008427B0, all of them a guard
// over a call and nothing else.
//
// 0x00841540 (10 bytes) -- `push ecx / call / add esp,4 / ret`: a __thiscall
// member that hands `this` to a cdecl function and cleans one argument.  The
// cleanup is `add esp,4` and NOT `pop ecx`, which is the tell that the call's
// result is live: MSVC 7.1 pops into ecx when the return value is dead and
// spends the three-byte add when eax has to survive.  So the member returns
// what the callee returned.
//
// 0x00841640 (29 bytes) -- a flag byte at +0x68 guards a virtual call through
// slot 0x30 with the argument -1; the result is compared against -1 and turned
// into 0 / -1 by `xor ecx,ecx / setne cl / dec ecx`.  The `je` at the top jumps
// FORWARD to the `xor eax,eax / ret` at the very end, so in the source the
// zero return is the fall-through tail after the guarded block, not an early
// return inside it -- writing it the other way round flips the branch.
//
// 0x00841E10 and 0x008427B0 (29 bytes each) -- THREE flag bytes at consecutive
// offsets, each tested and each returning on non-zero, and then a TAIL JUMP
// into another member with the same single argument.  A tail jump rather than a
// call is what says the wrapper adds nothing after the callee returns.  The two
// rows are the same shape at two different offsets (+0x67/+0x68/+0x69 and
// +0x37/+0x38/+0x39), which is two classes, not one.
//
// Identity is not recovered; every name is derived from an address, and the
// three callees are pinned by those names.

struct Rva00841540Owner
{
	int run();
};
extern int Rva0084B210Run(Rva00841540Owner *self);
int Rva00841540Owner::run()
{
	return Rva0084B210Run(this);
}

struct Rva00841640Stream
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual int seek(int pos);

	char m_pad[0x64];
	char m_open;

	int tell();
};

int Rva00841640Stream::tell()
{
	if (m_open)
		return seek(-1) == -1 ? -1 : 0;
	return 0;
}

struct Rva00841E10Owner
{
	char m_pad[0x67];
	char m_busy;
	char m_locked;
	char m_closed;

	void set(int value);
	void apply(int value);
};

void Rva00841E10Owner::set(int value)
{
	if (!m_busy && !m_locked && !m_closed)
		apply(value);
}

struct Rva008427B0Owner
{
	char m_pad[0x37];
	char m_busy;
	char m_locked;
	char m_closed;

	void set(int value);
	void apply(int value);
};

void Rva008427B0Owner::set(int value)
{
	if (!m_busy && !m_locked && !m_closed)
		apply(value);
}

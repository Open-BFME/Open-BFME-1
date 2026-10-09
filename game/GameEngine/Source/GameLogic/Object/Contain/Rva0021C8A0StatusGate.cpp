// Address-derived reconstruction of retail RVA 0x0021C8A0.
// ContestableContain secondary vtable 0x010AB140 slot 0xAC.
// Same Object+0x94 status byte as Rva21C8E0ConditionalDispatch.

class Object
{
public:
	char gap[0x94];
	unsigned char status;
};

// The tail branch names ledger-owned ILT 0x0002B2D8. Its target,
// Rva00221960Owner::test, returns exactly 0 or 1 in AL and pops two pointers.
extern void j_0002b2d8();

class Rva0021C8A0StatusGate
{
public:
	bool check(Object *a, Object *b);
};

// ?check@Rva0021C8A0StatusGate@@QAE_NPAVObject@@0@Z
bool Rva0021C8A0StatusGate::check(Object *a, Object *b)
{
	Object *x = a;
	Object *y = b;

	if ((x->status & 0x10) != 0 && (y->status & 0x10) != 0)
		return false;
	union TailCall {
		void (*thunk)();
		bool (Rva0021C8A0StatusGate::*member)(Object *, Object *);
	} call;
	call.thunk = j_0002b2d8;
	return (this->*call.member)(x, y);
}

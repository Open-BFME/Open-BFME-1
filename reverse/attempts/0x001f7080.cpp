// ?apply@Rva001F7080@@QAEXPAX@Z
// partial score=0.95 date=2026-09-09
// Clean wrapper reproduces the full 23-byte body except VC7 allocates the
// field and incoming argument in the opposite registers.  Retail loads the
// field into EAX and the argument into EDX before calling the adjusted
// BfmeGateAMB receiver; the compiler chooses EDX and EAX respectively.

class BfmeKeyAMB;

class BfmeGateAMB
{
public:
	void bfmeAskAMB(void *value, const BfmeKeyAMB *key);
};

class Rva001F7080
{
public:
	void apply(void *argument);
};

void Rva001F7080::apply(void *argument)
{
	unsigned value = *(unsigned *)((char *)this - 0x1c);
	BfmeGateAMB *gate = *(BfmeGateAMB **)((char *)this - 0x20);
	gate = (BfmeGateAMB *)((char *)gate + 8);
	gate->bfmeAskAMB((void *)value, (const BfmeKeyAMB *)argument);
}

// ?update@Gen_009434E0@@QAEXPAX@Z
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Near-miss for 0x009434E0 (105B). Retail pushes ebx/ebp and reloads the two
// mapped indices into those registers between `test eax,eax` and `jl`. This
// shape is 109B, two callee-saved registers short, same control flow.

class Gen_009434E0
{
public:
	void update(void *obj);

private:
	void first(void *obj, int *a, int *b, int *c);
	void unlink(void *obj);
	void link(void *obj, int a, int b, int c);
};

void Gen_009434E0::update(void *obj)
{
	int i;
	int j;
	void *saved = obj;
	first(saved, (int *)&obj, &j, &i);
	int addr = *(int *)((char *)saved + 0x94);
	if (addr >= 0) {
		int packed = (((int)obj << 10) | j) << 10 | i;
		if (packed == addr)
			return;
		unlink(saved);
	}
	link(saved, i, j, (int)obj);
}

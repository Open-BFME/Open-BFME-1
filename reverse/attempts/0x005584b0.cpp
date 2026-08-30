// ?d_005584b0@@YAXXZ
// partial score=0.95 date=2026-08-30
// Clean reconstruction of the retail dispatcher at RVA 0x005584B0.

class BfmeK1058
{
public:
	void bfmeUse1058(int value);
};

extern BfmeK1058 *g_bfmeK1058;
extern void bfmeGet1058(int value, int *result);
extern int bfmeConv1058(int value, int argument);

class Rva005584B0Owner
{
public:
	char padding[0x6C];
	int value;
};

void __fastcall dispatch(Rva005584B0Owner *owner, int unused, int argument, ...)
{
	int result;
	bfmeGet1058(owner->value, &result);
	g_bfmeK1058->bfmeUse1058(bfmeConv1058(owner->value, argument));
}

// cl: /DNDEBUG /MD /EHsc

// 26-byte cdecl bridge at retail 0x009CD760: forwards its three stack
// dwords plus a literal zero to the matched __cdecl bfmeStepVOU at
// 0x009CD630. Retail reads [esp+4/8/0xC] as (edx,ecx,eax), pushes
// (eax,0,ecx,edx), calls, pops 0x10, returns bare. Address-derived opaque
// name keeps the address token.

void __cdecl bfmeStepVOU(void *a, void *b, int n, void *c);

// ?dup_009cd760@@YAXPAX00@Z
void __cdecl dup_009cd760(void *a, void *b, void *c)
{
	bfmeStepVOU(a, b, 0, c);
}

// ?bfmeReleaseYU@@YGXPAX00D@Z (identity unknown)
// partial score=0.95 date=2026-09-07
// 64/64, identical instruction count. Structure fully solved: __stdcall with
// four args, a stdcall 3-arg finder, `thing->vf100(flag == 0)` where the
// xor/sete pair is the int 0/1 conversion, then `if (--thing->m_ref == 0)
// thing->vf0();` -- the `dec dword ptr [esi+4]` is a direct pre-decrement of the
// member, no local needed.
// Residue is [[argument-shuttle-register]] preload depth:
//   retail  a3->eax, a2->edx, push esi, push eax, THEN `mov eax,[esp+0xc]` for
//           a1 (reusing eax after its push), push edx, push eax
//   MSVC    a3->eax, a2->ecx, a1->edx all preloaded, then three pushes
// plus the knock-on cl/dl and edx/eax naming. Per that note, hoisting arguments
// into locals is already ruled out for this shape -- do not re-sweep.
class BfmeThingYU
{
public:
	virtual void bfmeDestroyYU();
	virtual void bfmeT01YU();
	virtual void bfmeT02YU();
	virtual void bfmeT03YU();
	virtual void bfmeT04YU();
	virtual void bfmeT05YU();
	virtual void bfmeT06YU();
	virtual void bfmeT07YU();
	virtual void bfmeT08YU();
	virtual void bfmeT09YU();
	virtual void bfmeT10YU();
	virtual void bfmeT11YU();
	virtual void bfmeT12YU();
	virtual void bfmeT13YU();
	virtual void bfmeT14YU();
	virtual void bfmeT15YU();
	virtual void bfmeT16YU();
	virtual void bfmeT17YU();
	virtual void bfmeT18YU();
	virtual void bfmeT19YU();
	virtual void bfmeT20YU();
	virtual void bfmeT21YU();
	virtual void bfmeT22YU();
	virtual void bfmeT23YU();
	virtual void bfmeT24YU();
	virtual void bfmeT25YU();
	virtual void bfmeT26YU();
	virtual void bfmeT27YU();
	virtual void bfmeT28YU();
	virtual void bfmeT29YU();
	virtual void bfmeT30YU();
	virtual void bfmeT31YU();
	virtual void bfmeT32YU();
	virtual void bfmeT33YU();
	virtual void bfmeT34YU();
	virtual void bfmeT35YU();
	virtual void bfmeT36YU();
	virtual void bfmeT37YU();
	virtual void bfmeT38YU();
	virtual void bfmeT39YU();
	virtual void bfmeT40YU();
	virtual void bfmeT41YU();
	virtual void bfmeT42YU();
	virtual void bfmeT43YU();
	virtual void bfmeT44YU();
	virtual void bfmeT45YU();
	virtual void bfmeT46YU();
	virtual void bfmeT47YU();
	virtual void bfmeT48YU();
	virtual void bfmeT49YU();
	virtual void bfmeT50YU();
	virtual void bfmeT51YU();
	virtual void bfmeT52YU();
	virtual void bfmeT53YU();
	virtual void bfmeT54YU();
	virtual void bfmeT55YU();
	virtual void bfmeT56YU();
	virtual void bfmeT57YU();
	virtual void bfmeT58YU();
	virtual void bfmeT59YU();
	virtual void bfmeT60YU();
	virtual void bfmeT61YU();
	virtual void bfmeT62YU();
	virtual void bfmeT63YU();
	virtual void bfmeT64YU();
	virtual void bfmeT65YU();
	virtual void bfmeT66YU();
	virtual void bfmeT67YU();
	virtual void bfmeT68YU();
	virtual void bfmeT69YU();
	virtual void bfmeT70YU();
	virtual void bfmeT71YU();
	virtual void bfmeT72YU();
	virtual void bfmeT73YU();
	virtual void bfmeT74YU();
	virtual void bfmeT75YU();
	virtual void bfmeT76YU();
	virtual void bfmeT77YU();
	virtual void bfmeT78YU();
	virtual void bfmeT79YU();
	virtual void bfmeT80YU();
	virtual void bfmeT81YU();
	virtual void bfmeT82YU();
	virtual void bfmeT83YU();
	virtual void bfmeT84YU();
	virtual void bfmeT85YU();
	virtual void bfmeT86YU();
	virtual void bfmeT87YU();
	virtual void bfmeT88YU();
	virtual void bfmeT89YU();
	virtual void bfmeT90YU();
	virtual void bfmeT91YU();
	virtual void bfmeT92YU();
	virtual void bfmeT93YU();
	virtual void bfmeT94YU();
	virtual void bfmeT95YU();
	virtual void bfmeT96YU();
	virtual void bfmeT97YU();
	virtual void bfmeT98YU();
	virtual void bfmeT99YU();
	virtual void bfmeSetYU(int on);

	unsigned char m_bfmeHeadYU[4];
	int m_bfmeRefYU;
};

BfmeThingYU * __stdcall bfmeFindYU(void *a, void *b, void *c);

__forceinline void *reloadArg003C8030(void *volatile *value)
{
	return *value;
}

void __stdcall bfmeReleaseYU(void *a, void *b, void *c, char flag)
{
	BfmeThingYU *thing = bfmeFindYU(reloadArg003C8030(&a), b, c);

	if (thing == 0)
		return;

	thing->bfmeSetYU(flag == 0);

	if (--thing->m_bfmeRefYU == 0)
		thing->bfmeDestroyYU();
}

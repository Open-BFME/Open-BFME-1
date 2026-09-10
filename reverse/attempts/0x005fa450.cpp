// ?d_005fa450@@YAXXZ
// partial score=0.91 date=2026-09-10
// CORRECT SIZE (83/83). Grouping all three ground stores ahead of all three
// lifted stores is what makes MSVC push the trailing zero argument before the
// struct fills, so no store lands at [esp+0] with the short 3-byte encoding.
// The previous stash was the lifted-first variant at 82/83.
// Settled: __stdcall (x, y, z) with ret 0xc, two 12-byte {int,int,float} locals
// with the LIFTED one at esp+0 and the GROUND one at esp+0xc, the lifted z is
// (float)(z + <double at RVA 0x0107FD90>), the ground z is a raw 4-byte copy of
// the argument, and the call is thiscall virtual slot 11 on the view global at
// RVA 0x012F1600 taking (&ground, &lifted, 0xccaaffff, 0).
//
// REMAINING WALL: the two integer materializations are swapped in the prologue.
// Retail loads eax=x first, then fld z, ecx=y, fadd, and only then edx=z-bits.
// Ours hoists edx=z-bits above the fld and loads eax=x after the fadd. Every
// downstream difference is that swap plus its displacement shifts: 39 non-reloc
// bytes differ, down from 56.
//
// RULED OUT for the prologue swap (all leave the 39-byte diff untouched):
//  - all 240 statement orders of the six field stores that begin with an x store
//    (exhaustive brute force); the 82/83 split is decided purely by whether the
//    three ground stores precede the three lifted ones, nothing else moves.
//  - explicit locals for x, y, (z+K) and z defined in retail's materialization
//    order, and gz defined at every position among the lifted stores.
//  - chained assignment (lifted.m_x = ground.m_x = x) in both directions.
//  - flag sweep: /G5 /G6 /G7 /GB /Gd /Ot /Ox all identical to the default
//    /O2 /GR- /EHsc-; /O1 /Os /Oy- all regress the frame.
//  - a two-element array instead of two named structs; a static inline setPt
//    helper; a struct copy for the ground-to-lifted duplication (88 bytes).
//  - writing the ground z through *(unsigned int *)& to force an integer copy.
// The z-bits load and the argument push are coupled: any spelling that sinks
// the load lets eax be reused for it and sinks the push too (82 bytes), and any
// spelling that hoists the push hoists the load above the fld. Breaking that
// coupling is the whole remaining problem.
//
// Also ruled out (shape_search, masked score unchanged at 0.530): naming the
// colour/flag call arguments as locals in either order, casting them
// explicitly, and taking the struct addresses through named pointer locals
// instead of &ground/&lifted. The call site's spelling has no effect on the
// prologue swap; the wall is purely in how MSVC schedules the eax/edx
// materializations around the fld/fadd, not in how the call is written.
extern const double g_liftK;

struct Vec3ZT
{
	int m_x;
	int m_y;
	float m_z;
};

class ViewZT
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void drawLine(Vec3ZT *from, Vec3ZT *to, unsigned int colour, int flag);
};

extern ViewZT *TheViewZT;

void __stdcall Rva005FA450DrawLine(int x, int y, float z)
{
	Vec3ZT lifted;
	Vec3ZT ground;

	ground.m_x = x;
	ground.m_y = y;
	ground.m_z = z;

	lifted.m_x = x;
	lifted.m_y = y;
	lifted.m_z = (float)(z + g_liftK);

	TheViewZT->drawLine(&ground, &lifted, 0xccaaffff, 0);
}

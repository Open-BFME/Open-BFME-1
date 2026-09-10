// ?allow@Rva000F9170Owner@@QAEDPAVRva000F9170Holder@@D@Z
// partial score=0.95 date=2026-09-10
// 86/88 bytes, 24 non-relocation diff bytes (previous bank: 83/88, 33 diffs).
// Everything through +0x31 is byte-exact: the guards, the resolve call, the
// 0x1000 flag test, the block order and all three epilogues.
// Residue is the last 7 bytes of the strict path:
//   retail  mov eax,[glob]; mov eax,[eax+0b60h]; mov ecx,[esi+10h];
//           xor edx,edx; cmp ecx,eax; setl dl; mov al,dl
//   ours    mov eax,[glob]; mov ecx,[eax+0b60h]; mov edx,[esi+10h];
//           xor eax,eax; cmp ecx,edx; setg al
// Writing the compare as `limit > count` (not `count < limit`) is what fixed
// the operand order and produced the zero-extended int temp; that is the gain
// over the previous bank. What is left is a consistent eax->ecx->edx rotation
// plus the missing `mov al,dl`: retail's limit reuses eax, so the temp needs a
// third register, while MSVC reserves eax for the return and puts the limit in
// ecx.
// RULED OUT (all probed, none reaches 88 bytes):
//   `count < limit` in any spelling always loads the count first (83 or 89 B),
//   whether the limit is a local, a const local, an inlined getter on the
//   global struct, or an argument of an inlined comparison helper.
//   Inlined helpers `toChar(int)`, `pick(int)`, `keep(int)`, `lessThan(int,int)`
//   and `belowLimit(gd,count)` in both argument orders: 82, 86 or 89 B, never
//   the retail register assignment.
//   `? 1 : 0` on the comparison, an `int allowed` temp, an extra `int dummy`
//   copy, `!(count >= limit)`, and a zero-then-set `if` (91 B).
//   Return type `unsigned char` and `bool` both collapse back to the 82-byte
//   folded `cmp reg,[mem]` form.
class Rva000F9170Thing;

class Rva000F9170Inner
{
public:
	Rva000F9170Thing *resolve(void);
};

class Rva000F9170Thing
{
public:
	int m_spare;
	Rva000F9170Inner *m_inner;
	unsigned char m_gap[0xc0];
	int m_flags;
};

class Rva000F9170Holder
{
public:
	int m_spare;
	Rva000F9170Thing *m_thing;
};

struct Rva006C9270GlobalData
{
	unsigned char m_head[0xb60];
	int m_limit;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class Rva000F9170Owner
{
public:
	char allow(Rva000F9170Holder *holder, char strict);

	unsigned char m_head[0x10];
	int m_count;
};

char Rva000F9170Owner::allow(Rva000F9170Holder *holder, char strict)
{
	if (holder)
	{
		Rva000F9170Thing *thing = holder->m_thing;

		if (thing && thing->m_inner)
			thing = thing->m_inner->resolve();

		if ((thing->m_flags & 0x1000) == 0)
		{

			if (strict)
			{
				return (char)(TheWritableGlobalData->m_limit > m_count ? 1 : 0);
			}

			return 1;
		}
	}

	return 0;
}

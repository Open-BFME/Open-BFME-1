// ?apply@Rva00077ce0@@QAEXH@Z
// partial score=0.35 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// Open-BFME5: retail 0x00077CE0, 339 bytes. Real identity unproven -- landed
// under an address-derived name. Evidence and open questions in the ledger
// notes; see re_attempts.log / re_log for the working theory (a keyed
// modifier lookup that applies set/add/sub to a target int once, then marks
// a "processed" flag).
//
// The retail body calls each callee through the exact thunk retail used
// (e.g. ?j_00025739@@YAXXZ), but every such thunk is declared void(void) in
// the ledger even though it tail-jumps to a pointer-returning function
// (bfmeTreeYN/bfmeTreeYK). A C++ call through that declared signature cannot
// read the pointer retail leaves in eax, so the plumbing calls are issued in
// inline asm by decorated name, matching the exact push/call order and
// letting the compiler's inline assembler resolve local addresses.

void j_00025739(void);
void j_00017a9e(void);
void j_0002803d(void);
void j_0004275d(void);
void j_000155b9(void);
void j_0003e39c(void);
void j_00038811(void);
void j_00026fd5(void);
void j_0004a985(void);
void j_0003803c(void);
void j_00049918(void);

struct ModifierRecord
{
	char pad_00[0x18];
	int op;          // +0x18: 0 = set, 1 = add, 2 = sub
	char pad_1c[4];
	int value;       // +0x20
	int *dest;       // +0x24
	char pad_28[8];
	int processed;   // +0x30
};

// ?d_00077ce0@@YAXXZ (address-derived; real name/signature unproven)
class Rva00077ce0 { public: void apply(int key); };

void Rva00077ce0::apply(int key)
{
	void *range1first, *range1second;
	unsigned int sentinel1;
	void *range2first, *range2second;
	unsigned int sentinel2;
	ModifierRecord *rec;
	char found1, found2;

	__asm {
		push eax
		mov eax, 0CFCECDCCh
		mov eax, 0477CEFh
		mov eax, 0
		mov eax, 0
		mov eax, 0CFCECDCCh
		pop eax

		lea eax, key
		push eax
		lea ecx, range1first
		push ecx
		call j_00025739
		mov ecx, eax
		call j_00017a9e

		lea edx, sentinel1
		push edx
		call j_00025739
		mov ecx, eax
		call j_0002803d
		push eax
		lea ecx, range1first
		call j_0004275d
		movzx eax, al
		mov found1, al
	}

	if (!found1)
		return;

	__asm {
		lea ecx, key
		push ecx
		lea edx, range2first
		push edx
		call j_000155b9
		mov ecx, eax
		call j_0003e39c

		lea eax, sentinel2
		push eax
		call j_000155b9
		mov ecx, eax
		call j_00038811
		push eax
		lea ecx, range2first
		call j_00026fd5
		movzx ecx, al
		mov found2, cl
	}

	if (!found2)
		return;

	__asm {
		lea ecx, range2first
		call j_0004a985
		push eax
		lea ecx, range2second
		call j_0003803c
	}

	rec = static_cast<ModifierRecord *>(range2second);

	if (rec->processed == 0)
	{
		switch (rec->op)
		{
		case 0: *rec->dest = rec->value; break;
		case 1: *rec->dest += rec->value; break;
		case 2: *rec->dest -= rec->value; break;
		default: break;
		}
		rec->processed = 1;
	}
	else
	{
		char flag = 0;
		__asm {
			mov edx, key
			push edx
			lea ecx, flag
			call j_00049918
			push eax
		}
	}

	__asm {
		push eax
		mov eax, 0CFCECDCCh
		mov eax, 0477CEFh
		mov eax, 0
		mov eax, 0
		mov eax, 0CECDCCCBh
		pop eax
	}
}

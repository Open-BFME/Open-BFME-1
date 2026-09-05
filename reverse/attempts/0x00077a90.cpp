// ?grow@Rva00077a90@@QAEXPAUInputArg@@@Z
// partial score=0.1 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// Open-BFME5: retail 0x00077A90, 373 bytes. Real identity unproven -- landed
// under an address-derived name (partial only, banked). Evidence in
// re_attempts.log / re_log notes: this body walks a struct at [ebp+8] (an
// incoming pointer argument, fields read at +0, +4, +0x1c, +0x28, +0x2c),
// grows a pointer array with the retail array-new operator
// (0x00881F70, ??_U@YAPAXI@Z), stores into it, then makes several more calls
// through bfmeTreeYM()/bfmeTreeYN()-shaped singleton thunks
// (0x00025739 -> bfmeTreeYN, 0x000259aa -> FUN_00477930 = bfmeTreeYM,
// 0x0002576b -> FUN_00477510, a third tree singleton) before a final call
// chain (0x00037c22, 0x000053d0, 0x00023fe2) that looks like a hash bucket
// insert. Only a compiling skeleton with the entry/exit shape below was
// produced in this session; the interior is NOT yet a faithful port.

void j_00025739(void);
void j_00017a9e(void);
void j_0002803d(void);
void j_0004275d(void);
void j_00039c70(void);
void j_00014673(void);
void j_000155b9(void);
void j_00022cb9(void);
void j_00023fe2(void);
void j_000053d0(void);
void j_000259aa(void);
void j_0002576b(void);
void j_00037c22(void);
void *__cdecl operator_new_array_vec(unsigned int);

struct InputArg
{
	void *field0;   // +0x00: base pointer, dereferenced at [eax]
	void *field4;   // +0x04
	char pad8[0x14];
	int field1c;    // +0x1c
	char pad20[8];
	int field28;    // +0x28: element count, scaled by 4 for the array-new size
	void **field2c; // +0x2c: destination array pointer written back
};

// ?d_00077a90@@YAXXZ (address-derived; real name/signature unproven)
class Rva00077a90 { public: void grow(InputArg *arg); };

void Rva00077a90::grow(InputArg *arg)
{
	__asm {
		push eax
		mov eax, 0CFCECDCCh
		mov eax, 0477A9Fh
		mov eax, 0
		mov eax, 0
		mov eax, 0CFCECDCCh
		pop eax
	}

	void *base = arg->field0;
	(void)base;

	__asm {
		push eax
		mov eax, 0CFCECDCCh
		mov eax, 0477A9Fh
		mov eax, 0
		mov eax, 0
		mov eax, 0CECDCCCBh
		pop eax
	}
}

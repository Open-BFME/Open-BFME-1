// ?d_0086f740@@YAXXZ
// partial score=0.45 date=2026-08-27
// PARTIAL for ?d_0086f740@@YAXXZ @0x0086F740 size 116
// decoded via ndisasm + manual stack sim, t=12m model=muse-spark-1.2

// Raw bytes (116):
// 83 EC 0C 56 8B 74 24 18 83 7E 24 03 75 61 8B 46 20 8B 48 04 53 55 57 51 FF 15 84 93 35 01 ...
// Disasm (ndisasm -b 32 -o 0x0086F740):
// 83EC0C sub esp,0xc
// 56 push esi
// 8B742418 mov esi,[esp+0x18]  ; esi = arg2 (second stack arg)  [orig esp+8]
// 837E2403 cmp dword [esi+0x24],0x3
// 7561 jnz 0x86f7af
// 8B4620 mov eax,[esi+0x20]
// 8B4804 mov ecx,[eax+0x4]    ; ecx = *(esi->p+4)  string for atoi
// 53 push ebx ; 55 push ebp ; 57 push edi ; 51 push ecx ; FF1584933501 call [0x1359384] (atoi)
// 8B5620 mov edx,[esi+0x20]
// 8B6C2424 mov ebp,[esp+0x24]  ; ebp = arg1 [orig esp+4]  (first stack arg, owner with +0x814 list)
// 8B5A08 mov ebx,[edx+0x8]
// 8BF8 mov edi,eax            ; edi = atoi result
// ... then local struct at [esp+0x14] = {0,0} etc, lea ecx,[esp+0x14], push ecx, mov [esp+0x20],0, push 1, mov eax,ebp, mov [esp+0x1c],0x10, call 0x86BA70
// 8BF0 mov esi,eax ; 83C40C add esp,0xc ; 85F6 test esi,esi ; 7415 jz ; 55 push ebp ; 8D442414 lea eax,[esp+0x14] ; 897C2414 mov [esp+0x14],edi ; 895C2418 mov [esp+0x18],ebx ; E847C4FFFF call 0x86BBF0
// Callees:
//   IAT 0x01359384 -> atoi (MSVCR71, import slot, gen-import row ?ji_009f6dee@@YAXXZ)
//   0x0086BA70 (d_0086ba70, 157B)  E8 at 0x0086F789 disp -0x3D1E -> target 0x0086BA70  (rel32)
//   0x0086BBF0 (d_0086bbf0, 1224B) E8 at 0x0086F7A4 disp -0x3BB9 -> target 0x0086BBF0
// Helpers remain in Code/gen_asm/d_00868970.asm (147.5KB dump, 40+ FUNs). Do not edit that .asm.
//
// Struct guess (from offsets):
struct F740_IniBlock {
    char _00[0x20];          // +0x00..0x1F
    struct F740_Data* d;     // +0x20
    int type;                // +0x24  check ==3
};
struct F740_Data {
    char _00[4];
    const char* token;       // +0x04  for atoi
    char _08[4];
    int val08;               // +0x08  -> ebx
    // ... more fields used by helpers:.helpers read [esi+0x18],[esi+0x10],[esi+0x1C] etc (see 0086BBF0 switch on [esi] 0..0x10)
};

// Why c++ shape is tricky:
// - Placeholder name ?d_0086f740@@YAXXZ says void(void) but bytes read two stack args:
//     esi = [esp+0x18] => [orig+8] (arg2), ebp = [esp+0x24] after 4 pushes => [orig+4] (arg1)
//   So real signature is at least (void* owner, void* ini) or (INI* ini, void* owner) with owner at +0x814.
//   Any clean C++ must change name via add_match --replace-rva to expose args.
// - Helpers use register calling convention: BA70 expects this in EAX (mov esi,[eax+0x814] as first instr),
//   BBF0 expects this in ESI (mov ecx,[esi] as first instr). Normal cdecl would pass owner via stack,
//   not EAX/ESI. To match, caller must do `mov eax,ebp` / `mov esi,eax` explicitly. That is achieved
//   in C++ via `__asm mov eax,ebp` or by casting helper to `__fastcall`/`__thiscall` with register this,
//   but MSVC 7.1 only does ecx/edx for fastcall, not eax/esi. So a TU-scoped shim with `__asm` is required
//   as proven blocker: the dump's `mov eax,ebp` before E8 and `mov esi,eax` before second E8 are register
//   moves the optimizer would not normally emit for cdecl.
// - Local struct at [esp+0x14] is {0,0,0} then patched to {0x10,0,0} at [esp+0x1c] after pushes. In C++ this is
//   `struct Local {int a; int b; int c; int d; } local = {0,0,0,0}; local.a = 0x10;` folded.

#include <cstdlib>

struct F740_Owner {
    unsigned char _00[0x814];
    void* listHead; // +0x814
};

extern "C" void* __cdecl d_0086ba70(); // real proto: void* owner_in_eax, int count, void* localPtr
extern "C" void __cdecl d_0086bbf0(); // real proto: void* result_in_esi, void* owner_on_stack, int edi, int ebx

// Draft that compiles but does NOT yet byte-match (ret mismatch, prologue uses ebp frame):
// Kept as stash to give next converter the callee pins, offsets, and globals.
void d_0086f740_draft(void* owner, void* ini) {
    auto* blk = (F740_IniBlock*)ini;
    if (blk->type != 3)
        return;
    const char* tok = blk->d->token;
    int v = atoi(tok); // -> FF15 84 93 35 01
    int ebx = blk->d->val08;
    struct Local { int a; int b; int c; int d; } loc{};
    loc.a = 0x10;
    // Need to force: lea ecx,loc; push ecx; push 1; mov eax,owner; call 0x86BA70
    // and then if (res) { push owner; // lea eax,&loc2 where loc2={v,ebx} ; call 0x86BBF0 }
    // The second local is just two ints at [esp+0x14]/[esp+0x18] before call.
    // Without inline asm the compiler will use ebp frame and different esp offsets.
}

// Next steps for byte-match:
// 1. Change ledger name to something like ?parseRank_0086F740@@YAXPAVF740_Owner@@PAVF740_IniBlock@@@Z and repoint with
//    python3 tools/add_match.py '?parseRank_0086F740@@YAXPAVF740_Owner@@PAVF740_IniBlock@@@Z' 0x0086F740 116 Code/GameEngine/Source/GameLogic/Object/RankParse.cpp --replace-rva 0x0086F740
// 2. In that TU, declare helpers with correct register convention via tiny naked shims that just `jmp` to real addresses,
//    then call shims via normal C++ so the `mov eax,ebp` is inside shim, not caller, matching bytes differently.
// 3. Verify with ./build.sh '?parseRank_0086F740@@YAXPAVF740_Owner@@PAVF740_IniBlock@@@Z' and iterate on esp offsets (sub esp 0xC vs 8).


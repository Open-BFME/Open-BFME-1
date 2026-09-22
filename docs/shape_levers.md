# Shape levers: the checklist for "everything matches except..."

Run `python3 tools/probe.py <file.cpp> "<symbol>" 0x<RVA>` first: it compiles, diffs against retail with relocations masked, and prints the symptom row below with its lever.

Read this before banking a near-miss. Each lever below turned a 0.9+ partial into
a byte-exact landing on 2026-09-02. Each row states its own mechanism.

| Symptom in the byte diff | Lever |
|---|---|
| Two call arguments have the same stack address, but a repeated output pointer emits `mov` where retail uses a second `lea` | Decode the callee before treating both arguments as output pointers. At `0x00585CF0`, the four-argument helper is STLport `__find`: a pointer range, a value reference, and an empty iterator tag. Native `std::find` lets the empty tag share the value home and reproduces both address computations, landing 90 bytes on the first probe after the 88-byte fake-output model resisted repeated alias and flag changes. The independently decoded callee at `0x005853B0` is a four-element unrolled equality search, not a calculation with two outputs. |
| An empty three-word by-value temporary matches except retail clears EDX while the reconstruction clears ECX | Verify the callee receiver as well as its stack arguments. At `0x000BE410`, the bank modeled a stdcall free function and an opaque three-word value. Independent decoding of `0x000BE300` proved a thiscall resize taking an unsigned count and a native `ScienceVec` by value (`ret 16`); ECX must remain the receiver. The native member wrapper matched all 34 bytes on its first probe. The apparent zero-register residue was a wrong ABI, not evidence that the allocator needed forcing. |
| A complete grid scan is seven bytes short and keeps newly stored coordinates in registers instead of reloading the pair | Express the final pair comparison through an inline `operator!=(const ICoord2D &, const ICoord2D &)` rather than two scalar member comparisons. At 0x003D86E0 the complete scalar model was 471/478 bytes with 158 differing bytes; the coordinate operator reproduced all 478 bytes, including the prologue, induction variables, and final reloads. The result also held with the existing TerrainLogic header and its coordinate types. This is a measured source-shape lever, not evidence for an otherwise unproven class identity. |
| A ring scan nearly matches but manual stride counters and repeated guards change initialization, stack slots, and loop branches | Express the native induction: subtract `4 * delta + 2` from the budget, use two loops of `count = delta; count > 0; --count`, then two inclusive loops of `count = 0; count <= delta; ++count`, and advance `delta += 2`. VC7.1 derives the stride counter and the otherwise puzzling repeated sign guards. At 0x003F5340 this reproduced all 527 bytes; manually spelling the stride and guards had left 382 differing bytes. Recheck the algorithm first: this instance returns after the first ring with a successful closest-cell test. Do not introduce volatile counters to imitate the derived stores. |
| Allocating a record and then calling an initializer leaves a parser short, with a smaller frame and missing construction cleanup | Verify whether the initializer is really a constructor: its own stores/base calls, return-this ABI, and the caller’s allocation/unwind path must agree. Then use an actual `new T(args)` expression. At 0x000941D0, splitting allocation from initialization gave 216 bytes; declaring an address-derived constructor taking `const AsciiString&` and using `Register(ini, AsciiString(name), new T(name, value))` kept both string temporaries alive through registration and reproduced 233 bytes. A `void*` parameter suppressed the implicit string temporary and remained 221 bytes. The constructor is pinned at its independently decoded body 0x000947F0 (called through ILT 0x0003D30C); byte shape alone did not justify it. |
| A script seconds-to-counter arm calls `__ftol2` or changes its frame under `/QIfist`, while retail stores a float then reloads it with `fld; fistp` | Preserve the named float temporary after imported `bfmeMathVE(double)` and use the two-instruction `fast_float2long_round` helper in `ScriptEngineExecuteActions.cpp`. This is a proven x87 codegen blocker, not permission to lift a body. At 0x00346560 it landed the 1118-byte dispatcher. The 1632-byte COFF section also contains alignment and jump tables: all 36 pointer entries and the remaining tail bytes were independently compared with retail; the ledger claims only the executable body. Derive switch case values from the retail tables (373/374/375 here), not a neighbouring game’s enum. |
| Body five bytes short: retail materialises a boolean with `test <mem>,<reg>` / `setne al` / `test al,al` / `je`, ours branches straight off the first `test` | The boolean is a variable ASSIGNED INSIDE A GUARD and tested after the merge, not a condition. Declare `Bool hit = 0;` before the guard, assign it in the guard (`if (bit != -1) hit = flags->test(bit);`) and test it after. MSVC 7.1 folds `setcc` into the branch whenever the byte's only consumer is that branch, so no spelling of a single `if` reaches retail's shape: an inline accessor returning `Bool`, a second accessor wrapping it, a two-return `if (x) return 1; return 0;` body, a masked-int accessor narrowed by the caller, the mask written on the left, a named `Bool` local in the same scope, one declared in the enclosing scope, a `static` helper folding the -1 check in, and the /DWIN32 /O2 /Ob1 /GX /Gy /Ot /Op flag sweep all leave the five bytes missing. The dead-path merge is what gives the byte a second reaching definition and forces it into a register. Landed the 141-byte Lua status binding at 0x002E7740 on 2026-09-22, which was otherwise exact. |
| `!call()` on a one-byte return: ours `neg al; sbb al,al; inc al`, retail `test al,al; sete al` | Land the call result in an `unsigned char` local first, then negate the local. MSVC 7.1 negates a call result branchlessly and negates a named one-byte local with `setcc`. Landed 0x0055DCB0 (756 B) on 2026-09-16 after a bool parameter, a bool return, `== 0`, `== false`, a ternary, an inline accessor and the /G5 /G6 /G7 /O1 /Os /Og /GB flag sweep all left the six-byte sequence. |
| A constructor is short by the width of the stores a base writes and the derived class immediately overwrites | The optimiser drops a plain store it can see overwritten. Write only the BASE pair through a volatile cast (`*(volatile unsigned *)&m_v4 = ...`) and leave the derived stores plain. Marking the members themselves volatile also keeps the stores, but then the zero constant cannot be materialised ahead of them and `xor ebx,ebx` lands three instructions late. Landed 0x007F7FA0 (228 B) on 2026-09-16. |
| One ModRM/SIB byte: ours `[edi+edx]`, retail `[edx+edi]` | Add the pointer as an INTEGER on the right of the counter: `*(const char *)(i + (unsigned int)p)`. `p[i]`, `*(p+i)`, `i[p]` all give the other order. |
| `mov ecx,esp` before `mov [esp+N],esp` (EH saved-esp) at a by-value string arg | The string class must be `class AsciiString : private StringBase<char>` with INLINE forwarding copy ctor/dtor to the base; use `reference/shims/stringinline/StringInline.h`. Out-of-line ctor/dtor on the string class itself transposes it on every flag. |
| Scoped parser constructor remains 142/144 bytes versus retail 146, with the saved-`this` slot or EH state wrong despite matching registration calls | Model the receiver's real 12-byte registration base and put the temporary in its initializer: `: BfmeParserRegistrationVE(table, (AsciiString *)&AsciiString("chunk"), label ? label : &AsciiString::TheEmptyString)`. Use the existing `stringbaseascii/Common/AsciiString.h` shim; do not add a second string-base destructor or manually destroy a named local. The temporary ends after base initialization, before derived context/vptr stores. Matched witnesses: `Rva00450460ParserRegistrationCtor.cpp` (146 B), `Rva00352AB0ParserRegistrationCtor.cpp` (153 B with two extra fields), and `Rva0074A680ParserRegistrationCtor.cpp` (139 B with no extra field). Derive each literal, vptr and argument count independently; `registerParser` returns `UserParser*`, not `void*` or `void`. This is a receiver-initialization lifetime issue, distinct from the by-value string-argument row above. |
| Whole body one callee-saved register apart (esi/edi, esi/edx) | Register assignment follows local DEFINITION ORDER. Define locals in the order retail first materializes each value (`const T *q = s2; const T *p = s1;`). |
| A pure volatile-register mirror (eax/edx swapped everywhere) that NO spelling flips, in a body claimed under an address-derived name | Before blaming the allocator, check the placeholder ABI: read what retail leaves in EAX at EVERY exit (including early-out paths). If one value consistently reaches EAX at `ret`, the function RETURNS it and the placeholder's `void` return is wrong — EAX is reserved for the return value, so no void-typed source can ever claim it for that value. Correcting the mangled name's return type made 0x00133F50 (a 53 B `uninitialized_copy`-style copier whose advancing destination exits in EAX) byte-exact on the FIRST probe after the void-typed form had been banked as unreachable, and it retired that body's naked-asm lift. Retract the old row in its own commit, land under the corrected name, and update any `gen-alias` rows whose `object-symbol=` names the old spelling. |
| Loads retail hoists above a guard (`test ecx,ecx; mov esi,[a]; mov edx,[b]; jle`) | Copy the parameters into locals AFTER the preceding computation and BEFORE the `if`. Inside the guard they sink; at the top they change the prologue. |
| Import called twice: retail `mov edi,[__imp_X]; call edi ... call edi` | Call the real `__declspec(dllimport)` function directly. MSVC CSEs the IAT load into a callee-saved register allocated after existing locals; a pointer global or a cached local allocates first and mirrors ESI/EDI (and flips the vtable temp eax/edx nearby). |
| `flag = 1` reached by two forward jumps, placed after the main path | One fall-through tail: `if (a) { ... if (b) { ...; return; } } flag = 1;` -- never two inline `{ flag = 1; return; }`. |
| PMF constants `{pfn, -100, 0}` and a `[obj+0x68]` vbtable walk | `reference/shims/objectdlink/ObjectDlinkPmf.h`: Object's vbptr is inherited from a base at +0x68 (vbtable[0]==0), DLINK base at +4; pass the PMF as a value. |
| Two parameter loads swapped: retail `mov eax,[esp+8]` (arg2) before `mov edx,[esp+4]` (arg1), body otherwise exact | The allocator claims registers in the order values are first MATERIALIZED, and a field address counts before a field load. Take the address of a field of the later-used pointer into a local before the first expression: `const float *tp = &other->m_x;` then use `tp[0]`, `tp[1]`. It folds into the addressing mode, so only the load order changes. Landed 0x001E24F0 (78 B) on 2026-09-04 after 25 min of local-definition-order and reference-parameter variants had failed. |
| One displacement byte in `mov [esp+N],esp` (the EH saved-esp of a by-value temporary): retail N points at a LATER incoming-argument slot than ours | With no frame locals MSVC parks that saved-esp in a dead argument slot, choosing the first argument that is dead when the temporary is built. Reference the earlier argument in every expression that needs it (`(T *)b - 1` three times) instead of copying it to a local once: its slot stays live past the temporary and the allocator moves on to the next dead slot. Landed 0x002EADF0 (47 B) on 2026-09-04; class-size, typing and copy-order variants all left the byte alone. |
| A two-byte vector load temporary uses the version local's slot; separating it grows the frame by four bytes instead of reusing an incoming argument slot | Keep the version in its existing four-byte union, and declare a separate `union { Element value; unsigned char padding[4]; }` inside the load branch. At `0x003C2830` this preserves the 12-byte frame while placing the count and element in the two dead argument homes; a plain two-byte element local grew the frame to 16 bytes. Landed the 326-byte `Rva003C2830XferMissionObjectiveStateVector.cpp` after six stack-displacement differences. The matched Xfer siblings ruled out a virtual-call ABI change; do not change callee declarations to force this frame. |
| Frame the right size, but a contiguous run of locals sits on each other's slots, and reordering the declarations changes nothing | Retail holds one more object than your source, packed onto a user local that is already dead. Find the in-place update that should have produced a value and write it as an expression: `offset = offset * r * 0.5f` instead of `offset *= r; offset *= 0.5f;`. See "A run of locals on the wrong slots" below. Took `0x002C8A20` (1154 B) from 58 differing bytes to exact on 2026-09-15. |
| Frame larger than ours by the size of a small struct (`sub esp,0xC` vs `sub esp,8`), spill slots otherwise identical, no extra stores | Retail kept an aggregate local whose stores were forwarded away but whose frame space stayed. Declare `float v[3]` (or the struct) and fill it from the calls, then build the return value from `v[0..2]`: the array gets the frame, the loads are forwarded, and the body is otherwise unchanged. A `volatile` or an address-taken scalar does NOT do it. Landed 0x005F9DE0 (65 B) on 2026-09-04. |
| A temporary's or RAII local's destructor call (string releaseBuffer, Release_Ref reload-and-branch) sits LATER in ours than in retail, e.g. after a `return expr;` copy-construct or at the end of the enclosing block | The destructor fires at the end of the object's OWN scope. Wrap the local in its own nested `{ }` block ending where retail's destructor call sits; the rest of the body is unchanged. Landed 0x0010D940 (326 B, 137-byte diff -> exact) and 0x0071B1F0 (384 B) on 2026-09-05. |
| Identical-looking return tails NOT merged (an extra `call` + epilogue per `return f(v).first;` site, body ~30 B long, one relocation more than retail), and a pointer loaded before an out-of-line comparator/functor call is RELOADED from memory after it | The callee is opaque: MSVC 7.1 assumes a declared-only function may write the object it gets a pointer into, so it reloads and cannot cross-jump the tails. Give the callee a VISIBLE body and `__declspec(noinline)` (`__declspec(noinline) bool operator()(const K &a, const K &b) const { return a.m_bits < b.m_bits; }`): the call stays out of line (still a REL32 to pin) but the compiler now knows it has no side effects. Landed the two 629 B SparseMatchFinder MatchMap hinted insert_unique bodies 0x001429C0 / 0x001426A0 on 2026-09-05 after key size, const-ness, ctor/dtor triviality, allocator and include-order experiments all left the body at 661 B. |
| An EH state store (`mov byte ptr [esp+N],K`) appears in ours around a call that retail makes with NO state change (typically a by-value string temporary passed to a lookup: retail goes ctor, call, dtor with no state bytes between) | Retail knew that callee cannot throw. Declare it `throw()` (`PreferenceNode *find(const AsciiString &) const throw();`): MSVC 7.1 then elides the unwind state for the temporary across that call. Landed the three 377 B getPreferredMap bodies 0x0009E470 / 0x00086A20 / 0x0009E830 on 2026-09-05 (together with the StringInline shape for the by-value temporary and the ZH `isValidMap(ret, TRUE)` tail). |
| Split epilogue with `xor eax,eax` vs a folded one | `return new X;` splits; `new X;` as a statement folds. |
| A hand-declared STL list matches except for `fs:[0]` restoration versus `pop ebx` | Try the actual STLport `<list>` implementation before declaring a compiler wall. At `0x001F5500`, native list plus the witnessed out-of-line `_Construct<BridgeFXInfo, BridgeFXInfo>` call matched all 231 bytes; the canonical `BridgeFXInfo` member layout also matched. At `0x0043A3B0`, native list removed the same epilogue mismatch but left two source-register bytes. Do not inline the element-construction call when retail's separate callee is independently proven. |
| A trivially-copyable class arg gets built as a local + pushed copy | Give the class a declared copy ctor/dtor (non-trivial) so it is constructed in place. |
| A call to a C runtime function comes out as `call rel32` where retail has `call dword ptr [__imp__name]` | The translation unit is compiling against the static C runtime. Retail links the C runtime as a DLL, so every call reaches it through an import pointer. Give the source a `// cl:` line carrying `/MD`. Add `/D_STLP_USE_STATIC_LIB` to that line when the file is an STLport one, or `vendor/stlport/stl/_ios.h` fails with an explicit-specialization error. A `Code/stlport/*.cpp` file with no `// cl:` line gets no `/MD` at all. That is what kept `__write_formatted_time` at 0x00846320 compiling 172 bytes long over its seven `sprintf` calls until 2026-09-16. |
| Retail sets up an inline `rep stosd` as `lea edi,<dest>` then `mov ecx,<count>` then `xor eax,eax`, and ours emits those three in the order `mov ecx`, `xor eax`, `lea edi` | Clear the array with the upstream `for` loop over its elements instead of calling `memset`. MSVC 7.1 recognizes the loop and emits the destination address first. `memset` emits it last, whether the destination is the array expression or a pointer local. The loop removed 48 of the 54 differing bytes in `DX8Caps::Vendor_Specific_Hacks` at 0x0091BE00 on 2026-09-16, over its four render-to-texture clears. |
| A body compiled `/Od` matches up to an `__asm` block and then every instruction after it picks the next temp register along (`mov edx,[ebp+8]` where retail has `mov eax,[ebp+8]`), often one byte short overall | Delete the `__asm` block and write the same thing in C. Under `/Od` MSVC hands each statement its temp registers in a rotation, and an `__asm` block takes a turn the C statement it replaced would not have taken, so the whole tail shifts by one register. Two blocks in `_Rva0080ADE0` at 0x0080ADE0 (542 B) hid this: the first only called a cdecl function pointer out of a table, the second only stored 0 and 1 into two fields. Replacing the call block moved the first divergence from +0x60 to +0x8a, and replacing the store block too made all 542 bytes exact on 2026-09-16. Read the block before you assume it needs assembly: neither of those two touched anything C cannot say. |
| Every EH state constant in a constructor is one lower than retail, the final state store lands well before retail puts it, and the body is otherwise instruction-identical | Run `python3 tools/eh_info.py <rva>` and count the states against your tracked members. A state whose cleanup funclet adds nothing to `this` before it jumps destroys the BASE subobject, so the base class needs a destructor. Declaring one is enough, and an empty inline `virtual ~Base() {}` links with no pin. On `??0StealthUpdateModuleData@@QAE@XZ` at 0x0012A3A0 (372 B) retail's map has eight states where the build had seven, the missing one being state 0 at this+0 jumping to 0x00122D40. Adding the base destructor took the body from 43 differing bytes to exact on 2026-09-16. |
| A member is cleared twice, once where it is built and once from the constructor body, and retail computes `lea <callee-saved>,[this+N]` once and stores through a copy in ECX where ours folds both runs onto `[this+N]` and saves one register fewer | Clear the member with one `memset` over an array instead of assigning its fields one at a time. Three plain field assignments let MSVC fold the address into every store and drop the register save. The memset makes it materialise the address once, keep it in a callee-saved register across the function, and copy it into ECX for the first run. Field assignments, an out-of-class constructor definition, a three-iteration `for` loop, a `clear()` returning a reference, volatile fields and a nested struct assigned by value all left the folded form. This is the opposite direction from the `rep stosd` row above, which needs the loop and not the memset, so read which register retail spends before choosing. Landed as part of 0x0012A3A0 on 2026-09-16. |
| A constructor that only writes constants has every store and both `rep stosd` runs right, but MSVC reorders the stores among themselves and slides the `push esi` / `push edi` saves in between them | Mark EVERY scalar member volatile, not the two or three the first divergence points at. A half-volatile class still lets MSVC sink a late store below the ones after it, and the store that moves is rarely the one the diff names first. Then put one `_ReadWriteBarrier()` between the last store before the first array clear and the pointer local that clear reads, which stops MSVC hoisting a register save over those stores. On `??0Rva009A45A0CollisionData@@QAE@XZ` at 0x009A45A0 (117 B) the two together took the diff from 67 bytes to 30 on 2026-09-16, where six earlier sessions had stalled at 67. Barriers at eight other positions, a doubled barrier, one reused pointer local, an inner scope, a member initializer list, and the /G5 /G6 /G7 /GB /Og /Oy /Oa /Ow /Op /Oi /Os /Ot /Gy /Gf /GF /Ob1 sweep all left the residue unchanged. |
| A constructor that clears two arrays puts a callee-saved register push in the middle of the leading stores, and computes the second array pointer ahead of the stores that precede it | Retail wrote each array and the scalars that sit right after it as one nested struct with an inline clear function. Give the struct the array plus the volatile members that follow it, and call the clear once per array. The inline region pins the register save next to the other pushes, and it holds the array pointer back until the stores ahead of it are done. On `??0Rva009A45A0CollisionData@@QAE@XZ` at 0x009A45A0 (117 B) this took the diff from 30 bytes to 7 on 2026-09-16, where the volatile and barrier lever above had stalled at 30. One `pop esi` lands two stores late and nothing else differs. Nine further source shapes and the /G5 /G6 /G7 /GB /Os /Ot /Oy- /Gy sweep all left that pop where it was. |
| A vtable slot holds a body whose argument count and `ret N` belong to a different overload of the name you expected, and two neighbouring slots look swapped | MSVC 7.1 writes an overload set into the vtable in REVERSE declaration order. `_STL::ctype<char>` in `vendor/stlport/stl/_ctype.h` declares do_toupper(char), do_tolower(char), do_toupper over a range and do_tolower over a range, and the retail vtable at VA 0x0112F254 runs range-toupper, char-toupper, range-tolower, char-tolower. Match each slot on its argument count and its stack cleanup before you name it. This named 0x008407D0 and 0x008407C0 on 2026-09-16. |
| An STLport facet body built from the vendored headers runs hundreds of bytes long because `equal`, `_M_getc` and `sbumpc` are inlined where retail calls them, and the frame carries one extra eight-byte local | Read `stl/_streambuf.h` under `#pragma auto_inline(off)` after including `stl/_ios_base.h` and `stl/_stdio_file.h` outside the pragma, so only the narrow streambuf loses automatic inlining. The wide streambuf comes from the primary template instead, so give its `sbumpc` a `__declspec(noinline)` explicit specialization and leave it to the link. Replace the vendored `istreambuf_iterator` behind `#define _STLP_INTERNAL_ISTREAMBUF_ITERATOR_H` with a model whose `equal` and `_M_getc` carry real bodies under `__declspec(noinline)`. A body-less declaration keeps the iterator address alive and costs the extra local, while the real body lets VC7.1 fold the returned iterator onto the incoming one. Retail also inlines `locale::~locale`, so complete the opaque `_Locale_impl` and define that destructor as the landed 0x00832170 body spells it. Whether `equal` is inlined varies per body, so read the retail call first: the num_get bool readers call it and the money_get long double reader inlines it. This landed 0x00838CE0 (704 B), 0x0083ABE0 (628 B) and 0x00837620 (325 B) on 2026-09-16. |
| Retail opens `push ebp`, `mov ebp,esp`, `and esp,0xfffffff8` and our build emits no frame pointer at all, so the body fails at offset zero | Two triggers for that prologue are measured under this toolchain, and the guess that it means a `double` or an `__int64` is wrong. A local declared `__declspec(align(8))` produces it. So does a loop of whole-object assignments out of a member array into a local array, which MSVC 7.1 collapses into one `rep movsd` and then aligns the destination frame for, as `GarrisonContain_redeployOccupants.cpp` shows at 0x0021F850. Direct tests rule out a `double` local, a `long double` local, an `__int64` local, a 1024-byte char array, an 800-byte struct array written field by field, a struct holding a `double`, a struct holding an `__int64`, an array of doubles, an eight-byte POD returned by value, and the flags `/arch:SSE2`, `/Op` and `/Zp16`. Read the retail body for a `rep movsd` first, because a body with one is the second case and a body without one needs a third trigger nobody has named. This was measured on 2026-09-16 against the money_put digits writers at 0x008379C0 and 0x00839850, which have no `rep movsd` and no x87 instruction, and it applies to the same open question on `LANAPI::update` at 0x006870F0. |
| Every instruction matches but the EH state constants are all one higher in retail than in ours | Read the retail unwind map instead of guessing which object is missing. The second dword the prologue pushes is the handler thunk, whose first instruction loads the FuncInfo address, and that record holds `maxState` and a pointer to an unwind map of `{toState, action}` pairs. Each action is an eleven-byte funclet that does one `lea ecx,[ebp-N]` and jumps to a destructor, so the map names every tracked object and its frame slot in order. On the wide money_put long double writer at 0x00836140 the map has three entries where our build has two, and the extra one destroys a one-byte object through an empty out-of-line body, which is the allocator temporary of the string constructor. VC7.1 drops both the call and the unwind entry for a destructor defined empty inside the class. A body-less explicit specialization restores the entry but adds a normal-path call. **Landed lever:** specialize `allocator<wchar_t>::~allocator()` with an intrinsic `_ReadWriteBarrier()` body (`extern "C"` declaration and `#pragma intrinsic`). This retains the allocator cleanup state without emitting a normal-path instruction; `MoneyPutWideLongDouble.cpp` now matches all 217 bytes. Preserve the vendor flags and the bank's noinline node deallocator. Apply this only when the retail unwind map independently proves the missing lifetime; never patch EH state literals. |
| "Owning class unidentified" | `python3 tools/vtable_lookup.py <vtable VA>` -- retail slot table, ledger names per slot, and the ctors/dtors that install it. If only the body RVA is known, use `--target 0x<RVA>` to find candidate table heads through bounded slots and retail thunks; verify the installing constructor and caller ABI before assigning a name. |
| Callee "unpinned" in an old stash | Look it up again -- `reverse/zh_sweep/requeue_resolved_callees.csv` lists 72 bodies whose blockers have since been pinned. |
| Extra register saves or local copies around a non-inlined helper taking a local's address | Check the real helper's definition in the original TU. MSVC 7.1 uses knowledge that the helper does not retain the pointer even with `__declspec(noinline)`. `python3 tools/callee_visibility.py` reproduces this; [controls and limits](callee_visibility.md). Do not invent a non-retaining stub. |
| Two `if` arms test the same value against two constants, and ours folds the first arm's exit into the second arm's (`jmp <je>` where retail has its own `je`) | MSVC propagates the first constant into the second test, so the first arm's false edge skips the second compare and the two identical exits cross-jump. A `_ReadWriteBarrier()` between the two `if` statements stops both and emits no byte. Read the field into a local BEFORE the barrier, or the barrier forces a reload and adds a byte. Landed 0x008D20F0 (52 B) on 2026-09-11 after 8 phrasings and a flag sweep had left the fold. |
| A 12-bit bitfield store emits the MSVC insert (`shl; xor; and; xor`) where retail has `and <keep-mask>; or` | Retail knew the value fits the field, and a clamp written as an `if` does not tell MSVC that. Declare the word as a union of the bitfield struct and a plain `unsigned int`, read the count through the bitfield so retail `xor esi,esi; mov si,[p+6]; and esi,0xfff` survives, and write through the dword with an explicit keep-mask and shift. Took 0x008D6010 (163 B) from 52 differing bytes to 11 on 2026-09-11. |
| A member read that retail performs twice is served once, and the live pointer steals the register retail spends on the next value | MSVC keeps the first read alive across the guard chain. Qualify the member `volatile`, as `Rva008D2070AvailabilityScan.cpp` does for `m_owner`, or put a `_ReadWriteBarrier()` before the second read. Both restore the second load. Recovered the size and the register assignment of 0x008D6010 on 2026-09-11. |
| The SEH registration prologue is in the wrong order. Ours is `push -1`, `push <scopetable>`, `mov eax,fs:[0]`, `push eax`. Retail is `mov eax,fs:[0]`, `push -1`, `push <scopetable>`, `push eax` | One thing decides the order, whether the function allocates a frame slot. A function that emits `push ecx` or `sub esp,N` for a local or a compiler temporary reads `fs:[0]` third. A function that allocates none reads it first. So stop respelling the local as a temporary or a reference, and find what wants the slot instead. Usually it is the raw pointer MSVC parks for a `new` expression while the constructor may still throw. MSVC puts that pointer in a dead incoming-argument slot when one is free, and an argument is only dead once it has been read into a callee-saved register and never reloaded. Two probe functions that differ only in how many values stay live across the `new` print both forms side by side. The matched witness for the no-slot form is `?apply@SkirmishScreenState@@QAE_NPAXH@Z` (443 B) in `SkirmishScreenStateApply.cpp`, which pushes four callee-saved registers and allocates nothing. This replaces the guess in the project note seh-prologue-has-two-forms that a named local with a constructor picks the form. |
| Every instruction matches but the argument setup before a `p->f(...)` call on a global receiver uses the wrong registers. Retail holds one argument in ecx, pushes it, then reloads ecx with the receiver. Ours loads the receiver into ecx before the pushes and parks that argument in edx | Look at the guard chain above the call. A byte-sized equality test written as a term in the `&&` chain and the same test written as a one-case `switch` both emit `movzx eax,byte ptr [esp+N]`, `dec eax`, `jne`, so the bytes before the call are identical and the diff starts at the call setup. The switch is what frees eax for the first hoisted load, which pushes the second load into ecx, which makes MSVC sink the receiver load below the last push. Landed `?bfmeKey0052CDA0@BfmeA1021@@QAEHHHEE@Z` (99 B) after five sessions had banked the `&&` spelling at 0.97 with a 15-byte residue. The matched neighbour `?bfmeHandleAI@BfmeOwnAI@@QAEHPAXHEH@Z` at 0x005597B0 needs the same switch. |
| A float guard emits `fcomp; fnstsw ax; test ah,5; jp` where retail has `test ah,1; je`, or the other way round | Spell the comparison the way retail reads the status word. `a < b` tests C0 and C2 together, so it needs `test ah,5` and a parity jump to keep an unordered pair out of the true arm. `!(a >= b)` tests C0 alone and gives `test ah,1` with a plain `je`. The pair `test ah,0x41` with `jp` is what `a <= b` gives. Respelling the guard costs no bytes anywhere else. Took 0x0069AE40 from a wrong compare to a byte-exact one through +0x35 on 2026-09-15, and was one of the two changes that landed the 174 B ramp step at 0x0069ACE0. |
| Two return arms each build the same class from a different pointer, and ours pushes the string literal as an immediate where retail loads it into a register first, with one `push esi` before the branch where retail has one inside each arm | Move the choice of pointer into a `static` free function that returns it, and call that function inside the single `return Class(pick(...));`. MSVC 7.1 inlines the helper, gives its return value a register, and duplicates the construction into both arms with its own register save in each. Writing the same choice as two `return Class(...)` statements, as a local assigned in both arms, or as a ternary all fold the literal back into the push and hoist the save. This landed the 101 B room-type name accessor at 0x0069D240 on 2026-09-15 after a nine-shape search over loop and return spellings had left it two bytes short. |
| Retail keeps `this` in ECX across a call and never reloads it, and ours copies `this` into a callee-saved register | MSVC 7.1 treats ECX as surviving a `__thiscall` call whose receiver is the caller's own `this`, so a member that calls its own members keeps `this` in ECX and never reloads it. It makes no such assumption about a receiver it computed, such as `((Block *)(global + 0xb8 + i))->method(...)`, which it recomputes before every call. Read the retail call site and see whose object it passes. A receiver that is `this` reaches retail's shape as soon as the callee is declared a member of the same class. A computed receiver does not reach it at all, so bank the body rather than respell it, as 0x00699AF0 and 0x00699B90 had to be. Register pressure also beats the assumption. At 0x0069F3B0 the search loop claimed ECX for its candidate pointer and `this` spilled to EBX anyway. |
| Retail keeps two identical return tails, one reached by falling through a guard and one reached by a jump, and ours keeps only the first with the second arm jumping back into it | MSVC 7.1 cross-jumps identical tails. One barrier intrinsic is not enough, because the arm without it still jumps backwards into the arm with it. Put a DIFFERENT barrier intrinsic in each arm, `_WriteBarrier()` in the early return and `_ReadWriteBarrier()` in the late one. The same intrinsic in both arms merges the tails again, and `_ReadBarrier` costs five bytes. Neither `_WriteBarrier` nor `_ReadWriteBarrier` emits an instruction or a relocation. Took the second retail copy of STLport `basic_string<char>::find(char, size_type)` at 0x00653990 from 61 bytes to all 69 on 2026-09-15, after four sessions had banked it at 0.82 and ruled out condition polarity and `#pragma optimize`. A third site returning the same value picks whichever copy carries the SAME intrinsic it does, so tag it with that one to choose which copy retail jumps back into. That took `LinePassableStruct::linePassableCallback` at 0x003E5950 from 191 bytes to all 203 the same day, where retail keeps two copies of a twelve-byte `return 1` tail and a third site jumps back into the first. Order the arms so the copy retail falls through to is the fall-through in the source too, or the block layout still differs. |
| A shared `return x` block that retail places between the guard and the body, and ours sinks below the body (both guard branches point at the far copy and the second test comes out inverted) | Write the guard as two separate early-return statements instead of one `||` conjunction. With `if (a >= b || b - a < 1) return a;` MSVC 7.1 treats the merged return as cold and moves it past the body; with the two tests as two statements it leaves the block in source position, so the first test jumps to it and the second jumps over it. Landed the bounded string append `?rva68d730@@YAPADPAD00@Z` at 0x0068D730 (129 B) on 2026-09-16, where the conjunction left 48 differing bytes and the split guard was exact. This is the complement of the bounds-test section below, where four early returns had to become one conjunction: read the block ORDER in the diff to decide which way to go. |
| A local class with an array member: ours stores the vtable BEFORE the EH vector constructor arguments and stores it again at the head of the inlined destructor, retail stores it once just before the `??_L` call and starts the destructor at the `??_M` arguments | Delete the user-written constructor and destructor and let the class take the compiler-generated pair. A user-written empty pair pins the vtable store to the top of each body, which also gives the constant two uses in a loop and makes MSVC hoist it into `ebp`; the implicit pair sinks the store to just before the array constructor call and emits none at the head of the destructor. Modelling the base as a polymorphic MEMBER at +0 instead fixes the destructor but leaves the constructor store early, so the base has to stay a base. Landed the 225-byte record scan `?bfmeGo7530@BfmeOwnerBR@@QAEXPAUBfmeMaskYN@@0PAVObject@@@Z` at 0x002E7530 on 2026-09-16, where the written pair cost 14 bytes and the implicit pair was exact. |
| Two adjacent stores into neighbouring fields come out in source order, and writing them in retail's order changes the instruction selection: retail copies the value into a second register before both stores, ours consumes it in place after the first store | Declare the two fields as a nested struct and assign them as ONE struct value: `Pair updated = { p, (p != 0) ? -1 : 0 }; m_pair = updated;`. Building the struct makes MSVC materialize both halves before either store, and it then emits the stores in field order. A local for the second value, an inline two-field setter, a helper returning the pair by value and a `_ReadWriteBarrier()` all let the second value sink below the first store. This took the texture setter at 0x006EB000 (54 B) from a four-byte store transposition to six bytes that only swap eax and ecx on 2026-09-16; the body is in `reverse/attempt_history/0x006eb000/`. |
| An accumulator that retail keeps in a stack slot comes out in a callee-saved register for us, so our body saves one more register, allocates one fewer frame slot and runs short | Declare the accumulator in the scope ABOVE the branch that uses it and assign its first value inside the branch. A declaration inside the branch lets MSVC 7.1 enregister it. A declaration with an initialiser above the branch keeps it in memory but starts its live range too early, so it cannot share the slot the dead incoming argument left behind. The split form does both: the variable lands in that argument slot and the store stays where retail put it. On AptInGameChat::Send at 0x00514000 (778 B) the inner declaration cost EBX and 21 bytes, the initialised outer declaration left 38 bytes differing, and the split form was exact on 2026-09-16. |
| One displacement byte points at a different stack slot and no source change moves it | Add `/FAsc /Fa<path>.cod` to the `// cl:` line and read the `_name$ = N` table. A negative N is a frame slot and a POSITIVE N is an incoming argument slot that MSVC reused after that argument died, so the table names which object won the slot. Retail and our build often disagree about that, not about the frame. At 0x003C2830 retail puts the element count in the xfer argument slot and shares the vector argument slot between the `"std::vector"` string-pointer temporary and the two-byte element value; declaring that value as a local gives the local the xfer slot and pushes the count into the frame. At 0x0035F600 retail allocates three four-byte slots and our build merges two of them, which the banked `char m_pad[4]` on UnicodeString hides. |
| Retail materialises a repeated constant in a callee-saved register (`or esi,0xffffffff` then `push esi`) where ours pushes the literal every time | Count the constant's uses inside the arm. Retail reaches the register when the arm also writes the unwind state with it, and the arm only writes that state when it exits on its own `return` instead of falling into the shared tail. Adding `return;` at the end of the arm gave the constant its eighth use, and MSVC then held -1 in esi for six pushes, one `cmp mem,esi` and the state store. Six literal pushes alone never trigger it, and a probe body with twelve pushes still emitted `push -1`, so this is not a use-count threshold on the pushes. Took `?d_005625c0@@YAXXZ` at 0x005625C0 (2797 B) from 1156 differing bytes to twelve on 2026-09-16. |
| Retail allocates a local block four bytes larger than ours and one dword in it is dead, which `/FAsc` confirms because no instruction reads or writes it | Declare the local that sits next to the dead dword as a two-element int array and write only one element. Which element decides where the dead dword lands, so try both. At 0x005625C0 the sealed loop limit as `int limit[2]` with `limit[1]` carrying the value reproduced retail's 52-byte frame and put the dead dword at retail's offset. A volatile int nobody reads and a one-element array both vanish and leave the frame short, and widening a class by four bytes moves every other slot instead. |
| Ours reads a member as a plain int and compares it against a literal (`mov eax,[ecx+N]; cmp eax,-1`) where retail compares the member in place (`cmp dword ptr [ecx+N],esi`) | Give the member its real enum type and read it through an inline accessor that returns that enum. At 0x005625C0 modelling `m_staticLODLevel` as `StaticGameLODLevel` behind `getStaticLODLevel()` also fixed the register MSVC picked for the reload two instructions later. |
| Two arms test the same member against a threshold and share one tail block, and retail places the shared block after the else body while ours places it before | Write the condition so the branch retail takes is the one that reaches the shared block. Retail's `jg` to a shared `push esi` means the source reads `if (level <= 1) { disable } else { plain }`, and the greater-than spelling inverts both arms. Two Options checkbox arms at 0x005625C0 needed this. |

For the 408-byte wind update at `0x005FE480`, the whole native body already
matched except four EAX/EDX operand bytes loading its two float bounds.
Declaring the lower bound before the upper bound fixed all four, even though
the optimized instruction stream loads the upper bound first. Test the small
declaration-order change; do not infer source order solely from scheduled loads.

## Hard-lane choices generator

The recurring non-EH residues now have a bounded source-level front end:

```text
python3 tools/shape_family_levers.py BODY.cpp --families sib,register,bool,test,copy,store,loop,branch,constant,frame > choices.json
python3 tools/shape_search.py BODY.cpp "MANGLED" 0xRVA --size N --choices choices.json
```

`sib` reverses one independent integer addition, `register` swaps adjacent
independent local definitions, `bool` tries the documented call-result
`unsigned char` temporary before a negation, and `test` reverses operands in a
simple bit-test condition. `copy` inserts a typed pointer alias before one
following null guard or member load, probing whether the compiler should keep
the copy in a separate register. `store` swaps adjacent independent simple
field stores, probing retail store scheduling without reordering a dependency.
`loop` toggles a `while` header and an equivalent empty-init/increment `for`
header, and structures the narrow counted label/goto loop shape behind the
`jle`-guard/`jl`-latch versus one `jge` branch family. `branch` tries both a
folded boolean return and the polarity-inverted two-return form, probing
branch length and tail placement. `constant` materialises a literal boolean
or one-byte scalar return through a named temporary, including the
false/true EAX-versus-byte-register choice.
`frame` promotes a simple integer local to an indexed two-element array and
rewrites its uses, probing the dead-dword frame shape documented above.
Each edit is a hypothesis and `shape_search`
rejects assembly injection. The five hard-lane SIB bodies
(`0x0078D410`, `0x0078FDE0`, `0x0078FF40`, `0x007901F0`, and `0x005A0450`)
were re-probed with their first-divergence offsets; the compiler kept the
opposite base/index encoding, so these are recorded as an exhausted family,
not as a reason to add inline assembly. The two commutative TEST bodies at
`0x002D9F90` (+0x2f) and `0x002D9F30` (+0x34) likewise remained compiler-
canonical after the generated operand reversal; their body-level blocked
verdicts name that offset and the exhausted `test-operand-order` lever. The
copy-lifetime pair at `0x00347DA0` (+0x81) and `0x009F2AE0` (+0x12) also
remained non-exact after typed alias, cast, and volatile-alias alternatives;
the compiler still copy-propagated or selected the source register. Their
blocked evidence names the exhausted `copy-lifetime` choices. The
same distinction applies when a register, boolean, or TEST alternative
produces a new shape but not a masked exact match: bank the best source and
record the residue.

## Search-loop failure tails

At `0x007334B0` (161 bytes), embedding the state update inside the entry-search
loop merged retail's separate not-found and invalid-entry returns. Extracting
the search into a `__forceinline` pointer-returning member, then checking its
result and the entry fields with separate early returns, matches all 161 bytes.
An ordinary inline member was not inlined and produced a 120-byte caller;
forcing this real search operation inline recovered the full body. The witness
is `W3DTreeBufferRva007334B0.cpp`. No barrier, volatile access, or assembly is
needed. This is a source-structure lever, not proof that every duplicated tail
comes from a helper; verify each candidate independently.

The adjacent 444-byte force application at `0x007331F0` needed the same
inlined lookup and **separate** early returns for its two record guards.
Combining those guards with `||` still merged a ten-byte failure tail.
After splitting them, moving the second float multiplication before the
state stores recovered the remaining scheduling bytes. Its native matrix
identity/translation and typed FX calls then matched the complete body.

## Compiler-private ABI: compile the static helper with its caller

At `0x0072FCA0`, the track binder passed a render object in ESI, one bone
name in ECX, and another on the stack to `computeTrackSpacing`. An external
declaration could not reproduce this private convention; an old bank even
declared the helper with unrelated argument types. Copy the actual static
helper's source into the caller TU and use its real `RenderObjClass*` and
two string arguments. With the native render-object/math headers, VC7.1
reproduced both the 155-byte caller and the already-matched 201-byte helper,
including the register convention. Verify BOTH bodies: matching the caller's
relocation-masked call alone does not prove its helper ABI. This is ordinary
C++ compiler optimization, not a reason to add an assembly adapter.

The same-TU visibility lever also applies to a normal member call: at
`0x0072EEB0`, declaring `releaseTrack` externally made the caller save its
owner in EBP. Providing the actual 137-byte definition let VC7.1 observe that
the callee preserves ECX; the 263-byte caller then matched exactly. Check the
callee too, and do not substitute an empty or simplified stand-in just to
change register allocation. Witness: `TerrainTracksSystemUpdate.cpp`.

## Reload a member after a native aggregate update

At `0x00733000`, native `Vector3`, `Matrix3D`, and `SphereClass` operations
matched through the sphere-center scale, but caching the scale for both center
and radius emitted 393 bytes instead of 397. Retail consumes the cached x87
value for the center's Z component, then reloads the record's scale for radius.
Keep the local for `bounds.Center *= scale`, and use the member expression in
`bounds.Radius *= records[index].scale`. This reproduces all 397 bytes without
barriers, volatile, or assembly. Inspect the actual reload before applying this
lever; a cached local and a member access carry different aliasing information.

## Coordinate setters after matrix transforms

The 1,207-byte tree toppling update at `0x00733580` uses native
`Matrix3D::In_Place_Pre_Rotate_X/Y` and `Transform_Vector`. Copying the
transformed vector into a separate coordinate with three direct stores gave
1,215 bytes and an extra 12-byte stack temporary. Passing the vector through
a layout cast removed the temporary but gave 1,205 bytes: the X result was
stored before Y was calculated, unlike retail. Using the native
`Coord3D::set(x, y, z)` operation after the transform matched all 1,207 bytes
without the cast. The setter's arguments are computed before its field stores;
do not replace it with sequential stores merely because they look equivalent.
The witness is `W3DTreeBufferRva00733580.cpp`; the setter is defined in the
reference `Lib/BaseType.h`.

## Constructor cleanup evidence

Before changing constructor cleanup states, inspect the retail unwind map with
`python3 tools/eh_info.py 0x<RVA>`. It prints each state's predecessor and cleanup
instructions, resolving one ILT jump. It deliberately does not infer names or
callee boundaries. At `0x005FFBB0`, state 0 passes the original `this` to
`0x005E9B90`, whose two vptr stores cover offsets 0 and 4; state 1 adjusts `this`
by 8 before calling `0x005E9AA0`; state 2 destroys the stack handle. These are
evidence for an eight-byte composite base and a separate values base, not three
independent four-byte bases. Inspect the full cleanup target, including branches
after its first `ret`, before assigning its identity or boundary. The tool
accepts only the witnessed VC7.1 prologue/handler form and fails explicitly on
other forms. The supported registration-load-first variant begins with
`mov eax,fs:[0]` before `push -1; push handler`: `0x00732130` has one unwind
state whose cleanup calls `0x000FFCA0` on its local geometry object. This
distinguishes a scoped copy requiring cleanup from raw stack storage. Its
output is evidence for reconstruction, not byte-match proof.

## Filter construction: visible non-retaining constructors

`Rva002622D0Collect.cpp` (532 bytes) initially kept a six-word mask
temporary in separate stack storage: frame `0x84`, retail `0x6C`.
The real `PartitionFilterAcceptByKindOf` constructor copies both masks;
it does not retain either reference. Giving the TU its complete, independently
exact 102-byte constructor at `0x000C3DD0`, with `__declspec(noinline)`,
lets VC7.1 reuse the mask's storage for the relationship-filter temporary.
This is the same callee-visibility mechanism as the pathfinding lookup below,
not permission to invent a non-retaining stub or shorten a lifetime.

Native `BitFlags<192>` construction also matters. The immediate `0x40000`
belongs to the fourth word here: bit **114**, not bit 18. Derive the word
offset before assigning a semantic flag name. Temporary filters are destroyed
after iterator initialization and before iteration, as in the other filter
witnesses.

The caller's nested pointer-vector base exposed a second boundary: native
inlined node allocation emitted 130 bytes, whereas retail's 97-byte base at
`0x001D95B0` calls the 29-byte node allocator at `0x00061CE0` out of line.
A TU-local specialization of the scoped pointer allocator preserves the
zero-count check and element-size multiplication, but calls that real,
independently exact allocator through a noinline definition. This recovers
the base without changing the 532-byte caller. It is a local template
inlining decision, not a reason to change the shared allocator or pin a
130-byte emission to a 97-byte body.

The 898-byte LevelGrant action at `0x00260180` exposed the same issue for
object-status masks: use native `BitFlags<86>` (12 bytes), not a hand-written
three-word struct with chained zero assignments. Native temporary construction
removed an extra EBP lifetime. Its `0x20` store is in the second mask word,
so the absolute bit index is **37**, not 5. Two other semantic details were
necessary for the exact body: sequential, left-associated filter appends
(`a.link(&b)->link(&c)`), and the query position at the primary owner's
`this + 0xB0`, not at its nested Object pointer plus `0xB0`. Trace the receiver
reloads independently; matching field displacements do not identify the owner.

The 777-byte DominateEnemy action at `0x0025AEE0` confirms the distinction:
its 32-byte filter is two `BitFlags<86>` masks, not one `BitFlags<192>` mask
despite equal total storage. Identify the installed vtable before choosing
the mask type. Its template accessor needs an explicit null return before
following the override; the caller still dereferences that result, as retail
does. A signed-byte high-bit test `(value & 0x80) != 0` produces retail's `js`
where `value < 0` produces `jl`. Finally, its local-static key initializes from
`"TemporarilyDefectUpdate"`, not the enclosing class name: inspect string
relocations even after a masked probe says exact.

For the 806-byte GrabPassenger action at `0x0025F2D0`, finish the control-flow
inventory before changing compiler flags: retail has **three** nearest-object
queries, including the `0x2000` option path. Its two distance calculations need
different local shapes: interleave each terrain-point component copy with its
subtraction, but keep the object-position delta as a `Coord3D`. A whole-struct
copy followed by both calculations gives different x87 spill scheduling.
The final dispatch reloads Object through the secondary receiver rather than
reusing the earlier Object local. Preserve that reload and the observed
null-target branch; do not initialize or copy coordinates on a path where
retail does neither merely to make the reconstruction look safer.

The 250-byte Lightning emission velocity method at `0x005FB220` needs the
global, non-trivial `Coord3D` class and the emission interface's secondary
receiver at enclosing-object `+0x18`. A trivial namespaced return struct is
not the same ABI evidence even when its three floats fit. For the x87 body,
retain the upstream LINE algorithm's statement order: default-construct
`up`, assign its components `0.0, 0.0, 1.0` separately, perform the two native
static `crossProduct` calls, then assign each result component as
`perp.component * speed + up.component * radialSpeed` before returning the
named `Coord3D`. Value-constructor initialization and flattened scalar
reconstructions produced different x87 schedules. Independently verify the
referenced float constants and installed interface table, not just masked
bytes. This is a source-level lifetime and expression-order lever, not a
reason to insert floating-point assembly.

The Sphere emission-position body at `0x005FAA40` isolates a native copy
construction lever. `Coord3D result = *FillUnitVector(&randomPoint)` compiled
to 109 bytes and diverged at `+0x35`; spelling `Coord3D result; result =
*FillUnitVector(&randomPoint)` invokes implicit memberwise assignment and
compiled to the exact 117-byte retail body, including the three integer
loads/stores before the x87 multiplies. This is an ordinary `Coord3D` lifetime
choice; no volatility, barrier, or register forcing is involved.

## Nullable grid accessors: preserve the bounds helper

`Pathfinder::getLayer` at `0x003D93A0` landed at 105 bytes after retaining
an inline, nullable ground-cell lookup rather than flattening its four bounds
checks into the caller. The helper returns the row address plus `y * 16`
inside the valid extent and null otherwise; the caller checks that pointer
before reading packed layer bits 6..11 at cell offset `+0x0c`. The earlier
103-byte bank folded away retail's separate pointer `test` instruction.
The landed source uses ordinary, nonvolatile storage: removing an experimental
`volatile` qualifier still matched exactly, so volatility was not the lever.
This helper represents only the ground-map subset of the native layer-aware
cell accessor, not a newly discovered exported overload. Try the same source
structure on related bounds-and-cell near misses, but verify each body rather
than assuming the instruction will survive every inlining context.

## Model-condition bit masks: retain the native accessor layers

When retail materializes a constant mask in a register (`mov eax,mask;
test eax,ecx; or ecx,eax`) but a raw word expression emits an immediate OR
or a compare against the updated word, preserve the native accessor layers:
a small condition wrapper with inline `test/set/reset` forwarding to
`_STL::bitset<320>`, consumed by a free `__forceinline` conditional-update
helper that calls the real Object notifier. Calling bitset directly from an
Object member was not equivalent for VC7.1's code generation.

Verified witnesses are `Rva0025EF90ChargeApplication.cpp` (230 B),
`Rva0018E210TurretAngleConditions.cpp` (405 B), and
`TurretAI::friend_turnTowardsAngle` in `TurretAI.cpp` (274 B). The last went
from an 11-byte residual to exact with the accessor layers; direct bitset
calls still differed by 53 bytes. Its canonical-header integration also
needed BFME's callback slot `0x30`, not the reference header's `0x20`.

Keep the full field base and the bit index honest: Object's 40-byte array
starts at `+0x110`; accesses at `+0x114`, `+0x124`, and `+0x130` are interior
words, not new arrays. Derive names from the shipped enum table rather than
Zero Hour's different numbering. This lever does not validate a routine's
identity or excuse a changed lifetime or comparison.

Also check that the attempts log entry is not stale: `grep ,0xRVA, reverse/functions.csv`
-- if the row already points at a `.cpp`, someone landed it.

## Verified results from the Astra campaign (2026-09-04)

These are targeted hypotheses, not flags to apply to every translation unit.
Each landed through the ordinary relocation-aware byte and identity gates.

| Observed mismatch | Proven cause and bounded experiment |
|---|---|
| Two identical branch tails merge into one; body is seven bytes short | In `luaV_execute` (0x00997C80, 2924 B), an MSVC `_WriteBarrier` intrinsic inside one conditional-pop arm preserves both tails while emitting no instruction or relocation. `_ReadWriteBarrier` also worked; `_ReadBarrier` added five bytes. Document this as reconstruction shaping, not original source. The same experiment did not solve Weapon or road-junction register drift. |
| A large constructor lacks 16 frame bytes and several EH states | In the ParticleBuffer copy constructor (0x00989A20, 4714 B), four texture getters return owning one-pointer handles through hidden result slots. Legacy raw-pointer declarations hid their lifetimes. TU-local ABI shims, normal destructors, and the retail `else if` LOD clamp recovered the whole body. Check getter retain, setter handle-address consumption, cleanup release, and a matched caller before assigning identity. |
| Constant-2 register reuse spreads through a body with local statics | `ParticleBufferClass::Render_Line` (0x0098AD00, 1763 B) needed `/EHsc` instead of the build default `/EHsc-`. The default emitted extra EH states 0/2/4 around `atexit` registrations; that state 2 induced unrelated-looking EBX reuse. Retail omits those states. Correcting the exception model recovered the whole body without forced registers or barriers. |
| Final `rep movsd` setup has its source address and count loads swapped | In the terrain matrix helper (0x007DCF00, 281 B), put the final matrix assignment inside each branch after its last matrix multiplication. MSVC still merges the copy tails but emits retail's `lea esi` before `mov ecx,16`. Explicit intrinsic `memcpy` did not help. Independent relocation review also corrected the old bank's terrain-global name and reversed scale signs; masked equality alone hid both defects. |

## Additional verified family results (2026-09-04)

- Shader resource cleanup: an inline `int decrement(int *p) { return --*p; }`
  followed by a separate member zero test preserves retail's address materialization.
  Use the global object directly in the guarded `Release_Ref()` call; caching it
  in a local changes register allocation. This recovered shutdown (0x00717DA0,
  187 B), dependent-resource cleanup (0x00717C90, 218 B), and resource creation
  (0x00716770, 399 B). Counter wrapper classes and volatile fields were unnecessary.
  Identify the object independently: VA 0x012F9D1C holds a DX8 vertex buffer,
  proved by the matched constructor at 0x0091F2F0, despite an old bank calling it
  a texture. COM `Release` alone does not identify the resource subtype.
- Lua `codepushbool` (0x0099EF70, 151 B): `__assume(i != 0)` after instruction
  encoding preserves the encode/codelineinfo ordering without emitting bytes.
  The assumption is justified by the nonzero OP_PUSHBOOL opcode, not merely by
  the desired disassembly. Do not generalize it to opcodes that may encode zero.
- StreakLine construction: the real empty Vector3/Vector4 constructors retain
  null EH states that a POD declaration loses. Nonthrowing array deallocation
  also recovered the StreakLine and MaterialInfo destructors. Inspect the actual
  member constructors and deallocation contract before inventing guard objects.
- MaterialRemapper mesh mapping (0x0092F2C0, 493 B): retain each source owning
  texture handle as a loop local, while passing the remapped temporary to the
  setter. Nested getter/setter expressions give different cleanup lifetimes.
- Display clock wipe (0x006EBF20, 2319 B): restore the original parentheses in
  `start + (width / 2 * percent)` and equivalent height expressions. They constrain
  MSVC 7.1 x87 reassociation even when the algebra is otherwise equivalent.

These are verified source-shape examples, not claims that the reconstructed
spelling is the original EA source. Failed neighboring hypotheses remain banked.

## Solo viewport family results (2026-09-05 UTC)

- Viewport rendering at 0x00716AD0 (913 B): all instructions matched but 38
  stack-displacement bytes differed. Two separate display-dimension floats,
  instead of a `Coord2D` local or a two-element array, restore retail's stack
  placement. Constructor, assignment, inheritance, and declaration-order changes
  did not fix the aggregate version. The vertex-buffer layout and owning append
  lock came from independently matched creation and lock functions.
- The adjacent quad renderer at 0x00716F50 (532 B) reuses that model. Keep
  `inverse = 1.0f / size` and `halfTexel = inverse * 0.5f` as separate locals;
  a single expression lets MSVC fold the numerator, removing a retail FPU
  instruction. Populate each vertex's position, color, and UVs together. Both
  complete bodies passed the normal relocation-aware byte gate and have a
  matched highlight-filter caller. Neither needs new symbol pins or inline asm.

## Verify the deleting-destructor ABI before chasing frame layout

`Campaign::newMission` (RVA `0x005BC7C0`, 343 bytes) was banked as a
stack-layout near miss. The old shim emitted 337 bytes. Modeling the retail
null check and virtual deleting-destructor call (`push 1; call [edx]`) made
the complete body exact; explicit virtual destruction emitted flag zero.
Mission's retail vtable at VA `0x0110F658` leads through `0x0044534A` to
`0x009BBDF0`, whose flag-one path calls global delete at `0x00C81EB0`.
The Generals reference's get-pool / destroy / freeBlock implementation is
therefore not the lifetime model for this BFME caller. The accepted source
uses a TU-local lifetime view and emits no vtable. For another family, trace
its actual vtable and free path first; this is not a global pool-shim change.

## Fleet tools (all read-only except add_match/re_log)

| Need | Tool |
|---|---|
| Send a worker fresh, non-stale work with per-body context | `python3 tools/brief.py --dump <gen_asm file> \| --rvas ... \| --csv <worklist>` |
| Find banked bodies already landed, or whose blockers got resolved | `python3 tools/stale_partials.py [--stale] [--requeue out.csv]` |
| Find which one pin/model unlocks the most dump bodies | `python3 tools/dump_families.py [--show N]` |
| Whose function is this (vtable in the prologue) | `python3 tools/vtable_lookup.py <vtable VA>` |
| Compile, retail-diff, name the wall | `python3 tools/probe.py <cpp> "<symbol>" 0x<RVA>` |
| Per-site inline-ctor load order | Same `__forceinline` ctor inlined at N macro sites; retail loads the buffer pointer first at early sites but the terminator byte first at late sites (`mov cl,[m_NullChar]` before `mov edx,[esp+N]`), ours pointer-first everywhere (1 byte off: AL short form). | Add a tag-overloaded ctor variant reading the byte through `*(volatile char *)&m_NullChar` and use a second macro for the late sites only; the volatile read forces byte-first at those sites and leaves the others alone. Landed 0x00717E90 setShroudTex (2072 B) with the last 3 of 8 sites switched. |
| Static function with a private register convention | Retail body reads its argument from esi with no stack load and starts with `push ecx`; a standalone extern function compiles a normal prologue (twin landed inside its big ported TU, the copy did not). | Declare the function `static` and give it a TU-local caller (marked absent-from-retail); MSVC 7.1 then passes the argument in a register exactly as in the port. Landed WOLLobbyMenu and LanLobbyMenu shutdownComplete (0x004F98B0, 0x004CE910). |
| Store-before-load ordering via escaped address | Retail stores a static flag before loading through a pointer parameter; ours sinks the store next to the call. Volatile does not move it. | The flag's address escapes somewhere in the retail TU, so MSVC cannot prove the pointer does not alias it. Add an absent-from-retail helper returning `&flag`; the store then stays ahead of the pointer load. Landed 0x004CE910. |
| Twin inside a large ported file: copy the include block | Copying only the function and the obvious headers produced a wrong field offset (MeshClass::Model at 0x94 instead of 0xc8). | Header order defines the class layouts; copy the ported file's cl: line and its full #include block into the new TU. Landed 0x006F8720. |
| sret result addressed through eax | A helper returns a record by value (sret slot pushed first); retail then uses the returned eax as the record's address (`mov edi,eax; push edi; mov cl,[edi+4]`) and starts the record's EH state after the call, while a named local (or a reference bound to the result) makes MSVC re-derive the address with `lea [esp+N]` (+3 bytes). | Make the record a full-expression temporary consumed inside the next call: `insert(Record(helper(a, b)))` with a small adapter struct deriving from the pair type. Destruction order then matches retail too (pair first, record second). Landed 0x003476F0 setHumanImpassableArea (192 B). |
| STLport helper kept out of line (`_M_create_node`, `__destroy_aux`, `_M_fill_insert`...) or an extra try/catch region where retail inlines the node creation straight from `__node_alloc::_M_allocate` | Retail game TUs were built with STLport exceptions off per TU: `#define _STLP_NO_EXCEPTIONS 1` before the vendor `<map>`/`<vector>`/`<list>` (before `PreRTS.h` in port-style TUs, with `#include <map>` first so the default node allocator is kept). Landed the `_M_insert` family, hinted inserts (684, 1122, 629 B), vector twins, PSPlayerStats dtor. Second copies of a claimed name take an alias tag (empty comparator subclass / tagged element); `build/autopin.py` pins the callees. |
| Extra `mov [esp+N],-1` (EH state reset) after a vector-constructor iterator or array new, plus a loop-alignment `lea` NOP, 8-16 bytes long | Retail's TU saw `operator delete[]` declared `throw()`: with a nothrow array delete MSVC 7.1 has no reason to reset the EH state before the later `delete[]`. Declare `void __cdecl operator delete[](void *) throw();` before the includes (VectorClass<Vector2/3/4>::Resize, 480/515/550 B). |
| Twin of a port function blocked because adding a define to the port breaks its gen-funclet rows | The dump is a copy-paste twin in another retail TU: copy the whole port source into a new file, add the define, wrap everything after the includes in `namespace RvaXXXXXXXXTwin { }`, claim only the twin; autopin resolves its file-local statics and string literals (DIR32) to the retail copy's own (WOLWelcomeMenuUpdate twin 1164 B). |
| Body 4 bytes short: retail keeps `test edi,edi ... je` (the `delete` null test) after the next-link load; ours drops the test, or moving the store under an explicit `if` gives test/branch/store instead of retail's test/store/branch | VC7.1 folds the `delete n` null test once `n` itself has been dereferenced. Read the link through the FIELD, not the local: `e->m_list = e->m_list->m_next; delete n;`. Volatile reloads, a do-while, an explicit `if (n)`, and an inlined pop-front all still fold it (BfmeSecondZUnregister.cpp, 92 B). |
| Store-only body, every store right, but the incoming argument sits in the wrong scratch register (retail `mov edx,[esp+4]` then `mov eax,ecx`, ours `mov eax,ecx` then `mov ecx,[esp+4]`) | The allocator gives ecx to whichever value is first materialized after `this` is copied out. Move one constant store AHEAD of the argument store in the source: MSVC schedules the store anyway, but it claims ecx for the constant and pushes the argument into edx. Landed 0x001A1A40 (51 B) on 2026-09-16 after a ctor form, a reference return, a pointer return, /G5 /G6 /G7 /Ot /O1 /Os and eleven other store orders all left the two prefix instructions swapped. |
| Retail computes a count with a memory operand (`mov edx,[ecx+0x28]; sub edx,[ecx+0x24]`) and reloads the same field after the branch, while ours keeps that field in a callee-saved register and spends a `push esi` | MSVC common-subexpresses the member load across the branch because the guarded arm indexes through it. `_ReadWriteBarrier()` as the first statement of the guarded arm stops that: the count keeps its memory operand and the arm reloads. Took 0x00206100 from 64 bytes to all 61 on 2026-09-16. The same body also needs an out-pointer parameter rather than a twelve-byte return, or the allocator wants a fourth register, and an unsigned range compare, which is what makes `jae` instead of `jge`. |
| A float sum of three or four products comes out in the wrong order and no parenthesisation changes it | MSVC 7.1 canonicalises a float sum into ascending operand-address order and ignores the source tree, so parentheses buy nothing. Write the sum as a statement chain instead: `float s = c*z; s = s + b*y; s = s + a*x; result = s + d;`. That took 0x006E1BE0 from 44 differing bytes to 6 on 2026-09-16, where six parenthesisations, /Op, a by-value argument struct and array indexing had all produced the same ascending order. |
| Whole body the right size but two registers exchanged all the way through, with retail walking a chain in ecx and MSVC walking it in eax | Retail returns a small object BY VALUE through a hidden pointer, not through an out parameter. Give the returned class a copy constructor: MSVC returns a four- or twelve-byte class in registers until it has one, and the hidden pointer changes which register the allocator hands the chain. Landed 0x008951B0 (52 B) and 0x00206100 (61 B) on 2026-09-16, after local-definition order, arm order, barriers, out references and member-wise stores had all left the exchange alone. |
| Retail copies three floats with `fld`, `fld`, an integer move and an `fxch`, over a stack frame whose only surviving store is dead | The source copies the argument member by member into a local, not with a whole-struct assignment. A struct assignment gives three integer moves and no frame; the member-wise copy leaves the frame, forwards two members through the FPU and keeps the third store. Landed 0x001B49E0 (44 B) on 2026-09-16. |

| Every byte matches but this toolchain writes a `lea` or `mov edi,edi` nop ahead of a loop head and retail writes none, or retail writes one and this toolchain writes none | No source spelling and no flag moves it, so record the verdict and take another body. MSVC 7.1 pads a loop head onto a 16-byte boundary at `/O2` unconditionally. The sweep on `?doTeamForceEmotion@ScriptActions@@` at 0x002F75D0 (121 B, six-byte pad) tried /Os /O1 /Og- /Oy- /G5 /G6 /G7 /Gy- /Gd /Ob1 /Oi- /Gs- /GF- /Oa /Ow /Op /GX and /Zp1, and only the four that rewrite the whole body drop the pad. Putting another function ahead of this one in the file does not move it, with or without /Gy-, so the pad does not come from a location counter running across the text section. The same pad blocks `?giveUpgrade@Team@@` at 0x000ED9D0 by five bytes and 0x001A2D50 by six, while retail pads two bytes at 0x00107A50 where this toolchain pads none. All four functions start on a 16-byte boundary, so the two compilers disagree in both directions at the same offsets. |

## AI pathfinding: authentic lookup visibility

`AIUpdateInterface::doPathfind` (RVA `0x0027B3A0`, 2031 bytes) was six
non-relocation bytes short of an exact match: two independent loads after
`destroyPath` appeared in reverse order. Local ordering and volatile reads
did not recover it. The out-of-line `findObjectByID` declaration hid the real
BFME hash-map lookup, which differs from Zero Hour's later flat vector.
Giving the TU-local lookup view its authentic body with `__declspec(noinline)`
recovered the caller exactly and allowed the old volatile cast to be removed.
The visible helper independently matches all 82 bytes at `0x0009A510`, and all
69 claimed emissions in AIUpdate.cpp pass the normal gate. This is another
case where callee side-effect knowledge affects scheduling in its caller;
the helper must be real, not an invented pure stub.


The same mechanism recovered two more AI siblings from real source:

- `blockedBy` (`0x00274630`, 1052 B): the opaque
  `Thing::bfmeRelativeAngleTo` call kept address-taken coordinate locals in
  separate stack slots. Its authentic non-inlined definition lets VC7.1 prove
  the pointers are not retained, reducing the frame from 0x5C to retail 0x4C
  and restoring copy scheduling. The helper independently matches 214 B at
  `0x00150510`. Nontrivial Coord3D copying is also required; the helper's
  arithmetic-only delta stays a trivial three-float temporary.
- `setPathFromWaypoint` (`0x00270B40`, 398 B): an inline Coord3D copy constructor
  reduced the mismatch to one swapped load/store pair (seven bytes at +0x94).
  Local-order, memcpy, flag, and copy-expression variations did not fix it.
  Exposing real `Path::prependNode` with `__declspec(noinline)` and its real
  inline PathNode constructor recovered the caller exactly. The helper also
  independently matches its existing 104-byte body at `0x0026E4D0`.

For a remaining load/store swap or excess frame slots, inspect the actual
called helper's memory effects before attempting register-order variations.
Keep the authentic helper and verify its emission; a fabricated side-effect
stub would manufacture a compiler assumption rather than recover the program.

## GameSpy packets: preserve native accessor expressions

An inlined getter can affect VC7.1 register allocation even when its result is
the same member load. The BFME results packet at `0x006386F0` compiled to
1694 bytes with direct seed/quick-match field reads, against retail's 1684.
Restoring `getSeed()`, `isQuickMatch()` and `getQuickMatchType()` as ordinary
inline accessors recovered all 1684 bytes. The earlier bank had broad register
and stack-home drift, not merely ten isolated extra bytes. The complete source
is `GameSpy/GenerateGameSpyGameResultsPacket.cpp`.

The same source-level context helped the 1583-byte ladder packet at
`0x00639190`: native seed, ladder-port and quick-match getters restored the
register schedule. The final one-byte difference was a real extra leading
variadic argument at `+0x4AB`. That malformed retail call shifts the format's
values and can feed a small integer to `%s`; preserve and document it for byte
matching rather than silently correcting it. This body's previous 1580-byte
claim also omitted its final `ret 4`, proven at `+0x62C` before INT3 padding.

For `PlayerInfoMap::operator[]` at `0x006359C0`, STLport's old built-in
value-initialization workaround emitted an extra `__default_constructed`
call. Selecting direct `PlayerInfo()` construction locally before parsing
`<map>` recovered all 288 bytes and the register schedule. See
`GameSpy/PeerDefs_PlayerInfoMap_Subscript.cpp`; no vendored header was edited.

## Special-power containers: access expressions and lifetimes

At `0x0025C7C0` (266 B), caching a separate vector-entry pointer produced a
264-byte weighted-choice body with 179 non-relocation differences: VC7.1
hoisted the extent and changed the loop and register allocation. Keeping
`choices[i]` in the accumulation and string selection recovered the complete
body, including its extent reloads. The entries contain an owning AsciiString
and a float; accumulation truncates to an integer after each addition.
See `Rva0025C7C0ElvenWoodChoice.cpp` under Object/SpecialPower.

At `0x0025ED50` (355 B), the filter objects die at the end of the iterator's
initialization expression, **before** the enumeration loop. Named locals that
survive the loop change both lifetime and emitted cleanup. Genuine temporary
virtual filters, STLport's `_STLP_NO_EXCEPTIONS` configuration, and copying the
ObjectID to a local before `list::push_back` recovered the body. Passing a
reference to the Object's field instead changed the allocation/load schedule.
See `Rva0025ED50ChargeTargets.cpp`; it uses actual three-slot BFME filter
views and verified vtables, not hand-written vptr stores or dummy predicates.

## Read the member again instead of caching it in a local

Retail sometimes computes a sub-object address before it loads through that
address. The 156-byte body at `0x00615FE0` reads a pointer member at +4 as
`mov eax, [edi+8]`, `add eax, 4`, `mov eax, [eax]`. The obvious C++ spelling
compiles to the shorter `mov eax, [ecx+4]` and shifts the rest of the body by
two bytes. Five other spellings of the plain member load fold the same way:

- a cast through `char *`
- a cast through `unsigned int`
- an array member that decays to a pointer
- a second base class placed at offset 4
- a pointer local holding `&obj->member`

Caching the member in a local inside an inline accessor folds too. What splits
the address off is reading the member several times through one accessor and
letting VC7.1 common up the loads. This spelling reaches all 156 bytes:

```cpp
Overridable *getFinal() const
{
    if (m_override != 0 && m_override->m_nextOverride != 0)
        return (Overridable *)m_override->m_nextOverride->getFinalOverride();
    return m_override;
}
```

The matched `LivingWorldRegionManager::rva003C8A50` at `0x003C8A50` shows the
same shape from another angle. It passes `candidate->m_name` by const
reference into an inline `compare` that reads `that.m_data` twice.

## Write a bounds test as one conjunction, not four early returns

VC7.1 compiles `if (a < b) return fail;` to `test ah, 1` plus `jne`, and
`if (a > b) return fail;` to `test ah, 41h` plus `je`. Retail's 202-byte Apt
point-in-bounds test at `0x008C6730` uses `test ah, 1` with `jne` and
`test ah, 41h` with `jp` instead. The `jp` form also branches on an unordered
compare, which is the jump-if-false of `a <= b`, not the jump-if-true of
`a > b`. Writing the four tests as one conjunction produces exactly that:

```cpp
if (x >= bounds.left && x <= bounds.right
    && y >= bounds.top && y <= bounds.bottom)
    return AptInteger::Create(1);
return fallback;
```

The same edit also fixed which callee-saved register held the argument count
and moved the success block ahead of the failure block, so a residue that
looked like three separate problems was one.

## A frame four bytes too big: put the local in its own block

When every stack displacement in the body is exactly four higher than retail's
and nothing else differs, the frame carries one extra slot. The compiler will
say which one. Add `/FAsc /Fa<path>.cod` to the source's `// cl:` line, compile
once, and read the `_name$ = -NN` table at the top of the listing's function.
That table gives every local and every `$T` temporary its frame offset.

The 359-byte push button number draw at `0x00794B70` listed `_width$ = -48`
through `_size$ = -20`. It also gave `$T470` and `$T471` a slot of their own at
-32. Those two are the pointers MSVC keeps to each by-value `UnicodeString`
argument so the unwind funclet can destroy it. Retail allocated `0x20` of
locals where we allocated `0x24`. Declaring the two colours in their own block
moved `_textColor$` onto -32 beside the two temporaries, and the body went
exact:

```cpp
{
    Color textColor;
    Color dropColor;
    getButtonTextColors( window, instData, &textColor, &dropColor );
    ...
    text->draw( textX, textY, 1, 1 );
}
```

VC7.1 overlaps a compiler temporary with a user local only when the local's
scope says the two cannot both be live. A local declared at the top of the
function blocks the overlap even when nothing writes it until far below.
Moving the declaration down without a block does not help. `Color textColor;`
on the line above `getButtonTextColors` left the frame at `0x24`. So did
dropping `register`, reordering the six declarations, and deleting a dead
struct.

The listing catches the opposite mistake too. At `0x009C0A30` we merged the
`fild` temporary with a user integer on `[ebp-4]`. Retail kept the two apart on
-4 and -8, so every double below them sat eight bytes lower than ours.

## A run of locals on the wrong slots: retail had one more object

Read this when the frame is the right size, every local is the right size, and
a contiguous run of them still sits on each other's slots. The 1154-byte
`WorkerAIUpdate::findGoodBuildOrRepairPosition` at `0x002C8A20` spent four
sessions there. Ours listed `offset` at `esp+0x14`, `workingPosition` at
`0x20` and `theirPosition` at `0x2c`. Retail wants `workingPosition` at
`0x14`, `theirPosition` at `0x20` and `offset` at `0x2c`. The three slots
above them, `bestPosition` at `0x38`, `ourPosition` at `0x44` and the options
record at `0x50`, already agreed, and so did `sub esp,0x64`. All 58 remaining
bytes were displacement bytes.

Seven declaration orders failed, and the reason is that declaration order does
not decide this. Swapping two declarations reordered the code and left every
slot where it was. What decides it is how many objects the function holds. Add
`/FAsc /Fa<path>.cod` to the `// cl:` line and read the `_name$ = -NN` table,
then compare it against the slots the retail diff asks for. Count the objects
retail needs. Retail wrote the scaled vector to `0x44`, the slot its own
`ourPosition` occupied, and `ourPosition` is dead by then. That is a seventh
object packed onto a dead sixth, and our source only had six.

The source change that supplies the seventh object is one line. Ours scaled
the vector in place:

```cpp
offset *= targetRadius;
offset *= 0.5f;
```

Retail builds a new value instead, which MSVC materializes as a `$T`
temporary:

```cpp
offset = offset * targetRadius * 0.5f;
```

The listing then reads `$T666 = -68` beside `_offset$ = -68` and
`_halfOffset$ = -44` beside `_ourPosition$ = -44`, the whole run moves onto
retail's slots, and the body goes from 58 differing bytes to 24. The same one
line then closed the other 24 without another edit. It fixed the order of the
three squares in the inlined `Length2`, where ours summed `Z*Z` first because
`Z` sat in `st(0)`, and it fixed `fld offset.X; fadd workingPosition.x`, which
ours emitted the other way round because MSVC reads `a += b` and `a = b + a`
as the same thing and loads the destination. Neither of those is reachable by
respelling the statement that shows the residue.

So when a run of slots is rotated rather than swapped, do not respell the
declarations. Count the objects, find the in-place update that should have
produced a value, and write it as an expression.

## The two-register lea operand order is not a spelling

Four bodies sit at exactly one non-relocation byte, and in all four that byte
is the SIB of a `lea` that adds two registers. Retail writes `lea edi,
[eax+ecx]` at `0x0078D410+0x88`, `lea edi, [ecx+eax-6]` at `0x007901F0+0x9b`,
`lea edx, [ebx+ecx]` at `0x005A0450+0xde` and `lea edx, [edi+eax]` at
`0x0045C2F0+0x62`. Our build picks the same two registers every time and swaps
which one is the base.

Nothing in the C++ reaches it. On `0x005A0450` the addends were swapped, a
`__forceinline` helper was added and removed, the helper was moved onto the
sibling assignment, and the two assignments were reordered. On `0x0078D410`
twelve forms were tried, including an unsigned round trip, an assign-then-add
pair, a dead pre-store, an inline helper, and hoisting the locals to function
scope. Each one left the identical byte. `/G5`, `/G6` and `/GB` reproduce it
and `/G7` rewrites 116 bytes.

MSVC commutes the addition before it picks the base, so the source order of
the two operands never survives to the encoder. Within one body retail stays
consistent and our build does not. `0x005A0450` and `0x0078D410` each contain
two leas of the same shape, and in both we match the second and miss the first.
Bank the body and take another one. Do not spend a session on this byte.

## A constructor's store order comes from the initializer list

Retail constructors emit their stores in the order of the member-initializer
list, and the body's statements follow after. Writing every store as a body
statement gives MSVC one flat list to schedule, and it reorders freely. Moving
the same stores into the initializer list pins them.

An initializer list also changes how a bitfield clear compiles. A narrow bitfield initialized in the list
compiles to a register read-modify-write, `mov cl, [esi+0x20]` then `and cl,
0xf8` then the store back, while the same clear written in the body folds to a
single `and byte ptr [esi+0x20], 0xf8` and loses three bytes. Declaring the
flag word as `unsigned char m_bits : 3` and initializing it with `m_bits( 0 )`
is what produced retail's form at `0x004945E0` (72 B, landed 2026-09-16).

Do not reach for a barrier inside a constructor. `_WriteBarrier()` after a
member store does pin that store, and on `0x004945E0` it matched the first
sixteen bytes exactly. It also drags the implicit vptr store up to the barrier,
and retail writes the vptr after the member stores, so the body loses more
bytes than it gains.

## Recover the native lifetime before forcing constructor bookkeeping

At `0x005F3750` (227 B), a bank manually wrote three vtables and used
volatile storage. Native `ParticleModule005F2CA0` and `DefaultDrawModuleInfo`
bases reproduce the intermediate vtable and unwind-state transitions without
those writes. The complete body must also retain its global guard, construct
the local `AssetList` before resolving the system pointer, and insert the
asset name whether the system was already present or came from the null-system
accessor. Omitting these branches obscured the useful native shape.

Let the local's implicit destructor reach its native STLport tree destructor.
An external `AssetList::~AssetList` declaration gave the same instruction
shape but invented a callee identity: retail calls the tree destructor.
The native 124-byte destructor and its 53-byte recursive erase helper were
independently matched before adding their typed dependencies. The resulting
constructor is exact. Its class remains address-derived: the tempting
`DefaultModule<6>` name belongs to a different constructor and vtable.

The four-base constructor at `0x005FDE80` confirms the same lever: omitting
the head/intermediate virtual destructors produced 148 bytes instead of 196.
Restoring their native declarations generated the missing constructor cleanup
and an exact body. Include the actual `DefaultPhysicsModuleInfo` header, and
make the existing `GameClientRandomVariable::operator=` body visible inline:
calling its out-of-line declaration instead produced 191 bytes and an extra
call. This is a lifetime/definition-visibility issue, not a reason to write
manual exception state or duplicate the random-variable type.

## A null-first conditional can preserve the fallback branch order

The 692-byte model-name selector at `0x005F6B60` first matched its entire
641-byte random/string path, but a local pointer assignment in the fallback
emitted four fewer bytes. Selecting the pointer with `p ? p : nullSystem()`
restored the size and saved register, yet inverted the two branches.
`!p ? nullSystem() : p` retained the native conditional expression while
putting the call in retail's fall-through path: all 692 bytes then matched.
No volatile pointer, barrier, extra call, or manual register state was needed.

Keep the owning string operations native too: visible `AsciiString` copy and
destructor forwarding plus the actual `StringBase<char>::concat` length
wrapper reproduced three separate return-value lifetimes and their shared
cleanup tail. Do not flatten those branches into one mutable string merely
because the filename construction looks repetitive.

## Secondary-base calls and inline boolean setters

In terrain initialization `0x00730590` (684 bytes), calling inherited
`water->Set_Position(...)` reproduced the unconditional secondary-base
adjustment. `static_cast<RenderObjClass *>(water)->Set_Position(...)` instead
emitted a null-preserving pointer conversion before evaluating the arguments.
Use the real inheritance and call expression, not pointer arithmetic.

The same body then matched except for an eight-byte-short cloud flag update:
direct stores in the two arms became `setne`. Restoring the actual upstream
inline `toggleCloudLayer(Bool)` setter in both arms retained retail's branches
and made the complete body exact. The setter is real source behavior, not a
dummy code-generation helper. First verify all field offsets and reloads after
calls: five missing array-stride gaps and cached owner pointers initially hid
these two source-shape issues.

## Native render-state inlines and conditional handle temporaries

Terrain rendering `0x0072DC30` (1044 bytes) needs the actual `dx8wrapper.h`
render-state helper, including native `StringClass` diagnostic lifetimes.
A hand-expanded state-cache macro with raw global addresses compiled to 950
bytes; the native header restored the complete frame and cleanup structure.
Model the stored option at `+0x51` as its witnessed `Bool`, not an unsigned
byte requiring another boolean conversion: this removed an early EBX save.

The final 16 differing bytes had two causes: clearing the dirty flag before
constructing the update region, and using a positive
`if (count && returnedOwningHandle) { draw; }` block. The negated early-return
form reversed the temporary-condition flag arms. The positive form preserves
the handle's destruction before entering the draw block. Together these made
the full function exact, including both draw paths and all five unwind states.


For the narrow STLport `num_get` facet at vtable `0x0112E97C`, MSVC 7.1
places the bool overload at slot 11 (`+0x2c`) when the complete overload set
is declared in the vendor header's order. A reduced bool/long shim changed
the fallback virtual dispatch to `+4`. Restore the full witnessed ABI before
working on frame layout. The 2026-09-16 bank at `0x00838CE0` demonstrates this
correction but is **not matched**: it remains 704/704 bytes with 63 differing
stack-layout bytes. Its compiler frame is `0x24`, retail's is `0x1c`.


Renderer view/projection handoff `0x0078C440` is another native-header case.
Its retail x87 schedule uses `Matrix4::Transpose()` temporaries, not scalar
matrix assignment. The existing `DX8Wrapper::Set_Transform` inline restores
the `0x80` frame and the exact prefix through `+0x18c`. The independently
reprobed 2026-09-16 bank remains **unmatched**, at 628 versus 627 bytes with
92 differing non-relocation bytes in projection stores and the tail. Adding
an explicit extra matrix copy expands the frame to `0xc0`; it is not a fix.

For the audio helper at `0x00694130`, caller pushes alone initially suggested
an explicit output-pointer argument. Following the returned EAX and the
caller's EH cleanup proves a nontrivial four-byte handle return: the cleanup
uses ILT `0x000298e8`. Modeling that return restores the retail prefix, but
`return dispatch(filename, value)` still materializes an extra temporary.
The measured bank is **unmatched**, 219 versus 203 bytes with 73 differing
non-relocation bytes. An explicit local-output spelling grew to 261 bytes.
Prove the hidden return and destructor ABI before tuning return lifetimes.


Constructor `0x006070E0` (170 bytes) lands with the native STLport `_Rb_tree`
and a nested prefix subobject, rather than manual header-node stores. The
matched copy constructor at `0x006071C0` witnesses `0x28` POD bytes followed
by 109 owned pointer slots, then the tree at `+0x1dc`. Grouping the initialized
prefix preserves the retail EH state before the tree's allocation. The node
is `0x84` bytes: a `0x10` tree header plus a four-byte key and `0x70` mapped
value. The related tree copy constructor at `0x00606E60` independently verifies
that layout. Keep the aggregate owner opaque; a nearby generated STL name is
not evidence of the original enclosing class.


Do not infer a texture interface ABI from the historical `dx8wrapper.h` name.
The direct D3DX targets of `0x0090CAD0` are ledgered to the summer-2003
`d3dx9.lib`. Its observed texture calls use `+0x44`, `+0x48`, `+0x4c`, and
`+0x50`; a reduced D3D8 declaration does not supply that slot layout. The
2026-09-16 investigation corrected the interface declaration before probing,
but remained 539/559 bytes with 428 differing non-relocation bytes. This is
ABI evidence for future work, not a matched reconstruction.


Before using `throw()` to remove a copy-construction EH state, check whether
the callee is actually assignment. In the `PredefinedEvaEvent` parser at
`0x00425C90`, existing `??0Gen_004256E0` metadata initially suggested placement
construction. Retail `0x004256E0` copies four scalars, then calls
`0x00424AC0` through ILT `0x000083E1`. That nested tree operation compares
self/source and clears an existing tree: it is assignment. An address-derived
`operator=` declaration reproduces the complete 342-byte parser without the
incorrect construction lifetime or a `throw()` annotation. The legacy helper
name itself still requires separate correction; do not reuse it as constructor
evidence. The compiler's extra trailing `int3` is accepted as padding by the
ordinary scoped gate and is not added to claimed coverage.


When a native STLport vector assignment gains an inline cleanup path, compare
the donor TU's exception configuration before inventing element destructors.
For `0x00136C10` (258 bytes; element stride `0xEC`), plain POD and special-member
variants initially emitted 296 bytes. The verified donor at `0x003B6A40` uses
`/O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS`; adopting that configuration
with an address-derived raw-copy element reproduced the retail instruction
shape. Four helper dependencies were established from both aligned calls and
independent bodies, then pinned to their actual body addresses. The assignment
passes five cdecl arguments to the generic copy helper, although that optimized
helper reads only the first three; a legacy three-argument declaration alone
does not describe the caller. Likewise, the uninitialized-copy fourth argument
is unused here, so its legacy “counter” spelling is not semantic evidence.


For a four-byte mapped value, matching `map<AsciiString, float>` is a type
hypothesis, not proof: a typedef does not hide `float` in the mangled name.
At `0x006AF6D0`, float value-initialization reproduces immediate-zero stores
missed by integer/aggregate variants. Independent support comes from caller
`0x006B0850`: it transfers the value through Xfer slot `0x6C`, calls the map
subscript through ILT `0xD9D1`, and stores that transferred value. The same
slot handles the floating-point record in the matched `Rva006ABC60Xfer.cpp`.
The hinted insertion at `0x006AB6D0` has a hidden iterator output pointer and
`ret 0x0C`; its delegated insertion at `0x005C7490` allocates `0x18` bytes.
Do not infer a direct scalar return or a 20-byte node from the caller alone.


A nested scope can also recover reuse between two address-taken POD locals.
The `positionStartSpotControls` bank at `0x0044F960` now combines the proven
nontrivial Region3D copy ABI with a scope ending the `lr` coordinate after
width/height calculation. VC7.1 reuses its slot for `tempPos`, restoring the
retail 427-byte instruction shape and `0x34` frame. Twenty-nine stack-home
operand bytes still differ, so this is a banked partial, not a conversion.
Changing the upper-left array to a struct or reordering its declaration did
not help; grouping its fields with the width increased the frame to `0x3C`.

### Preserve nullable helper boundaries before inlining

`Rva0090C280::Apply` at `0x0090C840` (264 bytes) retains an AddRef null
guard even after its outer texture-enabled/non-null test. A separate forced-inline
SetTexture helper with a nullable argument reproduces this guard; manually
flattening the same operations produced a 260-byte near miss. Keep the source
helper boundary when retail repeats a check that appears redundant. The owner
remains address-derived; its constructor and vtable establish layout, not a
TextureClass identity. Device slot 65 and COM AddRef/Release use stdcall.

### Native map donors and mapped-value constructor shape

The verified float-map operator at `0x006AF6D0` led to the 191-byte waypoint
map operator at `0x000C0D00`. A trivial 12-byte mapped struct emitted 182 bytes;
a witnessed empty-constructor payload reproduced retail. The retail sequence
at +0x46 copies overlapping stack dwords, not zeros. Keep the payload opaque
when the reference type's initialization semantics differ; matching its size
alone does not prove that declaration. The hinted insertion helper takes the
hidden iterator output pointer first and pops 12 bytes. Verify this in its body,
not from a guessed STL return convention or an existing ILT label.

### Cleanup-bearing members recover a destructor frame

The 339-byte destructor at `0x0058DBC0` previously emitted a 344-byte
EH-prologue shape. Its unwind entries at RVA `0x00C37420`/`0x00C3742B`
prove cleanup of fields `+0x20` and `+0x24`. Modeling those as subobjects
with conditional/unconditional delete destructors reproduces the frame;
putting equivalent deletes only in the enclosing destructor body loses
that lifetime information. The source reuses the canonical string header
and keeps the unidentified owner and cleanup views address-derived.

The same approach lands the 240-byte destructor at `0x005927F0`: unwind
cleanup on `this+8` and `this+0xC` identifies embedded one-word holders.
Their normal-path cleanup inlines, but their member lifetimes determine the
EH frame. The owner destructor is nonvirtual; adding a virtual destructor
changed the prologue. Reuse the canonical ASCII header.

This investigation also found two unused pins that confused VA with RVA:
`0x0043FA7B` and `0x004347D9` were encoded virtual addresses, whose RVAs are
`0x0003FA7B` and `0x000347D9`. Existing correct helper pins suffice. A label
mentioning an ILT does not cause the resolver to subtract the image base.
Decode the branch and inspect the target before diagnosing a missing pin;
passing `HelpBoxText` to a helper does not prove a registration operation.

### Incoming argument reuse in a vector append

The 262-byte INI callback at `0x005CC4F0` uses its incoming `data` argument
slot for the created factory result before STLport `push_back`. A separate
local value left a 41-byte stack-displacement mismatch; retaining the owner
pointer and assigning the result back to `data` reproduces the retail frame.
Use the witnessed four-byte element and native vector operation, including
the five-argument overflow helper at `0x005C6BF0` via ILT `0x00016AE5`.
The canonical ASCII header also matches when the witnessed inline comparison
is kept as a separate helper over the string's buffer layout. The factory
list proves names at +4 and links at +0xC, not an original owner identity.

### Secondary-interface donors and constructor expressions

The 593-byte Worker construction body at `0x002C96D0` follows the landed
Dozer construction shape. A nontrivial coordinate copy, the typed terrain
virtual call, and the direct health-delta expression preserve the retail
x87 and local-variable shape. Keep mask construction at the member-call
site; a wrapper can move evaluation and change the emitted sequence.

Identity also requires the receiver adjustment: constructor `0x002C9ED0`
installs table VA `0x010C9DE8` at owner+`0x340`, and slot 4 reaches the body
through ILT `0x0003DF3C`. This proves the secondary receiver and the `WDEA`
ledger spelling. An old `WCAA` candidate pin was not that proof, even though
the underlying body could match under an opaque local view.

For an EBP-framed body that saves ESP but whose bank has no `try`, inspect the
retail FuncInfo's try-block map as well as its unwind map. At `0x0019BA40`,
`eh_info.py 0x0019BA43` skips the three-byte EBP prefix; FuncInfo `0x00DF5E78`
then leads to a catch-all at `0x0019BB8B` that clears the entry's Dict and
rethrows. Restoring that `try` around the update call, and ending the temporary
entry's scope before updating the free head, matched all 331 parent bytes with
native STLport and Dict headers. Stack padding and exception-flag sweeps had
missed this behavior; the following catch remains a separate ledger extent.

Native containers can change caller register allocation without changing its
operations. At `0x006155E0` the opaque map-method bank had a three-register
cycle across a 150-byte get-or-create body. The constructor independently
identified the mapped value as `LivingWorldSound*`; native
`hash_map<AsciiString, LivingWorldSound*>` find/index operations reproduce all
150 bytes. Its 142-byte index helper was initially blocked by an overlapping
naked lift; the verified boundary repair described below now lands it too.

At `0x0077D150`, native vector `insert`/`push_back` removes synthetic stack pads
and supplies the placement-copy exception state, landing 437 bytes. The first
record member is a narrow string and the next forty bytes are condition bits,
independently witnessed by the default and copy constructors. Preserve those
contracts and include the canonical string header; a misleading old alias is
not identity evidence.

Native list also fixes the FS-restore/pop ordering in the banked Target parser
`0x0014C8E0` (nine differences reduced to five) and font parser `0x0043A3B0`
(six reduced to two). Those residuals remain unlanded; do not treat this lever
as a guarantee or repeat old register-only sweeps.

Three more native-container callers closed after that investigation:
`0x00347DA0` (143B) uses the native hash iterator's increment, eliminating a
synthetic volatile bucket load/barrier and fixing the final copied-node test;
`0x0022DA50` (223B) uses native list insertion and the canonical string header,
fixing the four-byte EH epilogue residue; `0x00494EC0` (62B) keeps its two local
key copies but uses the native const-reference lookup/erase calls, fixing the
ECX-load/count-store order that opaque pointer-to-key declarations hid. The
last helper's plain-parameter spelling is only 48B: use the observed temporary
lifetime, not an arbitrary register-local rewrite. Callee bodies and mapped
pointer usage were independently verified before pinning each native spelling.

At `0x00614F50`, manually splitting the two override-lookup branches gave 330B
because the direct clone call pushed ESI. An inline lookup which returns
`next->friend_getFinalOverride()` or `this`, consumed by the clone call,
reproduces retail's returned-pointer temporary in EAX and all 332B. The lookup
behavior follows the existing Overridable contract; no padding instruction or
member-function-pointer union is needed. See
[living-world boundary evidence](living_world_parser_boundary.md).

## A free-call declaration can conceal a live receiver

At RVA `0035E710`, the bank declared a five-argument `__stdcall` free
function and its three-argument helper the same way. Twenty blocked verdicts
attributed its missing byte to register allocation and loop alignment. But
the physical helper `0035E5A0` (ILT `0000CEC8`) preserves incoming ECX in
EBX and addresses that receiver at +0C/+18. The caller leaves ECX intact.
Declaring both as members of an opaque address-derived owner restores the
retail ESI save/restore and loop NOP: 56/56 bytes, one operand byte remaining
(`mov eax,[edx]` versus `[eax]` after `mov edx,eax`). This is an improved
bank at that point. With the ABI corrected, expressing the walk directly as
`while (*link != target) { if (!*link) return; link = &(*link)->next; }`
also fixes the last operand and lands all56B. The direct link-slot spelling
had no power to fix the original wrong calling convention. Production source:
`Code/GameEngine/Source/Common/Rva0035E710LinkWalk.cpp`. Inspect the callee's
use of incoming ECX before treating an unused-in-the-caller ECX as spare.

The same audit **lands** `003F0EC0` (43B). Its bank forwarded six stack
arguments plus zero to `003EEB90` through ILT `0001FA14`, declaring both
functions free `__stdcall`. The helper saves incoming ECX at `003EEBA3`,
then reads receiver+8 at `003EEBCB`. Correcting **both** declarations to
member `__thiscall` and retaining the original source-field local reproduces
all43B, including the resolved call. A prior caller-only member spelling
left the helper declaration wrong and missed this lever. The helper returns
with `ret 1C` at `003EFE7E`; its generated ledger extent ends earlier, so
read through the actual return when checking the ABI. Production source:
`Code/GameEngine/Source/Common/Rva003F0EC0Forward.cpp`.

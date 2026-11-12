# BFME1 GameSpy shared socket-select and native byte-swap ownership

Reviewed OWN candidate-range base: 7c09e7477b8004f928da3446ecc5222f42057970.
A content-identical public rebase may add external ancestry; it is not OWN input.
Historical fixture source base: a77e288e9c49868f1e239d05dda3057a959b2fd0;
all19 affected source blobs equal the publication base before this repair.
This is source-scope equality only, NOT whole-tree/input equivalence.
Retail SHA256:
1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.
This is an existing-source provider/consumer repair, not a new algorithm.
The parent-run v5 local native pair and current normal 19-TU gate now pass;
independent immutable-range review/publication remains pending. No global
linked-byte or new source-function credit follows from this note.

## One genuine select provider, not two source spellings

BFME1 already owns complete330B `_ghiSocketSelect` at RVA00854530 in
GameSpy/ghttp/ghttpCommon.c. Its matched GHTTP callers and existing
GP/gpiUtility.c reference that same provider. The older GameSpy SDK function
returns signed32 GHTTPBool/int and accepts PE32 unsigned32 SOCKET plus three
nullable pointers to32-bit result slots. The native body conditionally builds
three fd_sets, calls select, writes each requested result as dword0/1 using
WSAFDIsSet, returns select's signed result (including SOCKET_ERROR=-1) in EAX,
and ends in plain RET: four cdecl words, caller cleanup. This is independently
visible in all330 native bytes, not inferred from the callee pin alone.

The later-upstream `GSISocketSelect` copied into nonport.c was unrowed and
not that native body: its compiled assert path adds a nonretail _assert
import and extra code/literals. The native image imports no _assert. The
existing gpiUtility.c comment already records the older `ghiSocketSelect`
identity, while gstats.c and ChatSocketCore.cpp still referenced the later
name. Their fresh full-object relocations identify exactly these matched
consumers: InitStatsThink009D5670; ciSocketSelect0085AA50;
ciSocketThinkSend0085AAB0; ciSocketThinkRecv0085AB70. Their native call target
is the existing330B provider. No new wrapper or second identity is needed.

The repair redirects those two source units to the existing provider, then
removes only the unsupported duplicate from nonport.c. The original
nonport.h declaration is left inert; all actual game source calls to the old
name are gone (gpiUtility's historical comment is not a call). Parent approved
exact TU-local declarations following gpiUtility's existing native ABI:
int-return, SOCKET/unsigned-int32, three int32-pointer slots; Chat uses extern C.
No new class, layout, function-pointer cast, header or alternate API is added.

`build/spike2-closure/ghttp-abi/abi.c` compiled with the actual PE32 MSVC7.1
compiler and real canonical GHTTP header checks unsigned32 SOCKET, SIGNED32
GHTTPBool, False0/True1. ReturnNegative emits83C8FFC3 (EAX=-1), StoreTrue emits
8B442404C70001000000C3 (dword store1). Native330B writes/reads the same
representation. No assumption that width alone proves enum compatibility.

## Real native Winsock identities, no new aliases/pins

IsPrivateIP is an existing76B matched nonport.c body at008547C0. NativeE8 at
+8 reaches0081BDDE, exactly FF25[01359718]; the actual PE import directory
names WSOCK32.dll!htonl there. The old source used ntohl, whose legacy pin and
DIR32 entry falsely alias that native htonl route. Changing the call to
htonl preserves the full32-bit conversion but names the real import. No new
pin/alias is introduced; existing real htonl routes0081BDDE/0081BE32 were
independently checked by pin_consistency.

The same native PE imports WSOCK32.dll!ntohs at0135972C, reached by actual
six-byte FF25 thunks0081BE14/0081BE3E. It imports NO htons. The Win32 canonical
API is unsigned-short stdcall(unsigned-short): a16-bit value in one4B stack
argument, callee cleanup4, AX result consumed by word storage/MOVZX. Native
get_sockaddrin009D2FF0, its expansion in InitStatsAsync009D4600, and
ciSocketConnect0085A870 witness this route and storage. Explicit call spelling
is corrected in the two already-changed consumers, including Chat's existing
TU-local declaration NAME only. Host/network16-bit conversion is an involution
on the target architecture; actual native DLL/name/slot proves identity rather
than relying only on equal byte-swap behavior. No header/type/layout change.
Other unrelated SDK files still using old spellings are outside this claim.
The existing available.c /Dhtons=ntohs BASE flag is unchanged on both sides;
no macro or alias is copied from it.

## Existing availability state, not a new definition/initializer

Canonical available.h declares signed32 enum GSIACResult with Waiting0,
Available1, Unavailable2, TemporarilyUnavailable3. Existing available.c ALREADY
defines `GSIACResult __GSIACResult;` as the unique external C definition.
The actual object has symbol `___GSIACResult`, section0/COMMON, value4; C scalar
alignment4, no constructor/.CRT registration. Native VA01352894 is aligned4
and contains exactly00000000 before initialization. No other data row owns it.

Existing matched223B GSIAvailableCheckThink00855190 stores results to that
exact dword (00855206/00855218) and Available1 at0085524B. Existing283B
GSIStartAvailableCheckA00855000 invokes the availability-reset path;
37B GSICancelAvailableCheck00855270 stores Waiting0 at0085528A. The native
functions and corresponding source are checked together. Readers compare the
same dword against enum1. Normal add_data_match verifies the whole4B datum
under the actual compiler, not a hand-written row or assumed neighboring size.
This formalizes ownership of existing storage: zero new physical function,
source-definition or constructor credit. available.c joins BOTH native
before/after inputs, not an after-only fabricated provider.

## Native boundary and acceptance requirements

All provider/consumer objects must remain full, with real CRT/kernel/User32/
Advapi32/WinMM and the native mixed Winsock boundary. Retail uses WS2_32 for
recv/recvfrom/getsockopt/setsockopt and WSOCK32 for its remaining legacy APIs.
Parent approved only unmodified stock short-import members for actual needed
four APIs from tracked WS2_32.Lib, then unchanged stock WSOCK32/WS2_32
libraries for descriptors; preserve member/header/DLL/name-or-ordinal/hash.
No handwritten stub, alias, DEF, force/include/export, dropped directive,
rewritten import member or new source pin. Use exactly the same library and
member set/order/flags on both sides. Record ordinal-vs-name lookup form and
verify endpoint identity from stock member plus real DLL export, not guesses.
Every actual PE import, selected provider body/data/relocation and two-base
route still needs proof. No produced game/DLL is executed.

Before source edits, the seven GHTTP TUs passed104/104. Existing darray and
nonport added58/58; full additional consumer gates passed62(gstats)+23(Chat/GP).
First approved three-file repair passed117/117+1data; second explicit16-bit
correction passed76/76. Those are byte gates, NOT yet native closure credit.
Full affected SDK/cohort footprint/gates and immutable fresh review remain
mandatory. Private proofs/logs are under build/spike2-closure/ghttp-*.

BFME2 donor76f0baefa6f285d54bc1ca922397674312a5913f was reviewed at
Code/GameEngine/Source/GameNetwork/GameSpy/{nonport.c,ghttp/ghttpCommon.c,
gp/gpiUtility.c}, including nonport history ce7bb480/e8d69749. Its later SDK
uses GSISocketSelect and an alternatename; that identity/alias is INAPPLICABLE
to BFME1's witnessed older provider and is not copied. Its byte-order alias
macros are not imported. BFME1 target callers/imports and existing source
establish the repair; donor names/addresses are not treated as BFME1 proof.

## Parent continuation after actual resource recovery

The first native links were invalid despite exit0: four WS2 thunks referenced
IAT cells outside a live DLL descriptor. An explicit standalone descriptor did
not repair their grouping. Those images remain negative controls, not success.
The first standard LLVM container changed archive labels/order and was rejected.

After free disk recovered above20GiB, the parent continued directly without
restarting a worker. Standard GNU ar qS packages ONLY the seven original stock
payloads under their original duplicate WS2_32.dll basenames. Tracked VC7
lib.exe indexes that raw archive. Its observed exact order reversal is compensated
by reversing the input list once; final member names/order/payload hashes and
all11 index symbols equal the selected original stock records. No archive header
or index was hand-built, payload rewritten, DEF/alias added or API fabricated.
The same resulting WS2_32.Lib and unchanged real libraries/order serve BOTH sides.

Four new VC7 DLL/NOENTRY links at51000000/62000000 bind all four WS2 APIs to a
live descriptor. All438 BEFORE/435 AFTER source runtime sections match exact
COFF bytes/addends/relocations; no placement conflicts or unknown PE fixups.
The exact HIGHLOW multiset/types and every complete two-base section pass.
Normal311 functions+2data across19 sources pass again; all19 current parsed
COFF section/symbol/aux/relocation graphs equal the frozen AFTER fixture.

Complete scope additionally binds283B of real shipped CRT code: chkstk61,
lldiv170 and llmul52, to actual MAP holders and byte-identical archive sections.
These bodies, genuine existing chkstk/alloca labels, real import thunks, PE import/
relocation metadata and uncovered zero/CC bytes earn ZERO source recovery credit.
There are no unclassified nonpadding section bytes. The strict import validator
rejects the preserved malformed v2/v3 images without rerunning their links.

Both corrected-boundary BEFORE and AFTER link. Their nonretail endpoint count
changes3 to0; this is provider/import fidelity evidence, NOT a newly linked
whole-program byte figure. Normal link_check reports UNKNOWN because the census
index is absent; no old index is copied or remote census fetched. No image is
executed. Machine evidence and immutable artifact hashes are recorded in
20261112-gamespy-native-family-proof.json. Helpers/logs/full local proofs remain
under build/spike2-closure/ghttp-parent-*; early failures are retained separately.

# GameSpy buddy-message native import identities

The existing `_gpiProcessRecvBuddyMessage` row remains at RVA `0x008F35B0`
in `game/GameEngine/Source/GameNetwork/GameSpy/gp/gpiBuddy.c`. No function
identity, size, source lane, or body address is added or moved.

## Existing identity and extent

The 2004 SDK's adjacent `gpiBuddy.h` declares
`GPResult gpiProcessRecvBuddyMessage(GPConnection *, const char *)`.
The already matched `_gpiProcessConnectionManager` at RVA `0x008EC130`
calls that C symbol with those two arguments. The physical selected link
checks the actual caller operand against the selected native definition.
The ledger and compiler COMDAT cover 1819 bytes, including its dispatch
tables; Ghidra's instruction extent is 1686 bytes (`FUN_00cf35b0`). This
repair preserves both existing extents and the complete 1819-byte match.

## Independently read retail calls

Both call fields are offsets within the existing 1819-byte symbol.
Each thunk was read from the unpacked retail image as an actual `FF 25`
instruction; its operand was then resolved through the PE import directory.

| Field | Retail thunk RVA | IAT VA | Actual imported identity |
| --- | --- | --- | --- |
| REL32 +0x4C6 | 0x0081BE32 | 0x01359718 | WSOCK32.dll!htonl |
| REL32 +0x4FE | 0x0081BE14 | 0x0135972C | WSOCK32.dll!ntohs |

The first call already names `htonl`. Its existing second symbols.csv pin
at `0x0081BE32` lacked the independently verifiable `route=` note. The
first pin at `0x0081BDDE` has the same six bytes and same IAT slot. Adding
the route note admits that actual second REL32 route without changing a
body home or supplying a DIR32 target. No new pin or alias is introduced.

The upstream port expression used `htons(port)`. The same-width byte swap
does not establish the retail import identity: retail imports `ntohs` at
this call. The source now calls the already declared native `ntohs(port)`.
The existing GameSpy Winsock shim declares both functions as
`u_short __stdcall(u_short)`, with `u_short` an unsigned short. No header or
ABI change is needed; the existing canonical `ntohs` pin is route-proven.
Other callers and existing pins remain untouched.

## Gates and physical controls

Both native source TUs passed all 16 ledger rows before and after, including
55 literal references and 20 DIR32 references. Symbol pin checks passed
before and after; the full pin guard passed with 245 re-derived route rows.
The current provider's strict RetailTruth verdict changed `wrong` to
`retail`; its only previous disagreement was the +0x4C6 route.

The physical harness links both actual source objects against the installed
VC71 SDK `WSock32.Lib` with `/NODEFAULTLIB /OPT:NOREF /OPT:NOICF`. It checks
1819 provider bytes, 765 caller bytes, and all 111 relocation operands,
including local dispatch labels and string contents. Native selected thunk
instructions resolve through the output PE's import table to the same DLL
and name as retail. Other unresolved dependencies use distinct labelled
poison symbols for this link-only test; nothing is executed.

The retained old compiled object also links successfully, but the strict
identity comparison rejects its actual native `htons` provider against
retail's `ntohs`. Independently, removing only the new htonl route from an
in-memory RetailTruth counterfactual rejects the current body as `wrong`.
Neither negative changes the tracked source, receipts, or frozen census.

Artifacts: `build/next_link_candidate2_36h/build/gpi_buddy_review/`.
`physical_proof.json` SHA256:
`a9a62d1c62fd4ed85a42a804ea148d6b07312ffd15be6508dbef209c2e0fd1ef`.
Native `WSock32.Lib` SHA256:
`f9becd1da1cf03cab8f093d9bc593eb2e1e6907e738cda0f71a45e18dfdb7586`.

The COMMON-complete historical ae75 index preview changes 0/2 files to 2/2,
0 to 5123 linked bytes (2305 caller, 2818 provider TU). This is explicitly
a historical preview; the old bb1f queue's 2305-byte projection is not a
fresh whole-image gain. No matched bytes, authored bytes, or source-lane
credit are added by this native callee repair.

# 0x007189B4 / 0x00718B14 / 0x00718D05: shader loader catch(...) blocks

2026-11-04, model=claude-opus-5-5. Link queue #7 (`<hard-coded image addresses>`).

## Retail evidence (BFME 1 target)

The three 17-byte bodies were ledgered as free functions
`?Rva007189B4Forward@@YAPAXXZ`, `?Rva00718B14Forward@@YAPAXXZ` and
`?Rva00718D05Forward@@YAPAXXZ` in
`game/GameEngine/Source/Common/Rva007189B4CatchForwarder.cpp`, which spelled the
returned continuation address as a hard-coded image address. Each is
`push "Error opening file \n"; call [OutputDebugStringA]; mov eax, <cont>; ret`:
the shape of an MSVC 7.1 catch block, which returns its continuation address.

The FuncInfo records (magic 0x19930520, read from lotrbfme.exe through each
parent's `push handler` / `mov eax, FuncInfo` thunk) name them as the parents'
only catch handlers (try 0..1, catch state 2, catch type 0 = `catch(...)`):

| parent (matched) | handler thunk | FuncInfo | catch handler | continuation |
|---|---|---|---|---|
| `?LoadAndCreateD3DShader@BfmeVertexShaderLoader@@SAJPBDPAK@Z` 0x007188B0 (260 B) | 0x0104CA58 | 0x0123C56C | 0x007189B4 | 0x007188FA (parent+0x4A) |
| `?LoadAndCreateD3DShader@BfmeShaderLoader@@SAJPBDPAK@Z` 0x00718A10 (260 B) | 0x0104CA78 | 0x0123C5CC | 0x00718B14 | 0x00718A5A (parent+0x4A) |
| `?LoadAndCreateD3DShader@Rva00718B70ShaderLoader@@SAJPBDPAK@Z` 0x00718B70 (405 B) | 0x0104CA98 | 0x0123C62C | 0x00718D05 | 0x00718C3B (parent+0xCB) |

Each handler starts exactly at its parent's end (parent RVA + size), and each
continuation lies inside the parent.

## Object evidence (BFME 1 build)

The parents' existing `try { ... } catch ( ... ) { OutputDebugString( "Error
opening file \n" ); }` sources already emit these blocks as compiler labels in
the parent's own section: `$L19599` at +0x104 in BfmeVertexShaderLoader.obj,
`$L40571` at +0x104 and `$L40615` at +0x195 in BfmeShaderLoader.obj. The
continuation is the parent-local label (`$L19602`/`$L40574` at +0x4A, `$L40618`
at +0xCB), so the relocated `mov eax` needs no hard-coded address.

## Repair

Each row is repointed to its parent's source as a `?dup_XXXXXXXX@@YAXXZ`
`compiler-catch;gen-funclet` row bound by `object-symbol=`; the free-function
forwarder TU is deleted. No donor material used.

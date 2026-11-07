# 0x006925F0: audio cache per-priority list push_back (45 B)

**Row change.** `?dup_006925f0@@YAXXZ` was a gen-alias on
`ShellMenuSchemeManager_parseImagePart_Thunk.cpp`, with object symbol
`list<ShellMenuSchemeImage*>::push_back`. It becomes
`?push_back@Rva006925F0List@@QAEXABQAVGen0002857E@@@Z`, defined in
`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp`.

## BFME 1 target evidence

- **Single caller.** A raw scan of every `E8`/`E9` rel32 in retail `.text` finds one jump to
  0x006925F0, its ILT thunk 0x0001F3A2. It finds one call to 0x0001F3A2, at 0x00693D40, inside
  the audio cache lookup 0x00693B90 (525 B). Nothing else in retail calls the body or its thunk.
- **The ShellMenuScheme alias was a byte coincidence.** ShellMenuScheme's own
  `list<ShellMenuSchemeImage*>::push_back` is matched separately at 0x00581290. The 45-byte
  STLport `push_back` shape (insert at `end()`) is shared by every `list<T*>`
  instantiation, so the generator aliased this body to that object symbol by masked bytes alone.
- **Caller context.** 0x00693B90 calls it on the clamped per-priority list `this+0x14+level*4`
  (`push 'file' ref; mov ecx, list; call`). That is the new-record path of the cache lookup.
- **Bytes.** The visible `__declspec(noinline)` `push_back` in the host TU emits a COMDAT that
  `probe.py` reports EXACT against 0x006925F0 at 45/45 B. In the same TU, 0x00693B90 (525 B) and
  0x00694230 (654 B) are also EXACT.

## Name

The element type and the owning class are still unproven: `Gen0002857E` is the existing
placeholder for the 0x44-byte cache record. The class therefore keeps an address-derived name,
`Rva006925F0List`. `push_back` describes the observed behaviour (one node allocated and linked
before the sentinel), which matches STLport `list::push_back`.

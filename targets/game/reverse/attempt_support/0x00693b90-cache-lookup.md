# 0x00693B90 audio cache lookup (525 B) — bank at shape 0.92

Session a1 s539 (2026-11-02), model claude-opus-5-5, cl 13.10 with the flags of
`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp`
(the bank appends the body to that TU; same owner class: hash map +0x00,
priority lists +0x14, failed set +0x2C, mutex +0x48).

Why it matters: link queue #102. `Rva00694130AudioWorker.cpp` defines an inline
forwarder `Rva00694710AudioWorker::rva00693B90` whose select-any copy (pinned
at 0x00693B90) is not retail's body. Landing this body under the pinned name
`?rva00693B90@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z`
and making the caller's member declaration-only fixes both.

Facts from retail: clamp priority to 0..2; ScopedMutex {h, bool} waits
INFINITE, flag set unless WAIT_TIMEOUT, flag re-read from memory at every exit
(a `volatile` flag reproduces that); empty name -> default handle; hash
`_M_find` (0x006931A0) hit: prepareRemoval (0x00693B00) when +0x34 == 0, then if
!+0x41 && +0x3C < prio move the record between the per-priority lists with the
inline STLport erase + push_back, update (0x006BA130), return Handle(file);
failed-set hit -> default handle; else new 0x44-byte record (0x006BA2D0, args
this,name), Handle tmp, hash operator[] (0x00693880) = file, out-of-line
push_back via ILT 0x0001F3A2 (gen-alias ?dup_006925f0), update, return copy
(copy ctor 0x00691110). Unwind: state 0 return flag, 1 mutex (ILT 0x0001E961 ->
0x006915E0), 2 new, 3 tmp handle.

Remaining mismatch (bank): frame 0x1C vs retail 0x18 — retail spills the
mutex-handle copy into the dead `priority` parameter home ([esp+0x40]); ours
gets a fresh slot, which also swaps ebx/ebp (priority vs name). The list scan
loop is rotated in ours (retail: unrotated `cmp eax,ecx; je; cmp [eax+8],edi;
je; mov eax,[eax]; jmp`). The new path keeps `file` in memory instead of edi.

Ruled out (no gain or worse): separate clamped local; STLport find form
`while (n != head && !(n->m_data == file))`; flipped failed-set test with
single tail return (0.83); default-ctor + acquire() mutex shape (0.915).
Levers that helped: lists at +0x14 (hash rep 0x14 bytes), inline empty test on
the string data (+4 length word), volatile lock flag, 0x44-byte record view.

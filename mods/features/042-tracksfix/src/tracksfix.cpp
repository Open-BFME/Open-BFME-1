// 042-tracksfix — stop the terrain-track renderer dereferencing a null vertex
// buffer.
//
// THE CRASH. Reproduced byte for byte against three retail minidumps; the
// evidence, the dumps and the reproduction are in
// mods/features/041-tracksprobe/README.md.
//
//   EXCEPTION_ACCESS_VIOLATION reading 0x00000004, eip = 0x0091DD7F
//     VertexBufferClass::WriteLockClass::WriteLockClass   edi (the buffer) == 0
//       TerrainTracksRenderObjClassSystem::flush          0x0072FEB0
//         RTS3DScene::Customized_Render / Render
//           GameEngine::_bfme_updateClientSubsystems      0x0006B910
//
// flush hands [this+0] straight to WriteLockClass, which bumps a refcount at
// buffer+4 -- the read of address 4. It guards on the track list at [this+0x10]
// being non-empty and on a shader-state query, and neither of those says
// anything about whether the buffer is still there.
//
// THE FIX, and why it is shaped like this. What is wanted is "return when the
// buffer is gone", and flush ALREADY has that exit: its own list guard three
// instructions in. So rather than add a second one, this takes the list away
// while the buffer is missing and gives it back when the buffer returns, and
// the engine's existing early-out does the returning.
//
// Two things that look simpler and are worse:
//
//   * Repointing the entry guard at the buffer instead of the list (a 3-byte
//     poke, no cave). flush re-checks the list itself at 0x0072FF66 and skips
//     the fill loop when it is empty, so this is safe -- but the entry guard is
//     what stops a Lock/Unlock pair on the vertex buffer in the common case,
//     and in BFME the list is almost always empty (see below). It would put a
//     lock in every frame to fix a crash almost nobody reaches.
//   * Checking both in place. It does not fit: re-encoding the prologue with a
//     second null test needs 38 bytes and the region is 34.
//
// Dropping the list instead of restoring it would also work and be shorter, and
// it is not what this does: those nodes are refcounted and the system is the
// only thing holding them, so forgetting the head leaks them. Parking costs
// four lines and is correct rather than merely non-fatal.
//
// WHEN IT FIRES. Rarely, and that is expected. TrackMarks is a W3DTankDraw /
// W3DTruckDraw field and exactly two objects in the shipped INI declare one --
// CINE_MordorCatapult_LR and Tank, a leftover Generals test object -- while
// every real unit uses W3DScriptedModelDraw. Measured: the list stayed empty
// across 1341 logic frames of ordinary play. So on almost every frame the
// engine's own guard has already returned before this matters, and this hook
// reads two pointers and does nothing.
//
// What still is not known is what leaves a LIVE system holding a null buffer;
// shutdown nulls it, but its only caller frees the object and nulls the global
// immediately after, and flush's caller null-checks that global. This removes
// the crash, not the cause, and it is deliberately silent about it: there is no
// console behind a code cave, and a shipped build is not the place to log.
// 041-tracksprobe is the place, and it watches exactly these two fields.
//
// No loader and no CRT: cave.py drops this into an appended section and jumps
// in from mid-function. Fixed-base 0x400000 image, DllCharacteristics 0x0000,
// so absolute addressing is safe.

enum {
    TT_BUFFER = 0x00,  // VertexBufferClass *, what flush locks
    TT_TRACKS = 0x10   // the track list head, what flush's own guard tests
};

// The list taken away while the buffer was missing. One system, one global.
static void *s_parked;

extern "C" __declspec(dllexport) void __cdecl tracksfix_flush(void *ecx) {
    unsigned char *sys = (unsigned char *)ecx;
    if (sys == 0) {
        return;
    }

    void **head = (void **)(sys + TT_TRACKS);
    const void *buffer = *(void **)(sys + TT_BUFFER);

    if (buffer == 0) {
        if (*head != 0) {
            s_parked = *head;
            *head = 0;
        }
    } else if (s_parked != 0) {
        // Only if nothing else has filled the head in the meantime: a real
        // track that arrived while the buffer was gone outranks a parked one.
        if (*head == 0) {
            *head = s_parked;
        }
        s_parked = 0;
    }
}

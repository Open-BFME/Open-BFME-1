// ?read_vertex_influences@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// partial score=0.5653 date=2026-09-28
// ?read_vertex_influences@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// Best reconstruction so far (measured 558B vs retail 559, 241 non-reloc
// diffs, shape 0.955, quality 0.5653 -- up from 0.5152). Loops 1 and 2 are
// now byte-identical to retail:
//  * the 8-byte chunk read loop, including the promoted plane-1 cursor in the
//    0x20 frame and the four plane writes, matches instruction for
//    instruction;
//  * the run-count loop matches once the four cached 16-bit influences are
//    written as TWO 2-element unsigned short arrays (p01/p23) instead of four
//    scalars: that is what puts v0/v1 in the incoming-argument home at
//    [esp+0x34]/[esp+0x36] and v2/v3 adjacently at [esp+0x10]/[esp+0x12],
//    exactly as retail does. Four scalars give four scattered frame slots.
//  * `int j = i;` before the loop-3 cache initialiser and the run stores
//    written as runs[0]/runs[1]/runs += 2 keep the loop-3 vertex count in a
//    frame slot instead of a register.
// Remaining blocker (entirely inside loop 3, the influence-run writer):
// retail re-reads this+0x28 into edx in the loop-3 preheader and again in the
// latch, parks the value at [esp+0x20] and reloads that slot for the inner
// scan, but re-reads the member for the rotated entry test
// (cmp ecx,[ebp+0x28] at retail +0x161). Because that entry test touches the
// member, `this` stays live in ebp through the body, so retail's two inner
// cursors spill to [esp+0x10]/[esp+0x14] and the scan index j lands in eax.
// This source CSEs the member read into a frame slot instead, so `this` dies
// before the body, both cursors stay in eax/ebp and j lands in edx; that one
// difference cascades into the dx-vs-ax scratch, mov eax,2 vs mov edx,2, the
// cursor slot offsets and the this-spill at [esp+0x20] vs [esp+0x1c].
// About 60 source spellings were tried (explicit count locals, do/while plus
// if guards, member vs cached guards, scalar/array/pair cache forms, run-store
// forms, and the register/copy/store/loop/sib families from
// tools/shape_family_levers.py) and every one of them normalises to this same
// shape: MSVC 7.1 substitutes its CSE temp for the rotated entry test instead
// of rematerialising the load.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

class ChunkLoadClass
{
public:
    unsigned long Read(void *buffer, unsigned long bytes);
};

class MeshGeometryClass
{
protected:
    unsigned short *get_bone_links(bool create);
    unsigned short *Rva00924760InfluenceRuns(int count);
    bool read_vertex_influences(ChunkLoadClass &cload);

    enum FlagsType { SKIN = 0x400 };
    void Set_Flag(FlagsType flag, bool enabled)
    {
        int *flags = reinterpret_cast<int *>(reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x18));
        if (enabled)
            *flags |= flag;
        else
            *flags &= ~flag;
    }
};

bool MeshGeometryClass::read_vertex_influences(ChunkLoadClass &cload)
{
    unsigned short *links = get_bone_links(true);
    const int vertexCount = *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x28);
    unsigned short influences[4];

    for (int i = 0; i < vertexCount; ++i) {
        if (cload.Read(influences, 8) != 8)
            return false;
        links[i] = influences[0];
        links[i + vertexCount] = influences[1];
        links[i + vertexCount * 2] = influences[2];
        links[i + vertexCount * 3] = influences[3];
    }

    int runCount = 0;
    for (int i = 0; i < vertexCount; ) {
        const unsigned short p01[2] = { links[i], links[i + vertexCount] };
        const unsigned short p23[2] = { links[i + vertexCount * 2], links[i + vertexCount * 3] };
        while (i < vertexCount && p01[0] == links[i] && p01[1] == links[i + vertexCount] &&
               p23[0] == links[i + vertexCount * 2] && p23[1] == links[i + vertexCount * 3])
            ++i;
        ++runCount;
    }

    unsigned short *runs = Rva00924760InfluenceRuns(runCount * 2);
    for (int i = 0; i < *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x28); ) {
        int j = i;
        const unsigned short c3[3] = {links[i + vertexCount], links[i + vertexCount * 2],
                                      links[i + vertexCount * 3]};
        while (j < *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x28) && links[i] == links[j] && c3[0] == links[j + vertexCount] &&
               c3[1] == links[j + vertexCount * 2] && c3[2] == links[j + vertexCount * 3]) {
            ++j;
        }
        runs[0] = links[i];
        runs[1] = static_cast<unsigned short>(j - i);
        runs += 2;
        i = j;
    }

    Set_Flag(SKIN, true);
    return true;
}

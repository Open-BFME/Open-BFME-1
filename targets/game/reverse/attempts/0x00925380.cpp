// ?read_vertex_influences@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
// partial score=0.35 date=2026-09-24
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
        int *flags = reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x18);
        if (enabled)
            *flags |= flag;
        else
            *flags &= ~flag;
    }
};

bool MeshGeometryClass::read_vertex_influences(ChunkLoadClass &cload)
{
    unsigned short *links = get_bone_links(true);
    int vertexCount = *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x28);
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
    int i = 0;
    while (i < vertexCount) {
        int end = i + 1;
        while (end < vertexCount &&
            links[i] == links[end] &&
            links[i + vertexCount] == links[end + vertexCount] &&
            links[i + vertexCount * 2] == links[end + vertexCount * 2] &&
            links[i + vertexCount * 3] == links[end + vertexCount * 3])
            ++end;
        ++runCount;
        i = end;
    }

    unsigned short *runs = Rva00924760InfluenceRuns(runCount * 2);
    i = 0;
    while (i < vertexCount) {
        int end = i + 1;
        while (end < vertexCount &&
            links[i] == links[end] &&
            links[i + vertexCount] == links[end + vertexCount] &&
            links[i + vertexCount * 2] == links[end + vertexCount * 2] &&
            links[i + vertexCount * 3] == links[end + vertexCount * 3])
            ++end;
        *runs++ = links[i];
        *runs++ = end - i;
        i = end;
    }

    Set_Flag(SKIN, true);
    return true;
}

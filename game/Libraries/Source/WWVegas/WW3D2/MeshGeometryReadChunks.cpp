// Open-BFME: complete BFME MeshGeometryClass::read_chunks reconstruction.
//
// Retail identity is the bool dispatcher at RVA 0x00927950.  The complete
// emitted range is 0x00927950..0x00927ABE (192 bytes of code followed by the
// eight-entry jump table and 0x8f-byte selector map); 0x00927ABF is INT3.
// Load_W3D at 0x00927F30 calls this body and ignores its bool result.  The
// inherited geometry handlers below are the exact callees selected by the
// retail arms.

class ChunkLoadClass {
public:
    bool Open_Chunk();
    unsigned long Cur_Chunk_ID();
    bool Close_Chunk();
};

enum {
    W3D_CHUNK_VERTICES = 0x02,
    W3D_CHUNK_VERTEX_NORMALS = 0x03,
    W3D_CHUNK_SURRENDER_NORMALS = 0x04,
    W3D_CHUNK_MESH_USER_TEXT = 0x0c,
    W3D_CHUNK_VERTEX_INFLUENCES = 0x0e,
    W3D_CHUNK_TRIANGLES = 0x20,
    W3D_CHUNK_VERTEX_SHADE_INDICES = 0x22,
    W3D_CHUNK_AABTREE = 0x90
};

class MeshGeometryClass {
protected:
    bool read_vertices(ChunkLoadClass &cload, bool alternate_format);
    bool read_vertex_normals(ChunkLoadClass &cload, bool alternate_format);
    bool read_triangles(ChunkLoadClass &cload);
    bool read_user_text(ChunkLoadClass &cload);
    bool read_vertex_influences(ChunkLoadClass &cload);
    bool read_vertex_shade_indices(ChunkLoadClass &cload);
    bool read_aabtree(ChunkLoadClass &cload);
    bool read_chunks(ChunkLoadClass &cload);
};

// ?read_chunks@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_chunks(ChunkLoadClass &cload)
{
    while (cload.Open_Chunk()) {
        bool error = true;

        switch (cload.Cur_Chunk_ID()) {
            case W3D_CHUNK_VERTICES:
                error = read_vertices(cload, false);
                break;
            case W3D_CHUNK_SURRENDER_NORMALS:
            case W3D_CHUNK_VERTEX_NORMALS:
                error = read_vertex_normals(cload, false);
                break;
            case W3D_CHUNK_TRIANGLES:
                error = read_triangles(cload);
                break;
            case W3D_CHUNK_MESH_USER_TEXT:
                error = read_user_text(cload);
                break;
            case W3D_CHUNK_VERTEX_INFLUENCES:
                error = read_vertex_influences(cload);
                break;
            case W3D_CHUNK_VERTEX_SHADE_INDICES:
                error = read_vertex_shade_indices(cload);
                break;
            case W3D_CHUNK_AABTREE:
                read_aabtree(cload);
                break;
            default:
                break;
        }

        cload.Close_Chunk();
        if (error != true) {
            return error;
        }
    }

    return true;
}

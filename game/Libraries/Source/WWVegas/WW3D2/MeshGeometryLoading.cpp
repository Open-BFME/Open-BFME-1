// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME MeshGeometryClass::read_aabtree at 0x00923930, complete 149 bytes.
// Mesh chunk 0x90 selects the arm at 0x009700A8 and this culling-tree loader.
// The original GeneralsMD meshgeometry.cpp body releases the prior tree,
// allocates its replacement, loads the chunk and binds the tree to this mesh.
// BFME CullTree is at +0x90; the allocation is 0x1C bytes. This callee itself
// returns true in AL. RET 4 at 0x009239C2 ends before padding at 0x009239C5.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "vector3.h"
#include "sphere.h"
#include "multilist.h"
#include "chunkio.h"
#include "sharebuf.h"
#include "vector4.h"
#include "vector3i.h"
#include "w3d_file.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass;

class AABTreeClass : public W3DMPO, public RefCountClass
{
public:
    AABTreeClass(void);
    void Load_W3D(ChunkLoadClass &cload);
    void Set_Mesh(MeshGeometryClass *mesh);
private:
    char _storage[0x14]; // total AABTreeClass size 0x1c (retail allocator operand)
};

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
protected:
    bool read_aabtree(ChunkLoadClass &cload);
    bool read_triangles(ChunkLoadClass &cload);
    enum FlagsType { DIRTY_PLANES = 0x00000002 };
    void Set_Flag(int flag, bool onoff)
    {
        if (onoff) Flags |= flag;
        else Flags &= ~flag;
    }
    int Get_Polygon_Count(void) const { return PolyCount; }
    TriIndex *get_polys(void) { return Poly->Get_Array(); }
    Vector4 *get_planes(bool create = true);
    uint8 *Get_Poly_Surface_Type_Array(void) { return PolySurfaceType->Get_Array(); }

protected:
    void *UserText;               // BFME this+0x10
    void *MeshName;               // BFME this+0x14
    int Flags;                    // BFME this+0x18
    char SortLevel;               // BFME this+0x1c
    uint32 W3dAttributes;         // BFME this+0x20
    int PolyCount;                // BFME this+0x24
    int VertexCount;              // BFME this+0x28
    ShareBufferClass<TriIndex> *Poly; // BFME this+0x2c
    void *Vertex;                 // BFME this+0x30
    void *Slot34;                 // BFME this+0x34
    void *Slot38;                 // BFME this+0x38
    void *Slot3c;                 // BFME this+0x3c
    void *Slot40;                 // BFME this+0x40
    void *Slot44;                 // BFME this+0x44
    void *Slot48;                 // BFME this+0x48
    void *Slot4c;                 // BFME this+0x4c
    void *Slot50;                 // BFME this+0x50
    void *Slot54;                 // BFME this+0x54
    void *Slot58;                 // BFME this+0x58
    void *Slot5c;                 // BFME this+0x5c
    ShareBufferClass<uint8> *PolySurfaceType; // BFME this+0x60
    void *Slot64;                 // BFME this+0x64
    Vector3 BoundBoxMin;          // BFME this+0x68
    Vector3 BoundBoxMax;          // BFME this+0x74
    SphereClass BoundSphere;      // BFME this+0x80, radius at +0x8c
    AABTreeClass *CullTree;       // BFME this+0x90
};

// ?read_aabtree@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_aabtree(ChunkLoadClass &cload)
{
    REF_PTR_RELEASE(CullTree);
    CullTree = NEW_REF(AABTreeClass,());
    CullTree->Load_W3D(cload);
    CullTree->Set_Mesh(this);
    return true;
}

// BFME triangle reader at 0x00925200, complete 190 bytes. Mesh chunk
// W3D_CHUNK_TRIANGLES calls this inherited geometry method. The GeneralsMD
// body reads 32-byte W3dTriStruct records into 16-bit indices, plane equations
// and surface types. The failure RET 4 ends at 0x009252BD; padding starts BE.
// ?read_triangles@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_triangles(ChunkLoadClass &cload)
{
    W3dTriStruct tri;

    TriIndex *vi = get_polys();
    Set_Flag(DIRTY_PLANES, false);
    Vector4 *peq = get_planes();
    uint8 *surface_types = Get_Poly_Surface_Type_Array();

    for (int i = 0; i < Get_Polygon_Count(); i++) {
        if (cload.Read(&tri, sizeof(W3dTriStruct)) != sizeof(W3dTriStruct)) {
            return false;
        }

        vi[i].I = tri.Vindex[0];
        vi[i].J = tri.Vindex[1];
        vi[i].K = tri.Vindex[2];

        peq[i].X = tri.Normal.X;
        peq[i].Y = tri.Normal.Y;
        peq[i].Z = tri.Normal.Z;
        peq[i].W = -tri.Dist;

        surface_types[i] = (uint8)tri.Attributes;
    }

    return true;
}

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
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
// BFME MeshModelClass::read_chunks, RVA 0x0096FF70, full 516-byte span.
// Load_W3D calls this dispatcher at 0x009705C7 after creating its mesh context.
// The source preserves inherited geometry-reader ownership and the BFME bool
// status. Geometry format variants 0xC00/0xC01 pass the additional true flag.
// Retail low dispatch: arm table 0x0097010C, selectors 0x00970134..0x00970153
// for IDs 0x02..0x21. ID 0x22 takes a direct arm. A second eight-entry table
// at 0x00970154..0x00970173 handles IDs 0x23..0x2A. Both tables belong to
// this function; the twelve INT3 bytes at 0x00970174..0x0097017F do not.
// The last RET 8 is at 0x00970106. Prelit and AABTree results are ignored,
// matching the original meshmdlio.cpp control flow; other child status values
// survive Close_Chunk and are returned on failure.
// Every typed child pin follows its actual chunk arm and reference body.
#include "w3d_file.h"

class ChunkLoadClass {
public:
    unsigned long Cur_Chunk_ID();
    bool Open_Chunk();
    bool Close_Chunk();
};

class MeshLoadContextClass {};

// These six geometry readers are inherited from MeshGeometryClass in the
// reference hierarchy.  Keeping that owner in the scratch view preserves the
// decorated callee identity used by the retail dispatch arms.
class MeshGeometryClass {
protected:
    bool read_vertices(ChunkLoadClass &cload, bool alternate_format);
    bool read_vertex_normals(ChunkLoadClass &cload, bool alternate_format);
    bool read_triangles(ChunkLoadClass &cload);
    bool read_user_text(ChunkLoadClass &cload);
    bool read_vertex_influences(ChunkLoadClass &cload);
    bool read_vertex_shade_indices(ChunkLoadClass &cload);
    bool read_aabtree(ChunkLoadClass &cload);
};

class MeshModelClass : public MeshGeometryClass {
protected:
    bool read_texcoords(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_v3_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_per_tri_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_vertex_colors(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_material_info(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_prelit_material(ChunkLoadClass &cload, MeshLoadContextClass *context);
    bool read_chunks(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

bool MeshModelClass::read_chunks(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
    while (cload.Open_Chunk()) {
        bool error = true;

        switch (cload.Cur_Chunk_ID()) {
            case W3D_CHUNK_VERTICES:
                error = read_vertices(cload, false);
                break;
            case W3D_CHUNK_VERTEX_NORMALS:
                error = read_vertex_normals(cload, false);
                break;
            case W3D_CHUNK_TEXCOORDS:
                error = read_texcoords(cload, context);
                break;
            case W3D_CHUNK_MATERIALS3:
                error = read_v3_materials(cload, context);
                break;
            case W3D_CHUNK_TRIANGLES:
                error = read_triangles(cload);
                break;
            case W3D_CHUNK_PER_TRI_MATERIALS:
                error = read_per_tri_materials(cload, context);
                break;
            case W3D_CHUNK_MESH_USER_TEXT:
                error = read_user_text(cload);
                break;
            case W3D_CHUNK_VERTEX_COLORS:
                error = read_vertex_colors(cload, context);
                break;
            case W3D_CHUNK_VERTEX_INFLUENCES:
                error = read_vertex_influences(cload);
                break;
            case W3D_CHUNK_VERTEX_SHADE_INDICES:
                error = read_vertex_shade_indices(cload);
                break;
            case W3D_CHUNK_MATERIAL_INFO:
                error = read_material_info(cload, context);
                break;
            case W3D_CHUNK_SHADERS:
                error = read_shaders(cload, context);
                break;
            case W3D_CHUNK_VERTEX_MATERIALS:
                error = read_vertex_materials(cload, context);
                break;
            case W3D_CHUNK_TEXTURES:
                error = read_textures(cload, context);
                break;
            case W3D_CHUNK_MATERIAL_PASS:
                error = read_material_pass(cload, context);
                break;
            case W3D_CHUNK_PRELIT_UNLIT:
            case W3D_CHUNK_PRELIT_VERTEX:
            case W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_PASS:
            case W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_TEXTURE:
                read_prelit_material(cload, context);
                break;
            case W3D_CHUNK_AABTREE:
                read_aabtree(cload);
                break;
            case 0xc00:
                error = read_vertices(cload, true);
                break;
            case 0xc01:
                error = read_vertex_normals(cload, true);
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

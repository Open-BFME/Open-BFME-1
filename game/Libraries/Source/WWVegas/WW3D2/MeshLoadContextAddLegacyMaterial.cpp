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
// BFME MeshLoadContextClass::Add_Legacy_Material: RVA 0x0096F210,
// complete 922 bytes. The version-3 material reader calls this at 0x0096FA3C
// with a shader, a vertex material and a borrowed owning-texture handle.
// The original GeneralsMD algorithm deduplicates shaders by value, vertex
// materials by CRC, and textures by identity or case-insensitive name.
// BFME texture names are returned as StringClass values; both temporaries
// are destroyed after comparison. The handle getter at 0x008FF5B0 calls
// the texture's name slot and the named StringClass copy constructor.
// Actual DynamicVectorClass layout is used at offsets 94/AC/C4/DC/F4.
// Vertex material refs/CRC/dirty are +4/+64/+68; texture refs are 16-bit +4.
// RET 12 at RVA 0x0096F5A7 ends before six INT3 bytes at 0x0096F5AA.
#include "w3d_file.h"
#include "wwstring.h"
#include "shader.h"
#include "vector.h"

class VertexMaterialClass {
public:
    virtual void Delete_This();
    void Add_Ref() { ++RefCount; }
    unsigned long Get_CRC() const {
        if (CRCDirty) {
            CRC = Compute_CRC();
            CRCDirty = false;
        }
        return CRC;
    }
private:
    int RefCount;
    unsigned char beforeCRC[0x64 - 8];
    mutable unsigned long CRC;
    mutable bool CRCDirty;
    unsigned long Compute_CRC() const;
};

class TextureClass {
public:
    void Add_Ref() {
        ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
    }
    void Release_Ref();
};

class BfmeHandleCX {
public:
    TextureClass *p;
    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) {
        if (p) p->Add_Ref();
    }
    ~BfmeHandleCX() {
        if (p) p->Release_Ref();
    }
    BfmeHandleCX &operator=(const BfmeHandleCX &other) {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
    StringClass Get_Texture_Name() const;
    bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
    bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }
};

class MeshLoadContextClass {
    struct LegacyMaterialClass {
        StringClass Name;
        int VertexMaterialIdx;
        int ShaderIdx;
        int TextureIdx;
        LegacyMaterialClass() : VertexMaterialIdx(0), ShaderIdx(0), TextureIdx(0) {}
    };
    unsigned char beforeLegacyMaterials[0x94];
    DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
    DynamicVectorClass<ShaderClass> Shaders;
    DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
    DynamicVectorClass<unsigned long> VertexMaterialCrcs;
    DynamicVectorClass<BfmeHandleCX> Textures;

    int Add_Shader(ShaderClass shader) {
        int index = Shaders.Count();
        Shaders.Add(shader);
        return index;
    }
    int Add_Vertex_Material(VertexMaterialClass *vmat) {
        vmat->Add_Ref();
        int index = VertexMaterials.Count();
        VertexMaterials.Add(vmat);
        return index;
    }
    int Add_Texture(const BfmeHandleCX &tex) {
        int index = Textures.Count();
        Textures.Add(tex);
        return index;
    }
    void Add_Legacy_Material(ShaderClass, VertexMaterialClass *, const BfmeHandleCX &);
};

void MeshLoadContextClass::Add_Legacy_Material(ShaderClass shader,VertexMaterialClass * vmat,const BfmeHandleCX &tex)
{
	// create a new legacy material
	LegacyMaterialClass * mat = new LegacyMaterialClass;

	// add the shader if it is unique
	for (int si=0; si<Shaders.Count(); si++) {
		if (Shaders[si] == shader) break;
	}
	if (si == Shaders.Count()) {
		mat->ShaderIdx = Add_Shader(shader);
	} else {
		mat->ShaderIdx = si;
	}

	// add the vertex material if it is unique
	if (vmat == NULL) {
		mat->VertexMaterialIdx = -1;
	} else {
		unsigned long crc = vmat->Get_CRC();
		for (int vi=0; vi<VertexMaterialCrcs.Count(); vi++) {
			if (VertexMaterialCrcs[vi] == crc) break;
		}
		if (vi == VertexMaterials.Count()) {
			mat->VertexMaterialIdx = Add_Vertex_Material(vmat);
			VertexMaterialCrcs.Add(crc);
			WWASSERT(VertexMaterialCrcs.Count() == VertexMaterials.Count());
		} else {
			mat->VertexMaterialIdx = vi;
		}
	}

	// add the texture if it is unique
	if (tex.p == NULL) {
		mat->TextureIdx = -1;
	} else {
		for (int ti=0; ti<Textures.Count(); ti++) {
			if (Textures[ti] == tex) break;
			if (_strcmpi(Textures[ti].Get_Texture_Name(),tex.Get_Texture_Name()) == 0) break;
		}
		if (ti == Textures.Count()) {
			mat->TextureIdx = Add_Texture(tex);
		} else {
			mat->TextureIdx = ti;
		}
	}

	LegacyMaterials.Add(mat);
}

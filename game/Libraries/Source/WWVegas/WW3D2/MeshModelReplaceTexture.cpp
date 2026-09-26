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
// BFME MeshModelClass::Replace_Texture: 0x0094F300, complete 334 bytes.
// GeneralsMD meshmdl.cpp supplies the traversal over texture stages/passes,
// polygon assignments and renderer categories. BFME takes two const owning
// handle references and releases temporary handles after comparisons.
// The old MatrixMapper coordinate label on this byte dump was incorrect:
// there are no coordinate calculations; this body walks mesh material and
// renderer state. RET 8 at 0x0094F44B ends before two INT3 padding bytes.
#include "multilist.h"

class VertexMaterialClass;

class TextureClass {
public:
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
    void Release_Ref();
};

class BfmeHandleCX {
public:
    TextureClass *p;

    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) {
        if (p) {
            p->Add_Ref();
        }
    }
    bool operator==(const BfmeHandleCX &other) const { return p==other.p; }
    ~BfmeHandleCX() {
        if (p) {
            p->Release_Ref();
        }
    }
};

class MeshMatDescClass {
    int PassCount;
    unsigned char beforeMaterial[0xa4-4];
    VertexMaterialClass *Material[4];
    void *TextureArray[4][2];
    void *MaterialArray[4];
public:
    bool Has_Material_Array(int pass) const { return MaterialArray[pass] != 0; }
    VertexMaterialClass *Peek_Single_Material(int pass) const { return Material[pass]; }
    VertexMaterialClass *Peek_Material(int index,int pass) const;
    void Set_Material(int index,VertexMaterialClass *mat,int pass);
    void Set_Single_Material(VertexMaterialClass *mat,int pass);
    enum { MAX_TEX_STAGES=2 };
    int Get_Pass_Count() const { return PassCount; }
    bool Has_Texture_Array(int pass,int stage) const { return TextureArray[pass][stage] != 0; }
    void Set_Single_Texture(const BfmeHandleCX &,int,int);
    void Set_Texture(int,const BfmeHandleCX &,int,int);
};

class MeshModelClass;
class DX8FVFCategoryContainer;
class DX8TextureCategoryClass : public MultiListObjectClass {
    unsigned char fields[0x34-8];
    DX8FVFCategoryContainer *container;
public:
    DX8FVFCategoryContainer *Get_Container() { return container; }
};
class DX8PolygonRendererClass : public MultiListObjectClass {
    MeshModelClass *mmc;
    DX8TextureCategoryClass *texture_category;
public:
    DX8TextureCategoryClass *Get_Texture_Category() { return texture_category; }
};
typedef MultiListClass<DX8PolygonRendererClass> DX8PolygonRendererList;
class DX8FVFCategoryContainer {
public:
    void Change_Polygon_Renderer_Material(DX8PolygonRendererList &,VertexMaterialClass *,VertexMaterialClass *,unsigned);
    void Change_Polygon_Renderer_Texture(DX8PolygonRendererList &,const BfmeHandleCX &,const BfmeHandleCX &,unsigned,unsigned);
};
class MeshModelClass {
    unsigned char beforePolyCount[0x24];
    int PolyCount;
    int VertexCount;
    unsigned char beforeCurMatDesc[0x9c-0x2c];
    MeshMatDescClass *CurMatDesc;
    unsigned char beforeRendererList[4];
    DX8PolygonRendererList PolygonRendererList;
    int Get_Pass_Count() const { return CurMatDesc->Get_Pass_Count(); }
    int Get_Vertex_Count() const { return VertexCount; }
    bool Has_Material_Array(int pass) const { return CurMatDesc->Has_Material_Array(pass); }
    VertexMaterialClass *Peek_Material(int index,int pass) const { return CurMatDesc->Peek_Material(index,pass); }
    VertexMaterialClass *Peek_Single_Material(int pass) const { return CurMatDesc->Peek_Single_Material(pass); }
    void Set_Material(int index,VertexMaterialClass *mat,int pass) { CurMatDesc->Set_Material(index,mat,pass); }
    void Set_Single_Material(VertexMaterialClass *mat,int pass) { CurMatDesc->Set_Single_Material(mat,pass); }
    int Get_Polygon_Count() const { return PolyCount; }
    bool Has_Texture_Array(int pass,int stage) const { return CurMatDesc->Has_Texture_Array(pass,stage); }
    void Set_Texture(int index,const BfmeHandleCX &tex,int pass,int stage) { CurMatDesc->Set_Texture(index,tex,pass,stage); }
    void Set_Single_Texture(const BfmeHandleCX &tex,int pass,int stage) { CurMatDesc->Set_Single_Texture(tex,pass,stage); }
    DX8FVFCategoryContainer *Peek_FVF_Category_Container() {
        if (PolygonRendererList.Is_Empty()) return 0;
        DX8PolygonRendererClass *polygon_renderer=PolygonRendererList.Get_Head();
        DX8TextureCategoryClass *texture_category=polygon_renderer->Get_Texture_Category();
        return texture_category->Get_Container();
    }
public:
    BfmeHandleCX Get_Texture(int,int,int) const;
    BfmeHandleCX Get_Single_Texture(int,int) const;
    void Replace_Texture(const BfmeHandleCX &,const BfmeHandleCX &);
    void Replace_VertexMaterial(VertexMaterialClass *,VertexMaterialClass *);
};
void MeshModelClass::Replace_Texture(const BfmeHandleCX &texture,const BfmeHandleCX &new_texture)
{


	for (int stage=0;stage<MeshMatDescClass::MAX_TEX_STAGES;++stage) {
		for (int pass=0;pass<Get_Pass_Count();++pass) {
			if (Has_Texture_Array(pass,stage)) {
				for (int i=0;i<Get_Polygon_Count();++i) {
					if (Get_Texture(i,pass,stage)==texture) {
						Set_Texture(i,new_texture,pass,stage);
					}
				}
			}
			else {
				if (Get_Single_Texture(pass,stage)==texture) {
					Set_Single_Texture(new_texture,pass,stage);
				}
			}
			// If this mesh model has been initialized for rendering we need to tell the rendering
			// system to change texturing as well.
			DX8FVFCategoryContainer* fvf_category=Peek_FVF_Category_Container();
			if (fvf_category) {
				fvf_category->Change_Polygon_Renderer_Texture(PolygonRendererList,texture,new_texture,pass,stage);
			}
		}
	}
}


// BFME vertex-material replacement at 0x0094F450, complete 208 bytes.
// MeshClass forwards Model (+0xC8) through its entry at 0x0092C3F0. The
// original GeneralsMD material-array/single-material traversal updates
// vertex materials and the renderer categories. RET8 at 0x0094F51D ends
// immediately before the next function at 0x0094F520.
void MeshModelClass::Replace_VertexMaterial(VertexMaterialClass* vmat,VertexMaterialClass* new_vmat)
{


	
	for (int pass=0;pass<Get_Pass_Count();++pass) {
		if (Has_Material_Array(pass)) {
			for (int i=0;i<Get_Vertex_Count();++i) {
				if (Peek_Material(i,pass)==vmat) {
					Set_Material(i,new_vmat,pass);
				}
			}
		}
		else {
			if (Peek_Single_Material(pass)==vmat) {
				Set_Single_Material(new_vmat,pass);
			}
		}
		// If this mesh model has been initialized for rendering we need to tell the rendering
		// system to change texturing as well.
		DX8FVFCategoryContainer* fvf_category=Peek_FVF_Category_Container();
		if (fvf_category) {
			fvf_category->Change_Polygon_Renderer_Material(PolygonRendererList,vmat,new_vmat,pass);
		}
	}	
}


// MeshClass wrapper at 0x0092C3F0, full 11 bytes. The six-byte Model load
// and five-byte tail jump form one function. The prior placement at
// 0x0092C310 was the unrelated Get_User_Text forwarding body.
// The MeshClass entry forwards both material pointers to Model at +0xC8.
class MeshClass {
    unsigned char beforeModel[0xc8];
    MeshModelClass *Model;
public:
    void Replace_VertexMaterial(VertexMaterialClass *vmat,VertexMaterialClass *new_vmat);
};
void MeshClass::Replace_VertexMaterial(VertexMaterialClass *vmat,VertexMaterialClass *new_vmat)
{
    Model->Replace_VertexMaterial(vmat,new_vmat);
}

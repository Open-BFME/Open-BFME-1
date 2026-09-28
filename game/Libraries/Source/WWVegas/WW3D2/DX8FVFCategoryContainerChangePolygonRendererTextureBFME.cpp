// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/Wwutil /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "../WWLib/multilist.h"

class TextureClass
{
public:
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
    void Release_Ref();
};

class BfmeHandleCX
{
public:
    TextureClass *p;
    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) { if (p) p->Add_Ref(); }
    ~BfmeHandleCX() { if (p) p->Release_Ref(); }
    BfmeHandleCX &operator=(const BfmeHandleCX &other)
    {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p=other.p;
        return *this;
    }
    operator TextureClass *() const { return p; }
    bool operator==(const BfmeHandleCX &other) const { return p==other.p; }
};

inline bool operator==(TextureClass *left,const BfmeHandleCX &right)
{
    return left==right.p;
}

class Gen_00945490
{
public:
    BfmeHandleCX bfmeGet(int stage) const throw();
};

class VertexMaterialClass
{
    unsigned char pad[0x64];
    unsigned long CRC;
    bool CRCDirty;
public:
    unsigned long Get_CRC() const;
};

class ShaderClass
{
public:
    unsigned ShaderBits;
    ShaderClass(const ShaderClass &other) : ShaderBits(other.ShaderBits) {}
};

class DX8PolygonRendererClass;
class DX8FVFCategoryContainer;
class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
    DX8TextureCategoryClass(int,TextureClass **,ShaderClass,VertexMaterialClass *,DX8FVFCategoryContainer *);
    DX8TextureCategoryClass(DX8FVFCategoryContainer *,TextureClass **,ShaderClass,VertexMaterialClass *,int);
    ShaderClass Get_Shader() const { return shader; }
    const VertexMaterialClass *Peek_Material() const { return material; }
    DX8FVFCategoryContainer *Get_Container() { return container; }
    void Remove_Polygon_Renderer(DX8PolygonRendererClass *);
    void Add_Polygon_Renderer(DX8PolygonRendererClass *);
private:
    DX8FVFCategoryContainer *container;
    TextureClass *textures[2];
    ShaderClass shader;
    VertexMaterialClass *material;
    MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
    unsigned pass;
    void *render_task_head;
};

class DX8PolygonRendererClass : public MultiListObjectClass
{
    void *mesh_model;
    DX8TextureCategoryClass *texture_category;
public:
    DX8TextureCategoryClass *Get_Texture_Category() { return texture_category; }
    void Set_Texture_Category(DX8TextureCategoryClass *category) { texture_category=category; }
};

typedef MultiListClass<DX8TextureCategoryClass> TextureCategoryList;
typedef MultiListIterator<DX8TextureCategoryClass> TextureCategoryListIterator;
typedef MultiListClass<DX8PolygonRendererClass> DX8PolygonRendererList;
typedef MultiListIterator<DX8PolygonRendererClass> DX8PolygonRendererListIterator;

class PolyRemover : public MultiListObjectClass
{
public:
    DX8TextureCategoryClass *src;
    DX8TextureCategoryClass *dest;
    DX8PolygonRendererClass *pr;
};
class TextureTrackerClass : public MultiListObjectClass {};
typedef MultiListClass<TextureTrackerClass> PolyRemoverList;
typedef MultiListIterator<TextureTrackerClass> PolyRemoverListIterator;

class DX8FVFCategoryContainer : public MultiListObjectClass
{
protected:
    TextureCategoryList texture_category_list[4];
    TextureCategoryList visible_texture_category_list[4];
    void *visible_matpass_head;
    void *visible_matpass_tail;
    void *index_buffer;
    int used_indices;
    void *unknown_D8;
    unsigned unknown_DC;
    unsigned FVF;
    unsigned passes;
    unsigned uv_coordinate_channels;
    bool sorting;
    bool AnythingToRender;
    bool AnyDelayedPassesToRender;
    DX8TextureCategoryClass *Find_Matching_Texture_Category(
        const BfmeHandleCX &,unsigned,unsigned,DX8TextureCategoryClass *);
public:
    void Remove_Texture_Category(DX8TextureCategoryClass *);
    void Change_Polygon_Renderer_Texture(
        DX8PolygonRendererList &,const BfmeHandleCX &,const BfmeHandleCX &,unsigned,unsigned);
};

class DX8MeshRendererClass
{
    unsigned char before_delete_list[0x1c];
public:
    MultiListClass<DX8TextureCategoryClass> texture_category_delete_list;
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

inline void DX8TextureCategoryClass::Remove_Polygon_Renderer(
    DX8PolygonRendererClass *p_renderer)
{
    PolygonRendererList.Remove(p_renderer);
    p_renderer->Set_Texture_Category(0);
    if (PolygonRendererList.Peek_Head()==0) {
        DX8FVFCategoryContainer *owner=*reinterpret_cast<DX8FVFCategoryContainer **>(
            reinterpret_cast<char *>(this)+0x34);
        owner->Remove_Texture_Category(this);
        DX8MeshRendererClass *renderer=TheDX8MeshRenderer;
        if (renderer)
            renderer->texture_category_delete_list.Add_Tail(this);
    }
}

inline void DX8TextureCategoryClass::Add_Polygon_Renderer(
    DX8PolygonRendererClass *p_renderer)
{
    PolygonRendererList.Add(p_renderer);
    p_renderer->Set_Texture_Category(this);
}

void DX8FVFCategoryContainer::Change_Polygon_Renderer_Texture(
    DX8PolygonRendererList &polygon_renderer_list,
    const BfmeHandleCX &texture,
    const BfmeHandleCX &new_texture,
    unsigned pass,
    unsigned stage)
{
    PolyRemoverList prl;
    bool foundtexture=false;
    if (texture==new_texture) return;
    TextureCategoryListIterator src_it(&texture_category_list[pass]);
    while (!src_it.Is_Done()) {
        DX8TextureCategoryClass *src_tex_category=src_it.Peek_Obj();
        if (reinterpret_cast<const Gen_00945490 *>(src_tex_category)->bfmeGet(stage)==texture) {
            foundtexture=true;
            DX8PolygonRendererListIterator poly_it(&polygon_renderer_list);
            while (!poly_it.Is_Done()) {
                DX8PolygonRendererClass *polygon_renderer=poly_it.Peek_Obj();
                DX8TextureCategoryClass *prc=polygon_renderer->Get_Texture_Category();
                if (prc==src_tex_category) {
                    DX8TextureCategoryClass *dest_tex_category=Find_Matching_Texture_Category(new_texture,pass,stage,src_tex_category);
                    if (!dest_tex_category) {
                        BfmeHandleCX tmp_textures[2];
                        for (int s=0;s<2;++s) tmp_textures[s]=reinterpret_cast<const Gen_00945490 *>(src_tex_category)->bfmeGet(s);
                        tmp_textures[stage]=new_texture;
                        DX8TextureCategoryClass *new_tex_category=new DX8TextureCategoryClass(
                            this,reinterpret_cast<TextureClass **>(tmp_textures),src_tex_category->Get_Shader(),
                            const_cast<VertexMaterialClass *>(src_tex_category->Peek_Material()),pass);
                        bool found_similar_category=false;
                        TextureCategoryListIterator tex_it(&texture_category_list[pass]);
                        while (!tex_it.Is_Done()) {
                            if (reinterpret_cast<const Gen_00945490 *>(tex_it.Peek_Obj())->bfmeGet(0)==tmp_textures[0]) {
                                texture_category_list[pass].Add_After(new_tex_category,tex_it.Peek_Obj());
                                found_similar_category=true;
                                break;
                            }
                            tex_it.Next();
                        }
                        if (!found_similar_category) texture_category_list[pass].Add_Tail(new_tex_category);
                        dest_tex_category=new_tex_category;
                    }
                    PolyRemover *rem=new PolyRemover;
                    rem->src=src_tex_category;
                    rem->dest=dest_tex_category;
                    rem->pr=polygon_renderer;
                    prl.Add(reinterpret_cast<TextureTrackerClass *>(rem));
                }
                poly_it.Next();
            }
        } else if (foundtexture) break;
        src_it.Next();
    }
    PolyRemoverListIterator prli(&prl);
    while (!prli.Is_Done()) {
        PolyRemover *rem=reinterpret_cast<PolyRemover *>(prli.Peek_Obj());
        rem->src->Remove_Polygon_Renderer(rem->pr);
        rem->dest->Add_Polygon_Renderer(rem->pr);
        prli.Remove_Current_Object();
        delete rem;
    }
}

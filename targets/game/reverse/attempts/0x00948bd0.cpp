// ?Render@DX8TextureCategoryClass@@QAEXXZ
// partial score=0.9918125999545144 date=2026-09-25
// ?Render@DX8TextureCategoryClass@@QAEXXZ
// BFME RVA 0x00948BD0, 4397 bytes: decoded through RET at 0x00949CFC;
// INT3 begins at 0x00949CFD. The internal branch target 0x009498A0 is not a start.

// Identity: matched DX8RigidFVFCategoryContainer::Render at 0x00949EA0 calls
// this body; the source-level task loop and category layout agree.
// Rebuilt from the ZH dx8renderer.cpp Render body, reconciled to retail.

// Compared using tools/probe.py: ours=4397, retail=4397, 36 differing bytes.
// Remaining differences are the sorted-render argument preparation at +0x683
// through +0x6CA, its join jump at +0x6D3, and the task reload at +0xFD9..+0xFE9.
// All 14 exception states and all other operations are reproduced.

// Important BFME differences kept here:
// - owning BfmeHandleCX texture accessor and BoxSetTexture reference argument;
// - snapshot state-name temporaries, supplied by including ww3d.h before dx8wrapper.h;
// - skin transform uses the pointer pair at mesh +0x314 and an inverse transform;
// - virtual scalar returns at +0x1A4 and +0x1D4 are full integers;
// - a separate bool stage comparison retains retail's sete/test sequence;
// - texture-stage device slot is +0x10C, not the shared D3D interface's +0x118;
// - task pool contains a lock at +0x10, absent from the shared ZH ObjectPoolClass.

// Mesh and mapper views retain address-derived names for unproved virtual identities.
// The category and math classes use the existing headers. A declaration-only
// polygon Render is necessary because retail calls 0x0092CB30 out of line.
// No compiler-generated helper bytes are included in the claimed body extent.
// cl: /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /FAsc /Fabuild/Rva00948BD0RenderScratch.cod /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#include "wwstring.h"
#define MUTEX_H
#include "ww3d.h"
#include "dx8renderer.h"
#include "matrix3d.h"
#include "sphere.h"
#include "sortingrenderer.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class BfmeHandleCX {
public:
    TextureClass *p;
    ~BfmeHandleCX() { if(p) p->Release_Ref(); }
    operator TextureBaseClass *&() { return (TextureBaseClass*&)p; }
};
class Gen_00945490 {
public: BfmeHandleCX bfmeGet(int stage) const throw();
};
extern void BoxSetTexture(unsigned stage,TextureBaseClass *&texture);

class Rva00948BD0Model {
public:
    char pad00[0x18]; int field18;
    int Get_Flag(int mask) const { return field18 & mask; }
};
class Rva00948BD0Mesh;
struct Rva00948BD0Field314 { Rva00948BD0Mesh *field00; };
class Rva00948BD0Mesh : public RefCountClass {
public:
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50() const;
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual float slot60() const;
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7c();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8c();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9c();
    virtual void slota0();
    virtual void slota4();
    virtual void slota8();
    virtual void slotac();
    virtual void slotb0();
    virtual void slotb4();
    virtual void slotb8();
    virtual void slotbc();
    virtual void slotc0();
    virtual void slotc4();
    virtual void slotc8();
    virtual void slotcc();
    virtual void slotd0();
    virtual void slotd4();
    virtual void slotd8();
    virtual void slotdc();
    virtual void slote0();
    virtual void slote4();
    virtual void slote8();
    virtual void slotec();
    virtual void slotf0();
    virtual void slotf4();
    virtual void slotf8();
    virtual void slotfc();
    virtual const SphereClass &slot100() const;
    virtual void slot104();
    virtual void slot108();
    virtual void slot10c();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11c();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12c();
    virtual void slot130();
    virtual void slot134();
    virtual void slot138();
    virtual void slot13c();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14c();
    virtual void slot150();
    virtual void slot154();
    virtual void *slot158() const;
    virtual void slot15c();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16c();
    virtual void slot170();
    virtual void slot174();
    virtual void slot178();
    virtual void slot17c();
    virtual void slot180();
    virtual void slot184();
    virtual void slot188();
    virtual void slot18c();
    virtual void slot190();
    virtual void slot194();
    virtual void slot198();
    virtual void slot19c();
    virtual void slot1a0();
    virtual int slot1a4() const;
    virtual void slot1a8();
    virtual void slot1ac();
    virtual void slot1b0();
    virtual void slot1b4();
    virtual void slot1b8();
    virtual void slot1bc();
    virtual void slot1c0();
    virtual void slot1c4();
    virtual void slot1c8();
    virtual void slot1cc();
    virtual void slot1d0();
    virtual int slot1d4() const;
    const Matrix3D &Get_Transform() const { slot50(); return *(const Matrix3D*)((const char*)this+0x18); }
    bool Is_Transform_Identity() const { slot50(); return *(const bool*)((const char*)this+0x7c); }
    float Get_ObjectScale() const { return *(const float*)((const char*)this+0x48); }
    int Get_Base_Vertex_Offset() const { return *(const int*)((const char*)this+0x304); }
    LightEnvironmentClass *Get_Lighting_Environment() const { return *(LightEnvironmentClass*const*)((const char*)this+0xcc); }
    Rva00948BD0Model *Peek_Model() const { return *(Rva00948BD0Model*const*)((const char*)this+0xc8); }
    float Get_Alpha_Override() const {
        if(slot60()>0.0f) return slot60();
        return *(const float*)((const char*)this+0x2f8);
    }
    Rva00948BD0Field314 *Field314() const { return *(Rva00948BD0Field314*const*)((const char*)this+0x314); }

};
class Rva00948BD0Mapper {
public:
    virtual void slot00(); virtual void slot04(); virtual int slot08() const;
    char pad04[0x14-4]; Vector2 field14; Vector2 field1c; unsigned field24;
};
struct Rva00948BD0MaterialOverride { int tag; Vector2 field04; };
static __forceinline void Rva00948BD0SetIndexBaseOffset(unsigned offset)
{
    RenderStateStruct *state = (RenderStateStruct *)0x01340EC0;
    if (state->index_base_offset == offset) return;
    unsigned changed = *(unsigned *)0x0133F49C;
    changed |= 0x00020000;
    state->index_base_offset = (unsigned short)offset;
    *(unsigned *)0x0133F49C = changed;
}
class DX8PolygonRendererClass : public MultiListObjectClass {
public:
    void Render(int);
    MeshModelClass *mmc; DX8TextureCategoryClass *category; unsigned field10; unsigned field14; unsigned field18; unsigned field1c; unsigned field20;
    void Render_Sorted(int base,const SphereClass &sphere) {
        Rva00948BD0SetIndexBaseOffset(base);
        SortingRendererClass::Insert_Triangles(sphere,field10,field18/3,field1c,field20);
    }
};
struct Rva00948BD0Pool {
    void *head; void *blocks; int freeCount; int totalCount; FastCriticalSectionClass mutex;
    void Free(void *p) {
        FastCriticalSectionClass::LockClass lock(mutex);
        *(void**)p=head; head=p; ++freeCount;
    }
};
extern Rva00948BD0Pool Rva0134B128Pool;
class PolyRenderTaskClass {
public:
    DX8PolygonRendererClass *Renderer;
    Rva00948BD0Mesh *Mesh;
    PolyRenderTaskClass *NextVisible;
    ~PolyRenderTaskClass() { Mesh->Release_Ref(); }
    DX8PolygonRendererClass *Peek_Polygon_Renderer() { return Renderer; }
    Rva00948BD0Mesh *Peek_Mesh() { return Mesh; }
    PolyRenderTaskClass *Get_Next_Visible() { return NextVisible; }
    void Set_Next_Visible(PolyRenderTaskClass *v) { NextVisible=v; }
    static void operator delete(void *p) { Rva0134B128Pool.Free(p); }
};
class Rva00948BD0DX8 : public DX8Wrapper {
public: static unsigned GetStage(unsigned stage,unsigned state) { return TextureStageStates[stage][state]; }
    static __forceinline void SetStage(unsigned stage,D3DTEXTURESTAGESTATETYPE state,unsigned value) {
        if(TextureStageStates[stage][state]==value) return;
        if(WW3D::Is_Snapshot_Activated()) {
            StringClass value_name(0,true);
            Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value);
        }
        TextureStageStates[stage][state]=value;
        typedef HRESULT (__stdcall *SetStageFunc)(IDirect3DDevice8*,DWORD,D3DTEXTURESTAGESTATETYPE,DWORD);
        IDirect3DDevice8 *device=_Get_D3D_Device8();
        ((SetStageFunc*)*(void**)device)[0x10c/4](device,stage,state,value);
        ++number_of_DX8_calls;
        ++texture_stage_state_changes;
    }
};

void DX8TextureCategoryClass::Render()
{
    for(unsigned stage=0; stage<2; ++stage)
        BoxSetTexture(stage, ((const Gen_00945490*)this)->bfmeGet(stage));
    VertexMaterialClass *vmaterial=(VertexMaterialClass*)Peek_Material();
    DX8Wrapper::Set_Material(vmaterial);
    ShaderClass theShader=Get_Shader();
    DX8Wrapper::Set_Shader(theShader);
    if(m_gForceMultiply && theShader.Get_Dst_Blend_Func()==ShaderClass::DSTBLEND_ZERO) {
        theShader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_SRC_COLOR);
        theShader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_ZERO);
        DX8Wrapper::Set_Shader(theShader);
        DX8Wrapper::Apply_Render_State_Changes();
        DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND,D3DBLEND_DESTCOLOR);
    }
    bool renderTasksRemaining=false;
    PolyRenderTaskClass *prt=render_task_head;
    PolyRenderTaskClass *last_prt=0;
    while(prt) {
        DX8PolygonRendererClass *renderer=prt->Peek_Polygon_Renderer();
        Rva00948BD0Mesh *mesh=prt->Peek_Mesh();
        if(mesh->Get_Base_Vertex_Offset()==0xffff) {
            last_prt=prt; prt=prt->Get_Next_Visible(); renderTasksRemaining=true; continue;
        }
        LightEnvironmentClass *lenv=mesh->Get_Lighting_Environment();
        if(lenv) DX8Wrapper::Set_Light_Environment(lenv);
        const Matrix3D *world_transform=&mesh->Get_Transform();
        bool identity=mesh->Is_Transform_Identity();
        Matrix3D tmp_world;
        if(mesh->Peek_Model()->Get_Flag(0x200)) {
            Vector3 mesh_position;
            Vector3 camera_z_vector;
            DX8MeshRendererClass *globalRenderer=*(DX8MeshRendererClass**)&TheDX8MeshRenderer;
            ((Rva00948BD0Mesh*)globalRenderer->Peek_Camera())->Get_Transform().Get_Z_Vector(&camera_z_vector);
            mesh->Get_Transform().Get_Translation(&mesh_position);
            tmp_world.Obj_Look_At(mesh_position,mesh_position+camera_z_vector,0.0f);
            world_transform=&tmp_world;
        } else if(mesh->Peek_Model()->Get_Flag(0x800)) {
            Vector3 mesh_position;
            Vector3 camera_position;
            DX8MeshRendererClass *globalRenderer=*(DX8MeshRendererClass**)&TheDX8MeshRenderer;
            ((Rva00948BD0Mesh*)globalRenderer->Peek_Camera())->Get_Transform().Get_Translation(&camera_position);
            mesh->Get_Transform().Get_Translation(&mesh_position);
            tmp_world.Obj_Look_At(mesh_position,camera_position,0.0f);
            world_transform=&tmp_world;
        } else if(mesh->Peek_Model()->Get_Flag(0x400)) {
            if(mesh->Field314() && mesh->Field314()->field00) {
                Matrix3D inverse;
                mesh->Field314()->field00->Get_Transform().Get_Inverse(inverse);
                Matrix3D::Multiply(mesh->Get_Transform(),inverse,&tmp_world);
                world_transform=&tmp_world;
                identity=false;
            } else identity=true;
        }
        if(identity) DX8Wrapper::Set_World_Identity();
        else DX8Wrapper::Set_Transform(D3DTS_WORLD,*world_transform);
        if(mesh->Get_ObjectScale()!=1.0f)
            DX8Wrapper::Set_DX8_Render_State(D3DRS_NORMALIZENORMALS,TRUE);
        if((mesh->Peek_Model()->Get_Flag(0x10)) && WW3D::Is_Sorting_Enabled()) {
            renderer->Render_Sorted(mesh->Get_Base_Vertex_Offset(),mesh->slot100());
        } else {
            if(mesh->Get_Alpha_Override()!=1.0 || (mesh->slot158() && *(int*)mesh->slot158()==0x1234567)) {
                Vector2 oldUVOffset;
                unsigned oldUVOffsetSyncTime=0;
                Rva00948BD0Mapper *oldMapper=*(Rva00948BD0Mapper**)((char*)vmaterial+0x20);
                if(mesh->slot158() && *(int*)mesh->slot158()==0x1234567 && oldMapper && oldMapper->slot08()==1) {
                    Rva00948BD0MaterialOverride *matOverride=(Rva00948BD0MaterialOverride*)mesh->slot158();
                    oldUVOffsetSyncTime=oldMapper->field24;
                    oldMapper->field24=WW3D::Get_Sync_Time();
                    oldUVOffset=oldMapper->field14;
                    oldMapper->field14=matOverride->field04;
                } else oldMapper=0;
                if(mesh->Get_Alpha_Override()!=1.0) {
                    ShaderClass theAlphaShader=theShader;
                    theAlphaShader.Set_Src_Blend_Func(ShaderClass::SRCBLEND_SRC_ALPHA);
                    theAlphaShader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA);
                    if(mesh->slot1d4()) theAlphaShader.Set_Dst_Blend_Func(ShaderClass::DSTBLEND_ONE);
                    bool field1a4=mesh->slot1a4()!=0;
                    float alpha=mesh->Get_Alpha_Override();
                    if(field1a4 && alpha<0.5f) theAlphaShader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
                    DX8Wrapper::Set_Shader(theAlphaShader);
                    DX8Wrapper::Apply_Render_State_Changes();
                    bool stageFlag=Rva00948BD0DX8::GetStage(1,D3DTSS_ALPHAOP)==D3DTOP_MODULATE;
                    if(stageFlag!=false) {
                        Rva00948BD0DX8::SetStage(0,D3DTSS_ALPHAARG1,D3DTA_TFACTOR);
                        Rva00948BD0DX8::SetStage(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
                    } else {
                        Rva00948BD0DX8::SetStage(1,D3DTSS_ALPHAARG1,D3DTA_CURRENT);
                        Rva00948BD0DX8::SetStage(1,D3DTSS_ALPHAARG2,D3DTA_TFACTOR);
                        Rva00948BD0DX8::SetStage(1,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
                        if(Rva00948BD0DX8::GetStage(1,D3DTSS_COLOROP)==D3DTOP_DISABLE) {
                            Rva00948BD0DX8::SetStage(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
                            Rva00948BD0DX8::SetStage(1,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
                        }
                    }
                    DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,((int)(255.0f*alpha))<<24);
                    DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAREF,(int)(96.0f*alpha));
                    renderer->Render(mesh->Get_Base_Vertex_Offset());
                    DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHAREF,0x60);
                    DX8Wrapper::Set_Shader(theShader);
                    ShaderClass::Invalidate();
                } else renderer->Render(mesh->Get_Base_Vertex_Offset());
                if(oldMapper) {
                    oldMapper->field24=oldUVOffsetSyncTime;
                    oldMapper->field14=oldUVOffset;
                }
                DX8Wrapper::Set_Material(0);
                DX8Wrapper::Set_Material(vmaterial);
                _ReadWriteBarrier();
            } else renderer->Render(mesh->Get_Base_Vertex_Offset());
        }
        if(mesh->Get_ObjectScale()!=1.0f)
            DX8Wrapper::Set_DX8_Render_State(D3DRS_NORMALIZENORMALS,FALSE);
        PolyRenderTaskClass *next_prt=prt->Get_Next_Visible();
        if(last_prt==0) render_task_head=next_prt;
        else last_prt->Set_Next_Visible(next_prt);
        delete prt;
        prt=next_prt;
    }
    if(!renderTasksRemaining) Clear_Render_List();
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /I.
// ?setup@WaterShader007A7240@@QAEXPAD@Z -- BFME RVA 0x007A7240 (2263 bytes).
// Flat-water shader setup: the BFME form of Zero Hour's
// WaterRenderObjClass::setupFlatWaterShader (W3DWater.cpp), with the settings
// pointer on the stack as in the matched siblings 0x007A6460 and 0x007A6AA0
// (the same caller, drawTrapezoidWater at 0x007A8FF0, reaches all three).
// Identity is not proven beyond the Zero Hour twin, so the name keeps the
// address like the siblings do. ret 4; 0x15C-byte frame; one EH state for the
// shroud TextureHandle and seven for the snapshot value-name strings.
// ww3d.h comes first: it defines MESH_RENDER_SNAPSHOT_ENABLED, which is what
// puts the StringClass temporaries retail shows into the inline
// DX8Wrapper::Set_Shader and Set_DX8_Texture_Stage_State bodies.
#define private public
#define protected public
#include "game/Libraries/Source/WWVegas/WW3D2/ww3d.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#undef protected
#undef private
#include <string.h>

class ShroudFilter {};
class ShroudTexture { public: ShroudFilter *getFilter(); };
class Gen_00920a60 { public: void m(int); };
void BoxSetTexture(unsigned, TextureBaseClass *&);

struct BfmeObjRB;

// Counted texture handle returned by W3DShroud::getShroudTexture (0x006D2630).
class TextureHandle
{
public:
	~TextureHandle() { if (m_p) m_p->Release_Ref(); }
	TextureBaseClass *m_p;
};

class W3DShroud { public: TextureHandle getShroudTexture(void); };

// BaseHeightMapRenderObjClass keeps its W3DShroud at +0x30B8
// (BaseHeightMapConstructor.cpp).
class BfmeTerrainRenderObject
{
public:
	W3DShroud *getShroud(void) { return m_shroud; }
	char m_pad[0x30B8];
	W3DShroud *m_shroud;			// +0x30B8
};
extern BfmeTerrainRenderObject *TheTerrainRenderObject;

// Retail reaches W3DShaderManager's texture-slot and shader setters through
// their ILT thunks 0x0003F427 (-> 0x006D25E0) and 0x0003FD82 (-> 0x00716980),
// which the ledger already pins under these names.
void bfmeOneRB(int stage, BfmeObjRB *texture);
void bfmeTwoRB(int shader, int pass);
static inline void setShaderTexture(int stage, const TextureHandle &texture) {
    bfmeOneRB(stage,(BfmeObjRB *)&texture);
}

struct WaterMatrix007A7240 { float m[16]; };
inline WaterMatrix007A7240 operator*(const WaterMatrix007A7240 &a, const WaterMatrix007A7240 &b) {
    WaterMatrix007A7240 r; D3DXMatrixMultiply((D3DXMATRIX *)&r,(const D3DXMATRIX *)&a,(const D3DXMATRIX *)&b); return r;
}
// Device interface view: retail virtual slots established by the actual indirect calls.
struct WaterShaderDevice007A7240 {
    virtual void __stdcall slot000() = 0;
    virtual void __stdcall slot001() = 0;
    virtual void __stdcall slot002() = 0;
    virtual void __stdcall slot003() = 0;
    virtual void __stdcall slot004() = 0;
    virtual void __stdcall slot005() = 0;
    virtual void __stdcall slot006() = 0;
    virtual void __stdcall slot007() = 0;
    virtual void __stdcall slot008() = 0;
    virtual void __stdcall slot009() = 0;
    virtual void __stdcall slot010() = 0;
    virtual void __stdcall slot011() = 0;
    virtual void __stdcall slot012() = 0;
    virtual void __stdcall slot013() = 0;
    virtual void __stdcall slot014() = 0;
    virtual void __stdcall slot015() = 0;
    virtual void __stdcall slot016() = 0;
    virtual void __stdcall slot017() = 0;
    virtual void __stdcall slot018() = 0;
    virtual void __stdcall slot019() = 0;
    virtual void __stdcall slot020() = 0;
    virtual void __stdcall slot021() = 0;
    virtual void __stdcall slot022() = 0;
    virtual void __stdcall slot023() = 0;
    virtual void __stdcall slot024() = 0;
    virtual void __stdcall slot025() = 0;
    virtual void __stdcall slot026() = 0;
    virtual void __stdcall slot027() = 0;
    virtual void __stdcall slot028() = 0;
    virtual void __stdcall slot029() = 0;
    virtual void __stdcall slot030() = 0;
    virtual void __stdcall slot031() = 0;
    virtual void __stdcall slot032() = 0;
    virtual void __stdcall slot033() = 0;
    virtual void __stdcall slot034() = 0;
    virtual void __stdcall slot035() = 0;
    virtual void __stdcall slot036() = 0;
    virtual void __stdcall slot037() = 0;
    virtual void __stdcall slot038() = 0;
    virtual void __stdcall slot039() = 0;
    virtual void __stdcall slot040() = 0;
    virtual void __stdcall slot041() = 0;
    virtual void __stdcall slot042() = 0;
    virtual void __stdcall slot043() = 0;
    virtual long __stdcall SetTransform(unsigned,const WaterMatrix007A7240 *) = 0;
    virtual long __stdcall GetTransform(unsigned,WaterMatrix007A7240 *) = 0;
    virtual void __stdcall slot046() = 0;
    virtual void __stdcall slot047() = 0;
    virtual void __stdcall slot048() = 0;
    virtual void __stdcall slot049() = 0;
    virtual void __stdcall slot050() = 0;
    virtual void __stdcall slot051() = 0;
    virtual void __stdcall slot052() = 0;
    virtual void __stdcall slot053() = 0;
    virtual void __stdcall slot054() = 0;
    virtual void __stdcall slot055() = 0;
    virtual void __stdcall slot056() = 0;
    virtual long __stdcall SetRenderState(unsigned,unsigned) = 0;
    virtual void __stdcall slot058() = 0;
    virtual void __stdcall slot059() = 0;
    virtual void __stdcall slot060() = 0;
    virtual void __stdcall slot061() = 0;
    virtual void __stdcall slot062() = 0;
    virtual void __stdcall slot063() = 0;
    virtual void __stdcall slot064() = 0;
    virtual long __stdcall SetTexture(unsigned,IDirect3DBaseTexture8 *) = 0;
    virtual void __stdcall slot066() = 0;
    virtual long __stdcall SetTextureStageState(unsigned,unsigned long,unsigned) = 0;
    virtual void __stdcall slot068() = 0;
    virtual long __stdcall SetSamplerState(unsigned,unsigned long,unsigned) = 0;
    virtual void __stdcall slot070() = 0;
    virtual void __stdcall slot071() = 0;
    virtual void __stdcall slot072() = 0;
    virtual void __stdcall slot073() = 0;
    virtual void __stdcall slot074() = 0;
    virtual void __stdcall slot075() = 0;
    virtual void __stdcall slot076() = 0;
    virtual void __stdcall slot077() = 0;
    virtual void __stdcall slot078() = 0;
    virtual void __stdcall slot079() = 0;
    virtual void __stdcall slot080() = 0;
    virtual void __stdcall slot081() = 0;
    virtual void __stdcall slot082() = 0;
    virtual void __stdcall slot083() = 0;
    virtual void __stdcall slot084() = 0;
    virtual void __stdcall slot085() = 0;
    virtual void __stdcall slot086() = 0;
    virtual void __stdcall slot087() = 0;
    virtual void __stdcall slot088() = 0;
    virtual void __stdcall slot089() = 0;
    virtual void __stdcall slot090() = 0;
    virtual void __stdcall slot091() = 0;
    virtual void __stdcall slot092() = 0;
    virtual void __stdcall slot093() = 0;
    virtual void __stdcall slot094() = 0;
    virtual void __stdcall slot095() = 0;
    virtual void __stdcall slot096() = 0;
    virtual void __stdcall slot097() = 0;
    virtual void __stdcall slot098() = 0;
    virtual void __stdcall slot099() = 0;
    virtual void __stdcall slot100() = 0;
    virtual void __stdcall slot101() = 0;
    virtual void __stdcall slot102() = 0;
    virtual void __stdcall slot103() = 0;
    virtual void __stdcall slot104() = 0;
    virtual void __stdcall slot105() = 0;
    virtual void __stdcall slot106() = 0;
    virtual long __stdcall SetPixelShader(unsigned) = 0;
    virtual void __stdcall slot108() = 0;
    virtual long __stdcall SetPixelShaderConstant(unsigned,const void *,unsigned) = 0;
};
static inline WaterShaderDevice007A7240 *waterDevice() { return (WaterShaderDevice007A7240 *)DX8Wrapper::_Get_D3D_Device8(); }
static inline void addressState(unsigned stage, unsigned long state, unsigned value) {
    waterDevice()->SetSamplerState(stage,state,value);
    ++number_of_DX8_calls; ++DX8Wrapper::texture_stage_state_changes;
}
// DX8Wrapper::Set_DX8_Texture_Stage_State as dx8wrapper.h writes it, snapshot
// branch included, but calling through the device view: BFME's device puts
// SetTextureStageState at +0x10C, where the shim's IDirect3DDevice8 has +0x118.
static __forceinline void stageState(unsigned stage, D3DTEXTURESTAGESTATETYPE state, unsigned value) {
    if (stage >= MAX_TEXTURE_STAGES) {
        waterDevice()->SetTextureStageState(stage,state,value); ++number_of_DX8_calls;
        return;
    }
    if (DX8Wrapper::TextureStageStates[stage][(unsigned int)state]==value) return;
    if (WW3D::Is_Snapshot_Activated()) {
        StringClass value_name(0,true);
        DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value);
    }
    DX8Wrapper::TextureStageStates[stage][(unsigned int)state]=value;
    waterDevice()->SetTextureStageState(stage,state,value); ++number_of_DX8_calls;
    ++DX8Wrapper::texture_stage_state_changes;
}
static __forceinline void pixelConstant(int reg,const void *data) {
    if(memcmp(data,&DX8Wrapper::Pixel_Shader_Constants[reg],16)==0) return;
    memcpy(&DX8Wrapper::Pixel_Shader_Constants[reg],data,16);
    waterDevice()->SetPixelShaderConstant(reg,data,1); ++number_of_DX8_calls;
}
class WaterShader007A7240 { public: void setup(char *settings); };
void WaterShader007A7240::setup(char *settings) {
    BoxSetTexture(0,*(TextureBaseClass **)(settings+0x24));
    if(!*(bool *)(settings+0x3c)) DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);
    else DX8Wrapper::Set_Shader(ShaderClass::_PresetAdditiveShader);
    VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::Set_Material(vmat);
    REF_PTR_RELEASE(vmat);
    *(int *)((char *)((ShroudTexture *)(settings+0x24))->getFilter()+4)=2;
    *(int *)((ShroudTexture *)(settings+0x24))->getFilter()=2;
    ((Gen_00920a60 *)((ShroudTexture *)(settings+0x24))->getFilter())->m(2);
    DX8Wrapper::Apply_Render_State_Changes();
    if(*(unsigned *)((char *)this+0x2b8)) {
        if(TheTerrainRenderObject->getShroud()) {
            setShaderTexture(0,TheTerrainRenderObject->getShroud()->getShroudTexture());
            bfmeTwoRB(5,3);
            waterDevice()->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
        } else {
            WaterShaderDevice007A7240 *white=waterDevice();
            white->SetTexture(3,((TextureBaseClass *)((char *)this+0x2a8))->Peek_D3D_Base_Texture());
        }
    }
    stageState(0,(D3DTEXTURESTAGESTATETYPE)4,7);
    stageState(0,(D3DTEXTURESTAGESTATETYPE)11,0);
    stageState(1,(D3DTEXTURESTAGESTATETYPE)11,0);
    if(*(unsigned *)((char *)this+0x2b8)) {
        waterDevice()->SetTexture(1,((TextureBaseClass *)(settings+0x30))->Peek_D3D_Base_Texture());
        waterDevice()->SetTexture(2,((TextureBaseClass *)(settings+0x28))->Peek_D3D_Base_Texture());
        addressState(1,1,1); addressState(1,2,1);
        addressState(2,1,1); addressState(2,2,1);
        stageState(2,(D3DTEXTURESTAGESTATETYPE)11,0x20000);
        stageState(2,(D3DTEXTURESTAGESTATETYPE)24,2);
        WaterMatrix007A7240 inv; float det; WaterMatrix007A7240 curView;
        waterDevice()->GetTransform(2,&curView); ++number_of_DX8_calls;
        D3DXMatrixInverse((D3DXMATRIX *)&inv,&det,(D3DXMATRIX *)&curView);
        WaterMatrix007A7240 scale;
        D3DXMatrixScaling((D3DXMATRIX *)&scale,0.0625f,0.0625f,1.0f);
        WaterMatrix007A7240 destMatrix=inv*scale;
        D3DXMatrixTranslation((D3DXMATRIX *)&scale,*(float *)(settings+0x5c),*(float *)(settings+0x5c),0);
        destMatrix=destMatrix*scale;
        ++DX8Wrapper::matrix_changes;
        waterDevice()->SetTransform(18,&destMatrix); ++number_of_DX8_calls;
    } else {
        stageState(1,(D3DTEXTURESTAGESTATETYPE)1,1);
        stageState(1,(D3DTEXTURESTAGESTATETYPE)4,1);
    }
    WaterShaderDevice007A7240 *dev=waterDevice();
    dev->SetSamplerState(0,6,2); dev->SetSamplerState(0,5,2);
    dev->SetSamplerState(1,6,2); dev->SetSamplerState(1,5,2);
    dev->SetSamplerState(2,6,2); dev->SetSamplerState(2,5,2);
    if(*(unsigned *)((char *)this+0x2b8)) {
        { float c0[4]={0.1f,0.1f,0.1f,1.0f}; pixelConstant(0,c0); }
        waterDevice()->SetPixelShader(*(unsigned *)((char *)this+0x2b8));
    }
}

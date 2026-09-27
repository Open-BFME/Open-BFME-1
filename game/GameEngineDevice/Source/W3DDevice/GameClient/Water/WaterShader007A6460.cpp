// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /I.
// BFME RVA 0x007A6460. Whole-body reconstruction from retail and ZH setupJbaWaterShader.
// BFME adds one settings pointer; ret 4. No EH, 0x154-byte local frame.
#define private public
#define protected public
#include "game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#undef protected
#undef private
#include <string.h>

class ShroudFilter {};
class ShroudTexture { public: ShroudFilter *getFilter(); };
class Gen_00920a60 { public: void m(int); };
void BaseHeightMapScorchSetShader(const ShaderClass &);

struct WaterMatrix007A6460 { float m[16]; };
inline WaterMatrix007A6460 operator*(const WaterMatrix007A6460 &a, const WaterMatrix007A6460 &b) {
    WaterMatrix007A6460 r; D3DXMatrixMultiply((D3DXMATRIX *)&r,(const D3DXMATRIX *)&a,(const D3DXMATRIX *)&b); return r;
}
// Device interface view: retail virtual slots established by the actual indirect calls.
struct WaterShaderDevice007A6460 {
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
    virtual long __stdcall SetTransform(unsigned,const WaterMatrix007A6460 *) = 0;
    virtual long __stdcall GetTransform(unsigned,WaterMatrix007A6460 *) = 0;
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
    virtual void __stdcall slot057() = 0;
    virtual void __stdcall slot058() = 0;
    virtual void __stdcall slot059() = 0;
    virtual void __stdcall slot060() = 0;
    virtual void __stdcall slot061() = 0;
    virtual void __stdcall slot062() = 0;
    virtual void __stdcall slot063() = 0;
    virtual void __stdcall slot064() = 0;
    virtual long __stdcall SetTexture(unsigned,IDirect3DBaseTexture8 *) = 0;
    virtual void __stdcall slot066() = 0;
    virtual void __stdcall slot067() = 0;
    virtual void __stdcall slot068() = 0;
    virtual long __stdcall SetTextureStageState(unsigned,unsigned long,unsigned) = 0;
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
static inline WaterShaderDevice007A6460 *waterDevice() { return (WaterShaderDevice007A6460 *)DX8Wrapper::_Get_D3D_Device8(); }
static inline void addressState(unsigned stage, unsigned long state, unsigned value) {
    waterDevice()->SetTextureStageState(stage,state,value);
    ++number_of_DX8_calls; ++DX8Wrapper::texture_stage_state_changes;
}
static __forceinline void pixelConstant(int reg,const void *data) {
    if(memcmp(data,&DX8Wrapper::Pixel_Shader_Constants[reg],16)==0) return;
    memcpy(&DX8Wrapper::Pixel_Shader_Constants[reg],data,16);
    waterDevice()->SetPixelShaderConstant(reg,data,1); ++number_of_DX8_calls;
}
class WaterShader007A6460 { public: void setup(char *settings); };
void WaterShader007A6460::setup(char *settings) {
    if(!*(bool *)(settings+0x3c)) BaseHeightMapScorchSetShader(ShaderClass::_PresetAlphaShader);
    else BaseHeightMapScorchSetShader(ShaderClass::_PresetAdditiveShader);
    VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::Set_Material(vmat);
    REF_PTR_RELEASE(vmat);
    *(int *)((char *)((ShroudTexture *)(settings+0x24))->getFilter()+4)=2;
    *(int *)((ShroudTexture *)(settings+0x24))->getFilter()=2;
    ((Gen_00920a60 *)((ShroudTexture *)(settings+0x24))->getFilter())->m(2);
    DX8Wrapper::Apply_Render_State_Changes();
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)4,7);
    waterDevice()->SetTexture(3,((TextureBaseClass *)(settings+0x2c))->Peek_D3D_Base_Texture());
    addressState(3,1,1); addressState(3,2,1);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)11,0);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)11,0);
    DX8Wrapper::Set_DX8_Texture_Stage_State(3,(D3DTEXTURESTAGESTATETYPE)11,1);
    if(*(unsigned *)((char *)this+0x2b4)) {
        waterDevice()->SetTexture(1,((TextureBaseClass *)(settings+0x30))->Peek_D3D_Base_Texture());
        waterDevice()->SetTexture(2,((TextureBaseClass *)(settings+0x28))->Peek_D3D_Base_Texture());
        addressState(1,1,1); addressState(1,2,1);
        addressState(2,1,1); addressState(2,2,1);
        DX8Wrapper::Set_DX8_Texture_Stage_State(2,(D3DTEXTURESTAGESTATETYPE)11,0x20000);
        DX8Wrapper::Set_DX8_Texture_Stage_State(2,(D3DTEXTURESTAGESTATETYPE)24,2);
        WaterMatrix007A6460 inv; float det; WaterMatrix007A6460 curView;
        waterDevice()->GetTransform(2,&curView); ++number_of_DX8_calls;
        D3DXMatrixInverse((D3DXMATRIX *)&inv,&det,(D3DXMATRIX *)&curView);
        WaterMatrix007A6460 scale;
        D3DXMatrixScaling((D3DXMATRIX *)&scale,0.0625f,0.0625f,1.0f);
        WaterMatrix007A6460 destMatrix=inv*scale;
        D3DXMatrixTranslation((D3DXMATRIX *)&scale,*(float *)(settings+0x5c),*(float *)(settings+0x5c),0);
        destMatrix=destMatrix*scale;
        ++DX8Wrapper::matrix_changes;
        waterDevice()->SetTransform(18,&destMatrix); ++number_of_DX8_calls;
    }
    WaterShaderDevice007A6460 *dev=waterDevice();
    dev->SetTextureStageState(0,6,2); dev->SetTextureStageState(0,5,2);
    dev->SetTextureStageState(1,6,2); dev->SetTextureStageState(1,5,2);
    dev->SetTextureStageState(2,6,2); dev->SetTextureStageState(2,5,2);
    dev->SetTextureStageState(3,6,2); dev->SetTextureStageState(3,5,2);
    if(*(unsigned *)((char *)this+0x2b4)) {
        { float c0[4]={0.1f,0.1f,0.1f,1.0f}; pixelConstant(0,c0); }
        { float c1[4]={0,0,0,*(float *)(settings+0x60)}; pixelConstant(1,c1); }
        waterDevice()->SetPixelShader(*(unsigned *)((char *)this+0x2b4));
    }
}


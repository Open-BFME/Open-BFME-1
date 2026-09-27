// ?setup@WaterShader007A6AA0@@QAEXPAD@Z
// partial score=0.989060489060489 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /I.
// BFME RVA 0x007A6AA0 (1554 bytes): complete fixed-function bump-water setup.
// Retail has a settings pointer on the stack; ret 4; no EH; 0x190-byte local frame.
#define private public
#define protected public
#include "game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#undef protected
#undef private
#include <string.h>

void BaseHeightMapScorchSetShader(const ShaderClass &);

struct WaterMatrix007A6AA0 { float m[16]; };
inline WaterMatrix007A6AA0 operator*(const WaterMatrix007A6AA0 &a, const WaterMatrix007A6AA0 &b) {
    WaterMatrix007A6AA0 r; D3DXMatrixMultiply((D3DXMATRIX *)&r,(const D3DXMATRIX *)&a,(const D3DXMATRIX *)&b); return r;
}
// Device interface view: retail virtual slots established by the actual indirect calls.
struct WaterShaderDevice007A6AA0 {
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
    virtual long __stdcall SetTransform(unsigned,const WaterMatrix007A6AA0 *) = 0;
    virtual long __stdcall GetTransform(unsigned,WaterMatrix007A6AA0 *) = 0;
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
static inline WaterShaderDevice007A6AA0 *waterDevice() { return (WaterShaderDevice007A6AA0 *)DX8Wrapper::_Get_D3D_Device8(); }
static inline void addressState(unsigned stage, unsigned long state, unsigned value) {
    waterDevice()->SetTextureStageState(stage,state,value);
    ++number_of_DX8_calls; ++DX8Wrapper::texture_stage_state_changes;
}
#include <math.h>
// Address-derived names preserve the actual mutable global accesses.
// VA 0x01306D84 (RVA 0x00F06D84): wrapped phase; VA 0x012BBBE4: bump scale.
extern float WaterPhase01306D84;
extern float WaterBumpScale012BBBE4;
void BoxSetTexture(unsigned, TextureBaseClass *&);
static inline unsigned floatBits(const float f) { return *(const unsigned *)&f; }
class WaterShader007A6AA0 { public: void setup(char *settings); };
void WaterShader007A6AA0::setup(char *settings) {
    BaseHeightMapScorchSetShader(ShaderClass::_PresetAlphaShader);
    DX8Wrapper::Apply_Render_State_Changes();
    BoxSetTexture(0,*(TextureBaseClass **)(settings+0x34));
    BoxSetTexture(1,*(TextureBaseClass **)(settings+0x38));
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)1,22);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)2,2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)3,0);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)4,3);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)5,2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)6,1);
    addressState(0,1,1); addressState(0,2,1);
    WaterPhase01306D84=(float)fmod((double)(WaterPhase01306D84+0.0052359881810843945f),6.2831854820251465);
    float c=WWMath::Fast_Cos(WaterPhase01306D84); c*=WaterBumpScale012BBBE4;
    float s=WWMath::Fast_Sin(WaterPhase01306D84)*WaterBumpScale012BBBE4;
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)7,floatBits(c));
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)8,floatBits(-s));
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)9,floatBits(s));
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)10,floatBits(c));
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)1,2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)2,2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)3,1);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)4,2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)5,2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)6,1);
    addressState(1,1,1); addressState(1,2,1);
    DX8Wrapper::Apply_Render_State_Changes();
    waterDevice()->SetPixelShader(0);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)11,0x20000);
    DX8Wrapper::Set_DX8_Texture_Stage_State(0,(D3DTEXTURESTAGESTATETYPE)24,2);
    addressState(0,1,1); addressState(0,2,1);
    WaterMatrix007A6AA0 inv; float det; WaterMatrix007A6AA0 curView;
    waterDevice()->GetTransform(2,&curView); ++number_of_DX8_calls;
    D3DXMatrixInverse((D3DXMATRIX *)&inv,&det,(D3DXMATRIX *)&curView);
    WaterMatrix007A6AA0 scale;
    D3DXMatrixScaling((D3DXMATRIX *)&scale,0.0078125f,0.0078125f,1.0f);
    WaterMatrix007A6AA0 destMatrix=inv*scale;
    D3DXMatrixTranslation((D3DXMATRIX *)&scale,*(float *)(settings+0x5c)*-0.1,*(float *)(settings+0x5c)*0.1,0);
    destMatrix=destMatrix*scale;
    ++DX8Wrapper::matrix_changes;
    waterDevice()->SetTransform(16,&destMatrix); ++number_of_DX8_calls;
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)11,0x30000);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1,(D3DTEXTURESTAGESTATETYPE)24,2);
    addressState(1,1,1); addressState(1,2,1);
    WaterMatrix007A6AA0 bias;
    bias.m[0]=0.5f; bias.m[1]=0; bias.m[2]=0; bias.m[3]=0.5f;
    bias.m[4]=0; bias.m[5]=0.5f; bias.m[6]=0; bias.m[7]=0.5f;
    bias.m[8]=0; bias.m[9]=0; bias.m[10]=1; bias.m[11]=0;
    bias.m[12]=0; bias.m[13]=0; bias.m[14]=0; bias.m[15]=1;
    ++DX8Wrapper::matrix_changes;
    waterDevice()->SetTransform(17,&bias); ++number_of_DX8_calls;
}


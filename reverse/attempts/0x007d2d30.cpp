// ?postRender@Rva007D3580@@UAE_NHIAA_NPAUCoord2D@@@Z
// partial score=0.95 date=2026-09-04
// Bank: ours927B vs retail924B; 254/254 instruction mnemonics and46/46 x87 operations agree.
// Remaining frame164 vs160 and stack-slot allocation cause3 extra displacement bytes.
// Required relocation: vector constructor iterator ??_H@YGXPAXIHP6EPAX0@Z@Z must resolve thunk RVA0x0000AE5C.
// Default Vertex ctor pointer retail VA0x00425978 -> RVA0x007D2300 (no authored Vertex ctor claim).
// cl: /DNDEBUG /MD
// Retail0x007D2D30, vtable0x01128A2C slot3 installed by Rva007D3580.
// ZH ScreenBWFilterDOT3 postRender is the semantic twin; BFME passes dimensions as arg4.
struct Coord2D{float x,y;};
struct Vec4{float x,y,z,w;Vec4(){} Vec4(float a,float b,float c,float d):x(a),y(b),z(c),w(d){}};
struct Vertex{Vec4 p;unsigned color;float u,v;Vertex();};
struct Device;
struct DeviceVtable{char p0[0x104];long (__stdcall*SetTexture)(Device*,unsigned,void*);char p1[0x14c-0x108];long (__stdcall*DrawPrimitiveUP)(Device*,unsigned,unsigned,const void*,unsigned);char p2[0x164-0x150];long (__stdcall*SetVertexShader)(Device*,unsigned);};
struct Device{DeviceVtable*v;};
extern Device *HighlightDevice;
class View{public:
virtual void pad0();
virtual void pad1();
virtual void pad2();
virtual void pad3();
virtual void pad4();
virtual void pad5();
virtual void pad6();
virtual void pad7();
virtual void pad8();
virtual void pad9();
virtual void pad10();
virtual void pad11();
virtual void pad12();
virtual void pad13();
virtual void pad14();
virtual int getWidth();virtual void pad16();virtual int getHeight();virtual void pad18();virtual void getOrigin(int*,int*);};
extern View *Dot3View;
struct Caps{char pad[0x272];bool dot3;};extern Caps *Dot3Caps;
extern float ZoomFadeValue;
class ShaderClass{public:unsigned bits;ShaderClass(const ShaderClass&s){bits=s.bits;} };extern ShaderClass Dot3AlphaShader;
extern bool ScreenShaderDirty;
void BaseHeightMapScorchSetShader(const ShaderClass&);
class DX8Wrapper{public:static void Set_DX8_Render_State(unsigned long,unsigned);static void Set_DX8_Texture_Stage_State(unsigned,unsigned long,unsigned);static void Apply_Render_State_Changes();};
void*bfmeEndRenderToTexture();
class Rva007D3580{public:virtual int init();virtual int shutdown();virtual int pre();virtual bool postRender(int,unsigned,bool&,Coord2D*);virtual int setup();virtual int set(int);virtual void reset();};
bool Rva007D3580::postRender(int mode,unsigned unused,bool&extra,Coord2D*dims){
 void*tex=bfmeEndRenderToTexture();if(!tex)return false;if(!set(mode))return false;
 Device*dev=HighlightDevice;Vertex v[4];int xpos,ypos,width,height;
 Dot3View->getOrigin(&xpos,&ypos);width=Dot3View->getWidth();height=Dot3View->getHeight();

 v[0].p=Vec4(xpos+width-0.5f,ypos+height-0.5f,0,1);v[0].u=(float)(xpos+width)/dims->x;v[0].v=(float)(ypos+height)/dims->y;
 v[1].p=Vec4(xpos+width-0.5f,ypos-0.5f,0,1);v[1].u=(float)(xpos+width)/dims->x;v[1].v=(float)ypos/dims->y;
 v[2].p=Vec4(xpos-0.5f,ypos+height-0.5f,0,1);v[2].u=(float)xpos/dims->x;v[2].v=(float)(ypos+height)/dims->y;
 v[3].p=Vec4(xpos-0.5f,ypos-0.5f,0,1);v[3].u=(float)xpos/dims->x;v[3].v=(float)ypos/dims->y;
 unsigned color=((int)((1.0f-ZoomFadeValue)*255.0f)<<24)|0xffffff;
 v[0].color=color;v[1].color=color;v[2].color=color;v[3].color=color;
 dev->v->SetVertexShader(dev,0x144);
 if(Dot3Caps->dot3){
 DX8Wrapper::Set_DX8_Render_State(60,0x80a5ca8e);
 DX8Wrapper::Set_DX8_Texture_Stage_State(0,26,35);DX8Wrapper::Set_DX8_Texture_Stage_State(0,2,2);DX8Wrapper::Set_DX8_Texture_Stage_State(0,3,35);DX8Wrapper::Set_DX8_Texture_Stage_State(0,1,25);DX8Wrapper::Set_DX8_Texture_Stage_State(1,2,1);DX8Wrapper::Set_DX8_Texture_Stage_State(1,3,3);DX8Wrapper::Set_DX8_Texture_Stage_State(1,1,24);
 }else{DX8Wrapper::Set_DX8_Render_State(60,0x60606060);DX8Wrapper::Set_DX8_Texture_Stage_State(0,2,2);DX8Wrapper::Set_DX8_Texture_Stage_State(0,3,3);DX8Wrapper::Set_DX8_Texture_Stage_State(0,1,4);}
 HighlightDevice->v->SetTexture(HighlightDevice,0,tex);dev->v->DrawPrimitiveUP(dev,5,2,v,sizeof(Vertex));
 ScreenShaderDirty=true;ShaderClass shader=Dot3AlphaShader;shader.bits|=7;BaseHeightMapScorchSetShader(shader);DX8Wrapper::Apply_Render_State_Changes();DX8Wrapper::Set_DX8_Texture_Stage_State(0,4,3);dev->v->DrawPrimitiveUP(dev,5,2,v,sizeof(Vertex));reset();return true;
}






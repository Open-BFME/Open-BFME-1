// cl: /Igame /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// stlport
#include <new>
#define _OPERATOR_NEW_DEFINED_
#define Matrix4x4 Matrix4
#include "WW3D2/camera.h"
#include "WW3D2/w3derr.h"
// The matched BFME scene renderer returns bool.
#define WW3DErrorType bool
#include "WW3D2/ww3d.h"
#undef WW3DErrorType
#include "GameEngine/Include/GameClient/Display.h"
// Retail 0x00789BF0 / 492B: vtable 0x01126CCC slot 2 via ILT 0x00033CAD.
// Owner established by the matched Rva00789900Init constructor; camera/scene
// slots +0x10/+0x0c agree with its landed rva00789980 initializer.
// Display must use the BFME header: getWidth/getHeight are slots +0x2c/+0x30.
class Rva00789900Init {
public:
 virtual ~Rva00789900Init();
 virtual void rva00789980();
 virtual void renderViewport00789BF0(int x,int y,int width,int height);
 unsigned m_04,m_08;
 SceneClass *m_scene;
 CameraClass *m_camera;
 bool m_14;
 RenderObjClass *m_18;
 int m_1c;
};
void Rva00789900Init::renderViewport00789BF0(int x,int y,int width,int height)
{
 float w=(float)width;
 float h=(float)height;
 float dh=(float)TheDisplay->getHeight();
 float dw=(float)TheDisplay->getWidth();
 float invw=1.0f/dw;
 Vector2 lo;
 lo.X=x*invw;
 float invh=1.0f/dh;
 lo.Y=y*invh;
 Vector2 hi(lo.X+w*invw,lo.Y+h*invh);
 if(lo.X<0.0f) lo.X=0.0f;
 if(lo.Y<0.0f) lo.Y=0.0f;
 if(hi.X>1.0f) hi.X=1.0f;
 if(hi.Y>1.0f) hi.Y=1.0f;
 m_camera->Set_Viewport(lo,hi);
 if(m_14) m_camera->Set_Aspect_Ratio(w/h);
 if(m_18) {
  Matrix3D transform=m_18->Get_Bone_Transform(m_1c);
  m_camera->Set_Transform(transform);
 }
 WW3D::Render(m_scene,m_camera,false,false,Vector3(0,0,0));
}




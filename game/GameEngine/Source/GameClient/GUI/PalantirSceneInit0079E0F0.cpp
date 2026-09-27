// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep
// stlport
// Assigned suffix 0079E112 actually belongs to complete body 0079E0F0-0079E318.
// Asset set ABI follows AssetListOperatorInsert. Literal palantir and final
// create-window call prove initialization behavior; owner name remains opaque.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include "vector3.h"
struct Rva001408C0Target;
typedef Rva001408C0Target *AssetKey0079E0F0;
typedef _STL::set<AssetKey0079E0F0,_STL::less<AssetKey0079E0F0>,_STL::allocator<AssetKey0079E0F0> > AssetSet0079E0F0;
void *bfmeGoEMEb(void *);
void Rva009EBB20(int);
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
struct AssetList0079E0F0 {
 AssetSet0079E0F0 prototypes; unsigned field_c;bool changed;
 AssetList0079E0F0():field_c(0),changed(true){}
 void insert(const char *s){if(prototypes.insert((AssetKey0079E0F0)bfmeGoEMEb((void*)s)).second)changed=true;}
};
class RenderObjClass {public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void slot3c();
 virtual void slot40();virtual void slot44();virtual void slot48();virtual void slot4c();virtual void slot50();
 virtual void Set_Transform(const Matrix3D &);
};
RenderObjClass *Create_Render_Obj(const char *);
// Allocation footprint and vtable call slots witnessed directly in the body.
class SimpleSceneClass {public:
 SimpleSceneClass();
 virtual void handle();virtual void slot04();virtual void Add_Render_Object(RenderObjClass *);
 virtual void slot0c();virtual void slot10();virtual void slot14();virtual void Set_Ambient_Light(const Vector3 &);
 char footprint04[0x104];
};
class Rva0079D030 :public SimpleSceneClass {public: Rva0079D030(){} virtual void handle();};
class CameraClass {public:
 CameraClass();void Set_Clip_Planes(float,float);void Set_View_Plane(float,float);void Set_Aspect_Ratio(float);
 char footprint00[0x3c0];
};
class Rva00596970 {public: void create();};
class PalantirSceneInit0079E0F0 {public:
 char pad00[0x510];Rva0079D030 *scene510;CameraClass *camera514;RenderObjClass *object518;
 void initialize();
};
void PalantirSceneInit0079E0F0::initialize(){
 if(Rva0134FAA0){
  AssetList0079E0F0 assets;
  assets.insert("palantir");
  Rva009EBB20((int)&assets);
 }
 object518=Create_Render_Obj("palantir");
 Matrix3D identity(true);
 object518->Set_Transform(identity);
 scene510=new Rva0079D030;
 scene510->Set_Ambient_Light(Vector3(0,0,0));
 scene510->Add_Render_Object(object518);
 camera514=new CameraClass;
 camera514->Set_Clip_Planes(0.1f,5000.0f);
 camera514->Set_View_Plane(0.87266463f,-1.0f);
 camera514->Set_Aspect_Ratio(1.0f);
 ((Rva00596970*)this)->create();
}


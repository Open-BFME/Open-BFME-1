// ??0SimpleSceneClass@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Include
#include "../WWLib/bittype.h"
#define WWDEBUG_H
#define MEMPOOL_H
template <class T, int N> class AutoPoolClass {};
#define WWDEBUG_SAY(x)
#define WWDEBUG_WARNING(x)
#include "../WWLib/multilist.h"
#include "../WWLib/refcount.h"
#include "../WWMath/vector3.h"
#include "rendobj.h"
typedef RefMultiListClass<RenderObjClass> RefRenderObjListClass;
typedef MultiListClass<RenderObjClass> NonRefRenderObjListClass;

class RenderInfoClass;
class SceneIterator;
class CameraClass;
class ChunkSaveClass;
class ChunkLoadClass;

class SceneClass : public RefCountClass
{
public:
    SceneClass()
        : AmbientLight(0.5f, 0.5f, 0.5f), PolyRenderMode(2),
          ExtraPassPolyRenderMode(0), FogEnabled(false),
          FogColor(0.0f, 0.0f, 0.0f), FogStart(0.0f), FogEnd(1000.0f)
    {
    }
    virtual ~SceneClass();
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);
    virtual SceneIterator *Create_Iterator(bool onlyvisible) = 0;
    virtual void Destroy_Iterator(SceneIterator *it) = 0;
    virtual void Set_Ambient_Light(const Vector3 &color);
    virtual const Vector3 &Get_Ambient_Light();
    virtual void Set_Fog_Enable(bool set);
    virtual bool Get_Fog_Enable();
    virtual void Set_Fog_Color(const Vector3 &color);
    virtual const Vector3 &Get_Fog_Color();
    virtual void Set_Fog_Range(float start, float end);
    virtual void Get_Fog_Range(float *start, float *end);
    // scene.h RegType. Only the parameter type reaches the mangled name
    // (W4RegType@SceneClass@@); retail's switch has five cases, upstream three.
    enum RegType
    {
        ON_FRAME_UPDATE = 0,
        LIGHT,
        RELEASE,
    };
    virtual void Register(RenderObjClass *obj, RegType for_what) = 0;
    virtual void Unregister(RenderObjClass *obj, RegType for_what) = 0;
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    // BFME adds three pure virtuals that upstream scene.h lacks. Retail
    // SceneClass's vftable (0x0113CEC8) holds _purecall (0x00C8C500) at slots
    // 17/18/19, between Compute_Point_Visibility and Save; SimpleSceneClass's
    // (0x0113CF48) overrides them with 0x009197C2 / 0x009448C0 / 0x009448D0.
    // Bodies and identities unproven, so the slots stay named by position.
    virtual void Slot17(void) = 0;
    virtual void Slot18(void) = 0;
    virtual void Slot19(void) = 0;
    virtual void Save(ChunkSaveClass &save);
    virtual void Load(ChunkLoadClass &load);
protected:
    // protected virtual in retail: ?Render@SceneClass@@MAEXAAVRenderInfoClass@@@Z
    virtual void Render(RenderInfoClass &info);
public:
    Vector3 AmbientLight;
    int PolyRenderMode;
    int ExtraPassPolyRenderMode;
    bool FogEnabled;
    Vector3 FogColor;
    float FogStart;
    float FogEnd;
    virtual void Customized_Render(RenderInfoClass &info) = 0;
    virtual void Pre_Render_Processing(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
};

struct Rva00943FF0Bounds { float v[6]; };
struct BfmeSceneVectorElement;
struct Gen_00943CF0_Node;
struct Gen_uw_0002e866;
class BfmeSceneVector
{
public:
    BfmeSceneVector();
    void clear(Gen_uw_0002e866 *objects);
    void process(Gen_00943CF0_Node **objects);
    void Set_Level(unsigned int level);
    void rva00943FF0(const Rva00943FF0Bounds &bounds);
private:
    Rva00943FF0Bounds bounds;
    BfmeSceneVectorElement *vector;
    int vector_max;
    float scale;
    unsigned int level_mask;
};

class SimpleSceneClass : public SceneClass
{
public:
    SimpleSceneClass();
    virtual ~SimpleSceneClass();
    // BFME drift, the same one scene.h already records on SceneClass::Get_Scene_ID:
    // retail's SimpleSceneClass vftable ends at slot 27 (Remove_All_Render_Objects,
    // Visibility_Check), so Get_Scene_ID occupies no slot.
    int Get_Scene_ID();
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);
    virtual void Remove_All_Render_Objects();
    virtual void Register(RenderObjClass *obj, RegType for_what);
    virtual void Unregister(RenderObjClass *obj, RegType for_what);
    virtual SceneIterator *Create_Iterator(bool onlyvisible);
    virtual void Destroy_Iterator(SceneIterator *it);
    virtual void Visibility_Check(CameraClass *camera);
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
private:
    BfmeSceneVector scene_vector;
    RefRenderObjListClass list_5c;
    RefRenderObjListClass list_74;
    RefRenderObjListClass list_8c;
    RefRenderObjListClass list_a4;
    NonRefRenderObjListClass list_bc;
    NonRefRenderObjListClass list_d4;
    RefRenderObjListClass list_ec;
    int m_104;
protected:
    // Both overrides are protected virtual in retail (MAEX): Customized_Render
    // is 0x00943AD0, Post_Render_Processing 0x00943C60 (vtable slot 25).
    virtual void Customized_Render(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
};

SimpleSceneClass::SimpleSceneClass() : SceneClass(), m_104(1) {}

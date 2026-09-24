// ??0SimpleSceneClass@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
#include "../WWLib/bittype.h"
#define WWDEBUG_H
#define MEMPOOL_H
template <class T, int N> class AutoPoolClass {};
#define WWDEBUG_SAY(x)
#define WWDEBUG_WARNING(x)
#include "../WWLib/multilist.h"

class RenderObjClass { public: void Release_Ref(); };
typedef RefMultiListClass<RenderObjClass> RefRenderObjListClass;
typedef MultiListClass<RenderObjClass> NonRefRenderObjListClass;

class RefCountClass
{
public:
    RefCountClass() : NumRefs(1) {}
    virtual ~RefCountClass();
    int NumRefs;
};

class RenderInfoClass;
class SceneIterator;
class CameraClass;
class ChunkSaveClass;
class ChunkLoadClass;
struct Vector3
{
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    float x, y, z;
};

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
    virtual void Register(RenderObjClass *obj, int type) = 0;
    virtual void Unregister(RenderObjClass *obj, int type) = 0;
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    virtual void Save(ChunkSaveClass &save);
    virtual void Load(ChunkLoadClass &load);
    virtual void Render(RenderInfoClass &info);
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
    virtual int Get_Scene_ID();
    virtual void Add_Render_Object(RenderObjClass *obj);
    virtual void Remove_Render_Object(RenderObjClass *obj);
    virtual void Remove_All_Render_Objects();
    virtual void Register(RenderObjClass *obj, int type);
    virtual void Unregister(RenderObjClass *obj, int type);
    virtual SceneIterator *Create_Iterator(bool onlyvisible);
    virtual void Destroy_Iterator(SceneIterator *it);
    virtual void Visibility_Check(CameraClass *camera);
    virtual float Compute_Point_Visibility(RenderInfoClass &info, const Vector3 &point);
    virtual void Customized_Render(RenderInfoClass &info);
    virtual void Post_Render_Processing(RenderInfoClass &info);
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
};

SimpleSceneClass::SimpleSceneClass() : SceneClass(), m_104(1) {}

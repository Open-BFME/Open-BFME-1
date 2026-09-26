// cl: /EHsc
// The compiler emits this anonymous cleanup body for a two-base destructor.
// The retail boundary at 0x00C19748 has no recoverable parent identity; this
// helper keeps that identity anonymous while preserving the MSVC 7.1
// multiple-inheritance cleanup shape.

struct Gen_uwm_0003873f {
    virtual void f() = 0;
    ~Gen_uwm_0003873f();
};

struct AIPathfindUnwindBase {
    virtual void f() = 0;
    ~AIPathfindUnwindBase();
};

struct AIPathfindUnwindObject : AIPathfindUnwindBase, Gen_uwm_0003873f {
    ~AIPathfindUnwindObject();
};

extern void ai_pathfind_unwind_ext();

// ??1AIPathfindUnwindObject@@QAE@XZ absent-from-retail
AIPathfindUnwindObject::~AIPathfindUnwindObject()
{
    ai_pathfind_unwind_ext();
}

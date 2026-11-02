// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem {

class RenderObjectUpdateModuleTemplate
{
public:
    // ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@H@Z absent-from-retail
    // Forcer-only constructor: compiling it installs the vftable, which emits
    // the deleting destructor here without a copy of the matched destructor.
    explicit RenderObjectUpdateModuleTemplate(int) {}
    virtual ~RenderObjectUpdateModuleTemplate();
};

// The scalar destructor remains ledger-backed by
// RenderObjectUpdateModuleTemplateDestructorThunk.cpp; this definition emits
// the compiler-owned deleting destructor at the vtable slot.

// The complete destructor is a matched row in another unit; a second strong
// definition here duplicated it.
// ?forceRenderObjectUpdateModuleTemplateDeletingDestructor@FXParticleSystem@@YAXXZ absent-from-retail
void forceRenderObjectUpdateModuleTemplateDeletingDestructor()
{
    RenderObjectUpdateModuleTemplate value(0);
}
}

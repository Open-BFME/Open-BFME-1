// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem {

class RenderObjectUpdateModuleTemplate
{
public:
    __declspec(noinline) virtual ~RenderObjectUpdateModuleTemplate();
};

// The scalar destructor remains ledger-backed by
// RenderObjectUpdateModuleTemplateDestructorThunk.cpp; this definition emits
// the compiler-owned deleting destructor at the vtable slot.
RenderObjectUpdateModuleTemplate::~RenderObjectUpdateModuleTemplate()
{
}

}

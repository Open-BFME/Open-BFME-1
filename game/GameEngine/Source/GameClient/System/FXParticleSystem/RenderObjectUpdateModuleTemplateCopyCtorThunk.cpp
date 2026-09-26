// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift RenderObjectUpdateModuleTemplate copy-ctor __emit thunk to
// clean C++. Retail shape: the primary base subobject spans +0..+7 and itself
// has two polymorphic bases (vtables at +0 and +4); a second direct base sits
// at +8 and is copy constructed through the null-preserving src+8 adjustment
// idiom. The nested +4 vtable store sinks to the end of the ctor, after the
// direct subobject vtable stores. /EHs- because retail has no unwind frame.

class ROUMT_VtblBaseA
{
public:
    virtual ~ROUMT_VtblBaseA();
};

class ROUMT_VtblBaseB
{
public:
    virtual ~ROUMT_VtblBaseB();
};

class ROUMT_CopyBase : public ROUMT_VtblBaseA, public ROUMT_VtblBaseB
{
public:
    ROUMT_CopyBase(const ROUMT_CopyBase &);
    virtual ~ROUMT_CopyBase();
};

class ROUMT_OffsetBase
{
public:
    ROUMT_OffsetBase(const ROUMT_OffsetBase &);
    virtual ~ROUMT_OffsetBase();
};

namespace FXParticleSystem
{

class RenderObjectUpdateModuleTemplate : public ROUMT_CopyBase, public ROUMT_OffsetBase
{
public:
    RenderObjectUpdateModuleTemplate(const RenderObjectUpdateModuleTemplate &);
};

// ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectUpdateModuleTemplate::RenderObjectUpdateModuleTemplate(const RenderObjectUpdateModuleTemplate &that)
    : ROUMT_CopyBase(that), ROUMT_OffsetBase(that)
{
}

}

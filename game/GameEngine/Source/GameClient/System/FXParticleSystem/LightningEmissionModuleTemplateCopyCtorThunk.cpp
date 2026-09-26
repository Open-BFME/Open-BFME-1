// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift LightningEmissionModuleTemplate copy-ctor naked __emit to
// clean C++. Retail inlines CategoryModuleTemplate dual-vtable setup then
// calls LightningEmissionInfo copy for the +8 subobject (null-preserving
// src+8). /EHs- because retail has no unwind frame.

class LEMT_VtblBaseA
{
public:
    virtual ~LEMT_VtblBaseA();
};

class LEMT_VtblBaseB
{
public:
    virtual ~LEMT_VtblBaseB();
};

// Inline empty copy so MSVC emits intermediate dual-base vtable stores rather
// than an external call into CategoryModuleTemplate.
class LEMT_CategoryBase : public LEMT_VtblBaseA, public LEMT_VtblBaseB
{
public:
    LEMT_CategoryBase(const LEMT_CategoryBase &) {}
    virtual ~LEMT_CategoryBase();
};

namespace FXParticleSystem
{

// Declared only: REL32 resolves to the already-matched retail copy ctor.
class LightningEmissionInfo
{
public:
    LightningEmissionInfo(const LightningEmissionInfo &);
    virtual ~LightningEmissionInfo();
};

class LightningEmissionModuleTemplate : public LEMT_CategoryBase, public LightningEmissionInfo
{
public:
    __declspec(nothrow) LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &that);
};

// ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LightningEmissionModuleTemplate::LightningEmissionModuleTemplate(const LightningEmissionModuleTemplate &that)
    : LEMT_CategoryBase(that), LightningEmissionInfo(that)
{
}

}

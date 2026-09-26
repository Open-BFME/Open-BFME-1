// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RenderObjectDrawModuleTemplate copy constructor. Retail copies
// the two-vtable category base, then the RenderObjectDrawModuleInfo subobject
// at +8 with the usual null-preserving source adjustment.

class RenderObjectDrawCategoryBaseA
{
public:
	virtual ~RenderObjectDrawCategoryBaseA();
};

class RenderObjectDrawCategoryBaseB
{
public:
	virtual ~RenderObjectDrawCategoryBaseB();
};

class RenderObjectDrawCategoryBase
	: public RenderObjectDrawCategoryBaseA,
	  public RenderObjectDrawCategoryBaseB
{
public:
	RenderObjectDrawCategoryBase(const RenderObjectDrawCategoryBase &) {}
	virtual ~RenderObjectDrawCategoryBase();
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModuleInfo(const RenderObjectDrawModuleInfo &);
	virtual ~RenderObjectDrawModuleInfo();
};

class RenderObjectDrawModuleTemplate
	: public RenderObjectDrawCategoryBase,
	  public RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModuleTemplate(const RenderObjectDrawModuleTemplate &that);
	virtual ~RenderObjectDrawModuleTemplate();
};

// ??0RenderObjectDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectDrawModuleTemplate::RenderObjectDrawModuleTemplate(
	const RenderObjectDrawModuleTemplate &that)
	: RenderObjectDrawCategoryBase(that),
	  RenderObjectDrawModuleInfo(that)
{
}

}

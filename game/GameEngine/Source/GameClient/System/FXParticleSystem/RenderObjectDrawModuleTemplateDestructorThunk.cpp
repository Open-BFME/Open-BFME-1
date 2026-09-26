// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RenderObjectDrawModuleTemplate destructor.

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoDtorShim
{
public:
	void destroy();
};

extern "C" char RenderObjectDrawCategory_vtbl4;
extern "C" char ModuleTemplate_vtbl0;

class RenderObjectDrawTemplateBase
{
public:
	__forceinline ~RenderObjectDrawTemplateBase()
	{
		void *category = this ? (unsigned char *)this + 4 : 0;
		*(void **)category = &RenderObjectDrawCategory_vtbl4;
		*(void **)this = &ModuleTemplate_vtbl0;
	}
};

class RenderObjectDrawModuleTemplate : public RenderObjectDrawTemplateBase
{
public:
	~RenderObjectDrawModuleTemplate();
};

// ??1RenderObjectDrawModuleTemplate@FXParticleSystem@@UAE@XZ
RenderObjectDrawModuleTemplate::~RenderObjectDrawModuleTemplate()
{
	void *info = this ? (unsigned char *)this + 8 : 0;
	((RenderObjectDrawModuleInfoDtorShim *)info)->destroy();
}

}

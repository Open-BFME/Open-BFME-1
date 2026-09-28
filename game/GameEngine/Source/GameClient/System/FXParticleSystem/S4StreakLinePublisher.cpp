// cl: /EHsc
//
// Retail 0x005F4FF0 is a no-argument constructor.  It saves the incoming this
// pointer in esi and returns it in eax, and its EH state covers only the new
// expression.  The owner name below remains address-derived because no named
// caller identifies the enclosing class.
//
// The relocation-bearing calls do recover the work this constructor performs:
// the LightningDraw ConcreteModuleClass singleton, s4Second, the real
// StreakLineClass constructor, and StreakLineClass::Set_Texture_Mapping_Mode.
// The 0x1A0 allocation agrees with the independently matched StreakLineClass
// layout, while the final argument is the canonical TILED_TEXTURE_MAP value 2.

namespace FXParticleSystem
{

template <int N>
class DefaultParticleModule;

template <int N>
class DefaultParticleModuleTemplate;

class LightningDrawModule;
class LightningDrawModuleTemplate;

extern const char LIGHTNING_DRAW_MODULE_KEY[1];
extern const char LIGHTNING_DRAW_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME,
	LightningDrawModule, LightningDrawModuleTemplate,
	DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > LightningDrawTag;

template <>
class ConcreteModuleClass<LightningDrawTag>
{
public:
	static const ConcreteModuleClass<LightningDrawTag> &getInstance();
};

}

void s4Second(void);

class SegLineRendererClass
{
public:
	enum TextureMapMode
	{
		TILED_TEXTURE_MAP = 2
	};
};

// These structural declarations preserve the real primary-base conversion
// used by the store into g_rva005F4340Resource.  The sizes are the matched
// WW3D layouts: RefCountClass 0x08, MultiListObjectClass 0x08,
// RenderObjClass 0xC8, and StreakLineClass 0x1A0.
class RefCountClass
{
public:
	virtual void Delete_This();
	virtual ~RefCountClass();

	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

	void *ListNode;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
private:
	char m_retailTail[0xB8];
};

class StreakLineClass : public RenderObjClass
{
public:
	StreakLineClass();
	void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode);

private:
	char m_retailTail[0xD8];
};

typedef char S4CheckRefCountSize[(sizeof(RefCountClass) == 0x08) ? 1 : -1];
typedef char S4CheckMultiListObjectSize[(sizeof(MultiListObjectClass) == 0x08) ? 1 : -1];
typedef char S4CheckRenderObjSize[(sizeof(RenderObjClass) == 0xC8) ? 1 : -1];
typedef char S4CheckStreakLineSize[(sizeof(StreakLineClass) == 0x1A0) ? 1 : -1];

extern RefCountClass *g_rva005F4340Resource;

struct S4Publisher005F4FF0
{
	S4Publisher005F4FF0();
};

S4Publisher005F4FF0::S4Publisher005F4FF0()
{
	FXParticleSystem::ConcreteModuleClass<FXParticleSystem::LightningDrawTag>::getInstance();
	s4Second();
	StreakLineClass *line = new StreakLineClass;
	g_rva005F4340Resource = line;
	line->Set_Texture_Mapping_Mode(SegLineRendererClass::TILED_TEXTURE_MAP);
}

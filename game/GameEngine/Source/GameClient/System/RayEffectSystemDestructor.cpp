// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RayEffectSystem complete-object destructor at retail RVA 0x005D3650.

// The BFME RayEffectData array has an explicit empty destructor in the retail
// class layout.  Keeping that destructor non-trivial is what makes MSVC 7.1
// retain the __eh_vector_destructor_iterator call for the inline array.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_name[ 4 ];
};

struct RayEffectData
{
	~RayEffectData() {}

	const void *draw;
	float startLoc[ 3 ];
	float endLoc[ 3 ];
};

class RayEffectSystem : public SubsystemInterface
{
public:
	virtual ~RayEffectSystem();

private:
	RayEffectData m_effectData[ 128 ];
};

RayEffectSystem::~RayEffectSystem()
{
}

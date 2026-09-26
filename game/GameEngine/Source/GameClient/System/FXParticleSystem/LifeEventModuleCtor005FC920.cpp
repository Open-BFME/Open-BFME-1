// cl: /DNDEBUG /MD /GX /O2 /Ob2

class BfmeListCU
{
};

class BfmeLinkCU
{
public:
	BfmeListCU *m_list;
	BfmeLinkCU *m_next;
	BfmeLinkCU *m_prev;
};

class BfmeHolderCU
{
public:
	BfmeHolderCU( BfmeListCU **list, void *user );
	virtual void unusedVirtual();

private:
	unsigned int m_storage[ 4 ];
};

class FXList;

class GameClientRandomVariable
{
public:
	float getValue() const;
	unsigned int m_storage[ 3 ];
};

class FXListStore
{
public:
	const FXList *findFXList( const char *name ) const;
};

extern "C" FXListStore *g_terrainCollisionEventFXListStore;

namespace FXParticleSystem
{

class ParticleSystem;

template <class T>
class TrackingPtr
{
};

class LifeEventModuleTemplate;

class LifeEventCategorySlice
{
public:
	virtual void unusedVirtual();
	virtual __declspec( nothrow ) ~LifeEventCategorySlice() {}
};

class LifeEventFlagsSlice
{
public:
	LifeEventFlagsSlice()
	{
		*(volatile unsigned int *)this = 0x0107375c;
		bool one = true;
		*(volatile unsigned char *)( (unsigned char *)this + 4 ) = one;
		*(volatile unsigned char *)( (unsigned char *)this + 5 ) = one;
	}
	virtual void unusedVirtual();
	virtual __declspec( nothrow ) ~LifeEventFlagsSlice() {}

private:
	bool m_flag0;
	bool m_flag1;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class LifeEventModuleInfo : public Snapshot
{
public:
	LifeEventModuleInfo();
	virtual ~LifeEventModuleInfo();
	virtual void unusedVirtual();

protected:
	unsigned int m_eventName;
	GameClientRandomVariable m_eventTime;
	const FXList *m_cached;
};

struct LifeEventModuleTemplateImage
{
	unsigned char m_prefix[ 0x10 ];
	const char *m_eventName;
	GameClientRandomVariable m_eventTime;
	const FXList *m_cached;
};

class ParticleLifeEventModule
	: public BfmeHolderCU,
	  public LifeEventCategorySlice,
	  public LifeEventFlagsSlice
{
public:
	__forceinline ParticleLifeEventModule(
		TrackingPtr<ParticleSystem> &system, const void *source )
		: BfmeHolderCU( reinterpret_cast<BfmeListCU **>( &system ),
			const_cast<void *>( source ) )
	{
	}
};

class Rva005FC920LifeEventModule
	: public ParticleLifeEventModule,
	  public LifeEventModuleInfo
{
public:
	Rva005FC920LifeEventModule( TrackingPtr<ParticleSystem> &system,
		const LifeEventModuleTemplate *source );

private:
	int m_eventFrame;
	bool m_pending;
};

// ??0LifeEventModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVLifeEventModuleTemplate@1@@Z
Rva005FC920LifeEventModule::Rva005FC920LifeEventModule(
	TrackingPtr<ParticleSystem> &system,
	const LifeEventModuleTemplate *source )
	: ParticleLifeEventModule( system, source ),
	  LifeEventModuleInfo()
{
	const LifeEventModuleTemplateImage *sourceImage =
		reinterpret_cast<const LifeEventModuleTemplateImage *>( source );
	LifeEventModuleTemplateImage *mutableSourceImage =
		const_cast<LifeEventModuleTemplateImage *>( sourceImage );

	m_eventTime = sourceImage->m_eventTime;

	if ( !sourceImage->m_cached )
	{
		const char *text = sourceImage->m_eventName;
		mutableSourceImage->m_cached =
			g_terrainCollisionEventFXListStore->findFXList(
				text ? text + 8 : reinterpret_cast<const char *>( 0x0107388b ) );
	}
	m_cached = sourceImage->m_cached;

	reinterpret_cast<unsigned char *>( this )[ 0x1c ] =
		sourceImage->m_prefix[ 8 ];
	reinterpret_cast<unsigned char *>( this )[ 0x1d ] =
		sourceImage->m_prefix[ 9 ];

	m_eventFrame = static_cast<int>( m_eventTime.getValue() );
	m_pending = true;
}

}

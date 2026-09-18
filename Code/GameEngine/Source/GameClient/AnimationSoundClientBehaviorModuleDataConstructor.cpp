// cl: /DNDEBUG /MD /EHsc
// AnimationSoundClientBehavior module-data constructor 0x00606060 also
// emits scalar wrapper 0x006060F0; vtable 0x011155E0 slot zero identifies it.
// The complete destructor remains in AnimationSoundClientBehaviorModuleDataDestructor.cpp
// because its retail body requires the novtable view.
//
// The named friend_newModuleData factory at retail 0x00121DA0 allocates 0x18
// bytes and calls this constructor.  The eight-byte member at +0x08 owns a
// 0x70-byte list header; its matched destructor at 0x00605E60 independently
// confirms the header pointer/count layout and releases the same allocation.

namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate( unsigned int bytes );
	};
}

class AnimationSoundListHeader
{
public:
	unsigned char m_isData;
	unsigned char m_pad[ 3 ];
	void *m_first;
	AnimationSoundListHeader *m_next;
	AnimationSoundListHeader *m_prev;
	unsigned char m_payload[ 0x70 - 0x10 ];
};

class AnimationSoundList
{
public:
	AnimationSoundList()
	{
		m_header = 0;
		m_header = static_cast<AnimationSoundListHeader *>(
			_STL::__new_alloc::allocate( 0x70 ) );
		m_count = 0;
		m_header->m_isData = 0;
		m_header->m_first = 0;
		m_header->m_next = m_header;
		m_header->m_prev = m_header;
	}

	~AnimationSoundList();

private:
	AnimationSoundListHeader *m_header;
	unsigned int m_count;
};

class AnimationSoundClientBehaviorModuleDataBase
{
public:
	virtual ~AnimationSoundClientBehaviorModuleDataBase() {}

private:
	unsigned int m_unmodelled_04;
};

class AnimationSoundClientBehaviorModuleData
	: public AnimationSoundClientBehaviorModuleDataBase
{
public:
	AnimationSoundClientBehaviorModuleData();
	virtual ~AnimationSoundClientBehaviorModuleData();

private:
	AnimationSoundList m_animationSounds; // +0x08
	unsigned int m_unmodelled_10;
	float m_loudestSound;
};

// ??0AnimationSoundClientBehaviorModuleData@@QAE@XZ
AnimationSoundClientBehaviorModuleData::AnimationSoundClientBehaviorModuleData()
{
	m_loudestSound = 3.402823466e+38F;
}

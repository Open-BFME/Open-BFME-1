// cl: /DNDEBUG /MD /EHsc
// AnimationSoundClientBehavior module-data constructor 0x00606060 also
// emits scalar wrapper 0x006060F0; vtable 0x011155E0 slot zero identifies it.
// The complete destructor remains in AnimationSoundClientBehaviorModuleDataDestructor.cpp
// because its retail body requires the novtable view.
//
// The named friend_newModuleData factory at retail 0x00121DA0 allocates 0x18
// bytes and calls this constructor.  The eight-byte member at +0x08 owns a
// 0x70-byte tree header; its matched destructor at 0x00605E60 independently
// confirms the header pointer/count layout and releases the same allocation.

// Retail erase 0x00605820 recurses through +0x0c and iterates +0x08;
// inputs/vendor/stlport/stl/_tree.c::_M_erase and _tree.h::_M_empty_initialize
// independently establish the tree links and red header color. Key/value
// identities and the meaning of the float at module-data +0x14 remain unknown.

namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate( unsigned int bytes );
	};
}

class Rva00606060TreeHeader
{
public:
	unsigned char m_color;
	unsigned char m_pad[ 3 ];
	void *m_parent;
	Rva00606060TreeHeader *m_left;
	Rva00606060TreeHeader *m_right;
	unsigned char m_payload[ 0x70 - 0x10 ];
};

class Rva00606060Tree
{
public:
	Rva00606060Tree()
	{
		m_header = 0;
		m_header = static_cast<Rva00606060TreeHeader *>(
			_STL::__new_alloc::allocate( 0x70 ) );
		m_count = 0;
		m_header->m_color = 0;
		m_header->m_parent = 0;
		m_header->m_left = m_header;
		m_header->m_right = m_header;
	}

	~Rva00606060Tree();

private:
	Rva00606060TreeHeader *m_header;
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
	Rva00606060Tree m_tree08; // +0x08
	unsigned int m_unmodelled_10;
	float m_14;
};

// ??0AnimationSoundClientBehaviorModuleData@@QAE@XZ
AnimationSoundClientBehaviorModuleData::AnimationSoundClientBehaviorModuleData()
{
	m_14 = 3.402823466e+38F;
}

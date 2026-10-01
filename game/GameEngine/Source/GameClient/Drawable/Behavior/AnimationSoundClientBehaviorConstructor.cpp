// cl: /DNDEBUG /MD /EHsc
// AnimationSoundClientBehavior::AnimationSoundClientBehavior(Thing *, const
// ModuleData *) at 0x00605380, 245 bytes (the ledger extent is right: the last
// instruction is the `ret 8` at 0x006053F2).
//
// Identity: the matched friend_newModuleInstance (AnimationSoundClientBehaviorFactories.cpp)
// allocates and calls it, and it installs the vtables 0x011155A0 and 0x01115594
// that the matched destructor 0x00604B40 and the matched register-copy
// constructor 0x00605710 also install.
//
// Shape: the DrawableModule constructor through ILT 0x00002874 (pinned as
// ??0DrawableModule), an interface base at +0x0C, two zeroed links at +0x14 and
// +0x18, then a scale at +0x10. With no audio client the scale is 0 and the
// behavior never registers. Otherwise the scale is the largest scale in the
// module data's sound tree, capped by a limit in the module data, squared.
// The running maximum lives in the dead moduleData argument slot.

class Thing;

namespace _STL
{
	struct _Rb_tree_node_base
	{
		bool _M_color;
		_Rb_tree_node_base *_M_parent;
		_Rb_tree_node_base *_M_left;
		_Rb_tree_node_base *_M_right;
	};

	template <class Dummy> class _Rb_global
	{
	public:
		static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
	};
}

struct ASCB_SoundInfo
{
	unsigned char m_pad[0x78];
	float m_scale;
};

struct ASCB_SoundNode : public _STL::_Rb_tree_node_base
{
	int m_key;
	ASCB_SoundInfo *m_info;
};

class ModuleData
{
public:
	unsigned char m_pad00[8];
	ASCB_SoundNode *m_soundHeader;
	unsigned char m_pad0c[8];
	float m_scaleLimit;
};

class DrawableModule
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawableModule();

protected:
	const ModuleData *m_moduleData;
	unsigned char m_pad08[4];
};

class ASCB_Iface
{
public:
	virtual void ascbIfaceVslot();
};

struct Rva004091C0Node;
class AnimationSoundClientBehavior;

// ILT 0x0001B7A7 reaches the pinned registry insert at 0x004091C0.
class Rva004091C0Registry
{
public:
	void rva_004091C0(Rva004091C0Node *node);
};

// Retail's audio global, at 0x012ED668, is AudioManager *TheAudio
// (?TheAudio@@3PAVAudioManager@@A); only the null test is needed here.
class AudioManager;
extern AudioManager *TheAudio;
class BfmeResetSubsystem;
extern BfmeResetSubsystem *g_animationSoundClientBehaviorGlobal;

class AnimationSoundClientBehavior : public DrawableModule, public ASCB_Iface
{
public:
	AnimationSoundClientBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~AnimationSoundClientBehavior();
	virtual void ascbIfaceVslot();

private:
	float m_soundScale;
	AnimationSoundClientBehavior *m_next;
	AnimationSoundClientBehavior *m_prev;
};

// ??0AnimationSoundClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
AnimationSoundClientBehavior::AnimationSoundClientBehavior(Thing *thing, const ModuleData *moduleData)
	: DrawableModule(thing, moduleData), m_next(0), m_prev(0)
{
	if (TheAudio == 0)
	{
		m_soundScale = 0.0f;
		return;
	}

	float maxScale = 0.0f;
	const ModuleData *data = m_moduleData;
	for (_STL::_Rb_tree_node_base *node = data->m_soundHeader->_M_left; node != data->m_soundHeader;
	     node = _STL::_Rb_global<bool>::_M_increment(node))
	{
		ASCB_SoundInfo *info = static_cast<ASCB_SoundNode *>(node)->m_info;
		if (info->m_scale > maxScale)
			maxScale = info->m_scale;
	}
	if (maxScale > data->m_scaleLimit)
		maxScale = data->m_scaleLimit;
	m_soundScale = maxScale * maxScale;

	if (g_animationSoundClientBehaviorGlobal)
		((Rva004091C0Registry *)g_animationSoundClientBehaviorGlobal)->rva_004091C0(
			(Rva004091C0Node *)this);
}

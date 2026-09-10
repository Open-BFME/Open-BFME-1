// ?bfmeStep1_004647E0@@YAXXZ
// partial score=0.35 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Scratch reconstruction for the ASM-backed S3 helper at retail RVA 0x00463340.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

	void *m_data;
};

class AsciiString
{
public:
	void *m_data;
};

class GameWindow
{
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01();
	virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual void winDestroy(GameWindow *window);
};

class WindowManager
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30(const AsciiString *name) = 0;
};

namespace _STL
{
struct _Rb_tree_node_base
{
	bool m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};
}

extern "C" _STL::_Rb_tree_node_base *bfme_RbGlobalBoolIncrement_82B870(
	_STL::_Rb_tree_node_base *node);

extern void j_0004482d();
extern void j_000347d9();
extern void j_00025464();
extern void j_00042591();
extern void j_0000f547();

typedef void (WindowManager::*NameCall)(const AsciiString *);
union NameCallCast
{
	void (*raw)();
	NameCall member;
};

static __forceinline void callName(WindowManager *manager, void (*function)(),
	BFMERetailAsciiString *name)
{
	NameCallCast cast;
	cast.raw = function;
	(manager->*cast.member)(reinterpret_cast<const AsciiString *>(name));
}

struct S3Node : _STL::_Rb_tree_node_base
{
	int m_key;
	GameWindow *m_window;
};

struct S3Tree
{
	S3Node *m_header;
	unsigned int m_nodeCount;
	void erase(S3Node *root);
};

struct S3Guard
{
	virtual void release(int destroy);
};

struct GameSpyGroupRoom
{
	GameSpyGroupRoom(const BFMERetailAsciiString &source);
	~GameSpyGroupRoom();
};

struct S3Registration
{
	int m_zero;
	void *m_owner;
};

struct S3RefMap
{
	void add(S3Registration *registration);
};

static S3Tree *const s_tree = reinterpret_cast<S3Tree *>(0x012F19CC);
static S3Guard **const s_guard = reinterpret_cast<S3Guard **>(0x012F198C);
static WindowManager **const s_windowManager =
	reinterpret_cast<WindowManager **>(0x012F19E8);
static char *const s_twoSja = reinterpret_cast<char *>(0x012F19A4);
static BFMERetailAsciiString *const s_refObject =
	reinterpret_cast<BFMERetailAsciiString *>(0x012F1990);

extern GameWindowManager *TheWindowManager;

void bfmeStep1_004647E0(void)
{
	S3Node *header = s_tree->m_header;
	S3Node *node = reinterpret_cast<S3Node *>(header->m_left);
	while (node != header)
	{
		TheWindowManager->winDestroy(node->m_window);
		node = reinterpret_cast<S3Node *>(bfme_RbGlobalBoolIncrement_82B870(
			reinterpret_cast<_STL::_Rb_tree_node_base *>(node)));
	}

	if (s_tree->m_nodeCount != 0)
	{
		s_tree->erase(reinterpret_cast<S3Node *>(header->m_parent));
		header->m_left = header;
		header->m_parent = 0;
		header->m_right = header;
		s_tree->m_nodeCount = 0;
	}

	S3Guard *guard = *s_guard;
	if (guard != 0)
		guard->release(1);
	*s_guard = 0;
	if (*s_windowManager == 0)
		return;

	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F70AC));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F709C));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F7090));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F7080));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F7074));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F7068));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F705C));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F704C));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F7040));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F7038));
		callName(*s_windowManager, j_000347d9, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F7020));
		callName(*s_windowManager, j_00025464, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F700C));
		callName(*s_windowManager, j_00025464, &name);
	}
	{
		BFMERetailAsciiString name(reinterpret_cast<const char *>(0x010F6FFC));
		GameSpyGroupRoom room(name);
		S3Registration registration = { 0,
			reinterpret_cast<void *>(0x012F19A4) };
		char **first = *reinterpret_cast<char ***>(0x012F19A8);
		char **last = *reinterpret_cast<char ***>(0x012F19AC);
		unsigned int count = static_cast<unsigned int>(last - first);
		unsigned int index = 0;
		while (index < count)
		{
			if (first[index] != 0)
				break;
			++index;
			count = static_cast<unsigned int>(last - first);
		}
		if (index == count)
			(reinterpret_cast<S3RefMap *>(0x012F1990))->add(&registration);
	}

	(void)s_twoSja;
	(void)s_refObject;
}

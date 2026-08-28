// cl: /DNDEBUG /MD /EHsc
// readable body of ?registerTextWindow@GameSpyInfo@@: Code/GameEngine/Source/GameNetwork/GameSpy/Chat.cpp

// FILE: PeerDefsRegisterTextWindow.cpp //////////////////////////////////////
//
// GameSpyInfo::registerTextWindow, retail 0x00626060.
//
// This address was closed as "markPlayerAsPreorder, refuted": that symbol is
// already matched at 0x00633360, also 30 bytes, so it cannot also be here, and
// the two bodies are the same set-insert boilerplate differing only in the set
// offset -- 0x6E0 here against 0x6EC there. The earlier note asked the right
// question ("whichever GameSpyInfo member sits at +0x6E0 names it") and the
// answer is in the call, not in the body:
//
//   0x00626060 calls _Rb_tree::insert_unique at 0x00625940, whose comparisons
//   are UNSIGNED  -- 0f 92 c1 setb, 73 24 jae
//   0x00633360 calls the copy at 0x00235A30, whose comparisons are SIGNED
//                -- 0f 9c c1 setl, 7d 24 jge
//
// The two 145-byte bodies are otherwise instruction-for-instruction identical.
// A signed element is set<Int> = m_preorderPlayers; an unsigned one is a
// POINTER set, and Zero Hour's GameSpyInfo declares exactly one, immediately
// ahead of m_preorderPlayers:
//
//   std::set<GameWindow *> m_textWindows;    // +0x6E0, 12 bytes
//   std::set<Int>          m_preorderPlayers;// +0x6EC
//
// which fixes both the member and the method, registerTextWindow being the
// only GameSpyInfo virtual that inserts into it.
//
// Own TU with a local ABI slice, the shape PeerDefsGameSpyInfoReset.cpp uses:
// this body is in a different object from PeerDefs.cpp's GameSpyInfo methods
// -- that is what the second copy of insert_unique means -- and the class
// declaration lives in a vendored shim header this must not touch.
//
// _STL::pair must be NON-POD here. Spelled as a plain aggregate it is an
// 8-byte POD, MSVC returns it in edx:eax, and the sret temporary retail builds
// with `sub esp,8` plus the second `lea`/`push` pair disappears -- eleven of
// the thirty bytes. Giving pair its constructors restores it.
//
/////////////////////////////////////////////////////////////////////////////

class GameWindow;

namespace _STL
{

template <class Type> class allocator {};

template <class First, class Second> struct pair
{
	First first;
	Second second;
	pair() {}
	pair( const First &f, const Second &s ) : first( f ), second( s ) {}
};

template <class Type> struct _Identity {};
template <class Type> struct less {};
template <class Type> struct _Nonconst_traits {};

template <class Type, class Traits> struct _Rb_tree_iterator
{
	void *_M_node;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:

	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;

	// Declared, never defined: the call stays out of line at 0x00625940.
	pair<iterator, bool> insert_unique( const Value &v );

private:

	void *_M_header;
	unsigned int _M_node_count;
	Compare _M_key_compare;
};

}

typedef _STL::_Rb_tree<GameWindow *, GameWindow *, _STL::_Identity<GameWindow *>,
											 _STL::less<GameWindow *>,
											 _STL::allocator<GameWindow *> > TextWindowSet;

typedef char BFMETextWindowSetSizeCheck[ sizeof( TextWindowSet ) == 12 ? 1 : -1 ];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefsImplementation.h
class GameSpyInfo
{
public:

	virtual void registerTextWindow( GameWindow *win );

private:

	char m_bfmeBody[ 0x6E0 - 4 ];
	TextWindowSet m_textWindows;					// +0x6E0
};

void GameSpyInfo::registerTextWindow( GameWindow *win )
{
	m_textWindows.insert_unique( win );
}

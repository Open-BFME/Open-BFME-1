// ?setHumanImpassableArea@ScriptEngine@@QAEXABVAsciiString@@_N@Z
// partial score=0.96 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// The HUMAN_IMPASSABLE_AREA action stores the requested area state in the
// fifth tree constructed by ScriptEngine, at this+0x16070.  The action path
// calls this routine after resolving the area name; an existing entry is
// updated in place and a missing entry is inserted into the AsciiString map.

#include <stl/_tree.h>

template <class T> class StringBase
{
private:
	friend class AsciiString;
	struct Data
	{
		int refs;
		int length;
		T data[1];
	};

	Data *m_data;
	StringBase() {}
	StringBase(const StringBase &other);
	~StringBase();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) throw() : StringBase<char>(other) {}
	~AsciiString() {}
	int compare(const AsciiString &other) const;
};

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

struct Rva003404C0Value
{
	AsciiString m_key;
};

struct Rva003404C0KeyOfValue
{
	const AsciiString &operator()(const Rva003404C0Value &value) const
	{
		return value.m_key;
	}
};

typedef _STL::_Rb_tree<AsciiString, Rva003404C0Value, Rva003404C0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva003404C0Value> > Rva003404C0Tree;

struct Rva0033F870Value
{
	bool m_body;
};

typedef _STL::pair<const AsciiString, Rva0033F870Value> Rva0033F870Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0033F870Pair, _STL::_Select1st<Rva0033F870Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F870Pair> > Rva0033F870Tree;

struct HumanImpassableAreaMap
{
	Rva0033F870Tree m_tree;

	_STL::_Rb_tree_node<Rva003404C0Value> *find(const AsciiString &name)
	{
		Rva003404C0Tree::iterator found = ((Rva003404C0Tree *)&m_tree)->find(name);
		return (_STL::_Rb_tree_node<Rva003404C0Value> *)found._M_node;
	}

	_STL::_Rb_tree_node<Rva003404C0Value> *header() const
	{
		return *(reinterpret_cast<_STL::_Rb_tree_node<Rva003404C0Value> *const *>(
			&m_tree));
	}

	_STL::pair<Rva0033F870Tree::iterator, bool> insert(const Rva0033F870Pair &value)
	{
		return m_tree.insert_unique(value);
	}
};

class BfmeOtherDPB
{
public:
	void bfmeCallDPB(void *value);
	AsciiString m_bfmeHead;
	bool m_bfmeVal;

};

// Returns the record BY VALUE: retail pushes the result slot as the first of three
// arguments, keeps eax (= &result) afterwards, and only then starts the EH state
// for it -- a default-constructed local passed by pointer would be tracked before
// the call.
extern BfmeOtherDPB bfmeGoDPB(const AsciiString &name, const bool &blocked);

class ScriptEngine
{
public:
	void setHumanImpassableArea(const AsciiString &name, bool blocked);

private:
	char m_unknown[0x16070];
	HumanImpassableAreaMap m_humanImpassableAreas;
};

void ScriptEngine::setHumanImpassableArea(const AsciiString &name, bool blocked)
{
	_STL::_Rb_tree_node<Rva003404C0Value> *found =
		m_humanImpassableAreas.find(name);
	if (found != m_humanImpassableAreas.header()) {
		*(char *)((char *)found + 0x14) = blocked;
	} else {
		BfmeOtherDPB other = bfmeGoDPB(name, blocked);
		Rva0033F870Pair value(*(AsciiString *)&other.m_bfmeHead,
			*(Rva0033F870Value *)&other.m_bfmeVal);
		m_humanImpassableAreas.insert(value);
	}
}

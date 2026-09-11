// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Retail 0x005AA0F0 is the ordinary insert_unique body for the wider upgrade
// tree.  The key is a sixteen-byte BFME record of four StringBase<char>
// subobjects.  Retail orders the slots +0, +8, +4, +0xC; the mapped tail is
// opaque here, but the 0x38-byte node leaves exactly 24 bytes after that key.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS 1
#include <map>

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);

template <class T>
class StringBase
{
public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	int compareNoCase(const StringBase<T> &other) const
	{
		int other_length = other.m_data ? other.m_data->length : 0;
		const T *other_data = other.m_data ? &other.m_data->data[0] : (const T *)"";
		int this_length = m_data ? m_data->length : 0;
		const T *this_data = m_data ? &m_data->data[0] : (const T *)"";
		int count = this_length < other_length ? this_length : other_length;
		int result = _memicmp(this_data, other_data, count);
		if (result != 0)
			return result;
		return this_length - other_length;
	}

private:
	Header *m_data;
};

class AsciiString
{
public:
	StringBase<char> m_slot0;
	StringBase<char> m_slot4;
	StringBase<char> m_slot8;
	StringBase<char> m_slotC;
};

// ??8@YA_NABVAsciiString@@0@Z
inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	int order = left.m_slot0.compareNoCase(right.m_slot0);
	if (order < 0)
		return true;
	if (order > 0)
		return false;
	order = left.m_slot8.compareNoCase(right.m_slot8);
	if (order < 0)
		return true;
	if (order > 0)
		return false;
	order = left.m_slot4.compareNoCase(right.m_slot4);
	if (order < 0)
		return true;
	if (order > 0)
		return false;
	return left.m_slotC.compareNoCase(right.m_slotC) < 0;
}

struct BfmeUpgradeInfoWide005AA0F0
{
	char m_body[24];
};

struct upgradePairWide
{
	typedef AsciiString first_type;
	typedef BfmeUpgradeInfoWide005AA0F0 second_type;

	AsciiString first;
	BfmeUpgradeInfoWide005AA0F0 second;
};

namespace _STL
{
template <>
void _Construct(upgradePairWide *p, const upgradePairWide &value);
}

typedef _STL::_Rb_tree<AsciiString, upgradePairWide,
	_STL::_Select1st<upgradePairWide>, _STL::equal_to<AsciiString>,
	_STL::allocator<upgradePairWide> > Rva005AA0F0Tree;

// ?insert_unique@?$_Rb_tree@VAsciiString@@UupgradePairWide@@U?$_Select1st@UupgradePairWide@@@_STL@@U?$equal_to@VAsciiString@@@4@V?$allocator@UupgradePairWide@@@4@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@UupgradePairWide@@U?$_Nonconst_traits@UupgradePairWide@@@_STL@@@_STL@@_N@2@ABUupgradePairWide@@@Z
template _STL::pair<Rva005AA0F0Tree::iterator, bool>
Rva005AA0F0Tree::insert_unique(const upgradePairWide &);

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Two vector members torn down in reverse declaration order, then the base
// vftable store. The unwind states count down 1 then 0, which is what members of
// one class look like.
//
// The two vectors compile differently and that is what identifies their
// elements. The one at +0x14 is destroyed by an out-of-line call, so its element
// has a destructor -- an AsciiString. The one at +0x08 is torn down inline with
// no destroy loop at all, so its element is trivially destructible, and the
// arithmetic gives its size: multiply-high by 0x2AAAAAAB then sar 3 is a divide
// by 48, and the lea eax,[eax+eax*2] with shl 4 that follows multiplies straight
// back to bytes. A 48-byte POD.
//
// The 0x80 comparison is STLport's node allocator threshold, not anything about
// this class: small blocks go back to _M_deallocate, larger ones to operator
// delete. #include <vector> comes first so that allocator is the one in scope.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_str;
};

struct PropagandaEntry
{
	int m_words[12];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}

	unsigned int m_04;
};

class __declspec(novtable) PropagandaTowerBehaviorModuleData : public ModuleData
{
public:
	virtual ~PropagandaTowerBehaviorModuleData();

private:
	std::vector<PropagandaEntry> m_entries;	// +0x08
	std::vector<AsciiString> m_names;	// +0x14
};

// ??1PropagandaTowerBehaviorModuleData@@UAE@XZ
PropagandaTowerBehaviorModuleData::~PropagandaTowerBehaviorModuleData()
{
}

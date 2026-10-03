// Retail [00463340,00463716); the final bucket-found tail lies after RET.
// Matched caller bfmeRun_004647E0 names this address-derived helper.
// The holder-null branch skips twelve unregister calls, not the final cleanup.
// Canonical GameWindowManager and AsciiString headers retain the native shape.
// Evidence: targets/game/reverse/identity_evidence/00463340-shutdown.md
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include "GameClient/GameWindowManager.h"
#include <map>
#include <hash_map>
#include <algorithm>

typedef std::map<AsciiString, GameWindow *> S3WindowTree;
struct Rva00C6B8A0Init;
extern Rva00C6B8A0Init g_rva012F19CC;
#define s_windowTree (*reinterpret_cast<S3WindowTree *>(&g_rva012F19CC))

// S3Guard is the inherited bank label, not an original owner identity.
class S3Guard { public: virtual void release(int); };
extern void *g_rva012F198CLoadScreen;
#define g_s3Guard reinterpret_cast<S3Guard **>(&g_rva012F198CLoadScreen)

struct S4Holder0046DBB0 {
	void take0046DEF0(const AsciiString &);
	void take0046DBB0(const AsciiString &);
};
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
#define g_s4Holder ((S4Holder0046DBB0*)g_rva012F19E8WindowManager)

struct WindowRecord { char m_pad00[0x28]; AsciiString m_name; };
typedef _STL::hash_map<AsciiString, WindowRecord, rts::hash<AsciiString>,
	rts::equal_to<AsciiString> > WindowTable;
struct Rva00461A00Counted { virtual void release(unsigned int); int m_references; };
struct Rva00461A00Mapped {
	Rva00461A00Mapped() : m_counted(0) {}
	Rva00461A00Mapped(const Rva00461A00Mapped &other) : m_counted(other.m_counted) { if (m_counted) ++m_counted->m_references; }
	~Rva00461A00Mapped() { if (m_counted && --m_counted->m_references <= 0) m_counted->release(1); }
	Rva00461A00Counted *m_counted;
};
typedef _STL::hash_map<AsciiString, Rva00461A00Mapped,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > AptScreenRefTable;
struct NameClearFunctor00462540 {
	NameClearFunctor00462540(const AsciiString &name) : m_name(name) {}
	void operator()(_STL::pair<const AsciiString, WindowRecord> &record) {
		if (record.second.m_name == m_name)
			record.second.m_name.clear();
	}
	AsciiString m_name;
};
struct Rva00C6B860Init;
extern Rva00C6B860Init g_rva012F19A4;
struct Rva00C6B840Init;
extern Rva00C6B840Init g_rva012F1990;


struct Rva00463340Buckets {
    unsigned int prefix;
    _STL::vector<WindowTable::iterator::_Node *> buckets;
    __forceinline WindowTable::iterator begin() {
        for (unsigned int n=0; n < buckets.size(); ++n)
            if (buckets[n])
                return WindowTable::iterator(buckets[n], reinterpret_cast<WindowTable::iterator::_Hashtable *>(this));
        return WindowTable::iterator(0, reinterpret_cast<WindowTable::iterator::_Hashtable *>(this));
    }
};
static __forceinline WindowTable::iterator windowTableBegin()
{
    return reinterpret_cast<Rva00463340Buckets *>(&g_rva012F19A4)->begin();
}
static __forceinline WindowTable::iterator windowTableEnd()
{
    return WindowTable::iterator(0, reinterpret_cast<WindowTable::iterator::_Hashtable *>(&g_rva012F19A4));
}

void bfmeStep1_004647E0(void)
{
	S3WindowTree::iterator it = s_windowTree.begin();
	while (it != s_windowTree.end()) {
		TheWindowManager->winDestroy(it->second);
		++it;
	}
	if (s_windowTree.size() != 0)
		s_windowTree.clear();

	S3Guard *guard = *g_s3Guard;
	if (guard != 0)
		guard->release(1);
	S4Holder0046DBB0 *holder = g_s4Holder;
	*g_s3Guard = 0;
	if (holder != 0) {

	{
		AsciiString name("GameWindow");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("HorzSlider");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("ComboBox");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("ImageComboBox");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("CheckBox");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("TextEntry");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("ListBox");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("PushButton");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("BinkMovie");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("View3D");
		g_s4Holder->take0046DEF0(name);
	}
	{
		AsciiString name("DisableComponents");
		g_s4Holder->take0046DBB0(name);
	}
	{
		AsciiString name("EnableComponents");
		g_s4Holder->take0046DBB0(name);
	}
	}
	{
		AsciiString name("BinkMovieInit");
		_STL::for_each(windowTableBegin(), windowTableEnd(), NameClearFunctor00462540(name));
		reinterpret_cast<AptScreenRefTable *>(&g_rva012F1990)->erase(name);
	}
}

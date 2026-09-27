// ?bfmeStep1_004647E0@@YAXXZ
// partial score=0.77 date=2026-09-27
// ?bfmeStep1_004647E0@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <hash_map>
#include <algorithm>
#include "ascii_string.h"

class GameWindow {};
class GameWindowManager {
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void winDestroy(GameWindow *);
};
extern GameWindowManager *TheWindowManager;

struct Gen_t_004607f0_p12cd {
	GameWindow *m_window;
	char m_unknown[8];
};
typedef std::map<int, Gen_t_004607f0_p12cd> S3WindowTree;
class Gen_00C70080Target { public: void bfmeForward(void); };
extern Gen_00C70080Target TheBfmeObject_00C70080;
#define s_windowTree (*reinterpret_cast<S3WindowTree *>(&TheBfmeObject_00C70080))

class S3Guard { public: virtual void release(int); };
static S3Guard **const g_s3Guard = reinterpret_cast<S3Guard **>(0x012F198C);

struct S4Holder0046DBB0 {
	void take0046DEF0(const AsciiString &);
	void take0046DBB0(const AsciiString &);
};
extern S4Holder0046DBB0 *g_s4Holder;

namespace rts {
template <class T> struct hash { unsigned int operator()(T) const; };
template <class T> struct equal_to { bool operator()(const T &, const T &) const; };
}
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
class Gen_00C700A0Target { public: void bfmeForward(void); };
extern Gen_00C700A0Target TheBfmeObject_00C700A0;
class Gen_00C70090Target { public: void bfmeForward(void); };
extern Gen_00C70090Target TheBfmeObject_00C70090;


static __forceinline WindowTable::iterator windowTableBegin()
{
	WindowTable::iterator first;
	char **bucketStart = *reinterpret_cast<char ***>(
		reinterpret_cast<unsigned char *>(&TheBfmeObject_00C700A0) + 4);
	char **bucketEnd = *reinterpret_cast<char ***>(
		reinterpret_cast<unsigned char *>(&TheBfmeObject_00C700A0) + 8);
	unsigned int index = 0;
	for (; index < ((reinterpret_cast<char *>(bucketEnd) -
		reinterpret_cast<char *>(bucketStart)) >> 2); ++index) {
		if (bucketStart[index] != 0)
			break;
	}
	first._M_cur = index < ((reinterpret_cast<char *>(bucketEnd) -
		reinterpret_cast<char *>(bucketStart)) >> 2)
		? reinterpret_cast<WindowTable::iterator::_Node *>(bucketStart[index]) : 0;
	first._M_ht = reinterpret_cast<WindowTable::iterator::_Hashtable *>(
		&TheBfmeObject_00C700A0);
	return first;
}
static __forceinline WindowTable::iterator windowTableEnd()
{
	WindowTable::iterator last;
	last._M_cur = 0;
	last._M_ht = reinterpret_cast<WindowTable::iterator::_Hashtable *>(
		&TheBfmeObject_00C700A0);
	return last;
}

void bfmeStep1_004647E0(void)
{
	S3WindowTree::iterator it = s_windowTree.begin();
	while (it != s_windowTree.end()) {
		TheWindowManager->winDestroy(it->second.m_window);
		++it;
	}
	if (s_windowTree.size() != 0)
		s_windowTree.clear();

	S3Guard *guard = *g_s3Guard;
	if (guard != 0)
		guard->release(1);
	S4Holder0046DBB0 *holder = g_s4Holder;
	*g_s3Guard = 0;
	if (holder == 0)
		return;

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
	{
		AsciiString name("BinkMovieInit");
		_STL::for_each(windowTableBegin(), windowTableEnd(),
			NameClearFunctor00462540(name));
		reinterpret_cast<AptScreenRefTable *>(&TheBfmeObject_00C70090)->erase(name);
	}
}

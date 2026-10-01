// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stringinline /Iinputs/vendor/stlport /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Include /Igame/GameEngine/Source

#define BFME_STLP_NODE_ALLOC 1
#include "PreRTS.h"
#include "StringInline.h"
#include <algorithm>

extern "C" unsigned char bfmeVftDXG[];
extern void (__cdecl *g_bfmeFreeDXG)(void *what);

struct BfmeThingDXG
{
	void *bfmeGoDXG(unsigned char flags);
	void bfmeDtorDXG();
};

void *BfmeThingDXG::bfmeGoDXG(unsigned char flags)
{
	bfmeDtorDXG();
	if (flags & 1)
		g_bfmeFreeDXG(this);
	return this;
}

class BfmeSubDXH
{
	unsigned char m_bfmeHead[4];
};

extern void (__cdecl *g_bfmeDropDXH)(BfmeSubDXH *what);
void __cdecl bfmeCallDXH(BfmeSubDXH *a, void *b, BfmeSubDXH *c);

struct BfmeThingDXH
{
	void bfmeGoDXH(void *a);
	unsigned char m_bfmeHead[0x20];
	BfmeSubDXH m_bfmeSub;
};

void BfmeThingDXH::bfmeGoDXH(void *a)
{
	BfmeSubDXH *s = &m_bfmeSub;
	bfmeCallDXH(s, a, s);
	g_bfmeDropDXH(s);
}

extern "C" __declspec(dllimport) int __cdecl bfmeCvtDXI(void *a);

struct BannerMovieEntry
{
	unsigned char m_pad00[4];
	int m_id;
	int m_argument;
	unsigned char m_pad0C[4];
	int m_type;
	unsigned char m_pad14[8];
};

class BannerMovieEntryMatches
{
public:
	BannerMovieEntryMatches(int id) : m_id(id) {}
	bool operator()(const BannerMovieEntry &entry) const
	{
		return entry.m_id == m_id;
	}

private:
	int m_id;
};

class GameMessage
{
public:
	void appendIntegerArgument(int value);
};

class GameMessageDispatcher
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual GameMessage *dispatchMessage(int type) = 0;
};

class BfmeSharedString
{
public:
	BfmeSharedString(const BfmeSharedString &other);
	~BfmeSharedString();
	void *m_data;
};

class BfmeThingDVB
{
public:
	BfmeSharedString bfmeGoDVBb(int value);
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void receiveString(const BfmeSharedString &value) = 0;
};

class LoadGameFadeHolder
{
public:
	LoadGameFadeHolder(void *callback);
	LoadGameFadeHolder(const LoadGameFadeHolder &other)
		: m_value(other.m_value) {}
	~LoadGameFadeHolder() {}
	void *m_value;
};

bool postTimedOp(LoadGameFadeHolder holder, void *key);

extern GameMessageDispatcher *TheGameMessageDispatcher;
// The real GameLogic singleton (VA 0x012F0898), reached through this TU's own
// view of the object.
class GameLogic;
extern GameLogic *TheGameLogic;
extern ScriptEngine *TheScriptEngine;
extern int TheCurrentBannerMovie;
extern unsigned fadeQueueKey;
extern void __cdecl j_00020194();
extern void __cdecl j_0000fbb9();

class BfmeGlobDXI
{
public:
	void bfmeUseDXI(int id);

private:
	class BannerMovieEntryVector
	{
	public:
		BannerMovieEntry *begin() const { return m_begin; }
		BannerMovieEntry *end() const { return m_end; }

	private:
		BannerMovieEntry *m_begin;
		BannerMovieEntry *m_end;
	};

	unsigned char m_pad00[0x30];
	BannerMovieEntryVector m_entries;
};

extern BfmeGlobDXI *g_bfmeObjDXI;

void BfmeGlobDXI::bfmeUseDXI(int id)
{
	if (TheCurrentBannerMovie != -1)
		return;

	register int movieId;
	movieId = id;
	BannerMovieEntry *end = m_entries.end();
	BannerMovieEntry *entry = _STL::__find_if(
		m_entries.begin(), end, BannerMovieEntryMatches(movieId),
		_STL::random_access_iterator_tag());
	if (entry == end || entry == 0)
		return;

	if (entry->m_type == 0)
	{
		GameMessage *message = TheGameMessageDispatcher->dispatchMessage(0x45D);
		message->appendIntegerArgument(entry->m_argument);
		return;
	}
	if (entry->m_type != 2)
		return;

	TheScriptEngine->receiveString(
		reinterpret_cast<BfmeThingDVB *>(TheGameLogic)->bfmeGoDVBb(
			entry->m_argument));
	TheCurrentBannerMovie = movieId;
	postTimedOp(LoadGameFadeHolder((void *)&j_00020194), &fadeQueueKey);
	postTimedOp(LoadGameFadeHolder((void *)&j_0000fbb9), &fadeQueueKey);
}

void bfmeGoDXI(void *a)
{
	g_bfmeObjDXI->bfmeUseDXI(bfmeCvtDXI(a));
}

extern "C" __declspec(dllimport) void __stdcall bfmeCloseDXK(void *h);
void __cdecl bfmeFreeDXK(void *what);

struct BfmeThingDXK
{
	void bfmeGoDXKa();
	void bfmeGoDXKb();
	void *m_bfmeH;
	void *m_bfmeP;
};

void BfmeThingDXK::bfmeGoDXKa()
{
	if (m_bfmeH)
		bfmeCloseDXK(m_bfmeH);
	void *p = m_bfmeP;
	if (p)
		bfmeFreeDXK(p);
}

void BfmeThingDXK::bfmeGoDXKb()
{
	if (m_bfmeH)
		bfmeCloseDXK(m_bfmeH);
	void *p = m_bfmeP;
	if (p)
		bfmeFreeDXK(p);
}

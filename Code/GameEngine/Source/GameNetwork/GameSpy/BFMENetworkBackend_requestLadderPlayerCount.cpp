// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFMENetworkBackend::requestLadderPlayerCount, retail 0x0065BD40, 214 bytes.
// which==1 uses ladderid 25909 else 25911; ghttpGetA with completion 0x0065BC80;
// on success a 12-byte {this,which} record is stored in the map at +0x5C.

#include <map>

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void __cdecl format(AsciiString fmt, ...);
	const char *str(void) const { return m_data ? m_data->m_text : ""; }
};

typedef int (__cdecl *BfmeHttpCompleted)(int, int, char *, __int64, void *);
extern "C" int __cdecl ghttpGetA(const char *url, int blocking, BfmeHttpCompleted callback, void *param);
int __cdecl bfmeLadderCountCompleted(int request, int result, char *buffer, __int64 bufferLen, void *param);

struct BfmeLadderCountRecord
{
	void *backend;
	int which;
	int pad;
};

class BFMENetworkBackend
{
public:
	void requestLadderPlayerCount(int which);

private:
	char m_pad[0x5C];
	_STL::map<int, BfmeLadderCountRecord *> m_requests;
};

// ?requestLadderPlayerCount@BFMENetworkBackend@@QAEXH@Z
void BFMENetworkBackend::requestLadderPlayerCount(int which)
{
	AsciiString url;
	if (which == 1)
		url.format(AsciiString("http://lotrbfme.arenasdk.gamespy.com/ladderstats.sdk?ladderid=25909&action=COUNT"), which);
	else
		url.format(AsciiString("http://lotrbfme.arenasdk.gamespy.com/ladderstats.sdk?ladderid=25911&action=COUNT"), 2);

	int requestId = ghttpGetA(url.str(), 0, bfmeLadderCountCompleted, this);
	if (requestId != 0)
	{
		BfmeLadderCountRecord *rec = (BfmeLadderCountRecord *)::operator new(sizeof(BfmeLadderCountRecord));
		rec->backend = this;
		rec->which = which;
		m_requests[requestId] = rec;
	}
}

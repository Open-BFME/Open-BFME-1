// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// MilesAudioManager::doesViolateLimit, retail 006A6590, 777 bytes.
// Identity: GeneralsMD MilesAudioManager.cpp doesViolateLimit has the same
// playing-list counts, oldest-handle selection and AC_INTERRUPT tail;
// matched isPositionalAudio, StringBase::compare and setHandleToKill callees
// confirm the event ABI. BFME adds self-exclusion and event byte +44 rules.
// Request layout/table identity is shared with landed RequestFlags006A6B40.
// The original stash's EventNameOf/AudioEventRTSOf/PlayingHandleOf accessors
// and playing-list member names are retained. Only the incomplete tail and
// added null-info guard were corrected against retail.
// stlport
#include <hash_set>
#include "ascii_string.h"

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;
	void setHandleToKill(unsigned int handle);
};

struct BfmeListNode
{
	BfmeListNode *m_next;
	BfmeListNode *m_prev;
	void *m_value;
};

static inline AsciiString *EventNameOf(AudioEventRTS *ev)
{
	return (AsciiString *)((char *)ev + 0x14);
}

static inline AudioEventRTS *AudioEventRTSOf(void *playingAudio)
{
	return *(AudioEventRTS **)((char *)playingAudio + 0x14);
}

static inline unsigned int PlayingHandleOf(AudioEventRTS *ev)
{
	return *(unsigned int *)((char *)ev + 0xc);
}

// Reuse the already witnessed request-table type and its begin callee.
struct AudioRequest006A6B40 {
    unsigned int dword00;
    AudioEventRTS *event04;
    unsigned int hash08;
    char pad0c[6];
    bool byte12, byte13;
};
struct RequestHash006A6B40 {
    unsigned int operator()(const AudioRequest006A6B40 *p) const {
        if (!p) return 0;
        return p->hash08;
    }
};
typedef _STL::hash_set<AudioRequest006A6B40 *, RequestHash006A6B40> RequestTable006A6B40;
static inline bool EventFlag44(AudioEventRTS *ev) { return *(bool *)((char *)ev + 0x44); }

// Native StringBase<char> header view, matching string_base.h.
struct Rva006A6590StringData { int references; unsigned short length, capacity; char data[1]; };
struct Rva006A6590StringView {
    Rva006A6590StringData *m_data;
    __forceinline int compare(const Rva006A6590StringView &s) const {
        int thatLen = s.m_data ? s.m_data->length : 0;
        const char *thatData = s.m_data ? &s.m_data->data[0] : "";
        int thisLen = m_data ? m_data->length : 0;
        const char *thisData = m_data ? &m_data->data[0] : "";
        int n = thisLen < thatLen ? thisLen : thatLen;
        int c = memcmp(thisData, thatData, n);
        if (c != 0) return c;
        return thisLen - thatLen;
    }
};
static __forceinline int compareRequestNames(const AsciiString &left, const AsciiString &right) {
    return ((const Rva006A6590StringView *)&left)->compare(*(const Rva006A6590StringView *)&right);
}

class MilesAudioManager
{
public:
	bool doesViolateLimit(AudioEventRTS *event) const;

private:
	char m_pad[0x4c];
    BfmeListNode *m_requests4C;
    mutable RequestTable006A6B40 m_requests50;
    char m_pad64[0x9c8-0x64];
	BfmeListNode *m_playingSoundsHead;
	BfmeListNode *m_playing3DSoundsHead;
};

bool MilesAudioManager::doesViolateLimit(AudioEventRTS *event) const
{
	const int *info = *(const int **)((const char *)event + 8);
	int limit = *(const int *)((const char *)info + 0x30);
	if (limit == 0)
		return false;

	int totalCount = 0;
    int totalRequestCount = 0;
    if (!event->isPositionalAudio()) {
        for (BfmeListNode *node = m_playingSoundsHead->m_next; node != m_playingSoundsHead; node = node->m_next) {
            AudioEventRTS *candidate = AudioEventRTSOf(node->m_value);
            if (EventNameOf(candidate)->StringBase<char>::compare(*EventNameOf(event)) == 0 && candidate != event) {
                if (totalCount == 0) event->setHandleToKill(PlayingHandleOf(candidate));
                ++totalCount;
            }
        }
    } else {
        for (BfmeListNode *node = m_playing3DSoundsHead->m_next; node != m_playing3DSoundsHead; node = node->m_next) {
            AudioEventRTS *candidate = AudioEventRTSOf(node->m_value);
            if (EventNameOf(candidate)->StringBase<char>::compare(*EventNameOf(event)) == 0 && candidate != event) {
                if (totalCount == 0) event->setHandleToKill(PlayingHandleOf(candidate));
                ++totalCount;
            }
        }
    }

    RequestTable006A6B40::iterator requestIt;
    for (requestIt = m_requests50.begin(); requestIt != m_requests50.end(); ++requestIt) {
        AudioRequest006A6B40 *req = *requestIt;
        if (req && req->event04 && compareRequestNames(*EventNameOf(req->event04), *EventNameOf(event)) == 0
            && req->event04 != event && !EventFlag44(req->event04)) {
            ++totalRequestCount;
            ++totalCount;
        }
    }
    for (BfmeListNode *requestIt = m_requests4C->m_next; requestIt != m_requests4C; requestIt = requestIt->m_next) {
        AudioRequest006A6B40 *req = (AudioRequest006A6B40 *)requestIt->m_value;
        if (req && req->event04 && compareRequestNames(*EventNameOf(req->event04), *EventNameOf(event)) == 0
            && req->event04 != event && !EventFlag44(req->event04)) {
            ++totalRequestCount;
            ++totalCount;
        }
    }
    if (totalCount >= limit && EventFlag44(event)) {
        event->setHandleToKill(0);
        return true;
    }
    if ((*(unsigned char *)((char *)*(void **)((char *)event + 8) + 0x3c) & 8) && totalRequestCount < limit) {
        int totalPlayingCount = totalCount - totalRequestCount;
        if (totalRequestCount + totalPlayingCount < limit) {
            event->setHandleToKill(0);
            return false;
        }
        return false;
    }
    if (totalCount < limit) {
        event->setHandleToKill(0);
        return false;
    }
    return true;
}

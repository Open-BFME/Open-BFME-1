// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME retail 0x000EA390, 305 bytes: ScoreKeeper constructor.
// The BFME object derives from Snapshot.  Its vptr is therefore the first
// word, while the four ThingTemplate count maps begin at +0x144.

#include <map>

typedef int Int;

class ThingTemplate;
typedef _STL::map<const ThingTemplate *, Int> ObjectCountMap;

class BfmeStringTail
{
public:
	BfmeStringTail(void) : m_data(0), m_length(0), m_capacity(3) { }
	~BfmeStringTail(void);

private:
	void *m_data;
	Int m_length;
	Int m_capacity;
};

class Snapshot
{
public:
	virtual ~Snapshot(void) { }
	virtual void crc(void) = 0;
	virtual void xfer(void) = 0;
	virtual void loadPostProcess(void) = 0;
};

class ScoreKeeper : public Snapshot
{
public:
	ScoreKeeper(void);
	void reset(Int playerIdx);

	virtual void crc(void) { }
	virtual void xfer(void) { }
	virtual void loadPostProcess(void) { }

private:
	unsigned char m_pad004[0x140];
	ObjectCountMap m_objectsBuilt;
	ObjectCountMap m_objectsDestroyed[32];
	ObjectCountMap m_objectsLost;
	ObjectCountMap m_objectsCaptured;
	BfmeStringTail m_tail;
};

typedef char VerifyScoreKeeperSize[sizeof(ScoreKeeper) == 0x2F4 ? 1 : -1];

// ??0ScoreKeeper@@QAE@XZ
ScoreKeeper::ScoreKeeper(void)
{
	reset(0);
}

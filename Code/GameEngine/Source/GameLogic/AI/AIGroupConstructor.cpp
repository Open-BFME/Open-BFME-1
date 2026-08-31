// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// AIGroup::AIGroup, retail 0x00151BF0, 197 bytes.
//
// The constructor identity comes from AI::createGroup.  The list, identifier,
// path, speed and dirty-state initialization follows the Zero Hour source;
// the intervening formation fields are the BFME layout measured by this body.
#include <list>
#include <vector>

typedef unsigned int UnsignedInt;

class AIInterface
{
public:
	UnsignedInt getNextGroupID() { return ++m_nextGroupID; }

private:
	unsigned char m_unmodelled[0x18];
	UnsignedInt m_nextGroupID;
};

extern AIInterface *TheAI;

class Snapshot
{
public:
	virtual ~Snapshot();
};

class AIGroup : public Snapshot
{
public:
	AIGroup();
	virtual ~AIGroup();

private:
	_STL::list<void *> m_memberList;       // +0x04
	int m_memberListSize;                  // +0x08
	void *m_groundPath;                    // +0x0C
	bool m_dirty;                          // +0x10
	unsigned char m_pad11[3];
	UnsignedInt m_id;                      // +0x14
	float m_formationX;                    // +0x18
	float m_formationY;                    // +0x1C
	float m_formationZ;                    // +0x20
	float m_speed;                         // +0x24
	float m_formationSpacing;              // +0x28
	float m_formationAngle;                // +0x2C
	float m_formationOffset;               // +0x30
	_STL::vector<UnsignedInt> m_lastRequestedIDList; // +0x34
};

AIGroup::AIGroup()
{
	m_formationX = 0.0f;
	m_formationY = 0.0f;
	m_formationZ = 0.0f;
	m_speed = 0.0f;
	m_formationSpacing = 10.0f;
	m_formationAngle = 0.0f;
	m_formationOffset = 0.0f;
	m_groundPath = 0;
	m_dirty = false;
	m_id = TheAI->getNextGroupID();
	m_memberListSize = 0;
	m_memberList.clear();
}

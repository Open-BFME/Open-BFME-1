// cl: /DNDEBUG /MD /EHs-
// readable body of ?queueForPath@Pathfinder@@QAE_NW4ObjectID@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// Open-BFME5: lift Pathfinder::queueForPath __emit thunk to clean C++.
// Retail is 102 bytes at 0x003D5540 (the old 96B claim is truncated): scan
// the ring from head to tail for a duplicate, then append unless full.
// The do-while re-reads m_tail each iteration; the insert uses the tail
// value loaded at entry. /EHs- because retail has no unwind frame.

enum ObjectID { OBJECT_ID_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
    bool queueForPath(ObjectID);

private:
    unsigned char m_pad[0x24718];
    unsigned int m_queue[0x200];
    int m_head;
    int m_tail;
};

// ?queueForPath@Pathfinder@@QAE_NW4ObjectID@@@Z
bool Pathfinder::queueForPath(ObjectID id)
{
    int tail = m_tail;
    int i = m_head;
    while (i != m_tail) {
        if (m_queue[i] == (unsigned int)id) {
            return true;
        }
        ++i;
        if (i >= 0x200) {
            i = 0;
        }
    }
    int next = tail + 1;
    if (next >= 0x200) {
        next = 0;
    }
    if (next == m_head) {
        return false;
    }
    m_queue[tail] = id;
    m_tail = next;
    return true;
}

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef unsigned int UnsignedInt;

struct GameLogicFrameSource
{
	unsigned char m_padding[0x3c];
	UnsignedInt m_frame;
};

#define TheBfmeGameLogic (*(GameLogicFrameSource **)0x012F0898)

struct ObjectSMCHelperTimerValue
{
	int m_condition;
	UnsignedInt m_frame;
};

struct ObjectSMCHelperTimerNode
{
	ObjectSMCHelperTimerNode *m_next;
	ObjectSMCHelperTimerNode *m_previous;
	ObjectSMCHelperTimerValue m_value;
};

struct ObjectSMCHelperTimerList
{
	ObjectSMCHelperTimerNode *m_node;
};

class ObjectSMCHelper
{
private:
	int framesUntilNext();
	unsigned char m_padding[0x20];
	ObjectSMCHelperTimerList m_timers;
};

int ObjectSMCHelper::framesUntilNext()
{
	UnsignedInt frame = TheBfmeGameLogic->m_frame;
	UnsignedInt best = 0;
	ObjectSMCHelperTimerNode *n = m_timers.m_node->m_next;
	if (n != m_timers.m_node) {
		do {
			ObjectSMCHelperTimerValue value = n->m_value;
			UnsignedInt f = value.m_frame;
			n = n->m_next;
			if (f < best || best == 0)
				best = f;
		} while (n != m_timers.m_node);
	}
	if (best == 0)
		return 0x3fffffff;
	int delta = best - frame;
	if (delta > 0)
		return delta;
	return 1;
}

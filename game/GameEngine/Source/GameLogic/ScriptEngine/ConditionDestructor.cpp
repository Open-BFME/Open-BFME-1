// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Clean C++ body for the BFME Condition destructor at 0x00352D20.
// The vtable and field order are fixed by Condition's constructor at
// 0x00357CC0 and the complete vtable at 0x010E84DC.

void __cdecl operator delete(void *);

#include "ascii_string.h"

struct Coord3D
{
	float x, y, z;
};

class ObjectStatusMask
{
	unsigned int m_bits[2];
};

class Parameter
{
public:
	void deleteInstance(void) { delete this; }

private:
	int m_paramType;
	bool m_initialized;
	unsigned char m_padding[3];
	int m_int;
	float m_real;
	AsciiString m_string;
	Coord3D m_coord;
	ObjectStatusMask m_objectStatus;
};

enum { MAX_PARMS = 12 };

class Condition
{
public:
	virtual ~Condition(void);

	Condition *getNext(void) const { return m_nextAndCondition; }
	void setNextCondition(Condition *next) { m_nextAndCondition = next; }
	void deleteInstance(void) { delete this; }

private:
	int m_conditionType;
	int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	Condition *m_nextAndCondition;
	int m_hasWarnings;
	int m_customData;
	unsigned int m_customFrame;
};

Condition::~Condition(void)
{
	int i;
	for (i = 0; i < m_numParms; ++i) {
		m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}

	if (m_nextAndCondition) {
		Condition *cur = m_nextAndCondition;
		Condition *next;
		while (cur) {
			next = cur->getNext();
			cur->setNextCondition(0);
			cur->deleteInstance();
			cur = next;
		}
	}
}

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Clean C++ body for the BFME ScriptAction destructor at 0x00354330.
// The ScriptAction constructors and duplicate body use vtable 0x010E84E0.
// This virtual destructor also emits the scalar-deleting wrapper at 0x00356010;
// its retail complete-destructor call routes through ILT 0x0003492D.

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

class ScriptAction
{
public:
	virtual ~ScriptAction(void);

	ScriptAction *getNext(void) const { return m_nextAction; }
	void setNextAction(ScriptAction *next) { m_nextAction = next; }
	void deleteInstance(void) { delete this; }

private:
	int m_actionType;
	int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	bool m_hasWarnings;
	int m_bfmeActionTail;
};

ScriptAction::~ScriptAction(void)
{
	int i;
	for (i = 0; i < m_numParms; ++i) {
		m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}

	if (m_nextAction) {
		ScriptAction *cur = m_nextAction;
		ScriptAction *next;
		while (cur) {
			next = cur->getNext();
			cur->setNextAction(0);
			cur->deleteInstance();
			cur = next;
		}
	}
}

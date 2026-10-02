// RVA 0x005E2C70, 139-byte implicit destructor.
// Evidence: targets/game/reverse/identity_evidence/rva005e2c70.md
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

struct GenOwner_006fa270;

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner;
	GenNode_006fa270 *m_prev;
	GenNode_006fa270 *m_next;

	void unlink(void) throw();

	~GenNode_006fa270(void) { unlink(); }
};

class V3NodeHead
{
public:
	virtual ~V3NodeHead() { }
	GenNode_006fa270 m_node;
	int m_unreconstructed_10;
};

class V3Vt1110830
{
public:
	virtual void slot0();
	virtual ~V3Vt1110830() { }
};

class V3Vt107375C
{
public:
	virtual void slot0();
	virtual ~V3Vt107375C() { }
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() {}
};

class Rva005E2C70StringView : public BfmeBaseVUQ
{
	public:
	AsciiString m_str;
};

class Rva005DDD60 : public V3NodeHead, public V3Vt1110830, public V3Vt107375C { public: int m_v; };
class Rva005E2C70 : public Rva005DDD60, public Rva005E2C70StringView {};
void useRva005E2C70() { Rva005E2C70 t; }

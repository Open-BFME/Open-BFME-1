// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class GiantBirdRoot
{
public:
	virtual ~GiantBirdRoot();

private:
	void *m_p4;
	void *m_p8;
};

class GiantBirdIface1 { public: virtual void slot() = 0; };
class GiantBirdIface2 { public: virtual void slot() = 0; };
class GiantBirdIface3 { public: virtual void slot() = 0; };
class GiantBirdIface4 { public: virtual void slot() = 0; };

class GiantBirdUpdateBase : public GiantBirdRoot, public GiantBirdIface1,
	public GiantBirdIface2
{
private:
	unsigned char m_state14[0x0c];
};

class GiantBirdAIBase : public GiantBirdUpdateBase, public GiantBirdIface3,
	public GiantBirdIface4
{
public:
	virtual ~GiantBirdAIBase();
};

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    ~AsciiString();

private:
    void *m_data;
};

struct GiantBirdMemberARecord
{
    unsigned char m_bytes[12];
};

template class _STL::vector<GiantBirdMemberARecord>;
typedef _STL::vector<GiantBirdMemberARecord> GiantBirdRecordVector;

class GiantBirdMemberA
{
public:
    ~GiantBirdMemberA();

private:
    unsigned char m_padding[0x1c];
    AsciiString m_name;
    AsciiString m_description;
    GiantBirdRecordVector m_records;
};

class GiantBirdMemberB { public: ~GiantBirdMemberB(); };
class GiantBirdNestedTail { public: ~GiantBirdNestedTail(); };

class GiantBirdNestedBase
{
public:
	virtual ~GiantBirdNestedBase() {}
};

class GiantBirdNested : public GiantBirdNestedBase
{
public:
	virtual ~GiantBirdNested() {}

private:
	unsigned char m_pad04[0x28];
	GiantBirdNestedTail m_tail;
};

class GiantBirdAIUpdate : public GiantBirdAIBase
{
public:
	virtual ~GiantBirdAIUpdate();

private:
	unsigned char m_pad28[0x324];
	GiantBirdMemberA m_memberA;
	unsigned char m_pad34d[0x9f];
	GiantBirdMemberB m_memberB;
	unsigned char m_pad3ed[0x13];
	GiantBirdNested m_nested;
};

GiantBirdMemberA::~GiantBirdMemberA()
{
}

GiantBirdAIUpdate::~GiantBirdAIUpdate()
{
}

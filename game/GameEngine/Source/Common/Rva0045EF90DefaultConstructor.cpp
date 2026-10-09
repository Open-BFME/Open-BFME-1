// cl: /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class Rva0045EF90Base
{
public:
	// ??0Rva0045EF90Base@@QAE@XZ absent-from-retail
	Rva0045EF90Base() : m_value((unsigned)-1) {}
	virtual ~Rva0045EF90Base();
protected:
	unsigned m_value;
};

struct Rva0045EF90Fields
{
	AsciiString m_first;
	AsciiString m_second;
	unsigned m_handle;
	float m_value14;
	float m_value18;
	float m_value1c;
	float m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[3];
	AsciiString m_last;
	// ??0Rva0045EF90Fields@@QAE@XZ absent-from-retail
	Rva0045EF90Fields()
		: m_first()
		, m_second()
		, m_handle(0)
		, m_value24(0)
		, m_last()
	{
		m_value14 = -1.0f;
		m_value18 = -1.0f;
		m_value1c = -1.0f;
		m_value20 = -1.0f;
	}
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	Rva0045EF90Object();
	Rva0045EF90Object(const Rva0045EF90Object &source);
	virtual ~Rva0045EF90Object();
private:
	Rva0045EF90Fields m_fields;
};

// Open BFME 2: Code/GameEngine/Source/Common/Rva004103E7Finish.cpp
Rva0045EF90Object::Rva0045EF90Object()
{
}

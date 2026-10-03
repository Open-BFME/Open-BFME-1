// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: FloatingTextData constructor from InGameUI.cpp.

#include "unicode_string.h"

// Retail inlines default construction before explicitly clearing the buffer.
inline UnicodeString::UnicodeString() : m_text(0) {}

class DisplayString;

class DisplayStringManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual DisplayString *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;

struct Coord3D
{
	float x;
	float y;
	float z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class FloatingTextData
{
public:
	FloatingTextData();
	virtual ~FloatingTextData();

private:
	unsigned int m_color;
	UnicodeString m_text;
	DisplayString *m_dString;
	Coord3D m_pos3D;
	int m_frameTimeOut;
	int m_frameCount;
};

FloatingTextData::FloatingTextData()
{
	m_color = 0;
	m_frameCount = 0;
	m_frameTimeOut = 0;
	m_pos3D.zero();
	((StringBase<unsigned short> *)&m_text)->clear();
	m_dString = TheDisplayStringManager->newDisplayString();
}

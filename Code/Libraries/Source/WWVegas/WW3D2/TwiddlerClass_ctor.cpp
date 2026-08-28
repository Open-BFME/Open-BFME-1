// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??0TwiddlerClass@@: Code/Libraries/Source/WWVegas/WWSaveLoad/twiddler.cpp

#include <list>

// TwiddlerClass's constructor, retail 0x0078F500. The base's constructor and
// then this class's own vftable pointer; nothing else is touched.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void subsystemInterfaceAnchor();

private:
	unsigned int m_name;
};

class TwiddlerClassBase : public SubsystemInterface
{
public:
	TwiddlerClassBase();

	virtual void twiddlerClassBaseAnchor();

private:
	unsigned int m_fields08[9];
	std::list<void *> m_objects;
	unsigned int m_field30;
	unsigned int m_field34;
	int m_index;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad/twiddler.h
class TwiddlerClass : public TwiddlerClassBase
{
public:
	TwiddlerClass();

	virtual void twiddlerClassAnchor();
};

// ??0TwiddlerClassBase@@QAE@XZ
TwiddlerClassBase::TwiddlerClassBase()
{
	m_fields08[0] = 0;
	m_fields08[1] = 0;
	m_fields08[2] = 0;
	m_fields08[3] = 0;
	m_fields08[4] = 0;
	m_fields08[5] = 0;
	m_fields08[6] = 0;
	m_fields08[7] = 0;
	m_fields08[8] = 0;
	m_field30 = 0;
	m_field34 = 0;
	m_index = -1;
}

// ??0TwiddlerClass@@QAE@XZ
TwiddlerClass::TwiddlerClass()
{
}

// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LifeEventModuleInfo copy constructor.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &that)
		: StringBase<char>(that)
	{
	}
};

namespace FXParticleSystem
{

class LifeEventModuleInfoBase
{
public:
	LifeEventModuleInfoBase(const LifeEventModuleInfoBase &) {}
	virtual ~LifeEventModuleInfoBase() {}
};

struct LifeEventValueBlock
{
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
};

class LifeEventModuleInfo : public LifeEventModuleInfoBase
{
public:
	LifeEventModuleInfo(const LifeEventModuleInfo &);
	virtual ~LifeEventModuleInfo();

private:
	BFMERetailAsciiString m_name;
	LifeEventValueBlock m_values;
	unsigned int m_eventType;
};

// ??0LifeEventModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
LifeEventModuleInfo::LifeEventModuleInfo(const LifeEventModuleInfo &that)
	: LifeEventModuleInfoBase(that),
	  m_name(that.m_name),
	  m_values(that.m_values),
	  m_eventType(that.m_eventType)
{
}

}

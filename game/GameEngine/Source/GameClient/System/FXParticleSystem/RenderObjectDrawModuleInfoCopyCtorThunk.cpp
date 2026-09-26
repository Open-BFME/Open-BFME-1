// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RenderObjectDrawModuleInfo copy constructor.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);

private:
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &that)
		: StringBase<char>(that)
	{
	}
	~BFMERetailAsciiString();
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
public:
	RenderObjectDrawModuleInfoBase(const RenderObjectDrawModuleInfoBase &) {}
	virtual ~RenderObjectDrawModuleInfoBase() {}
};

class RenderObjectDrawModuleInfo : public RenderObjectDrawModuleInfoBase
{
public:
	RenderObjectDrawModuleInfo(const RenderObjectDrawModuleInfo &);
	virtual ~RenderObjectDrawModuleInfo();

private:
	bool m_enabled;
	unsigned int m_type;
	bool m_flag;
	BFMERetailAsciiString m_name0;
	unsigned int m_value00;
	unsigned int m_value01;
	unsigned int m_value02;
	BFMERetailAsciiString m_name1;
	unsigned int m_value10;
	unsigned int m_value11;
	unsigned int m_value12;
	BFMERetailAsciiString m_name2;
	unsigned int m_value20;
	unsigned int m_value21;
	unsigned int m_value22;
};

// ??0RenderObjectDrawModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectDrawModuleInfo::RenderObjectDrawModuleInfo(
	const RenderObjectDrawModuleInfo &that)
	: RenderObjectDrawModuleInfoBase(that),
	  m_enabled(that.m_enabled),
	  m_type(that.m_type),
	  m_flag(that.m_flag),
	  m_name0(that.m_name0),
	  m_value00(that.m_value00),
	  m_value01(that.m_value01),
	  m_value02(that.m_value02),
	  m_name1(that.m_name1),
	  m_value10(that.m_value10),
	  m_value11(that.m_value11),
	  m_value12(that.m_value12),
	  m_name2(that.m_name2),
	  m_value20(that.m_value20),
	  m_value21(that.m_value21),
	  m_value22(that.m_value22)
{
}

}

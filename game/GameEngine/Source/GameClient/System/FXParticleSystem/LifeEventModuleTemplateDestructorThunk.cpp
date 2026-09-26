// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LifeEventModuleTemplate destructor.

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
};

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
	virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
	virtual void unusedVirtual();

protected:
	~CategoryModuleInfo() {}
};

template <int Category>
class __declspec(novtable) CategoryModuleTemplateBase : public ModuleTemplate,
	public CategoryModuleInfo<Category>
{
public:
	virtual ~CategoryModuleTemplateBase() {}
};

template <int Category>
class __declspec(novtable) CategoryModuleTemplate
	: public CategoryModuleTemplateBase<Category>
{
public:
	virtual ~CategoryModuleTemplate() {}

private:
	bool m_enabled;
	bool m_inherited;
};

class LifeEventModuleInfoBase
{
public:
	virtual ~LifeEventModuleInfoBase() {}
};

class __declspec(novtable) LifeEventModuleInfo : public LifeEventModuleInfoBase
{
public:
	virtual ~LifeEventModuleInfo() {}

private:
	BFMERetailAsciiString m_buffer;
};

class __declspec(novtable) LifeEventModuleTemplate
	: public CategoryModuleTemplate<8>, public LifeEventModuleInfo
{
public:
	virtual ~LifeEventModuleTemplate();
};

// ??1LifeEventModuleTemplate@FXParticleSystem@@UAE@XZ
LifeEventModuleTemplate::~LifeEventModuleTemplate()
{
}

}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ModuleFactory method at retail 0x00127E80, 95 bytes.
//
// Same template-map lookup as newModule (0x00127E00): decorate the name,
// find the four-field ModuleTemplate at this+0xC, then call the +8 proc.
// addModuleInternal stores that third pointer; this body is the invoke side.
// No named caller, so the address stays in the name.
#include <map>

class AsciiString;

enum NameKeyType
{
};

enum ModuleType
{
};

class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		void *m_createProc;
		void *m_createDataProc;
		void *(__cdecl *m_field8)(void *, void *, void *);
		int m_whichInterfaces;
	};

	void *rva00127e80(const AsciiString &name, void *p, ModuleType type,
		void *a, void *b);

	virtual void init();

protected:
	static NameKeyType makeDecoratedNameKey(const AsciiString &name,
		ModuleType type);
	void *m_pad1;
	void *m_pad2;
	_STL::map<NameKeyType, ModuleTemplate> m_moduleTemplateMap;
};

// ?rva00127e80@ModuleFactory@@QAEPAXABVAsciiString@@PAXW4ModuleType@@11@Z
void *ModuleFactory::rva00127e80(const AsciiString &name, void *p,
	ModuleType type, void *a, void *b)
{
	if (p != 0)
	{
		NameKeyType key = makeDecoratedNameKey(name, type);
		_STL::map<NameKeyType, ModuleTemplate>::iterator it =
			m_moduleTemplateMap.find(key);
		if (it != m_moduleTemplateMap.end())
		{
			ModuleTemplate *mt = &it->second;
			if (mt != 0)
			{
				void *(__cdecl *proc)(void *, void *, void *) = mt->m_field8;
				if (proc != 0)
					return proc(p, b, a);
			}
		}
	}
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

class ControlBarScheme
{
public:
	~ControlBarScheme();
};

class ControlBarSchemeManager
{
public:
	~ControlBarSchemeManager();

private:
	ControlBarScheme *m_currentScheme;
	float m_multiplierX;
	float m_multiplierY;
	_STL::list<ControlBarScheme *> m_schemeList;
};

ControlBarSchemeManager::~ControlBarSchemeManager()
{
	_STL::list<ControlBarScheme *>::iterator it = m_schemeList.begin();
	while (it != m_schemeList.end())
	{
		ControlBarScheme *scheme = *it;
		if (scheme)
		{
			delete scheme;
		}
		it++;
	}
	m_schemeList.clear();
	m_currentScheme = 0;
}

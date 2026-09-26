// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Clean C++ definition for the third shadow manager's retail-default state.

class W3DShadowHelperManager
{
public:
	W3DShadowHelperManager();
	~W3DShadowHelperManager();

private:
	void *m_helper1;
	void *m_helper2;
	void *m_helper3;
	void *m_helper4;
	void *m_helper5;
	void *m_helper6;
	void *m_helper7;
};

W3DShadowHelperManager::W3DShadowHelperManager() :
	m_helper1(0),
	m_helper2(0),
	m_helper3(0),
	m_helper4(0),
	m_helper5(0),
	m_helper6(0),
	m_helper7(0)
{
}

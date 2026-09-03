class ShadowLightEnvironment007AF5A0
{
public:
	ShadowLightEnvironment007AF5A0();
	~ShadowLightEnvironment007AF5A0();

private:
	unsigned char m_data[0x228];
};

class ProjectedShadowManager
{
public:
	~ProjectedShadowManager();
};

class W3DProjectedShadowManager : public ProjectedShadowManager
{
public:
	W3DProjectedShadowManager();
	virtual ~W3DProjectedShadowManager();

private:
	void *m_04;
	void *m_08;
	void *m_0C;
	void *m_10;
	void *m_14;
	void *m_18;
	void *m_1C;
	void *m_20;
	ShadowLightEnvironment007AF5A0 m_lightEnvironment;
	void *m_24C;
	void *m_250;
};

W3DProjectedShadowManager::W3DProjectedShadowManager()
{
	m_0C = 0;
	m_04 = 0;
	m_08 = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_250 = 0;
	m_24C = 0;
	m_20 = 0;
}

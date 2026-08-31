// cl: /DNDEBUG /MD /EHsc

class Rva000441CAModuleDataBase
{
public:
	Rva000441CAModuleDataBase();
	virtual void moduleDataSlot();

private:
	char m_baseData[0x50];
};

class Rva00126080ModuleData : public Rva000441CAModuleDataBase
{
public:
	Rva00126080ModuleData();
	virtual void moduleDataSlot();

private:
	float m_value54;
	int m_value58;
	float m_value5C;
	float m_value60;
	float m_value64;
	int m_value68;
	int m_value6C;
	bool m_flag70;
};

Rva00126080ModuleData::Rva00126080ModuleData()
	: m_value54(0.0f),
	  m_value58(0),
	  m_value5C(0.5f),
	  m_value60(100.0f),
	  m_value64(0.5f),
	  m_value68(100),
	  m_value6C(5000),
	  m_flag70(false)
{
}

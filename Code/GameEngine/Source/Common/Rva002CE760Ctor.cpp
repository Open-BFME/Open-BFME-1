// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h
class DockUpdateModuleData
{
public:
	DockUpdateModuleData();
	virtual void handle();

private:
	char m_pad[0x0C];
};

class Rva002CE760 : public DockUpdateModuleData
{
	int m_10;
	int m_14;

public:
	Rva002CE760();
};

Rva002CE760::Rva002CE760()
{
	m_10 = 0;
	m_14 = 0;
}

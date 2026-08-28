// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportContain.h
class TransportContain
{
protected:
	virtual bool isSpecificRiderFreeToExit(Object *rider);
};

class Rva0022B290Obj : public TransportContain
{
public:
	bool allow(Object *rider);

private:
	char m_pad[0xEC - 4];
	unsigned char m_blocked;
};

bool Rva0022B290Obj::allow(Object *rider)
{
	if (m_blocked)
		return false;
	return TransportContain::isSpecificRiderFreeToExit(rider);
}

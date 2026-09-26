// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x00440A10 calls SuperweaponInfo::~SuperweaponInfo through ILT 0x000489BE.

class SuperweaponInfo
{
protected:
	virtual ~SuperweaponInfo();

private:
	friend void Force_SuperweaponInfo_Deleting_Destructor();
};

void Force_SuperweaponInfo_Deleting_Destructor()
{
	SuperweaponInfo info;
}

// Retail 0x0022D590: TransportContain::onCapture.

typedef int Int;
typedef bool Bool;

class Player;

enum DisabledType
{
	DISABLED_UNMANNED = 5
};

class Object
{
public:
	Bool isDisabledByType(DisabledType type) const
	{
		return (*((const unsigned char *)this + 0x1a4) & (1 << type)) != 0;
	}
};

#define CONTAIN_SLOT(n) virtual void containSlot##n();

class ContainModuleInterface
{
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26)
	virtual void orderAllPassengersToIdle(Int commandSource);
	CONTAIN_SLOT(28) CONTAIN_SLOT(29)
	virtual void bfmeCaptureAction(Int commandSource);
	CONTAIN_SLOT(31) CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34)
	CONTAIN_SLOT(35) CONTAIN_SLOT(36)
	virtual void bfmeFinishAGA(Bool exposeStealthUnits);
	CONTAIN_SLOT(38) CONTAIN_SLOT(39) CONTAIN_SLOT(40) CONTAIN_SLOT(41)
	CONTAIN_SLOT(42) CONTAIN_SLOT(43) CONTAIN_SLOT(44) CONTAIN_SLOT(45)
	CONTAIN_SLOT(46) CONTAIN_SLOT(47) CONTAIN_SLOT(48)
	virtual Bool bfmeCapturePredicate() const;
	CONTAIN_SLOT(50)
	virtual Player *bfmeCapturePlayer() const;
};

#undef CONTAIN_SLOT

class TransportContain
{
public:
	virtual void onCapture(Player *oldOwner, Player *newOwner);

private:
	Object *getObject() const
	{
		return *(Object *const *)((const char *)this + 8);
	}

	ContainModuleInterface *getContain() const
	{
		return (ContainModuleInterface *)((const char *)this + 0x20);
	}
};

// ?onCapture@TransportContain@@UAEXPAVPlayer@@0@Z
void TransportContain::onCapture(Player *oldOwner, Player *newOwner)
{
	if (oldOwner != newOwner)
	{
		if (getObject()->isDisabledByType(DISABLED_UNMANNED))
		{
			getContain()->bfmeFinishAGA(0);
		}
		else
		{
			ContainModuleInterface *contain = getContain();
			contain->orderAllPassengersToIdle(2);
			if (contain->bfmeCapturePredicate())
			{
				if (contain->bfmeCapturePlayer() != newOwner)
					contain->bfmeCaptureAction(2);
			}
		}
	}
}

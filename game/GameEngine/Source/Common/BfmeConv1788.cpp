class BfmeThingXK;

class BfmeInnerXK
{
public:
	BfmeThingXK *bfmeResolveXK(void);
};

class BfmeThingXK
{
public:
	int m_bfmeSpareXK;
	BfmeInnerXK *m_bfmeInnerXK;
	unsigned char m_bfmeGapXK[0x484];
	unsigned char m_bfmeAllowedXK;
};

class BfmeHolderXK
{
public:
	int m_bfmeSpareXK;
	BfmeThingXK *m_bfmeThingXK;
};

class BfmeTargetXK
{
public:
	virtual void bfmeT0XK(void);
	virtual void bfmeT1XK(void);
	virtual void bfmeT2XK(void);
	virtual void bfmeT3XK(void);
	virtual void bfmeT4XK(void);
	virtual void bfmeT5XK(void);
	virtual char bfmeOkXK(void);
};

class BfmeSubXK
{
public:
	virtual void bfmeS0XK(void);
	virtual void bfmeS1XK(void);
	virtual void bfmeS2XK(void);
	virtual void bfmeS3XK(void);
	virtual void bfmeS4XK(void);
	virtual void bfmeS5XK(void);
	virtual void bfmeS6XK(void);
	virtual void bfmeS7XK(void);
	virtual void bfmeS8XK(void);
	virtual void bfmeS9XK(void);
	virtual void bfmeS10XK(void);
	virtual void bfmeS11XK(void);
	virtual void bfmeS12XK(void);
	virtual void bfmeS13XK(void);
	virtual void bfmeS14XK(void);
	virtual void bfmeS15XK(void);
	virtual void bfmeS16XK(void);
	virtual void bfmeS17XK(void);
	virtual void bfmeS18XK(void);
	virtual void bfmeS19XK(void);
	virtual void bfmeS20XK(void);
	virtual void bfmeS21XK(void);
	virtual void bfmeS22XK(void);
	virtual void bfmeS23XK(void);
	virtual void bfmeS24XK(void);
	virtual void bfmeS25XK(void);
	virtual void bfmeS26XK(void);
	virtual void bfmeS27XK(void);
	virtual void bfmeS28XK(void);
	virtual void bfmeS29XK(void);
	virtual void bfmeS30XK(void);
	virtual void bfmeS31XK(void);
	virtual void bfmeS32XK(void);
	virtual void bfmeS33XK(void);
	virtual void bfmeS34XK(void);
	virtual void bfmeS35XK(void);
	virtual void bfmeS36XK(void);
	virtual void bfmeS37XK(void);
	virtual void bfmeS38XK(void);
	virtual void bfmeS39XK(void);
	virtual void bfmeS40XK(void);
	virtual void bfmeS41XK(void);
	virtual void bfmeS42XK(void);
	virtual void bfmeS43XK(void);
	virtual void bfmeS44XK(void);
	virtual void bfmeS45XK(void);
	virtual void bfmeS46XK(void);
	virtual void bfmeS47XK(void);
	virtual void bfmeS48XK(void);
	virtual void bfmeS49XK(void);
	virtual void bfmeS50XK(void);
	virtual void bfmeS51XK(void);
	virtual void bfmeS52XK(void);
	virtual void bfmeS53XK(void);
	virtual void bfmeS54XK(void);
	virtual void bfmeS55XK(void);
	virtual void bfmeS56XK(void);
	virtual void bfmeS57XK(void);
	virtual void bfmeS58XK(void);
	virtual void bfmeS59XK(void);
	virtual void bfmeS60XK(void);
	virtual void bfmeS61XK(void);
	virtual void bfmeS62XK(void);
	virtual void bfmeS63XK(void);
	virtual void bfmeS64XK(void);
	virtual void bfmeS65XK(void);
	virtual void bfmeS66XK(void);
	virtual void bfmeS67XK(void);
	virtual void bfmeS68XK(void);
	virtual void bfmeS69XK(void);
	virtual void bfmeS70XK(void);
	virtual void bfmeS71XK(void);
	virtual void bfmeS72XK(void);
	virtual void bfmeS73XK(void);
	virtual void bfmeS74XK(void);
	virtual void bfmeS75XK(void);
	virtual void bfmeS76XK(void);
	virtual void bfmeS77XK(void);
	virtual void bfmeS78XK(void);
	virtual void bfmeS79XK(void);
	virtual BfmeTargetXK *bfmePickXK(void);
};

class BfmeActorXK
{
public:
	unsigned char m_bfmeHeadXK[0x204];
	BfmeSubXK *m_bfmeSubXK;
};

bool __stdcall bfmeAllowXK(BfmeActorXK *actor, BfmeHolderXK *holder, int spare)
{
	if (holder)
	{
		BfmeThingXK *thing = holder->m_bfmeThingXK;

		if (thing && thing->m_bfmeInnerXK)
			thing = thing->m_bfmeInnerXK->bfmeResolveXK();

		if (thing->m_bfmeAllowedXK)
		{
			BfmeSubXK *sub = actor->m_bfmeSubXK;

			if (sub)
			{
				BfmeTargetXK *target = sub->bfmePickXK();

				if (target)
				{
					if (target->bfmeOkXK())
						return true;
				}
			}
		}
	}

	return false;
}

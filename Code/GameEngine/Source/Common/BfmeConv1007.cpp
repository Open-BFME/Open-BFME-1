// Open-BFME5 conversions.

struct BfmeSub1007
{
	char m_bfmePad[0x74];
	int m_bfmeId;
};

struct BfmeX1007
{
	char m_bfmePad[0xfc];
	BfmeSub1007 *m_bfmeSub;
};

class BfmeSrc1007
{
public:
	virtual void bfmeVS01007();
	virtual void bfmeVS11007();
	virtual void bfmeVS21007();
	virtual void bfmeVS31007();
	virtual void bfmeVS41007();
	virtual void bfmeVS51007();
	virtual void bfmeVS61007();
	virtual void bfmeVS71007();
	virtual void bfmeVS81007();
	virtual void bfmeVS91007();
	virtual void bfmeVS101007();
	virtual BfmeX1007 *bfmeFind1007(void *a);
};

extern BfmeSrc1007 *g_bfmeSrc1007;

enum BattlePlanStatus
{
	BfmeBattlePlanStatusNone = 0
};

enum DrawableID
{
	BfmeDrawableIDInvalid = 0
};

struct BfmeB1007Flags
{
	char m_bfmePad[ 0x38 ];
	unsigned char m_bfmeFlags;
};

class BattlePlanUpdate
{
public:
	BattlePlanStatus getActiveBattlePlan( void ) const;

	char m_bfmePad[ 0x08 ];
	BfmeB1007Flags *m_bfmeFlags;
};

class AudioEventRTS
{
public:
	DrawableID getDrawableID( void );
};

struct BfmeB1007Entry
{
	char m_bfmePad[ 0x14 ];
	void *m_bfmePayload;
};

struct BfmeB1007ListNode
{
	BfmeB1007ListNode *m_bfmeNext;
	BfmeB1007ListNode *m_bfmePrevious;
	BfmeB1007Entry *m_bfmeEntry;
};

class BfmeB1007
{
public:
	char bfmeGo1007B(void *a);
	char bfmeSend1007(int v, void *a);

	char m_bfmePad[ 0x9C8 ];
	BfmeB1007ListNode *m_bfmeFirstList;
	BfmeB1007ListNode *m_bfmeSecondList;
};

char BfmeB1007::bfmeGo1007B(void *a)
{
	if (!a)
		return 0;

	BfmeX1007 *x = g_bfmeSrc1007->bfmeFind1007(a);
	int v = 0;

	if (x && x->m_bfmeSub)
		v = x->m_bfmeSub->m_bfmeId;

	return bfmeSend1007(v, a);
}

char BfmeB1007::bfmeSend1007( int v, void *a )
{
	for( BfmeB1007ListNode *node = m_bfmeFirstList->m_bfmeNext;
		node != m_bfmeFirstList; node = node->m_bfmeNext )
	{
		if( ( (BattlePlanUpdate *)node->m_bfmeEntry->m_bfmePayload )
			->m_bfmeFlags->m_bfmeFlags & 0x10 )
		{
			if( ( (BattlePlanUpdate *)node->m_bfmeEntry->m_bfmePayload )
				->getActiveBattlePlan() == v )
			{
				return 1;
			}

			if( ( (AudioEventRTS *)node->m_bfmeEntry->m_bfmePayload )
				->getDrawableID() == (unsigned int)a )
			{
				return 1;
			}
		}
	}

	for( BfmeB1007ListNode *node = m_bfmeSecondList->m_bfmeNext;
		node != m_bfmeSecondList; node = node->m_bfmeNext )
	{
		if( ( (BattlePlanUpdate *)node->m_bfmeEntry->m_bfmePayload )
			->m_bfmeFlags->m_bfmeFlags & 0x10 )
		{
			if( ( (BattlePlanUpdate *)node->m_bfmeEntry->m_bfmePayload )
				->getActiveBattlePlan() == v )
			{
				return 1;
			}

			if( ( (AudioEventRTS *)node->m_bfmeEntry->m_bfmePayload )
				->getDrawableID() == (unsigned int)a )
			{
				return 1;
			}
		}
	}

	return 0;
}

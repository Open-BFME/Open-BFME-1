class BfmeVec3FW
{
public:
	float x;
	float y;
	float z;
};

class Gen_00609320
{
public:
	virtual void bfmeSlot0FW();
	virtual void bfmeSlot1FW();
	virtual void bfmeSlot2FW();
	virtual void bfmeSlot3FW();
	virtual void bfmeSlot4FW();
	virtual void bfmeSlot5FW();
	virtual void bfmeSlot6FW();
	virtual void bfmeSlot7FW();
	virtual void bfmeSlot8FW();
	virtual void bfmeSlot9FW();
	virtual void bfmeSlot10FW();
	virtual void bfmeSlot11FW();
	virtual void bfmeSlot12FW();
	virtual void bfmeSlot13FW();
	virtual void bfmeSlot14FW();
	virtual void bfmeSlot15FW();
	virtual void bfmeSlot16FW();
	virtual void bfmeGetFW(BfmeVec3FW *out);
};

class View
{
public:
	virtual void bfmeVSlot0FW();
	virtual void bfmeVSlot1FW();
	virtual void bfmeVSlot2FW();
	virtual void bfmeVSlot3FW();
	virtual void bfmeVSlot4FW();
	virtual void bfmeVSlot5FW();
	virtual void bfmeVSlot6FW();
	virtual void bfmeVSlot7FW();
	virtual void bfmeVSlot8FW();
	virtual void bfmeVSlot9FW();
	virtual void bfmeVSlot10FW();
	virtual void bfmeVSlot11FW();
	virtual void bfmeVSlot12FW();
	virtual void bfmeVSlot13FW();
	virtual void bfmeVSlot14FW();
	virtual void bfmeVSlot15FW();
	virtual void bfmeVSlot16FW();
	virtual void bfmeVSlot17FW();
	virtual void bfmeVSlot18FW();
	virtual void bfmeVSlot19FW();
	virtual void bfmeVSlot20FW();
	virtual void bfmeVSlot21FW();
	virtual void bfmeVSlot22FW();
	virtual void bfmeVSlot23FW();
	virtual void bfmeVSlot24FW();
	virtual void bfmeVSlot25FW();
	virtual void bfmeVSlot26FW();
	virtual void bfmeVSlot27FW();
	virtual void bfmeVSlot28FW();
	virtual void bfmeVSlot29FW();
	virtual void bfmeVSlot30FW();
	virtual void bfmeVSlot31FW();
	virtual void bfmeVSlot32FW();
	virtual void bfmeVSlot33FW();
	virtual void bfmeVSlot34FW();
	virtual void bfmeVSlot35FW();
	virtual void bfmeVSlot36FW();
	virtual void bfmeVSlot37FW();
	virtual void bfmeVSlot38FW();
	virtual void bfmeVSlot39FW();
	virtual void bfmeVSlot40FW();
	virtual void bfmeVSlot41FW();
	virtual void bfmeVSlot42FW();
	virtual void bfmeVSlot43FW();
	virtual void bfmeVSlot44FW();
	virtual void bfmeVSlot45FW();
	virtual void bfmeVSlot46FW();
	virtual void bfmeVSlot47FW();
	virtual void bfmeVSlot48FW();
	virtual void bfmeVSlot49FW();
	virtual void bfmeVSlot50FW();
	virtual void bfmeVSlot51FW();
	virtual void bfmeVSlot52FW();
	virtual void bfmeVSlot53FW();
	virtual void bfmeVSlot54FW();
	virtual void bfmeVSlot55FW();
	virtual void bfmeVSlot56FW();
	virtual void bfmeVSlot57FW();
	virtual void bfmeVSlot58FW();
	virtual void bfmeVSlot59FW();
	virtual void bfmeVSlot60FW();
	virtual void bfmeVSlot61FW();
	virtual void bfmeVSlot62FW();
	virtual void bfmeVSlot63FW();
	virtual void bfmeVSlot64FW();
	virtual void bfmeVSlot65FW();
	virtual void bfmeVSlot66FW();
	virtual void bfmeVSlot67FW();
	virtual void bfmeVSlot68FW();
	virtual void bfmeVSlot69FW();
	virtual const BfmeVec3FW *bfmeCenterFW();
};

extern Gen_00609320 *g_bfmeStateDF;
extern View *TheTacticalView;

class BfmeHostFW
{
public:
	void bfmeGetPosFW(BfmeVec3FW *out);

	unsigned char m_bfmeHeadFW[0x604];
	int m_bfmeModeFW;
};

void BfmeHostFW::bfmeGetPosFW(BfmeVec3FW *out)
{
	switch (m_bfmeModeFW)
	{
		case 0:
		{
			View *v = TheTacticalView;

			if (v != 0)
			{
				const BfmeVec3FW *p = v->bfmeCenterFW();

				out->x = p->x;
				out->y = p->y;
				out->z = p->z;

				return;
			}

			break;
		}

		case 1:
		{
			Gen_00609320 *s = g_bfmeStateDF;

			if (s != 0)
			{
				s->bfmeGetFW(out);

				return;
			}

			break;
		}
	}

	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
}

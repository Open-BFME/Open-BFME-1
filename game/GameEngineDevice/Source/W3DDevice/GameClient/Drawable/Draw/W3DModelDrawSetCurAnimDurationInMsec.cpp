// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME: W3DModelDraw::setCurAnimDurationInMsec, retail 0x0075BAF0.
// ZH computes frames*1000/rate then Set_Animation_Frame_Rate_Multiplier on the
// HLod; BFME stores that multiplier at this+0x80. Class_ID slot 3 == 0x19 is
// CLASSID_HLOD; Peek_Animation is slot 46 (+0xB8) per BFME rendobj.h.

class HAnimClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual int Get_Num_Frames(void);
	virtual float Get_Frame_Rate(void);
};

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual int Class_ID(void) const;
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual HAnimClass *Peek_Animation(void);
};

class W3DModelDraw
{
protected:
	bool setCurAnimDurationInMsec(float desiredDurationInMsec);

private:
	unsigned char m_pad[0x34];
	RenderObjClass *m_renderObject;
	unsigned char m_pad38[0x48];
	float m_animFrameRateMultiplier;
};

// ?setCurAnimDurationInMsec@W3DModelDraw@@IAE_NM@Z
bool W3DModelDraw::setCurAnimDurationInMsec(float desiredDurationInMsec)
{
	if (m_renderObject && m_renderObject->Class_ID() == 0x19)
	{
		HAnimClass *anim = m_renderObject->Peek_Animation();
		if (anim)
		{
			float naturalDurationInMsec =
				(float)anim->Get_Num_Frames() * 1000.0f / anim->Get_Frame_Rate();
			if (naturalDurationInMsec > 0.0f && desiredDurationInMsec > 0.0f)
			{
				m_animFrameRateMultiplier = naturalDurationInMsec / desiredDurationInMsec;
				return true;
			}
		}
	}
	return false;
}

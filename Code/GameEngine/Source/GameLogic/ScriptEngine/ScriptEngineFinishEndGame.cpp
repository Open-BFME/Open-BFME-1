// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

class Rva00367810GameLogic
{
public:
	bool isLivingWorld(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager
{
private:
	char m_bfmeGap[0x1d];

public:
	bool m_victorious;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class MessageStream
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void);
	virtual void appendMessage(int type);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void _bfme_finishEndGame(void);
};

#define TheGameLogic (*(Rva00367810GameLogic **)0x012F0898)
#define TheCampaignManager (*(CampaignManager **)0x012F1024)
#define TheMessageStream (*(MessageStream **)0x012ED5EC)

void ScriptEngine::_bfme_finishEndGame(void)
{
	if (TheGameLogic->isLivingWorld()) {
		if (TheCampaignManager->m_victorious) {
			TheMessageStream->appendMessage(2009);
		} else {
			TheMessageStream->appendMessage(2026);
		}
	} else {
		TheMessageStream->appendMessage(29);
	}
}

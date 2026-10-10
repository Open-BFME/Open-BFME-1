// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

// retail 0x003371A0 calls ILT 0x0001D1C9 -> 0x00382B50, the matched
// ?_bfme_isInLivingWorldCampaign@GameLogic@@QAE_NXZ row.
class GameLogic
{
public:
	bool _bfme_isInLivingWorldCampaign(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager
{
private:
	char m_bfmeGap[0x1d];

public:
	bool m_victorious;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void _bfme_finishEndGame(void);
};

extern GameLogic *TheGameLogic;
// data_rows.csv 0x012F1024 ?TheLivingWorldCampaignManager@@3PAVLivingWorldCampaignManager@@A
class LivingWorldCampaignManager;
extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;
extern MessageStream *TheMessageStream;

#define TheCampaignManager ((CampaignManager *)TheLivingWorldCampaignManager)

void ScriptEngine::_bfme_finishEndGame(void)
{
	if (TheGameLogic->_bfme_isInLivingWorldCampaign()) {
		if (TheCampaignManager->m_victorious) {
			TheMessageStream->appendMessage(2009);
		} else {
			TheMessageStream->appendMessage(2026);
		}
	} else {
		TheMessageStream->appendMessage(29);
	}
}

// cl: /DNDEBUG /MD /EHsc
// Retail 0x00382B50: true when the campaign object at 0x012F1028 has +0x2c set
// and the game is single-player (mode 0/7), a playback of those, or mode 6.

typedef int Int;
typedef bool ByteBool;

enum RecorderModeType
{
	RECORDERMODETYPE_PLAYBACK = 1
};

class RecorderClass
{
public:
	RecorderModeType getMode(void);

	char m_pad[0x2ac];
	Int m_recordedGameMode;
};

class CampaignObject
{
public:
	char m_pad[0x2c];
	char m_flag;
};

extern RecorderClass *TheRecorder;
extern CampaignObject *TheLivingWorldLogic;

class GameLogic
{
public:
	ByteBool _bfme_isInLivingWorldCampaign(void);

	char m_pad[0x10c];
	Int m_gameMode;
};

// ?_bfme_isInLivingWorldCampaign@GameLogic@@QAEEXZ
ByteBool GameLogic::_bfme_isInLivingWorldCampaign(void)
{
	GameLogic *self = this;
	Int mode = self->m_gameMode;
	if (mode != 0 && mode != 7)
	{
		if (TheRecorder && TheRecorder->getMode() == 1)
		{
			Int recorded = TheRecorder->m_recordedGameMode;
			if (recorded == 0 || recorded == 7)
				goto campaign;
		}
		if (self->m_gameMode != 6)
			return 0;
	}
campaign:
	CampaignObject *campaign = TheLivingWorldLogic;
	if (campaign && campaign->m_flag)
		return 1;
	return 0;
}

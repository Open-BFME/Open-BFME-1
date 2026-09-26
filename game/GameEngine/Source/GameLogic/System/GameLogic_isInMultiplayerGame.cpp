// ?_bfme_isInMultiplayerGame@GameLogic@@QAE_NXZ

typedef bool Bool;

enum RecorderModeType
{
	RECORDERMODETYPE_PLAYBACK = 1
};

class RecorderClass
{
public:
	RecorderModeType getMode(void);

	char m_pad[0x2ac];
	int m_recordedGameMode;
};

class GameLogic
{
public:
	Bool _bfme_isInMultiplayerGame(void);

	char m_pad[0x10c];
	int m_gameMode;
};

extern RecorderClass *TheRecorder;

Bool GameLogic::_bfme_isInMultiplayerGame(void)
{
	if (m_gameMode == 1)
		goto true_result;
	if (m_gameMode == 5)
		goto true_result;
	if (!TheRecorder)
		goto false_result;
	if (TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK)
		goto false_result;
	if (TheRecorder->m_recordedGameMode == 1)
		goto true_result;
	if (TheRecorder->m_recordedGameMode == 5)
		goto true_result;

false_result:
	return 0;

true_result:
	return 1;
}

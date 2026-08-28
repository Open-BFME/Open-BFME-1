// ?_bfme_isInMultiplayerOrSkirmishGame@GameLogic@@QAE_NXZ
// partial score=0.9 date=2026-08-28
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BFME's multiplayer-or-skirmish mode predicate.

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK
};

class RecorderClass
{
public:
	RecorderModeType getMode();
};

extern RecorderClass *TheRecorder;

class GameLogic
{
public:
	bool _bfme_isInMultiplayerOrSkirmishGame();
};

bool GameLogic::_bfme_isInMultiplayerOrSkirmishGame()
{
	int mode = *reinterpret_cast<const int *>(
		reinterpret_cast<const char *>(this) + 0x10c);
	for (;;)
	{
		if (mode == 1 || mode == 5 || mode == 2)
			return true;

		if (!TheRecorder ||
			TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK)
			break;

		mode = *reinterpret_cast<const int *>(
			reinterpret_cast<const char *>(TheRecorder) + 0x2ac);
		if (mode == 2 || mode == 1 || mode == 5)
			return true;
		break;
	}

	return false;
}

// cl: /DNDEBUG /MD /EHsc

class LANAPI
{
public:
	char m_fields[0x5c];
	volatile int m_activeGameWindow;
};

extern LANAPI *TheLAN;

struct LanGameGadgetState
{
	volatile int parentLanGameOptions;
	volatile int buttonEmote;
	volatile int buttonSelectMap;
	volatile int buttonStart;
	volatile int buttonBack;
	volatile int listboxChatWindow;
	volatile int textEntryChat;
	volatile int textEntryMapDisplay;
	volatile int checkboxLimitSuperweapons;
	volatile int comboBoxStartingCash;
	int comboBoxPlayer[7];
	int comboBoxColor[8];
	int comboBoxPlayerTemplate[8];
	int comboBoxTeam[8];
	int buttonAccept[8];
	int buttonMapStartPosition[8];
};

extern "C" LanGameGadgetState g_lanGameGadgets;

void DeinitLanGameGadgets()
{
	LANAPI *lan = TheLAN;
	int i;

	g_lanGameGadgets.parentLanGameOptions = 0;
	g_lanGameGadgets.buttonBack = 0;
	g_lanGameGadgets.buttonStart = 0;
	g_lanGameGadgets.buttonSelectMap = 0;
	g_lanGameGadgets.buttonEmote = 0;
	g_lanGameGadgets.checkboxLimitSuperweapons = 0;

	if (lan != 0)
		lan->m_activeGameWindow = 0;

	g_lanGameGadgets.listboxChatWindow = 0;
	g_lanGameGadgets.textEntryChat = 0;
	g_lanGameGadgets.textEntryMapDisplay = 0;
	g_lanGameGadgets.comboBoxStartingCash = 0;

	for (i = 0; i < 7; ++i) {
		g_lanGameGadgets.comboBoxPlayerTemplate[i] = 0;
		g_lanGameGadgets.comboBoxTeam[i] = 0;
		g_lanGameGadgets.buttonAccept[i] = 0;
		g_lanGameGadgets.comboBoxColor[i] = 0;
		g_lanGameGadgets.buttonMapStartPosition[i] = 0;
		g_lanGameGadgets.comboBoxPlayer[i] = 0;
	}

	g_lanGameGadgets.comboBoxPlayerTemplate[7] = 0;
	g_lanGameGadgets.comboBoxTeam[7] = 0;
	g_lanGameGadgets.buttonAccept[7] = 0;
	g_lanGameGadgets.comboBoxColor[7] = 0;
	g_lanGameGadgets.buttonMapStartPosition[7] = 0;
}

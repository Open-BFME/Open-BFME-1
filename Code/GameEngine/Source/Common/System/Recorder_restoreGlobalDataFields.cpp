// cl: /DNDEBUG /MD /EHsc

class GlobalData
{
public:
	char m_fields[0x11ec];
	unsigned char m_savedReplayFlag;
	char m_fields11ed[3];
	int m_savedReplayValue;
};

extern GlobalData *TheWritableGlobalData;
extern int g_recorderSavedGlobalValue;
extern unsigned char g_recorderSavedGlobalFlag;

class RecorderClass
{
public:
	void restoreGlobalDataFields();
};

void RecorderClass::restoreGlobalDataFields()
{
	TheWritableGlobalData->m_savedReplayFlag = g_recorderSavedGlobalFlag;
	TheWritableGlobalData->m_savedReplayValue = g_recorderSavedGlobalValue;
}

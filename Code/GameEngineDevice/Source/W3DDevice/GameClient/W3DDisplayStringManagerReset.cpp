// cl: /DNDEBUG /MD /EHsc

class RenderSentence
{
public:
	virtual void Reset();
};

struct W3DDisplayStringResetFields
{
	unsigned char m_padding00[0x0C];
	W3DDisplayStringResetFields *m_next;
	unsigned char m_padding10[0x04];
	RenderSentence m_textRenderer;
	unsigned char m_padding18[0xC8];
	RenderSentence m_textRendererHotKey;
	unsigned char m_paddingE4[0xC8];
	bool m_textChanged;
	unsigned char m_padding1AD[0x5B];
	unsigned int m_lastResourceFrame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayStringManager.h
class W3DDisplayStringManager
{
public:
	virtual void reset();

private:
	unsigned char m_padding04[0x04];
	W3DDisplayStringResetFields *m_stringList;
	W3DDisplayStringResetFields *m_currentCheckpoint;
};

void W3DDisplayStringManager::reset()
{
	W3DDisplayStringResetFields *string = m_stringList;
	while (string) {
		string->m_textRenderer.Reset();
		string->m_textRendererHotKey.Reset();
		string->m_textChanged = true;
		string->m_lastResourceFrame = 0;
		string = string->m_next;
	}
}

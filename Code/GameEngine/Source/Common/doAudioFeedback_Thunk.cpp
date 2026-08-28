// cl: /DNDEBUG /MD /EHsc
// Lift doAudioFeedback to clean C++ with the BFME GUI and audio layouts.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);                         ///< ILT thunk at 0x00046538
};

struct ListboxData
{
	unsigned char m_unreconstructed_00[0x0e];
	Bool audioFeedback;                                 ///< retail this+0x0e
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *name);
	~AsciiString();

private:
	void *m_data;
};

enum ObjectID
{
	OBJECT_ID_UNUSED = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString& eventName, ObjectID ownerID);
	virtual ~AudioEventRTS();

private:
	unsigned char m_unreconstructed_04[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual unsigned int addAudioEvent(const AudioEventRTS *eventToAdd);
};

extern AudioManager *TheAudio;                        ///< retail [0x012ED668]

// ?doAudioFeedback@@YAXPAVGameWindow@@@Z
__declspec(noinline) static void doAudioFeedback(GameWindow *window)
{
	if (!window)
		return;

	ListboxData *lData = (ListboxData *)window->winGetUserData();
	if (!lData)
		return;

	if (lData->audioFeedback)
	{
		AudioEventRTS buttonClick("GUIComboBoxClick", (ObjectID)2);

		if (TheAudio)
		{
			TheAudio->addAudioEvent(&buttonClick);
		}
	}
}

__declspec(noinline) void doAudioFeedbackAnchor(GameWindow *window)
{
	doAudioFeedback(window);
}

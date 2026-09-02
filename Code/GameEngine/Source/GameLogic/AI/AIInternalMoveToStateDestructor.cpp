// cl: /DNDEBUG /MD /EHsc
// Retail 0x00172430: AIInternalMoveToState removes its live movement-loop
// audio handle before the State base destructor runs.

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent( AudioHandle handle );
};

extern AudioManager *TheAudio;

class State
{
public:
	virtual ~State();

private:
	char m_state[ 0x3c ];
};

class AIInternalMoveToState : public State
{
public:
	virtual ~AIInternalMoveToState();

private:
	AudioHandle m_ambientPlayingHandle;
};

AIInternalMoveToState::~AIInternalMoveToState()
{
	if( TheAudio && m_ambientPlayingHandle >= 5 )
		TheAudio->removeAudioEvent( m_ambientPlayingHandle );
}

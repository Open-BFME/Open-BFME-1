// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x003C29D0. ScriptActions::executeAction arms 530 and 531 are
// SHOW_MISSION_OBJECTIVE and HIDE_MISSION_OBJECTIVE; their matched wrappers
// load TheLivingWorldLogic and pass the one-based script index minus one plus
// true/false to this method. The LivingWorldLogic constructor places its
// LivingWorldRegionManager at +0x28, the current region name at +0x30, and
// this two-byte-per-objective vector at +0x84.

#include <vector>

typedef bool Bool;
typedef int Int;

class AsciiString
{
public:
	Bool isNotEmpty() const { return m_data != 0; }

private:
	char *m_data;
};

struct LivingWorldRegionPointerVector
{
	void **m_begin;
	void **m_end;
	void **m_capacity;

	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}
};

class LivingWorldRegion
{
public:
	unsigned int missionObjectiveCount() const
	{
		return m_primaryObjectives.size() + m_secondaryObjectives.size();
	}

private:
	unsigned char m_unmodelled00[0x54];
	LivingWorldRegionPointerVector m_primaryObjectives;
	LivingWorldRegionPointerVector m_secondaryObjectives;
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50(const AsciiString &regionName);
};

struct MissionObjectiveState
{
	Bool m_visible;
	Bool m_completed;
};

typedef _STL::vector<MissionObjectiveState,
	_STL::allocator<MissionObjectiveState> > MissionObjectiveStateVector;

class PlayerTemplate
{
public:
	const AsciiString &getMissionObjectiveVisibleSound() const
	{
		return m_missionObjectiveVisibleSound;
	}

private:
	unsigned char m_unmodelled00[0x104];
	AsciiString m_missionObjectiveVisibleSound;
};

class Player
{
public:
	PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	void *m_vtable;
	PlayerTemplate *m_playerTemplate;
	unsigned char m_unmodelled08[0x1c];
	Int m_playerIndex;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

private:
	unsigned char m_unmodelled00[0x0c];
	Player *m_localPlayer;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, Int extra);
	virtual void slot00();
	~AudioEventRTS();
	void setPlayerIndex(Int index);

private:
	unsigned char m_beforeUninterruptable[0x3f];
	Bool m_uninterruptable;
	unsigned char m_beforeMusicFields[0x20];
	Int m_musicStackValue;
	Int m_musicPlayCount;
	AsciiString m_scriptName;
};

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual AudioHandle addAudioEvent(const AudioEventRTS *event) = 0;
};

extern PlayerList *ThePlayerList;
extern AudioManager *TheAudio;

class LivingWorldLogic
{
public:
	void setMissionObjectiveVisible(Int objectiveIndex, Bool visible);

private:
	unsigned char m_unmodelled00[0x28];
	LivingWorldRegionManager *m_regionManager;
	unsigned char m_unmodelled2C[4];
	AsciiString m_currentRegionName;
	unsigned char m_unmodelled34[0x50];
	MissionObjectiveStateVector m_missionObjectiveStates;
};

void LivingWorldLogic::setMissionObjectiveVisible(Int objectiveIndex, Bool visible)
{
	if (m_regionManager == 0 || objectiveIndex < 0)
		return;

	LivingWorldRegion *region =
		m_regionManager->rva003C8A50(m_currentRegionName);
	if (region == 0)
		return;

	if ((unsigned int)objectiveIndex >= m_missionObjectiveStates.size())
	{
		if ((unsigned int)objectiveIndex >= region->missionObjectiveCount())
			return;

		while (m_missionObjectiveStates.size() <=
			(unsigned int)objectiveIndex)
		{
			__declspec(align(1)) MissionObjectiveState initialState;
			initialState.m_visible = true;
			initialState.m_completed = false;
			m_missionObjectiveStates.push_back(initialState);
		}
	}

	MissionObjectiveState *states = reinterpret_cast<MissionObjectiveState *>(
		&m_missionObjectiveStates[0]);
	Bool wasVisible = states[objectiveIndex].m_visible;
	states[objectiveIndex].m_visible = visible;

	if (TheAudio != 0 && !wasVisible && visible)
	{
		if (ThePlayerList->getLocalPlayer() != 0 &&
			ThePlayerList->getLocalPlayer()->getPlayerTemplate() != 0 &&
			ThePlayerList->getLocalPlayer()->getPlayerTemplate()->
				getMissionObjectiveVisibleSound().isNotEmpty())
		{
			AudioEventRTS event(
				ThePlayerList->getLocalPlayer()->getPlayerTemplate()->
					getMissionObjectiveVisibleSound(), 2);
			event.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
			TheAudio->addAudioEvent(&event);
		}
	}
}

// ?setMissionObjectiveCompleted@LivingWorldLogic@@QAEXH_N@Z
// partial score=0.95 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x003C2BD0. ScriptActions::executeAction arms 532 and 533 are
// MARK_MISSION_OBJECTIVE_COMPLETED and MARK_MISSION_OBJECTIVE_NOT_COMPLETED.
// Their matched caller and action-template strings prove this method identity.

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
	const AsciiString &getMissionObjectiveCompletedSound() const
	{
		return m_missionObjectiveCompletedSound;
	}

private:
	unsigned char m_unmodelled00[0x108];
	AsciiString m_missionObjectiveCompletedSound;
};

class Player
{
public:
	PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Int getPlayerIndex() const { return m_playerIndex; }
	void addSciencePurchasePoints(Int delta);

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
	void setMissionObjectiveCompleted(Int objectiveIndex, Bool completed);

private:
	unsigned char m_unmodelled00[0x28];
	LivingWorldRegionManager *m_regionManager;
	unsigned char m_unmodelled2C[4];
	AsciiString m_currentRegionName;
	unsigned char m_unmodelled34[0x50];
	MissionObjectiveStateVector m_missionObjectiveStates;
};

void LivingWorldLogic::setMissionObjectiveCompleted(
	Int objectiveIndex, Bool completed)
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

	MissionObjectiveState *states = m_missionObjectiveStates.begin();
	Bool wasCompleted = states[objectiveIndex].m_completed;
	states[objectiveIndex].m_completed = completed;

	if (TheAudio != 0 && !wasCompleted && completed)
	{
		if (ThePlayerList->getLocalPlayer() != 0 &&
			ThePlayerList->getLocalPlayer()->getPlayerTemplate() != 0 &&
			ThePlayerList->getLocalPlayer()->getPlayerTemplate()->
				getMissionObjectiveCompletedSound().isNotEmpty())
		{
			AudioEventRTS event(
				ThePlayerList->getLocalPlayer()->getPlayerTemplate()->
					getMissionObjectiveCompletedSound(), 2);
			event.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
			TheAudio->addAudioEvent(&event);
		}
	}

	if (m_missionObjectiveStates.size() >= region->missionObjectiveCount())
	{
		Int completedCount = 0;
		for (unsigned int i = 0; i < m_missionObjectiveStates.size(); ++i)
		{
			if (states[i].m_completed)
				++completedCount;
		}

		if ((unsigned int)completedCount == m_missionObjectiveStates.size())
			ThePlayerList->getLocalPlayer()->addSciencePurchasePoints(1);
	}
}

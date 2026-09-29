// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ??0Mission@@QAE@XZ: game/GameEngine/Source/GameClient/System/CampaignManager.cpp
// Retail Mission constructor (RVA005BB9B0), destructor (RVA005BBA80),
// and scalar deleting destructor (RVA005BBDF0), with the verified BFME layout.

#include "ascii_string.h"

enum ObjectID {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName = AsciiString::TheEmptyString, ObjectID ownerID = (ObjectID)2);
	~AudioEventRTS();

private:
	unsigned char m_data[112];
};

// BFME lifetime view: the retail Mission table has one deleting-destructor
// slot (VA0110F658 -> ILT0044534A -> RVA005BBDF0). There is no separate
// deleteInstance slot or base-destructor unwind state. The former Generals
// pool-base declaration emitted a second, incorrect virtual slot.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Mission
{
public:
	Mission();
	virtual ~Mission();

private:
	AsciiString m_name;
	AsciiString m_mapName;
	AsciiString m_nextMission;
	AsciiString m_movieLabel;
	AsciiString m_missionObjectivesLabel[5];
	AudioEventRTS m_briefingVoice;
	AsciiString m_locationNameLabel;
	AsciiString m_unitNames[3];
	int m_voiceLength;
};

Mission::Mission() : m_voiceLength(0)
{
}

Mission::~Mission() {}

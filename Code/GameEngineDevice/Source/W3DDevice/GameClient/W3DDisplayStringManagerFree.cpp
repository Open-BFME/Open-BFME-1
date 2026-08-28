// cl: /DNDEBUG /MD /EHsc
// readable body of ?freeDisplayString@W3DDisplayStringManager@@UAEXPAVDisplayString@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayStringManager.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual ~DisplayString();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual ~DisplayStringManager();

protected:
	void unLink(DisplayString *string);

	unsigned char m_padding04[0x04];
	DisplayString *m_stringList;
	DisplayString *m_currentCheckpoint;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayStringManager.h
class W3DDisplayStringManager : public DisplayStringManager
{
public:
	virtual void freeDisplayString(DisplayString *string);
};

void W3DDisplayStringManager::freeDisplayString(DisplayString *string)
{
	if (!string) {
		return;
	}

	unLink(string);
	if (m_currentCheckpoint == string) {
		m_currentCheckpoint = 0;
	}
	delete string;
}

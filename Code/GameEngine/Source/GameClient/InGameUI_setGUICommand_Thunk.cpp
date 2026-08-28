// cl: /DNDEBUG /MD /EHsc
// readable body of ?setGUICommand@InGameUI@@UAEXPBVCommandButton@@@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// Open-BFME5: recovered command-selection logic with the BFME retail ABI.

enum RecorderModeType { RECORDER_MODE_PLAYBACK = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	RecorderModeType getMode();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	bool isContextCommand() const;
	int getOptions() const { return m_options; }
	const void *getSpecialPowerTemplate() const { return m_specialPowerTemplate; }
	int getRadiusCursorType() const { return m_radiusCursorType; }
	int getWeaponSlot() const { return m_weaponSlot; }

private:
	unsigned char m_pad0[0x18];
	int m_options;
	unsigned char m_pad1[0x18];
	const void *m_specialPowerTemplate;
	int m_radiusCursorType;
	unsigned char m_pad2[0x30];
	int m_weaponSlot;
};

class Mouse
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13();
	virtual void setMouseCursor(int);
	int getMouseCursor() const { return m_mouseCursor; }

private:
	unsigned char m_pad[0x4DA4];
	int m_mouseCursor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void setGUICommand(const CommandButton *);
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
	virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
	virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
	virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56();
	virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
	virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68();
	virtual void v69();
	virtual void setRadiusCursor(int, const void *, int, bool);
	virtual void setRadiusCursorNone();

private:
	unsigned char m_pad0[0x22C];
	const CommandButton *m_pendingGUICommand;
	unsigned char m_pad1[0x5F0];
	int m_mouseMode;
	int m_mouseModeCursor;
};

extern RecorderClass *TheRecorder;
extern Mouse *TheMouse;

void InGameUI::setGUICommand(const CommandButton *command)
{
	if (TheRecorder && TheRecorder->getMode() == 1) return;
	if (command) {
		if ((command->getOptions() & 0x227) == 0) {
			m_pendingGUICommand = 0;
			m_mouseMode = 0;
			return;
		}
		m_mouseMode = 2;
	} else {
		m_mouseMode = 0;
	}
	m_pendingGUICommand = command;
	if (command && (command->getOptions() & 0x227) && !command->isContextCommand()) {
		if (TheMouse) TheMouse->setMouseCursor(2);
		setRadiusCursor(command->getRadiusCursorType(), command->getSpecialPowerTemplate(), command->getWeaponSlot(), true);
	} else {
		if (TheMouse) TheMouse->setMouseCursor(2);
		setRadiusCursorNone();
	}
	m_mouseModeCursor = TheMouse->getMouseCursor();
}

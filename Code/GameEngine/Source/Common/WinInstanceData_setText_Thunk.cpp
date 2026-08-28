// cl: /DNDEBUG /MD /EHsc
// readable body of ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z: Code/GameEngine/Source/GameClient/GUI/WinInstanceData.cpp
// Open-BFME5: lift the WinInstanceData::setText MASM dump to clean C++.
//
// Same StringBase<unsigned short> friend shim as GameWindow::winSetText: private
// constructors on the base are what mangle the copy and destructor to
// ??0?$StringBase@G@@AAE@ABV0@@Z and ??1?$StringBase@G@@AAE@XZ.
//
// The display string at this+0x19C is created on first use through the manager
// global's tenth virtual, then given the text through its second. The by-value
// parameter is copied for that call and destroyed here at the end, which is
// MSVC's callee-destroys rule for value parameters.

class UnicodeString;

template <class T>
class StringBase
{
private:
	friend class UnicodeString;

	StringBase(const StringBase<T> &other);		///< body at 0x00888400
	~StringBase();								///< body at 0x008881D0

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void displayStringSlot0();
	virtual void setText(UnicodeString text);	///< vtable +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void managerSlot0();
	virtual void managerSlot1();
	virtual void managerSlot2();
	virtual void managerSlot3();
	virtual void managerSlot4();
	virtual void managerSlot5();
	virtual void managerSlot6();
	virtual void managerSlot7();
	virtual void managerSlot8();
	virtual DisplayString *newDisplayString();	///< vtable +0x24
};

extern DisplayStringManager *TheDisplayStringManager;	///< retail [0x012F12CC]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	void setText(UnicodeString text);

	unsigned char m_unreconstructed_00[0x19C];
	DisplayString *m_text;						///< retail this+0x19C
};

// ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z
void WinInstanceData::setText(UnicodeString text)
{
	if (m_text == 0)
	{
		m_text = TheDisplayStringManager->newDisplayString();
	}

	m_text->setText(text);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the GameWindow::winSetText MASM dump to clean C++.
//
// The string body lives on StringBase<unsigned short> with private constructors
// and UnicodeString as the friend, which is what mangles the copy and the
// destructor to ??0?$StringBase@G@@AAE@ABV0@@Z and ??1?$StringBase@G@@AAE@XZ
// rather than to UnicodeString's own names.
//
// The by-value parameter is copied once for the instance-data setter and then
// passed by address to the callback's fourth virtual, and MSVC destroys the
// parameter in the callee, which is the trailing releaseBuffer call.

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

// Shim so the call keeps retail's ILT thunk at 0x00004205 rather than resolving
// to the matched WinInstanceData::setText body directly.
class WinInstanceDataShim
{
public:
	void setText(UnicodeString text);
};

class GameWindowCallback
{
public:
	virtual void callbackSlot0();
	virtual void callbackSlot1();
	virtual void callbackSlot2();
	virtual void onTextChanged(UnicodeString *text);	///< vtable +0xC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	virtual int winSetText(UnicodeString text);

	GameWindowCallback *m_callback;				///< retail this+0x04
	unsigned char m_unreconstructed_08[0x28];
	WinInstanceDataShim m_instData;				///< retail this+0x30
};

// ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z
int GameWindow::winSetText(UnicodeString text)
{
	m_instData.setText(text);

	if (m_callback != 0)
	{
		m_callback->onTextChanged(&text);
	}

	return 0;
}

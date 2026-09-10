// cl: /DNDEBUG /MD /EHsc

/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// BFME's MessageBoxSystem callback.  Its four button names and callback-data
// layout are the retail operands/layout, rather than the generic placeholders
// in the banked probe.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;
typedef int Int;
typedef bool Bool;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

enum
{
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 0x17,
	GBM_SELECTED = 0x4008
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

template <typename T>
class StringBase
{
    friend class BFMERetailAsciiString;

protected:
	T *m_data;

private:
	StringBase(const T *text);
	void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text)
		: StringBase<char>(text)
	{
	}
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const BFMERetailAsciiString &name)
	{
		return nameToKey(name.str());
	}
};

extern NameKeyGenerator *TheNameKeyGenerator;

typedef void (*GameWinMsgBoxFunc)(void);

struct WindowMessageBoxData
{
	GameWinMsgBoxFunc yesCallback;
	GameWinMsgBoxFunc noCallback;
	GameWinMsgBoxFunc okCallback;
	GameWinMsgBoxFunc cancelCallback;
};

class GameWindow
{
public:
	Int winGetWindowId();
	void *winGetUserData();
	void winSetUserData(void *userData);
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual Int winDestroy(GameWindow *window);
};

extern GameWindowManager *TheWindowManager;

// ?MessageBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType MessageBoxSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	switch (msg)
	{
	case GWM_DESTROY:
	{
		delete (WindowMessageBoxData *)window->winGetUserData();
		window->winSetUserData(0);
		break;
	}

	case GWM_INPUT_FOCUS:
	{
		if (mData1 == 1)
			*(Bool *)mData2 = 1;
		break;
	}

	case GBM_SELECTED:
	{
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();
		static NameKeyType buttonOkID = TheNameKeyGenerator->nameToKey(
			BFMERetailAsciiString("MessageBox.wnd:ButtonOk"));
		static NameKeyType buttonYesID = TheNameKeyGenerator->nameToKey(
			BFMERetailAsciiString("MessageBox.wnd:ButtonYes"));
		static NameKeyType buttonNoID = TheNameKeyGenerator->nameToKey(
			BFMERetailAsciiString("MessageBox.wnd:ButtonNo"));
		static NameKeyType buttonCancelID = TheNameKeyGenerator->nameToKey(
			BFMERetailAsciiString("MessageBox.wnd:ButtonCancel"));
		WindowMessageBoxData *callbacks =
			(WindowMessageBoxData *)window->winGetUserData();

		if (controlID == buttonOkID)
		{
			if (callbacks->okCallback)
				callbacks->okCallback();
			TheWindowManager->winDestroy(window);
		}
		else if (controlID == buttonYesID)
		{
			if (callbacks->yesCallback)
				callbacks->yesCallback();
			TheWindowManager->winDestroy(window);
		}
		else if (controlID == buttonNoID)
		{
			if (callbacks->noCallback)
				callbacks->noCallback();
			TheWindowManager->winDestroy(window);
		}
		else if (controlID == buttonCancelID)
		{
			if (callbacks->cancelCallback)
				callbacks->cancelCallback();
			TheWindowManager->winDestroy(window);
		}
		break;
	}

	default:
		return MSG_IGNORED;
	}

	return MSG_HANDLED;
}

// ?drawThirdDebugDisplay@W3DDisplay@@QAEXXZ
// partial score=0.86 date=2026-09-09
// cl: /O2 /Ob0 /EHsc

class DebugDisplayInterface
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
	virtual void reset();
};

typedef void DebugDisplayCallback(DebugDisplayInterface *, void *, void *);

// The debug overlay uses the BFME DisplayString ABI slice.  The complete
// DisplayString class has these methods at the witnessed slots; the unused
// declarations are kept local so this TU does not move a shared header.
class Rva006E8800DisplayString
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void color006e(int color, unsigned int dropColor) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void place006e(int x, int y, int width, int height) = 0;
	virtual void size006e(int *width, int *height) = 0;
};

// This is the eight-record GameLogic status returned by the existing matched
// getPlayerLeaveStatus body at 0x00383B90.  The overlay only reads the fields
// below, but retaining the proven record offsets documents the ABI slice.
struct PlayerLeaveStatus
{
	int status;
	int quitFrame;
	int defeatFrame;
	int victoryFrame;
	bool notPresent;
	char padding[3];
	int isHuman;
	char playerName[4];
};

class GameLogic
{
public:
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex);
	char m_padding00[0x3c];
	int m_frame;
};

// The slots used here are independently named by the BFME Network vtable at
// 0x0111A968: isPacketRouter (+0x8c), getFramesBehindPacketRouter (+0xcc),
// and getPlayerLatestFrame (+0xd8).  The intervening slots are deliberately
// unnamed ABI padding, not semantic wrappers.
class Network
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot3c(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot4c(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot5c(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot64(void) = 0;
	virtual void slot68(void) = 0;
	virtual void slot6c(void) = 0;
	virtual void slot70(void) = 0;
	virtual void slot74(void) = 0;
	virtual void slot78(void) = 0;
	virtual void slot7c(void) = 0;
	virtual void slot80(void) = 0;
	virtual void slot84(void) = 0;
	virtual void slot88(void) = 0;
	virtual bool isPacketRouter(void) = 0;
	virtual void slot90(void) = 0;
	virtual void slot94(void) = 0;
	virtual void slot98(void) = 0;
	virtual void slot9c(void) = 0;
	virtual void slota0(void) = 0;
	virtual void slota4(void) = 0;
	virtual void slota8(void) = 0;
	virtual void slotac(void) = 0;
	virtual void slotb0(void) = 0;
	virtual void slotb4(void) = 0;
	virtual void slotb8(void) = 0;
	virtual void slotbc(void) = 0;
	virtual void slotc0(void) = 0;
	virtual void slotc4(void) = 0;
	virtual void slotc8(void) = 0;
	virtual int getFramesBehindPacketRouter(void) = 0;
	virtual void slotd0(void) = 0;
	virtual void slotd4(void) = 0;
	virtual int getPlayerLatestFrame(int playerIndex) = 0;
};

#define TheNetwork (*(Network **)0x012F7714)
#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class W3DDisplay
{
public:
	virtual void slot00();
	void drawDisplayStrings();
	void drawDebugStats();
	void drawThirdDebugDisplay();

	protected:
	void drawCurrentDebugDisplay();

private:
	char m_padding04[0x24];
	DebugDisplayInterface *m_debugDisplay;
	DebugDisplayCallback *m_debugDisplayCallback;
	void *m_debugDisplayUserData;
	char m_padding34[0x22c - 0x34];
	Rva006E8800DisplayString *m_displayStrings[17];
};

void W3DDisplay::drawThirdDebugDisplay()
{
	int y = 3;
	bool flip = false;
	int i = 0;

	for (; i < 17; ++i)
	{
		int color;
		if (i < 10 || i > 16)
		{
			color = -1;
			if (i == 8)
		{
			if (TheNetwork != 0 && !TheNetwork->isPacketRouter())
			{
				switch (TheNetwork->getFramesBehindPacketRouter())
				{
				case 1: color = 0xffffffa0; break;
				case 2: color = 0xffa0ffa0; break;
				case 3: color = 0xffa0a0ff; break;
				case 4: color = 0xff9696ff; break;
				case 5: color = 0xff9696ff; break;
				case 6: color = 0xff8c8cff; break;
				case 7: color = 0xff8282ff; break;
				case 8: color = 0xff7878ff; break;
				case 9: color = 0xff6e6eff; break;
				case 0:
					if (*(int *)0x012F8054 + 5 >= TheBfmeGameLogic->m_frame)
						color = 0xffff0000;
					else
					{
						color = (*(unsigned char *)0x012F81A9) ? -1 : 0xffff0000;
						flip = true;
					}
					break;
				default:
					color = (*(unsigned char *)0x012F81A9) ? -1 : 0xffff0000;
					flip = true;
					break;
				}
			}
		}
		else if (i == 9)
		{
			if (*(int *)0x012F8054 + 5 >= TheBfmeGameLogic->m_frame)
				color = (*(unsigned char *)0x012F81A9) ? -1 : 0xffff0000;
		}
		else if (i == 7)
		{
			if (TheNetwork != 0 && !TheNetwork->isPacketRouter())
				color = 0xffffc8c8;
		}
		}
		else
		{
			Network *network = TheNetwork;
			if (network == 0)
				continue;

			int playerIndex = i - 9;
			PlayerLeaveStatus *player =
				TheBfmeGameLogic->getPlayerLeaveStatus(playerIndex);
			if (player->notPresent)
				continue;

			if (player->isHuman == 1)
			{
				color = 0xffc8a0e1;
			}
			else if (!TheNetwork->isPacketRouter())
			{
				color = 0xffc8c8a0;
			}
			else
			{
				int frame = TheNetwork->getPlayerLatestFrame(playerIndex) +
					(10 - TheBfmeGameLogic->m_frame);
				switch (frame)
				{
				case 0: color = 0xffffffa0; break;
				case 1: color = 0xffa0ffa0; break;
				case 2: color = 0xffa0a0ff; break;
				case 3: color = 0xff9696ff; break;
				case 4: color = 0xff8c8cff; break;
				case 5: color = 0xff8282ff; break;
				case 6: color = 0xff8282ff; break;
				case 7: color = 0xff7878ff; break;
				case 8: color = 0xff6e6eff; break;
				default:
					color = (*(unsigned char *)0x012F81A9) ? -1 : 0xffff0000;
					flip = true;
					break;
				}
			}

			if (player->status != 0)
				color = 0xc8a06464;
			else if (player->isHuman == 0)
			{
				if (player->victoryFrame != 0)
					color = 0xff64c8c8;
				else if (player->defeatFrame != 0)
					color = 0xffc89664;
			}
			else if (player->isHuman == 1)
			{
				if (player->victoryFrame != 0)
					color = 0xffdca0ff;
				else if (player->defeatFrame != 0)
					color = 0xff9664af;
			}
		}

		int width;
		int height;
		m_displayStrings[i]->color006e(color, 0xff000000u);
		m_displayStrings[i]->place006e(3, y, 1, 1);
		m_displayStrings[i]->size006e(&width, &height);
		y += height;
	}

	if (flip)
		*(unsigned char *)0x012F81A9 =
			*(unsigned char *)0x012F81A9 ? 0 : 1;
}

void W3DDisplay::drawCurrentDebugDisplay()
{
	if (m_debugDisplayCallback ==
		reinterpret_cast<DebugDisplayCallback *>(0x0042f9f0))
	{
		drawDisplayStrings();
		return;
	}

	if (m_debugDisplayCallback ==
		reinterpret_cast<DebugDisplayCallback *>(0x0043413f))
	{
		drawDebugStats();
		return;
	}

	if (m_debugDisplayCallback ==
		reinterpret_cast<DebugDisplayCallback *>(0x0040d779))
	{
		drawThirdDebugDisplay();
		return;
	}

	if (m_debugDisplay != 0 && m_debugDisplayCallback != 0)
	{
		m_debugDisplay->reset();
		m_debugDisplayCallback(m_debugDisplay, m_debugDisplayUserData, 0);
	}
}

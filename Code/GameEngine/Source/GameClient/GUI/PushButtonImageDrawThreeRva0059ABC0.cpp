// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Retail 0x0059ABC0 is the 952-byte three-image push-button draw helper.  The
// body is the Zero Hour PushButtonImageDrawThree twin.  All ten call sites
// (0x0059B20D..0x0059B632) reach it through ILT 0x0004B457 and none is a
// matched caller that names it, so the identity keeps the address token.
//
// BFME's ICoord2D has a user-declared empty constructor (??0ICoord2D@@QAE@XZ,
// 0x00083360).  It makes the struct non-POD, and that is what gives the
// retail association order of the x sums (xOffset before origin.x).
//
// Display::drawImage is the inline begin/draw/end wrapper whose out-of-line
// copy is ILT 0x0000A114 (0x0040D900).  VC7.1 inlines it in the loop and the
// two end draws and calls it at the other three sites, as retail does.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

#define NULL 0
#define FALSE 0


struct ICoord2D
{
	Int x;
	Int y;
	ICoord2D() {}
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Image
{
public:
	Int getImageWidth(void) const { return m_imageSize.x; }
	Int getImageHeight(void) const { return m_imageSize.y; }

private:
	unsigned char m_unreconstructed_00[0x24];
	ICoord2D m_imageSize; // retail this+0x24
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class WinInstanceData
{
public:
	virtual ~WinInstanceData(void);
	unsigned char m_unreconstructed_004[0x14];
	WinDrawData m_enabledDrawData[9]; // retail this+0x18
	unsigned char m_unreconstructed_084[0xF8];
	ICoord2D m_imageOffset; // retail this+0x17c
};

class GameWindow
{
public:
	virtual void winDrawBorder(void) = 0;
	WinInstanceData *winGetInstanceData(void);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);

	const Image *winGetEnabledImage(Int index)
	{
		return m_instData.m_enabledDrawData[index].image;
	}

private:
	unsigned char m_unreconstructed_04[0x2C];
	WinInstanceData m_instData; // retail this+0x30
};

class Display
{
public:
	virtual void unused00(); virtual void unused01();
	virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09();
	virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13();
	virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21();
	virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25();
	virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33();
	virtual void setClipRegion(IRegion2D *region);
	virtual void unused35();
	virtual void enableClipping(Bool onoff);
	virtual void unused37(); virtual void unused38();
	virtual void unused39(); virtual void unused40();
	virtual void unused41(); virtual void unused42();
	virtual void unused43(); virtual void vfuncB0();
	virtual void unused45(); virtual void unused46();
	virtual void unused47(); virtual void unused48();
	virtual void unused49(); virtual void unused50();
	virtual void unused51(); virtual void unused52();
	virtual void vfuncD4(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode);
	virtual void unused54();
	virtual void vfuncDC(void);

	void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode = 2)
	{
		vfuncB0();
		vfuncD4(image, startX, startY, endX, endY, color, mode);
		vfuncDC();
	}
};

extern Display *TheDisplay;

inline const Image *GadgetButtonGetLeftEnabledImage(GameWindow *window)
{
	return window->winGetEnabledImage(0);
}

inline const Image *GadgetButtonGetMiddleEnabledImage(GameWindow *window)
{
	return window->winGetEnabledImage(5);
}

inline const Image *GadgetButtonGetRightEnabledImage(GameWindow *window)
{
	return window->winGetEnabledImage(6);
}

inline Color GameMakeColor(unsigned char, unsigned char, unsigned char,
	unsigned char alpha)
{
	return (alpha << 24) | 0x00ffffff;
}

namespace Rva0059ABC0
{
	void PushButtonImageDrawThree(GameWindow *window, Int alpha)
	{
		WinInstanceData *instData = window->winGetInstanceData();
		const Image *leftImage, *rightImage, *centerImage;
		ICoord2D origin, size, start, end;
		Int xOffset, yOffset;
		Int i;
		Int color = GameMakeColor(255,255,255,alpha);

		window->winGetScreenPosition(&origin.x, &origin.y);
		window->winGetSize(&size.x, &size.y);

		xOffset = instData->m_imageOffset.x;
		yOffset = instData->m_imageOffset.y;

		leftImage = GadgetButtonGetLeftEnabledImage(window);
		rightImage = GadgetButtonGetRightEnabledImage(window);
		centerImage = GadgetButtonGetMiddleEnabledImage(window);

		if (leftImage == NULL || rightImage == NULL || centerImage == NULL)
			return;

		ICoord2D leftSize, rightSize;
		leftSize.x = leftImage->getImageWidth();
		leftSize.y = leftImage->getImageHeight();
		rightSize.x = rightImage->getImageWidth();
		rightSize.y = rightImage->getImageHeight();

		ICoord2D leftEnd, rightStart;
		leftEnd.x = origin.x + leftSize.x + xOffset;
		leftEnd.y = origin.y + size.y + yOffset;
		rightStart.x = origin.x + size.x - rightSize.x + xOffset;
		rightStart.y = origin.y + yOffset;

		Int centerWidth, pieces;
		centerWidth = rightStart.x - leftEnd.x;

		if (centerWidth <= 0)
		{
			start.x = origin.x + xOffset;
			start.y = origin.y + yOffset;
			end.y = leftEnd.y;
			end.x = origin.x + xOffset + size.x / 2;
			TheDisplay->drawImage(leftImage, start.x, start.y, end.x, end.y, color);

			start.y = rightStart.y;
			start.x = end.x;
			end.x = origin.x + size.x;
			end.y = start.y + size.y;
			TheDisplay->drawImage(rightImage, start.x, start.y, end.x, end.y, color);
		}
		else
		{
			pieces = centerWidth / centerImage->getImageWidth();

			start.x = leftEnd.x;
			start.y = origin.y + yOffset;
			end.y = start.y + size.y + yOffset;
			for (i = 0; i < pieces; i++)
			{
				end.x = start.x + centerImage->getImageWidth();
				TheDisplay->drawImage(centerImage, start.x, start.y,
					end.x, end.y, color, 2);
				start.x += centerImage->getImageWidth();
			}

			IRegion2D reg;
			reg.lo.x = start.x;
			reg.lo.y = start.y;
			reg.hi.x = rightStart.x;
			reg.hi.y = end.y;
			centerWidth = rightStart.x - start.x;
			if (centerWidth > 0)
			{
				TheDisplay->setClipRegion(&reg);
				end.x = start.x + centerImage->getImageWidth();
				TheDisplay->drawImage(centerImage, start.x, start.y,
					end.x, end.y, color);
				TheDisplay->enableClipping(FALSE);
			}

			start.x = origin.x + xOffset;
			start.y = origin.y + yOffset;
			end = leftEnd;
			TheDisplay->drawImage(leftImage, start.x, start.y, end.x, end.y,
				color, 2);

			start = rightStart;
			end.x = start.x + rightSize.x;
			end.y = start.y + size.y;
			TheDisplay->drawImage(rightImage, start.x, start.y, end.x, end.y,
				color, 2);
		}
	}
}

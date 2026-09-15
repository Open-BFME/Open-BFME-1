// ?PushButtonImageDrawThree@Rva0059ABC0@@YAXPAVGameWindow@@H@Z
// partial score=0.93 date=2026-09-15
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Retail 0x0059ABC0 is the 952-byte three-image push-button transition
// helper.  The body is the Zero Hour PushButtonImageDrawThree twin, but the
// BFME window/instance layouts are independently witnessed by the retail
// operands below.  The identity remains address-derived until a caller or
// another binary witness distinguishes this copy from its ZH twin.

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
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Image
{
public:
	Int getImageWidth(void) const { return m_imageWidth; }
	Int getImageHeight(void) const { return m_imageHeight; }

private:
	unsigned char m_unreconstructed_00[0x24];
	Int m_imageWidth;
	Int m_imageHeight;
};

class WinInstanceData
{
public:
	unsigned char m_unreconstructed_000[0x17C];
	ICoord2D m_imageOffset; // retail this+0x17c
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData(void);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);

	const Image *winGetEnabledImage(Int index)
	{
		return m_enabledDrawData[index].image;
	}

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9]; // retail this+0x48
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
	virtual void unused43(); virtual void beginImageDraw();
	virtual void unused45(); virtual void unused46();
	virtual void unused47(); virtual void unused48();
	virtual void unused49(); virtual void unused50();
	virtual void unused51(); virtual void unused52();
	virtual void drawImageCore(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode);
	virtual void unused54();
	virtual void endImageDraw(void);

	// This is the direct Display wrapper used by the three short-path calls;
	// its REL32 is the printed 0x0000a114 callee contract.
	void drawImage(const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color, Int mode = 2);
};

extern Display *TheDisplay;

inline void drawImage(Display *display, const Image *image, Real startX,
	Real startY, Real endX, Real endY, Color color, Int mode)
{
	display->beginImageDraw();
	display->drawImageCore(image, startX, startY, endX, endY, color, mode);
	display->endImageDraw();
}

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
		rightSize.x = rightImage->getImageWidth();

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
			end.x = size.x / 2 + xOffset + origin.x;
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
				drawImage(TheDisplay, centerImage, start.x, start.y,
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
			drawImage(TheDisplay, leftImage, start.x, start.y, end.x, end.y,
				color, 2);

			start = rightStart;
			end.x = start.x + rightSize.x;
			end.y = start.y + size.y;
			drawImage(TheDisplay, rightImage, start.x, start.y, end.x, end.y,
				color, 2);
		}
	}
}

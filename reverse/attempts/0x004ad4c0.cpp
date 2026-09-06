// ?d_004ad4c0@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define BFME_STLP_NODE_ALLOC 1

#include <list>

struct Coord2D
{
	float x;
	float y;
};

struct ICoord2D
{
	int x;
	int y;
};

class Display
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void prepare() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void drawImage(void *image, float startX, float startY, float endX, float endY,
		unsigned int color, int mode) = 0;
	virtual void slot54() = 0;
	virtual void finish() = 0;
};

extern Display *TheDisplay;

struct ControlBarSchemeImage
{
	char name[4];
	ICoord2D position;
	ICoord2D size;
	void *image;
};

class ControlBarScheme
{
private:
	char padding[0x158];
	std::list<ControlBarSchemeImage *> layer[6];

public:
	void drawForeground(Coord2D multi, ICoord2D offset);
};

// ?drawForeground@ControlBarScheme@@QAEXUCoord2D@@UICoord2D@@@Z
void ControlBarScheme::drawForeground(Coord2D multi, ICoord2D offset)
{
	for (int layerIndex = 2; layerIndex >= 0; --layerIndex)
	{
		std::list<ControlBarSchemeImage *>::iterator it = layer[layerIndex].begin();
		while (it != layer[layerIndex].end())
		{
			ControlBarSchemeImage *schemeImage = *it;
			if (schemeImage == 0)
			{
				++it;
				continue;
			}
			void *image = schemeImage->image;
			if (image == 0)
			{
				++it;
				continue;
			}
			{
				float endY = (schemeImage->position.y + schemeImage->size.y) * multi.y + offset.y;
				float endX = (schemeImage->position.x + schemeImage->size.x) * multi.x + offset.x;
				float startY = schemeImage->position.y * multi.y + offset.y;
				float startX = schemeImage->position.x * multi.x + offset.x;
				Display &display = *TheDisplay;
				display.prepare();
				display.drawImage(image, startX, startY, endX, endY,
					0xFFFFFFFFu, 2);
				display.finish();
			}
			++it;
		}
	}
}

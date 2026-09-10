// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
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
// BFME retail W3DRadar constructor, RVA 0x006C1D70, 304 bytes.
//
// The adjacent matched W3DRadar destructor owns the same BFME tail: five
// counted texture references at +0x1478/+0x147C/+0x1488/+0x1494/+0x14A0,
// eleven image slots at +0x14B0, and four non-POD Coord2D values at +0x14E8.
// The 89-byte niladic factory at 0x006BAA10 independently proves a default
// __thiscall constructor for this 0x1508-byte object.  The class spelling is
// retained as W3DRadar because its destructor and contiguous named methods
// establish the owner; no alternate generated thunk name is introduced.

#include "Common/Radar.h"
#include "WW3D2/WW3DFormat.h"
#include <string.h>

class TerrainLogic;
class Image;
class RvaW3DRadarCoord2D
{
public:
	RvaW3DRadarCoord2D();
	~RvaW3DRadarCoord2D();

	float x;
	float y;
};

// Actual retail array callbacks: ILT21710 ->83350 returns self;
// ILT3EAB8 ->5BD90 returns. These aliases name existing real C++ bodies.
#pragma comment(linker, "/alternatename:??0RvaW3DRadarCoord2D@@QAE@XZ=??0Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1RvaW3DRadarCoord2D@@QAE@XZ=??1Coord2D@@QAE@XZ")

class TextureClass
{
public:
	void Release_Ref();
};

class TextureRef
{
public:
	TextureRef() : m_texture(0) {}

	~TextureRef()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

class W3DRadar : public Radar
{
public:
	W3DRadar();
	virtual ~W3DRadar();
	virtual void init();
	virtual void update();
	virtual void reset();
	virtual void newMap(TerrainLogic *terrain);
	virtual void draw(Int pixelX, Int pixelY, Int width, Int height);
	virtual void clearShroud();
	virtual void setShroudLevel(Int x, Int y, CellShroudStatus setting);
	virtual void refreshTerrain(TerrainLogic *terrain);

protected:
	void drawSingleBeaconEvent(Int pixelX, Int pixelY, Int width, Int height, Int index);
	void drawSingleGenericEvent(Int pixelX, Int pixelY, Int width, Int height, Int index);
	void initializeTextureFormats();
	void deleteResources();
	void drawEvents(Int pixelX, Int pixelY, Int width, Int height);
	void drawHeroIcon(Int pixelX, Int pixelY, Int width, Int height, const Coord3D *pos);
	void drawViewBox(Int pixelX, Int pixelY, Int width, Int height);
	void buildTerrainTexture(TerrainLogic *terrain);
	void drawIcons(Int pixelX, Int pixelY, Int width, Int height);
	void renderObjectList(const RadarObject *listHead, TextureClass *texture, Bool calcHero = FALSE);
	void interpolateColorForHeight(RGBColor *color, Real height, Real hiZ, Real midZ, Real loZ);
	void reconstructViewBox();
	void radarToPixel(const ICoord2D *radar, ICoord2D *pixel,
		Int radarUpperLeftX, Int radarUpperLeftY, Int radarWidth, Int radarHeight);

private:
	unsigned char m_padRadarBase[0x146c - sizeof(Radar)];
	Bool m_bfmeMapChanged;
	unsigned char m_pad146d[3];
	WW3DFormat m_terrainTextureFormat;
	Image *m_terrainImage;
	TextureRef m_terrainTexture;
	TextureRef m_texture147c;
	WW3DFormat m_overlayTextureFormat;
	Image *m_overlayImage;
	TextureRef m_overlayTexture;
	WW3DFormat m_shroudTextureFormat;
	Image *m_shroudImage;
	TextureRef m_shroudTexture;
	WW3DFormat m_borderShroudTextureFormat;
	Image *m_borderShroudImage;
	TextureRef m_borderShroudTexture;
	Int m_textureWidth;
	Int m_textureHeight;
	void *m_field14ac;
	Image *m_images[11];
	Bool m_reconstructViewBox;
	Bool m_field14dd;
	Bool m_field14de;
	Bool m_field14df;
	Real m_viewAngle;
	Real m_viewZoom;
	RvaW3DRadarCoord2D m_viewBox[4];
};

W3DRadar::W3DRadar()
	: m_bfmeMapChanged(TRUE), m_field14ac(0), m_field14de(0)
{
	m_terrainTextureFormat = WW3D_FORMAT_UNKNOWN;
	m_terrainImage = 0;
	m_overlayTextureFormat = WW3D_FORMAT_UNKNOWN;
	m_overlayImage = 0;
	m_shroudTextureFormat = WW3D_FORMAT_UNKNOWN;
	m_shroudImage = 0;
	m_borderShroudTextureFormat = WW3D_FORMAT_UNKNOWN;
	m_borderShroudImage = 0;
	m_viewAngle = 0.0f;
	m_viewZoom = 0.0f;
	m_reconstructViewBox = TRUE;
	m_textureWidth = RADAR_CELL_WIDTH;
	m_textureHeight = RADAR_CELL_HEIGHT;
	for (Int i = 0; i < 4; ++i)
	{
		m_viewBox[i].x = 0;
		m_viewBox[i].y = 0;
	}
	memset(m_images, 0, sizeof(m_images));
	m_field14dd = 0;
}

typedef char VerifyW3DRadarCoordSize[sizeof(RvaW3DRadarCoord2D) == 8 ? 1 : -1];
typedef char VerifyW3DRadarTextureRefSize[sizeof(TextureRef) == 4 ? 1 : -1];
typedef char VerifyW3DRadarSize[sizeof(W3DRadar) == 0x1508 ? 1 : -1];

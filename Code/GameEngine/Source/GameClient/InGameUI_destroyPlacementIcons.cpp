// cl: /DNDEBUG /MD /EHsc

class Drawable;

class TerrainVisual
{
public:
	virtual void reserved00();
	virtual void reserved01();
	virtual void reserved02();
	virtual void reserved03();
	virtual void reserved04();
	virtual void reserved05();
	virtual void reserved06();
	virtual void reserved07();
	virtual void reserved08();
	virtual void reserved09();
	virtual void reserved10();
	virtual void reserved11();
	virtual void reserved12();
	virtual void reserved13();
	virtual void reserved14();
	virtual void reserved15();
	virtual void reserved16();
	virtual void reserved17();
	virtual void reserved18();
	virtual void reserved19();
	virtual void reserved20();
	virtual void reserved21();
	virtual void reserved22();
	virtual void reserved23();
	virtual void reserved24();
	virtual void reserved25();
	virtual void removeFactionBibDrawable(Drawable *drawable);
	virtual void removeAllBibs();
};

class GameClient
{
public:
	virtual void reserved00();
	virtual void reserved01();
	virtual void reserved02();
	virtual void reserved03();
	virtual void reserved04();
	virtual void reserved05();
	virtual void reserved06();
	virtual void reserved07();
	virtual void reserved08();
	virtual void reserved09();
	virtual void reserved10();
	virtual void reserved11();
	virtual void reserved12();
	virtual void reserved13();
	virtual void reserved14();
	virtual void reserved15();
	virtual void reserved16();
	virtual void reserved17();
	virtual void reserved18();
	virtual void reserved19();
	virtual void reserved20();
	virtual void reserved21();
	virtual void reserved22();
	virtual void reserved23();
	virtual void destroyDrawable(Drawable *drawable);
};

extern TerrainVisual *TheTerrainVisual;
extern GameClient *TheGameClient;

class InGameUI
{
protected:
	void destroyPlacementIcons();

private:
	char m_fields[0x53c];
	Drawable **m_placeIcon;
};

void InGameUI::destroyPlacementIcons()
{
	Drawable *icon = m_placeIcon[0];

	if (icon != 0) {
		TheTerrainVisual->removeFactionBibDrawable(icon);
		TheGameClient->destroyDrawable(m_placeIcon[0]);
	}

	m_placeIcon[0] = 0;
	TheTerrainVisual->removeAllBibs();
}

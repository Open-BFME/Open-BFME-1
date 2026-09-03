// cl: /DNDEBUG /MD
// readable body of ?setDrawableHidden@Drawable@@QAEX_N@Z: Code/GameEngine/Source/GameClient/Drawable.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C();
	virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C();
	virtual void setHidden(bool hidden);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
private:
	char m_pad000[0x150];
	DrawModule **m_drawModules;
	char m_pad154[0x3B0 - 0x154];
	bool m_hidden;

	void updateHiddenStatus();

public:
	void setDrawableHidden(bool hidden);
};

void Drawable::setDrawableHidden(bool hidden)
{
	if (m_hidden != hidden)
	{
		for (DrawModule **module = m_drawModules; *module; ++module)
			(*module)->setHidden(hidden);

		m_hidden = hidden;
		if (!hidden)
			updateHiddenStatus();
	}
}

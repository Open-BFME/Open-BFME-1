// cl: /DNDEBUG /MD
// readable body of ?filterPostRender@W3DShaderManager@@SA_NW4FilterTypes@@W4FilterModes@@AAUCoord2D@@AA_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp

struct Coord2D;

enum FilterTypes
{
	FT_NULL_FILTER = 0
};

enum FilterModes
{
	FM_FIRST = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DFilterInterface
{
public:
	virtual int init();
	virtual int shutdown();
	virtual bool preRender(bool &skipRender, int &scenePassMode);
	virtual bool postRender(FilterModes mode, Coord2D &scrollDelta, bool &doExtraRender, int callerStackWord);
};

static W3DFilterInterface *W3DFilters[1];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DShaderManager
{
public:
	static bool filterPostRender(FilterTypes filter, FilterModes mode, Coord2D &scrollDelta, bool &doExtraRender);
	static bool filterPostRenderRetail(FilterTypes filter, FilterModes mode, Coord2D &scrollDelta,
		bool &doExtraRender, int callerStackWord);

protected:
	static FilterTypes m_currentFilter;
};

bool W3DShaderManager::filterPostRender(FilterTypes filter, FilterModes mode, Coord2D &scrollDelta, bool &doExtraRender)
{
	if (W3DFilters[filter])
		return W3DFilters[filter]->postRender(mode, scrollDelta, doExtraRender,
			*((int *)&doExtraRender + 1));

	m_currentFilter = FT_NULL_FILTER;
	return false;
}

bool W3DShaderManager::filterPostRenderRetail(FilterTypes filter, FilterModes mode, Coord2D &scrollDelta,
	bool &doExtraRender, int callerStackWord)
{
	if (W3DFilters[filter])
		return W3DFilters[filter]->postRender(mode, scrollDelta, doExtraRender, callerStackWord);

	m_currentFilter = FT_NULL_FILTER;
	return false;
}

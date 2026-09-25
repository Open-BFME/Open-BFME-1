#pragma once

#ifndef __SCRIPTENGINE_H_
#define __SCRIPTENGINE_H_

struct BreezeInfo
{
	Real m_direction;
	Coord2D m_directionVec;
	Real m_intensity;
	Real m_lean;
	Real m_randomness;
	Short m_breezePeriod;
	Short m_breezeVersion;
};

class ScriptEngine
{
public:
	const BreezeInfo &getBreezeInfo() const { return m_breezeInfo; }

private:
	char m_bfmePad[0x17604];
	BreezeInfo m_breezeInfo;
};

extern ScriptEngine *TheScriptEngine;

#endif

// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class TerrainLogic
{
public:
	char m_pad[0x18F4];
	unsigned char m_flag;
};

extern TerrainLogic *TheTerrainLogic;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

	virtual void bfmeSlot0(void);

private:
	AsciiString m_name;
};

class ScriptActionsInterface : public SubsystemInterface
{
public:
	ScriptActionsInterface();
	virtual ~ScriptActionsInterface() {}
	virtual void reset() = 0;
};

class ScriptActions : public ScriptActionsInterface
{
public:
	ScriptActions();
	virtual ~ScriptActions();

	virtual void bfmeSlot0(void);
	virtual void reset();

private:
	bool m_suppressNewWindows;
	char m_bfmePad09[3];
	AsciiString m_unnamedUnit;
};

ScriptActions::~ScriptActions()
{
	bool f = false;
	m_suppressNewWindows = f;
	if (TheTerrainLogic)
		TheTerrainLogic->m_flag = f;
	m_suppressNewWindows = f;
}

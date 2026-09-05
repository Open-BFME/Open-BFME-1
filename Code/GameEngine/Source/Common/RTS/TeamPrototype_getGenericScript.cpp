// cl: /DNDEBUG /MD /EHsc /Gy /O2 /Ob1
// TeamPrototype::getGenericScript at 0x000ED6F0 (236B).
// ZH twin: TeamPrototype::getGenericScript; BFME MAX_GENERIC_SCRIPTS=32,
// extra UnicodeString names at +0xAC, findScriptByName takes team name + out string.
// Callees: Script::duplicate ILT 0x0004589F, UnicodeString::set 0x00887C90,
//          StringBase<char>::releaseBuffer 0x00887940.

typedef bool Bool;
typedef int Int;

class AsciiString
{
public:
	Bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

private:
	void *m_data;
};

// Temp cleanup at 0x00887940 is StringBase<char>::releaseBuffer (export
// ?releaseBuffer@?$StringBase@D@@AAEXXZ), not UnicodeString::~ (0x005EEA0).
template <typename T>
class StringBase
{
protected:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void *m_data;

private:
	void releaseBuffer();
};

class UnicodeString : private StringBase<char>
{
public:
	UnicodeString() {}
	~UnicodeString() {}
	void set(const UnicodeString &other);
};

class Script
{
public:
	Script *duplicate(void) const;
};

class Player;
class Team;
class ScriptEngine
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual Bool evaluateConditions(UnicodeString *name, Script *pScript, Team *pThisTeam, Player *pPlayer);
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
	virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
	virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
	virtual Script *findScriptByName(AsciiString *teamName, AsciiString *scriptName, UnicodeString *outName);
};

extern ScriptEngine *TheScriptEngine;

enum { MAX_GENERIC_SCRIPTS = 32 };

class TeamPrototype
{
public:
	Script *getGenericScript(Int scriptToRetrieve, UnicodeString *outName);

private:
	void *m_vptr;					// +0x00
	void *m_factory;				// +0x04
	void *m_owningPlayer;				// +0x08
	int m_id;					// +0x0C
	AsciiString m_name;				// +0x10
	char m_pad14[0x14];				// +0x14 -> +0x28
	Bool m_retrievedGenericScripts;			// +0x28
	char m_pad29[3];
	Script *m_genericScriptsToRun[MAX_GENERIC_SCRIPTS];	// +0x2C
	UnicodeString m_genericScriptNames[MAX_GENERIC_SCRIPTS]; // +0xAC
	char m_pad12c[0x1F0 - 0x12C];			// +0x12C -> +0x1F0
	AsciiString m_teamGenericScripts[MAX_GENERIC_SCRIPTS];	// +0x1F0
};

// ?getGenericScript@TeamPrototype@@QAEPAVScript@@HPAVUnicodeString@@@Z
Script *TeamPrototype::getGenericScript(Int scriptToRetrieve, UnicodeString *outName)
{
	if (!m_retrievedGenericScripts)
	{
		m_retrievedGenericScripts = true;
		for (Int i = 0; i < MAX_GENERIC_SCRIPTS; ++i)
		{
			Script *scriptToSave = 0;
			UnicodeString tmp;
			if (!m_teamGenericScripts[i].isEmpty())
			{
				Script *tmpScript = TheScriptEngine->findScriptByName(&m_name, &m_teamGenericScripts[i], &tmp);
				if (tmpScript)
					scriptToSave = tmpScript->duplicate();
			}
			m_genericScriptsToRun[i] = scriptToSave;
			if (scriptToSave)
				m_genericScriptNames[i].set(tmp);
		}
	}

	Script *script = m_genericScriptsToRun[scriptToRetrieve];
	if (script && outName)
		outName->set(m_genericScriptNames[scriptToRetrieve]);
	return script;
}

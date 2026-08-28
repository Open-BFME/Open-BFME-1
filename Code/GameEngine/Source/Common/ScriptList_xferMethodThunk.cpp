// cl: /DNDEBUG /MD /EHsc
// readable body of ?xfer@ScriptList@@MAEXPAVXfer@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
// Open-BFME5: retail-layout C++ conversion of ScriptList snapshot transfer.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	struct Version { unsigned char Value; unsigned char Current; };
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void xferVersion(Version *);
	virtual void v11();
	virtual void xferSnapshot(void *);
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30();
	virtual void xferUnsignedShort(unsigned short *);
};

extern void *RetailScriptVTable[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Script
{
public:
	__forceinline Script()
	{
		VTable = RetailScriptVTable;
		for (int i = 0; i < 4; ++i) Words[i] = 0;
		Flags[0] = 1;
		Flags[1] = 1;
		Flags[2] = 1;
		Flags[3] = 0;
		Flags[4] = 1;
		Flags[5] = 1;
		Flags[6] = 1;
		for (int i = 0; i < 4; ++i) MoreWords[i] = 0;
		MoreFlag = 0;
		for (int i = 0; i < 4; ++i) TailWords[i] = 0;
	}

private:
	void *VTable;
	unsigned int Words[4];
	unsigned char Flags[7];
	unsigned char Pad;
	unsigned int MoreWords[4];
	unsigned char MoreFlag;
	unsigned char TailPad[3];
	unsigned int TailWords[4];
};

struct ScriptListNode
{
	int Next;
	unsigned int Reserved[3];
	void *Value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptList
{
protected:
	virtual void xfer(Xfer *);

private:
	char Pad0[8];
	void **GroupBegin;
	void **GroupEnd;
	char Pad14[4];
	ScriptListNode *GroupNodes;
	char Pad1C[12];
	int GroupHead;
	void **ScriptBegin;
	void **ScriptEnd;
	char Pad34[4];
	ScriptListNode *ScriptNodes;
	char Pad3C[12];
	int ScriptHead;

	static Script *EmptyScript;
};

Script *ScriptList::EmptyScript;

void ScriptList::xfer(Xfer *transfer)
{
	Xfer::Version version;
	version.Value = 1;
	version.Current = 2;
	transfer->xferVersion(&version);

	unsigned short scriptCount = (unsigned short)(ScriptEnd - ScriptBegin);
	transfer->xferUnsignedShort(&scriptCount);
	int node = ScriptHead;
	while (node != -1) {
		transfer->xferSnapshot((char *)ScriptNodes[node].Value + 4);
		--scriptCount;
		if (scriptCount == 0) break;
		node = ScriptNodes[node].Next;
	}
	if (scriptCount > 0) {
		if (EmptyScript == 0) EmptyScript = new Script;
		while (scriptCount != 0) {
			transfer->xferSnapshot(EmptyScript);
			--scriptCount;
		}
	}

	if (version.Current >= 2) {
		unsigned short groupCount = (unsigned short)(GroupEnd - GroupBegin);
		transfer->xferUnsignedShort(&groupCount);
		node = GroupHead;
		while (node != -1) {
			transfer->xferSnapshot((char *)GroupNodes[node].Value + 4);
			--groupCount;
			if (groupCount == 0) break;
			node = GroupNodes[node].Next;
		}
	}
}

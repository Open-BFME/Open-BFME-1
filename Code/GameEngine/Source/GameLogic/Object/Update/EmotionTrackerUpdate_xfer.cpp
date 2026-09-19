// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <set>
#include <vector>

typedef unsigned int UnsignedInt;

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *value, int size);
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual Xfer &xferInt(int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Xfer &xferBool(bool *value);
};

extern void bfmeCalcTGC(void *xfer, int *value);

#pragma comment(linker, "/alternatename:?xfer@Emotion@@QAEXPAVXfer@@@Z=?j_000091ec@@YAXXZ")
#pragma comment(linker, "/alternatename:?insert_unique@?$_Rb_tree@UGen_t_000ef440_k4@@U1@U?$_Identity@UGen_t_000ef440_k4@@@_STL@@U?$less@UGen_t_000ef440_k4@@@3@V?$allocator@UGen_t_000ef440_k4@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@UGen_t_000ef440_k4@@U?$_Nonconst_traits@UGen_t_000ef440_k4@@@_STL@@@_STL@@_N@2@ABUGen_t_000ef440_k4@@@Z=?j_000499f9@@YAXXZ")

class ModuleData;

class ObjectModule
{
public:
	ObjectModule(void *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(void *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData) {}
	virtual ~BehaviorModule();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(void *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData) {}
	virtual ~UpdateModule();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class EmotionTrackerUpdateSecondaryBase
{
public:
	virtual void slot();
};

struct EmotionTrackerUpdateEntry
{
	unsigned char m_pad00[4];
	int m_type;
	unsigned char m_pad08[4];
	int m_flag0c;
};

class Emotion
{
public:
	void xfer(Xfer *xfer);

	private:
	unsigned char m_pad00[4];
	EmotionTrackerUpdateEntry *m_entry;
};

struct Gen_t_000ef440_k4
{
	int value;
};

bool operator==(const Gen_t_000ef440_k4 &left, const Gen_t_000ef440_k4 &right)
{
	return left.value == right.value;
}

bool operator<(const Gen_t_000ef440_k4 &left, const Gen_t_000ef440_k4 &right)
{
	return left.value < right.value;
}

class EmotionTrackerUpdate
	: public UpdateModule,
	  public EmotionTrackerUpdateSecondaryBase
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_active[10];
	unsigned int m_startFrame[10];
	unsigned int m_endFrame[10];
	std::vector<Emotion *> m_emotions;
	Emotion *m_currentEmotion;
	unsigned int m_distributionIndex;
	std::set<Gen_t_000ef440_k4> m_emotionTypes;
	int m_activeEmotionType;
	int m_forcedRetry;
	int m_unknowna4;
	int m_unknowna8;
	bool m_enabled;
	unsigned char m_padb1[3];
	int m_currentEmotionIndex;
};

// ?xfer@EmotionTrackerUpdate@@MAEXPAVXfer@@@Z
void EmotionTrackerUpdate::xfer(Xfer *xfer)
{
	Emotion *emotion;
	UpdateModule::xfer(xfer);

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);

	for (int i = 0; i < 10; ++i)
	{
		xfer->xferBool(&m_active[i]);
		xfer->xferUnsignedInt(&m_startFrame[i]);
		bfmeCalcTGC(xfer, (int *)&m_endFrame[i]);
	}

	m_currentEmotionIndex = -1;
	int count = m_emotions.size();
	for (int i = 0; i < count; ++i)
	{
		emotion = m_emotions.begin()[i];
		if (xfer->isSaving() && emotion == m_currentEmotion)
			m_currentEmotionIndex = i;
		emotion->xfer(xfer);
	}

	xfer->xferInt(&m_currentEmotionIndex);
	xfer->xferInt((int *)&m_distributionIndex);

	if (version.m_currentVersion < 2)
	{
		int typeCount = m_emotionTypes.size();
		xfer->xferInt(&typeCount);
		if (xfer->isLoading())
		{
			Gen_t_000ef440_k4 type;
			type.value = 0;
			std::set<Gen_t_000ef440_k4> *types;
			if (typeCount > 0)
			{
				types = &m_emotionTypes;
				for (int i = 0; i < typeCount; ++i)
				{
					bfmeCalcTGC(xfer, &type.value);
					types->insert(type);
				}
			}
		}
		else
		{
			int value;
			for (std::set<Gen_t_000ef440_k4>::iterator it = m_emotionTypes.begin();
				it != m_emotionTypes.end(); ++it)
			{
				value = it->value;
				bfmeCalcTGC(xfer, &value);
			}
		}
	}

	xfer->xferUser(&m_activeEmotionType, 4);
	xfer->xferInt(&m_forcedRetry);
	bfmeCalcTGC(xfer, &m_unknowna4);
	if (version.m_currentVersion >= 2)
	{
		xfer->xferUnsignedInt((UnsignedInt *)&m_unknowna8);
		xfer->xferBool(&m_enabled);
	}
}

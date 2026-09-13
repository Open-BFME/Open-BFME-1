// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// TunnelTracker::loadPostProcess at retail RVA 0x000F8F60.
// The three BFME lists and the callback/helper ABIs are recovered from the
// matched TunnelTracker constructor, onTunnelCreated body, and this target.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int ObjectID;

class BfmeXCQE
{
public:
	void bfmeRunCQE(int value);
};

class BfmeObjectView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual BfmeXCQE *getDrawable();
};

class BfmeX1011 : public BfmeObjectView
{
};

class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011(int id);
};

class GameLogic
{
};

extern GameLogic *TheBfmeGameLogic;

class BfmeX1027
{
public:
	void bfmeStop1027();
};

class BfmeThingXV
{
public:
	void bfmeStopXV();
};

class BfmeHostCL;

class BfmePathCL
{
public:
	void bfmeDropOneCL(BfmeHostCL *object);
};

class AI
{
public:
	unsigned char m_pad[0x0c];
	BfmePathCL *m_path;
};

extern AI *TheAI;

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern "C" int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class TunnelTracker
{
public:
	// Retail vtable slot 0 is TunnelTracker's scalar/vector deleting destructor.
	// Keeping that destructor declaration ahead of this protected virtual models
	// loadPostProcess at slot 1 without emitting a table from this TU.
	virtual ~TunnelTracker();

protected:
	virtual void loadPostProcess();

private:
	_STL::list<ObjectID> m_tunnelIDs;
	_STL::list<BfmeX1011 *> m_containList;
	_STL::list<ObjectID> m_xferContainList;
};

// ?loadPostProcess@TunnelTracker@@MAEXXZ
void TunnelTracker::loadPostProcess()
{
	BfmeX1011 *object;
	_STL::list<ObjectID>::const_iterator it;

	if (m_containList.size() != 0)
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		return;
	}

	for (it = m_xferContainList.begin(); it != m_xferContainList.end(); ++it)
	{
		object = ((BfmeLook1011 *)TheBfmeGameLogic)->bfmeFind1011(*it);
		if (object == 0)
		{
			XferException error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			return;
		}

		m_containList.push_back(object);
		((BfmeX1027 *)object)->bfmeStop1027();
		((BfmeThingXV *)object)->bfmeStopXV();

		if (object->getDrawable() != 0)
			object->getDrawable()->bfmeRunCQE(1);

		if (TheAI != 0)
			TheAI->m_path->bfmeDropOneCL((BfmeHostCL *)object);

	}

	m_xferContainList.clear();
}

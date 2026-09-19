// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenBase constructor at retail 0x00477BC0 (210B).

class WinInstanceData
{
public:
	WinInstanceData();

private:
	char m_data[ 0x1A8 ];
};

struct BfmeAptScreenContext
{
	void *unused0;
	int status;
	int x;
	int y;
	int width;
	int height;
	int unused18;
	void *system;
	void *input;
	void *draw;
	void *tooltip;
	void *callbackExtra;
};

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase( void *context );
	virtual void slot0();

private:
	void *m_bfmeAnchor;
	int m_status;
	int m_sizeX;
	int m_sizeY;
	int m_regionLoX;
	int m_regionLoY;
	int m_regionHiX;
	int m_regionHiY;
	int m_cursorX;
	int m_cursorY;
	void *m_userData;
	WinInstanceData m_instData;
	void *m_inputData;
	void *m_bfmeInputExtra;
	void *m_input;
	void *m_system;
	void *m_draw;
	void *m_tooltip;
	void *m_bfmeCallbackExtra;
	int m_bfmeCallbackExtra2;
	void *m_next;
	void *m_prev;
	void *m_parent;
	void *m_child;
	void *m_nextLayout;
	void *m_prevLayout;
	void *m_layout;
	void *m_editData;
};

BfmeAptScreenBase::BfmeAptScreenBase( void *context )
{
	const BfmeAptScreenContext *ctx = (const BfmeAptScreenContext *)context;
	int zero = 0;

	m_bfmeAnchor = 0;
	m_status = ctx->status;
	m_bfmeCallbackExtra2 = 1;
	m_sizeX = ctx->width;
	m_sizeY = ctx->height;
	m_regionLoX = ctx->x;
	m_regionLoY = ctx->y;
	m_regionHiX = ctx->width + ctx->x;
	const BfmeAptScreenContext *q = (const BfmeAptScreenContext *)context;
	const BfmeAptScreenContext *p = ctx;
	m_regionHiY = q->height + p->y;
	m_cursorX = zero;
	m_cursorY = zero;
	m_userData = 0;
	m_inputData = 0;
	m_bfmeInputExtra = 0;
	m_input = ctx->input;
	m_system = ctx->system;
	m_draw = ctx->draw;
	m_tooltip = ctx->tooltip;
	m_bfmeCallbackExtra = ctx->callbackExtra;
	m_next = 0;
	m_prev = 0;
	m_parent = 0;
	m_child = 0;
	m_nextLayout = 0;
	m_prevLayout = 0;
	m_layout = 0;
	m_editData = 0;
}

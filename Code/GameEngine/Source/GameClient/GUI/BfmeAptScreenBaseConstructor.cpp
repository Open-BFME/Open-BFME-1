// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenBase constructor at retail 0x00477BC0 (210B).

#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"
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
	BfmeAptScreenBaseLayout<WinInstanceData> m_layout;
};

BfmeAptScreenBase::BfmeAptScreenBase( void *context )
{
	const BfmeAptScreenContext *ctx = (const BfmeAptScreenContext *)context;
	int zero = 0;

	m_layout.m_bfmeAnchor = 0;
	m_layout.m_status = ctx->status;
	m_layout.m_bfmeCallbackExtra2 = 1;
	m_layout.m_sizeX = ctx->width;
	m_layout.m_sizeY = ctx->height;
	m_layout.m_regionLoX = ctx->x;
	m_layout.m_regionLoY = ctx->y;
	m_layout.m_regionHiX = ctx->width + ctx->x;
	const BfmeAptScreenContext *q = (const BfmeAptScreenContext *)context;
	const BfmeAptScreenContext *p = ctx;
	m_layout.m_regionHiY = q->height + p->y;
	m_layout.m_cursorX = zero;
	m_layout.m_cursorY = zero;
	m_layout.m_userData = 0;
	m_layout.m_inputData = 0;
	m_layout.m_bfmeInputExtra = 0;
	m_layout.m_input = ctx->input;
	m_layout.m_system = ctx->system;
	m_layout.m_draw = ctx->draw;
	m_layout.m_tooltip = ctx->tooltip;
	m_layout.m_bfmeCallbackExtra = ctx->callbackExtra;
	m_layout.m_next = 0;
	m_layout.m_prev = 0;
	m_layout.m_parent = 0;
	m_layout.m_child = 0;
	m_layout.m_nextLayout = 0;
	m_layout.m_prevLayout = 0;
	m_layout.m_layout = 0;
	m_layout.m_editData = 0;
}

// ?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z
// partial score=0.72 date=2026-09-10
// ?deselectDrawable@InGameUI@@UAEXPAVDrawable@@@Z
// Full 0x00446490 probe body.  The live TU uses BFME_PARTICLE_LIST_NODE_TAIL;
// this local ABI view keeps the retail selected-list node at 0x0C.
struct BfmeDeselectDrawableNode
{
	BfmeDeselectDrawableNode *m_next;
	BfmeDeselectDrawableNode *m_previous;
	Drawable *m_drawable;
};

struct BfmeDeselectDrawableList
{
	BfmeDeselectDrawableNode *m_node;
};

struct BfmeDeselectDrawableLayout
{
	unsigned char m_padding00[0x3AC];
	unsigned char m_selected;
};

struct BfmeDeselectUIState
{
	unsigned char m_padding00[0x554];
	UnsignedInt m_selectCount;
	unsigned char m_padding558[4];
	UnsignedInt m_frameSelectionChanged;
};

class BfmeDeselectFlagView
{
public:
	void run();
};

class BfmeDeselectControlBarView
{
public:
	void onDrawableDeselected( Drawable *draw );
};

extern void j_00013368();
extern void j_000422f3();

#pragma comment(linker, "/alternatename:?run@BfmeDeselectFlagView@@QAEXXZ=?j_00013368@@YAXXZ")
#pragma comment(linker, "/alternatename:?onDrawableDeselected@BfmeDeselectControlBarView@@QAEXPAVDrawable@@@Z=?j_000422f3@@YAXXZ")

void InGameUI::deselectDrawable( Drawable *draw )
{
	BfmeDeselectUIState *ui = reinterpret_cast<BfmeDeselectUIState *>( this );
	BfmeDeselectDrawableLayout *drawable =
		reinterpret_cast<BfmeDeselectDrawableLayout *>( draw );

	if( drawable->m_selected )
	{
		ui->m_frameSelectionChanged = TheGameLogic->getFrame();
		reinterpret_cast<BfmeDeselectFlagView *>( draw )->run();

		BfmeDeselectDrawableList *selected =
			reinterpret_cast<BfmeDeselectDrawableList *>(
				reinterpret_cast<unsigned char *>( this ) + 0x18);
		BfmeDeselectDrawableNode *node = selected->m_node->m_next;
		while( node != selected->m_node && node->m_drawable != draw )
			node = node->m_next;
		BfmeDeselectDrawableNode *next = node->m_next;
		BfmeDeselectDrawableNode *previous = node->m_previous;
		previous->m_next = next;
		next->m_previous = previous;
		_STL::__node_alloc<true, 0>::_M_deallocate(
			node, sizeof(BfmeDeselectDrawableNode));

		--ui->m_selectCount;
		evaluateSoloNexus();
		reinterpret_cast<BfmeDeselectControlBarView *>( TheControlBar )
			->onDrawableDeselected( draw );

		UnsignedByte *flag = reinterpret_cast<UnsignedByte *>( this ) + 0x48;
		for( Int i = 0; i < 25; ++i )
		{
			*(reinterpret_cast<UnsignedInt *>( flag ) - 1) = 0;
			*flag = 1;
			flag += 0x14;
		}
	}
}

#ifndef BFME_TEXTURE_FILTER_TABLE_H
#define BFME_TEXTURE_FILTER_TABLE_H

// Each retail filter stage holds four options followed by the active value.
struct Rva00920AE0Slot
{
	int m_options[4];
	int m_selected;
};

extern Rva00920AE0Slot g_bfmeOptionSlots0[8];
extern Rva00920AE0Slot g_bfmeOptionSlotsA[8];
extern Rva00920AE0Slot g_bfmeOptionSlotsB[8];

#endif

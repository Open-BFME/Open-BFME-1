// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Grok promote from masm_dumps — retail 0x0019AED0 size 66
// was: Code/masm_dumps/SidesList_SidesInfo_clear.asm

class SidesInfoNodeShim {
public:
	virtual void clear(int) = 0;
};

class SidesInfoSegmentShim {
public:
	void reset(void);
	void finish(void *, void *);
};

class SidesInfo { public: void clear(void); };

// ?clear@SidesInfo@@QAEXXZ
void SidesInfo::clear(void)
{
	SidesInfoNodeShim *first =
		*(SidesInfoNodeShim **)((unsigned char *)this + 0x00);
	if (first)
		first->clear(1);
	SidesInfoSegmentShim *firstSegment =
		(SidesInfoSegmentShim *)((unsigned char *)this + 0x04);
	*(SidesInfoNodeShim **)((unsigned char *)this + 0x00) = 0;
	firstSegment->reset();
	SidesInfoNodeShim *second =
		*(SidesInfoNodeShim **)((unsigned char *)this + 0x08);
	if (second)
		second->clear(1);
	SidesInfoSegmentShim *secondSegment =
		(SidesInfoSegmentShim *)((unsigned char *)this + 0x0C);
	*(SidesInfoNodeShim **)((unsigned char *)this + 0x08) = 0;
	secondSegment->finish(*(void **)((unsigned char *)secondSegment + 0x00),
		*(void **)((unsigned char *)secondSegment + 0x04));
}


// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Shutdown release sweep at retail 0x008ACAC0.

class Rva008ACAC0Releaseable
{
public:
	virtual void slot0(void);
	virtual void release(void);
};

#define BFME_ACAC0_GLOBAL( ADDRESS ) \
	(*(Rva008ACAC0Releaseable **)(ADDRESS))

void d_008acac0(void)
{
	Rva008ACAC0Releaseable *p;

	p = BFME_ACAC0_GLOBAL(0x013382FC);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x013382FC) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x013382F8);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x013382F8) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338348);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338348) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338344);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338344) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x0133833C);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x0133833C) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338340);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338340) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338338);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338338) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338300);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338300) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338304);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338304) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338308);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338308) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x0133830C);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x0133830C) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338310);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338310) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338318);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338318) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338314);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338314) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x0133831C);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x0133831C) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338328);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338328) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338330);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338330) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x0133832C);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x0133832C) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338334);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338334) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338358);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338358) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x0133835C);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x0133835C) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338354);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338354) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x0133834C);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x0133834C) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338350);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338350) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338320);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338320) = 0;
	}

	p = BFME_ACAC0_GLOBAL(0x01338324);
	if (p)
	{
		p->release();
		BFME_ACAC0_GLOBAL(0x01338324) = 0;
	}
}

#undef BFME_ACAC0_GLOBAL

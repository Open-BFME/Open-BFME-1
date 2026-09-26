void __cdecl rva220840Callback();

struct Rva220840Request
{
	unsigned int first;
	unsigned int second;
	bool handled;
};

struct Rva220840DispatchThunk
{
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9c();
	virtual void slota0(); virtual void slota4(); virtual void slota8(); virtual void slotac();
	virtual void slotb0(); virtual void slotb4(); virtual void slotb8(); virtual void slotbc();
	virtual void slotc0(); virtual void slotc4(); virtual void slotc8(); virtual void slotcc();
	virtual void slotd0(); virtual void slotd4(); virtual void slotd8(); virtual void slotdc();
	virtual void slote0(); virtual void slote4(); virtual void slote8(); virtual void slotec();
	virtual void slotf0(); virtual void slotf4(); virtual void slotf8();
	virtual void dispatch(void (__cdecl *callback)(), Rva220840Request *request, int mode);

	bool invoke(unsigned int first, unsigned int second);
};

// ?d_00220840@@YAXXZ
bool Rva220840DispatchThunk::invoke(unsigned int first, unsigned int second)
{
	Rva220840Request request;
	request.second = second;
	request.first = first;
	request.handled = false;
	dispatch(rva220840Callback, &request, 1);
	return !request.handled;
}

// cl: /DNDEBUG /MD /EHsc

class Display
{
public:
	virtual void bfmeVt00HK();
	virtual void bfmeVt01HK();
	virtual void bfmeVt02HK();
	virtual void bfmeVt03HK();
	virtual void bfmeVt04HK();
	virtual void bfmeVt05HK();
	virtual void bfmeVt06HK();
	virtual void bfmeVt07HK();
	virtual void bfmeVt08HK();
	virtual void bfmeVt09HK();
	virtual void bfmeVt10HK();
	virtual void bfmeVt11HK();
	virtual void bfmeVt12HK();
	virtual void bfmeVt13HK();
	virtual void bfmeVt14HK();
	virtual void bfmeVt15HK();
	virtual void bfmeVt16HK();
	virtual void bfmeVt17HK();
	virtual void bfmeVt18HK();
	virtual void bfmeVt19HK();
	virtual void bfmeVt20HK();
	virtual void bfmeVt21HK();
	virtual void bfmeVt22HK();
	virtual void bfmeVt23HK();
	virtual void bfmeVt24HK();
	virtual void bfmeVt25HK();
	virtual void bfmeVt26HK();
	virtual void bfmeVt27HK();
	virtual void bfmeVt28HK();
	virtual void bfmeVt29HK();
	virtual void bfmeVt30HK();
	virtual void bfmeVt31HK();
	virtual void bfmeVt32HK();
	virtual void bfmeVt33HK();
	virtual void bfmeVt34HK();
	virtual void bfmeVt35HK();
	virtual void bfmeVt36HK();
	virtual void bfmeVt37HK();
	virtual void bfmeVt38HK();
	virtual void bfmeVt39HK();
	virtual void bfmeVt40HK();
	virtual void bfmeVt41HK();
	virtual void bfmeVt42HK();
	virtual void bfmeVt43HK();
	virtual void bfmeBeginHK();
	virtual void bfmeVtM45HK();
	virtual void bfmeVtM46HK();
	virtual void bfmeVtM47HK();
	virtual void bfmeRectHK(float x, float y, float w, float h, int c);
	virtual void bfmeVtT49HK();
	virtual void bfmeVtT50HK();
	virtual void bfmeVtT51HK();
	virtual void bfmeVtT52HK();
	virtual void bfmeVtT53HK();
	virtual void bfmeVtT54HK();
	virtual void bfmeEndHK();
};

extern Display *TheDisplay;

void __stdcall bfmeDrawHK(int p1, int p2, int p3, int p4, int p5, int p6)
{
	Display *d = TheDisplay;

	TheDisplay->bfmeBeginHK();
	d->bfmeRectHK((float)p3, (float)p4, (float)(p5 - p3), (float)(p6 - p4), p1);
	d->bfmeEndHK();
}

// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x0079F190 (57B): if m_at250 is set, copy the caller's Coord3D onto
// the stack and virtual-call slot +0x58 on that object with &copy. Always
// allocates the 0xC frame even on the null path. Retail loads m_at250 into
// eax for the null test, then reloads it into ecx for the vcall.

struct Coord3D79F
{
	float x;
	float y;
	float z;
};

class Sink79F190
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void accept(Coord3D79F *pos);		///< slot 22 / +0x58
};

class Rva0079F190
{
public:
	void forward(Coord3D79F *pos);

private:
	char m_pad[0x250];
	Sink79F190 *m_sink;							///< +0x250
};

// ?forward@Rva0079F190@@QAEXPAUCoord3D79F@@@Z
void Rva0079F190::forward(Coord3D79F *pos)
{
	if (m_sink)
	{
		Coord3D79F copy;
		copy.x = pos->x;
		copy.y = pos->y;
		copy.z = pos->z;
		m_sink->accept(&copy);
	}
}

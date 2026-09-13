// cl: /DNDEBUG /MD /EHsc
// readable body of ??1HeightMapRenderObjClass@@UAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/HeightMap.cpp
// Open-BFME5: lift HeightMapRenderObjClass destructor to standalone C++.

class HeightMapRenderObjClass;

class HeightMapBaseAtZero
{
public:
	virtual ~HeightMapBaseAtZero();

private:
	unsigned int m_pad;
};

class HeightMapBaseAtEight
{
public:
	virtual ~HeightMapBaseAtEight();

private:
	unsigned char m_pad[0xbc];
};

class HeightMapBaseAtC8
{
public:
	virtual ~HeightMapBaseAtC8();
};

class HeightMapBaseAtCC
{
public:
	virtual ~HeightMapBaseAtCC();
};

class BaseHeightMapRenderObjClass : public HeightMapBaseAtZero,
	public HeightMapBaseAtEight,
	public HeightMapBaseAtC8,
	public HeightMapBaseAtCC
{
public:
	virtual ~BaseHeightMapRenderObjClass();
};

extern HeightMapRenderObjClass *TheHeightMap;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/HeightMap.h
class HeightMapRenderObjClass : public BaseHeightMapRenderObjClass
{
public:
	virtual ~HeightMapRenderObjClass();
	virtual int freeMapResources();
};

// ??1HeightMapRenderObjClass@@UAE@XZ
HeightMapRenderObjClass::~HeightMapRenderObjClass()
{
	freeMapResources();
	TheHeightMap = 0;
}

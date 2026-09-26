// cl: /DNDEBUG /MD /EHsc

class RenderObjVisibilityScene
{
public:
	virtual void unused00() = 0;
	virtual void unused01() = 0;
	virtual void unused02() = 0;
	virtual void unused03() = 0;
	virtual void unused04() = 0;
	virtual void unused05() = 0;
	virtual void unused06() = 0;
	virtual void unused07() = 0;
	virtual void unused08() = 0;
	virtual void unused09() = 0;
	virtual void unused10() = 0;
	virtual void unused11() = 0;
	virtual void unused12() = 0;
	virtual void unused13() = 0;
	virtual void unused14() = 0;
	virtual void unused15() = 0;
	virtual void unused16() = 0;
	virtual void *getVisibilityToken() = 0;
};

#define TEN_VIRTUALS(n) \
	virtual void unused##n##0() = 0; \
	virtual void unused##n##1() = 0; \
	virtual void unused##n##2() = 0; \
	virtual void unused##n##3() = 0; \
	virtual void unused##n##4() = 0; \
	virtual void unused##n##5() = 0; \
	virtual void unused##n##6() = 0; \
	virtual void unused##n##7() = 0; \
	virtual void unused##n##8() = 0; \
	virtual void unused##n##9() = 0

class RenderObjVisibleShim
{
public:
	TEN_VIRTUALS(0);
	TEN_VIRTUALS(1);
	TEN_VIRTUALS(2);
	TEN_VIRTUALS(3);
	TEN_VIRTUALS(4);
	TEN_VIRTUALS(5);
	TEN_VIRTUALS(6);
	TEN_VIRTUALS(7);
	TEN_VIRTUALS(8);
	TEN_VIRTUALS(9);
	virtual void unused100() = 0;
	virtual void unused101() = 0;
	virtual void unused102() = 0;
	virtual int isForceVisible() const = 0;

	int isVisible() const;

private:
	char m_unmodelled04[ 0x7C ];
	RenderObjVisibilityScene *m_scene;
	char m_unmodelled84[ 0x0C ];
	void *m_visibilityToken;
};

#undef TEN_VIRTUALS

int RenderObjVisibleShim::isVisible() const
{
	if( isForceVisible() )
		goto visible;
	if( m_scene == 0 || m_visibilityToken == 0 )
		goto hidden;
	if( m_scene->getVisibilityToken() != m_visibilityToken )
		goto hidden;

visible:
	return 1;

hidden:
	return 0;
}

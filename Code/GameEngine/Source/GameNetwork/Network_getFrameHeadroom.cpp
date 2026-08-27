// cl: /DNDEBUG /MD /EHsc

class BFMEConnectionManager
{
public:
	int getFrameHeadroom(void);
};

class Network
{
public:
	virtual int _bfme_getFrameHeadroom(void);

private:
	void *m_subsystemName;
	BFMEConnectionManager *m_conMgr;
};

int Network::_bfme_getFrameHeadroom(void)
{
	if (m_conMgr != 0)
		return m_conMgr->getFrameHeadroom();

	return 0;
}

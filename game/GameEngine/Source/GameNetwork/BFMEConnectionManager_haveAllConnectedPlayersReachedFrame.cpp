// cl: /DNDEBUG /MD /EHsc

// BFME keeps the connection pointers at +0x04 and the latest announced frame
// for each player at +0x12060.  The retail loop checks every occupied slot and
// succeeds only after all connected players have reached the requested frame.
class BFMEConnectionManager
{
public:
	bool haveAllConnectedPlayersReachedFrame(unsigned int frame);

private:
	char m_retailPrefix[4];
	void *m_connections[8];
	char m_unknown24[0x1203C];
	unsigned int m_playerLatestFrame[8];
};

// ?haveAllConnectedPlayersReachedFrame@BFMEConnectionManager@@QAE_NI@Z
bool BFMEConnectionManager::haveAllConnectedPlayersReachedFrame(unsigned int frame)
{
	for (int slot = 0; slot < 8; ++slot) {
		if (m_connections[slot] != 0 && m_playerLatestFrame[slot] < frame)
			return false;
	}

	return true;
}

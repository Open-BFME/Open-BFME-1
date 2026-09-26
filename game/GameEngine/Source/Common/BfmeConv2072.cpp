class BfmeThingHM
{
public:
	void bfmeFillHM(unsigned int *out, unsigned int v, int mode);

	unsigned char m_bfmeHeadHM[0x28];
	unsigned int m_bfme28HM;
};

void BfmeThingHM::bfmeFillHM(unsigned int *out, unsigned int v, int mode)
{
	switch (mode)
	{
	case 0:
		{
			volatile unsigned int *o = out;
			unsigned int m = v & 0xffffff;

			o[0] = m;
			o[0] = ((m_bfme28HM >> 3) << 24) | m;
			o[1] = m;
			o[1] = ((m_bfme28HM >> 3) << 24) | m;
			o[2] = m;
			o[2] = ((m_bfme28HM >> 1) << 24) | m;
			o[3] = m;
			o[3] = ((m_bfme28HM >> 1) << 24) | m;
		}
		break;

	case 1:
		{
			volatile unsigned int *o = out;
			unsigned int m = v & 0xffffff;

			o[0] = m;
			o[0] = (m_bfme28HM << 24) | m;
			o[1] = m;
			o[1] = (m_bfme28HM << 24) | m;
			o[2] = m;
			o[2] = (m_bfme28HM << 24) | m;
			o[3] = m;
			o[3] = (m_bfme28HM << 24) | m;
		}
		break;

	case 2:
		{
			volatile unsigned int *o = out;
			unsigned int m = v & 0xffffff;

			o[0] = m;
			o[0] = ((m_bfme28HM >> 1) << 24) | m;
			o[1] = m;
			o[1] = ((m_bfme28HM >> 1) << 24) | m;
			o[2] = m;
			o[2] = ((m_bfme28HM >> 3) << 24) | m;
			o[3] = m;
			o[3] = ((m_bfme28HM >> 3) << 24) | m;
		}
		break;

	}
}

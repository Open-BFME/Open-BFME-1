// 48-byte bounding min/max update helper

void updateMinMax( float *min, float val, float *max )
{
	if ( val < *min )
	{
		*min = val;
		return;
	}
	if ( val > *max )
	{
		*max = val;
	}
}

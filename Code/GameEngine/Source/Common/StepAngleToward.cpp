// cl: /O2 /Ob0
// Open-BFME5: cdecl angle stepper at 0x0075B550 (209B). No named caller.
// Steps *p toward target by 0.1, reversing direction when |delta| > PI.
// Applies one wrap correction outside [-PI, PI]; endpoints remain unchanged.

void stepAngleToward(float *p, float target)
{
	if (*p > target)
	{
		if (*p - target > 3.14159265359f)
			*p = *p + 0.1f;
		else if (*p - target > 0.1f)
			*p = *p - 0.1f;
		else
			*p = target;
	}
	else if (*p < target)
	{
		if (target - *p > 3.14159265359f)
			*p = *p - 0.1f;
		else if (target - *p > 0.1f)
			*p = *p + 0.1f;
		else
			*p = target;
	}
	if (*p > 3.14159265359f)
		*p = *p - 6.28318530718f;
	if (*p < -3.14159265359f)
		*p = *p + 6.28318530718f;
}

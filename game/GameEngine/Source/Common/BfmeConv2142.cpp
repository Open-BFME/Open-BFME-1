char bfmeTestQP(void *a, void *b);

int bfmeEitherQP(void *a, void *b)
{
	if (bfmeTestQP(a, b) || bfmeTestQP(b, a))
		return 1;

	return 0;
}

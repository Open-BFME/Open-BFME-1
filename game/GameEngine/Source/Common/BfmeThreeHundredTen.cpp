void bfmeDoSixRC(void *what, void *one, void *two, void *three, void *four, int flag);

void *bfmeCallSixRC(void *what, void *one, void *two, void *three, void *four)
{
	bfmeDoSixRC(what, one, two, three, four, 0);
	return what;
}

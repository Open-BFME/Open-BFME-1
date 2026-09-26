// cl: /O2 /MD
extern void *bfmeRva0130CE50RegistrationHead;
extern void *bfmeRva012B3C84RegistrationNext;

void bfmeRva00C6B180LinkRegistration()
{
    bfmeRva012B3C84RegistrationNext = bfmeRva0130CE50RegistrationHead;
    bfmeRva0130CE50RegistrationHead = &bfmeRva012B3C84RegistrationNext;
}

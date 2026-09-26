// cl: /O2 /MD
extern void *bfmeRva0130CE50RegistrationHead;
extern void *bfmeRva012B3C84RegistrationNext;
extern void *bfmeRva012B3FCCRegistrationNext;
extern void *bfmeRva012B4120RegistrationNext;
extern void *bfmeRva012B42E4RegistrationNext;

void bfmeRva00C6B180LinkRegistration()
{
    bfmeRva012B3C84RegistrationNext = bfmeRva0130CE50RegistrationHead;
    bfmeRva0130CE50RegistrationHead = &bfmeRva012B3C84RegistrationNext;
}

void bfmeRva00C6B1A0LinkRegistration()
{
    bfmeRva012B3FCCRegistrationNext = bfmeRva0130CE50RegistrationHead;
    bfmeRva0130CE50RegistrationHead = &bfmeRva012B3FCCRegistrationNext;
}

void bfmeRva00C6B1C0LinkRegistration()
{
    bfmeRva012B4120RegistrationNext = bfmeRva0130CE50RegistrationHead;
    bfmeRva0130CE50RegistrationHead = &bfmeRva012B4120RegistrationNext;
}

void bfmeRva00C6B1E0LinkRegistration()
{
    bfmeRva012B42E4RegistrationNext = bfmeRva0130CE50RegistrationHead;
    bfmeRva0130CE50RegistrationHead = &bfmeRva012B42E4RegistrationNext;
}

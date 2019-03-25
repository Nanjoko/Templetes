#include <cstdio>
#include <windows.h>

#define qdo 262 
#define sqdo 277
#define qre 294
#define sqre 311
#define qmi 330
#define qfa 349
#define sqfa 370
#define qso 392
#define sqso 415
#define qla 440
#define sqla 466
#define qsi 494

#define do 523
#define sdo 554
#define re 578
#define sre 622
#define mi 659
#define fa 698
#define sfa 740
#define so 784
#define sso 831
#define la 880
#define sla 932
#define si 988

#define do1 1046
#define sdo1 1046
#define re1 1175
#define sre1 1245
#define mi1 1318
#define fa1 1480
#define sfa1 1480
#define so1 1568
#define sso1 1661
#define la1 1760
#define sla1 1865
#define si1 1976

#define b(a,b) Beep(a,b)
int main()
{
	int pai=200, ting=64;
	
	Beep(qla, pai);
	Beep(qsi, pai);
	Beep(do, pai);
	Beep(re, pai);
	Sleep(ting);
	
	Beep(qla, pai);
	Beep(qsi, pai);
	Beep(do, pai);
	Beep(re, pai);
	Sleep(ting);
	
	Beep(qso, pai);
	Beep(qla, pai);
	Beep(qsi, pai);
	Beep(do, pai);
	Sleep(ting);
	
	Beep(qso, pai);
	Beep(qla, pai);
	Beep(qsi, pai);
	Beep(do, pai);
	Sleep(ting);
	
	Beep(qfa, pai);
	Beep(qso, pai);
	Beep(qla, pai);
	Beep(qla, pai/2);
	Beep(qfa, pai/2);
	Sleep(ting);
	
	Beep(qfa, pai);
	Beep(qso, pai);
	Beep(qla, pai);
	Beep(qla, pai/2);
	Beep(qfa, pai/2);
	Sleep(ting);
	
	Beep(qfa, pai);
	Beep(qso, pai);
	Beep(qla, pai);
	Beep(do, pai);
	Sleep(ting);
	
	Beep(do, pai);
	Beep(qsi, pai);
	Beep(qla, pai);
	Beep(qso, pai);
	Sleep(ting);
	
	return 0;
}

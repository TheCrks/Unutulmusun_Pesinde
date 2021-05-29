#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#define developerMode 1


void Menu();
void Death();
void LvlUP();
void Savas();
void SatisMenu();
void SehirMenuYazilar();
void HanMenu();
void HanciMenu();
void Envanter();
void SehirMenu(void x(),int max);
void Isaretle(short x);
void EkranTaslak();
void AcceptYazilar();
void CharacterCreation();
void devCharacter();
void devMenu();
void Chapter0();
void Chapter1();
void Chapter2();
void Chapter3();
void CreationYazilar1();
void CreationYazilar2();
void CreationYazilar3(); 
void Creation(void x(),int max);
void Accept(void x(),int max);
void git(int x , int y);
void Temizle();
void sonMenu();

int slot=0;
short satir, kolon, karakter=219;
enum boolean{ F, T }durum=T;
unsigned char tus;

 
struct Enemy{
	char AD[30];
	int ATK;
	int DEF;
	int CAN;
}Def={"def",1,1,20}; 
 
void SavasMenu(struct Enemy x);
 
struct Item{
	char AD[30];
	int IATK;
	int IDEF;
	int IVLU;
}DefalutI={"Yok",0,0,0};

struct CItem{
	char ADI[30];
	int HEL;
	int VLU;
	int ADT;
}DefaultC={"Yok",0,0,0};

void TuccarMenu(struct Item x[10]);

struct player{
	int level;
	int EXP;
	int ATK;
	int DEF;
	int CAN;
	int MCAN;
	char AD[20];
	struct Item AITM;
	struct Item DITM;
	struct Item UITM[10];
	struct CItem CONS[5];
	int GLD;
	enum LOC{C0,C1,C2,C3}Location; 
}Baslangic={1,0,6,1,25,25,"Default",{"Yok",0,0,0},{"Yok",0,0,0},{},{},0,C0},player,playerOnDeath;



char *AttackItem[30]={"Basit K�l��","Basit Balta","Basit M�z�rak","�yi K�l��","�yi Balta","�yi M�z�rak","Ork K�l���","Ork Baltas�","Ork M�z�ra��","Elf K�l�c�","Elf Baltas�","Elf M�z�ra��","C�ce K�l�c�","C�ce Baltas�","C�ce M�z�ra��","B�y�k K�l�c","B�y�k Balta","B�y�k M�z�rak","K���k K�l�c","K���k Balta","K���k M�z�rak","�elik K�l�c","�elik Balta","�elik M�z�rak","K�l�c","Balta","M�z�rak","�zel K�l�c","�zel Balta","�zel M�z�rak",};
char *DefansItem[10]={"Basit Z�rh","�yi Z�rh","�elik Z�rh","Ork Z�rh�","Elf Z�rh�","C�ce i�i Z�rh","Kal�n Z�rh","�nce Z�rh","Ta� Z�rh","Zincir Z�rh"};


int main() {
	setlocale(LC_ALL, "Turkish");	
	player=Baslangic;	
	int i;
	
for(i=0;i<10;i++){
	player.UITM[i]=DefalutI;
}
for(i=0;i<5;i++){
player.CONS[i]=DefaultC;	
}
	strcpy(player.CONS[0].ADI,"�la�");	strcpy(player.CONS[1].ADI,"Elma");	strcpy(player.CONS[2].ADI,"Bandaj");  strcpy(player.CONS[3].ADI,"Portakal");	strcpy(player.CONS[4].ADI,"Mantar");
	player.CONS[0].HEL=5;		player.CONS[1].HEL=1;		player.CONS[2].HEL=4;		player.CONS[3].HEL=3;		player.CONS[4].HEL=2;
	srand(time(NULL)); 
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd,SW_SHOWMAXIMIZED);
	Menu();
	if (developerMode==0){
		CharacterCreation();	
		playerOnDeath=player;
		EkranTaslak();
		Temizle();
		Sleep(1000);
		Chapter0();	
		return 0;
	}
	else if(developerMode==1){
		devCharacter();
		playerOnDeath=player;
		EkranTaslak();
		Temizle();
		devMenu();
		return 0;
	}
}

void HideCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void git(int s,int k){
	HANDLE hConsoleOutput;
	COORD ImlecYeri={k-1,s-1};
	hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, ImlecYeri);
}
void EkranTaslak(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); 
	satir = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;  // Concole ekran y�ksekli�i al�n�yor  63
	kolon = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Console ekran geni�li�i al�n�yor 237
	short i,j;
	for(i=0;i<satir-1;i++){
		for(j=0;j<kolon;j++){
			if( i==0 || i==satir-2 ){
				git(i+1,j+1);printf("|");
			}
			if( j<2 || j>kolon-3 ){
				git(i+1,j+1);printf("|");
			}
		}
	}
}
void YaziYaz(short x, short y, char *adres, short byt){
	int i;
	git(x,y);
	for(i=0;i<byt;i++){printf("%c",*(adres+i));}
}

void Yazilar(){

  	char bilgi[]="HUBC";
  	char baslik[]="Unutulmu�un Pe�inde";
  	char menu1[]="B A � L A";
  	char menu2[]="� I K I �";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
}
void Isaretle(short sec){
	int i, konum[]={19,22,25,28,31,34,37,40};
	for(i=0;i<sizeof(konum)/sizeof(int);i++){
		if((i+1)==sec){
			git(konum[i],(kolon-4-strlen("B A � L A"))/2-7);
			printf("%c%c%c",16,16,16);
			git(konum[i],(kolon-4-strlen("B A � L A"))/2+13);
			printf("%c%c%c",17,17,17);
		}else{
			git(konum[i],(kolon-4-strlen("B A � L A"))/2-7);
			printf("   ");
			git(konum[i],(kolon-4-strlen("B A � L A"))/2+13);
			printf("   ");
		}
	}
}
void Menu(){
	system("cls");
	HideCursor();
	EkranTaslak();
	Yazilar();
	durum=T;
	int secim=1;

	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;	
			}else if(tus==13){
				if (secim==1){
					durum=F;
				}else if(secim==2){
					exit(0);
				}
			}
		}
		Isaretle(secim);
		Sleep(60);	
	}
}
void CreationYazilar1(){
	char bilgi[]="HUBC";
  	char baslik[]="S I N I F	S E �";
  	char menu1[]="SAVA��I";
  	char menu2[]="TANK";
  	char menu3[]="AVCI";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
  	YaziYaz(25,(kolon-4-strlen(menu3))/2,menu3,strlen(menu3));
	
}
void CreationYazilar2(){
	char bilgi[]="HUBC";
  	char baslik[]="I R K	S E �";
  	char menu1[]="�NSAN";
  	char menu2[]="ORK";
  	char menu3[]="ELF";
  	char menu4[]="C�CE";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
  	YaziYaz(25,(kolon-4-strlen(menu3))/2,menu3,strlen(menu3));
  	YaziYaz(28,(kolon-4-strlen(menu4))/2,menu4,strlen(menu4));
	
}
void CreationYazilar3(){
	char bilgi[]="HUBC";
  	char baslik[]="A�LEN";
  	char menu1[]="ASKERLERD�";
  	char menu2[]="DEM�RC�LERD�";
  	char menu3[]="MUHAFIZLARDI";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
  	YaziYaz(25,(kolon-4-strlen(menu3))/2,menu3,strlen(menu3));
	
}
void AcceptYazilar(){
	char bilgi[]="HUBC";
  	char baslik[]=" ";
  	char menu1[]="KABUL ET";
  	char menu2[]="TEKRAR YAP";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
	
}

void Creation(void x(),int max){
	int secim=1;
	durum=T;
	Temizle();
	
			x();
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						break;
				}
				secim=(secim==max)?1:secim;
				secim=(secim==0)?max-1:secim;	
			}else if(tus==13){
				if (secim==1){
					player.ATK+=1;
					player.DEF+=3;
					durum=F;
				}else if(secim==3){
					player.ATK+=2;
					durum=F;
				}else if(secim==2){
					player.DEF+=5;
					player.ATK+=1;
					durum=F;
				}else if(secim==4){
					player.DEF+=6;
					durum=F;
				}
			}
		}
		Isaretle(secim);
		Sleep(60);	
	}
	
}

void Creation1(void x(),int max){
	int secim=1;
	durum=T;
	Temizle();
			x();
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						break;
				}
				secim=(secim==max)?1:secim;
				secim=(secim==0)?max-1:secim;	
			}else if(tus==13){
				if (secim==1){
					player.ATK+=2;
					player.DEF+=2;
					player.GLD+=50;
					durum=F;
				}else if(secim==3){
					player.ATK+=2;
					player.GLD+=75;
					durum=F;
				}else if(secim==2){
					player.DEF+=4;
					player.ATK+=1;
					player.GLD=100;
					durum=F;
				}
			}
		}
		Isaretle(secim);
		Sleep(60);	
	}
	
}
void Accept(void x(),int max){
	int secim=1;
	durum=T;
			x();
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						break;
				}
				secim=(secim==max)?1:secim;
				secim=(secim==0)?max-1:secim;	
			}else if(tus==13){
				if (secim==1){
					durum=F;
				}else if(secim==2){
					player=Baslangic;
					CharacterCreation();
					durum=F;
				}
			}
		}
		Isaretle(secim);
		Sleep(60);	
	}
	
}
void CharacterCreation(){
	Temizle();
	Creation(CreationYazilar1,4);
	Temizle();
	Creation(CreationYazilar2,5);
	Temizle();
	Creation1(CreationYazilar3,4);
	Temizle();
	git(20,33);
	printf("� S M � N");
	Isaretle(3);
	git(25,35);
	scanf("%s",player.AD);
	Temizle();
	EkranTaslak();
	git(5,5);
	printf("%s'in De�erleri:",player.AD);
	git(7,5);
	printf("G�c:%d",player.ATK);
	git(8,5);
	printf("Defans:%d",player.DEF);
	git(9,5);
	printf("Alt�n:%d",player.GLD);
	Accept(AcceptYazilar,3);	
};

void devCharacter(){
	player.ATK=100;
	player.DEF=100;
	player.CAN=100;
	player.GLD=10000;
	player.AITM.IVLU=5;
	player.DITM.IVLU=5;
	player.AITM.IATK=5;
	player.DITM.IDEF=5;
	strcpy(player.AITM.AD,"A");
	strcpy(player.DITM.AD,"B");
	strcpy(player.AD,"Developer");
}

void devMenu(){
	Temizle();
	git(10,6);printf("Developer Menu");Sleep(60);
	git(13,6);printf("Chapter 0");Sleep(60);
	git(14,6);printf("Chapter 1");Sleep(60);
	git(15,6);printf("Chapter 2");Sleep(60);
	git(16,6);printf("Chapter 3");Sleep(60);
	git(17,6);printf("Sehir Menu");Sleep(60);
	git(18,6);printf("Han Menu");Sleep(60);
	git(19,6);printf("Savas");Sleep(60);
	git(20,6);printf("��k��");
	durum=T; int secim=1, max=9; 
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72: 
						secim--;
						break;
					case 80: 
						secim++;
						break;
				}
				secim=(secim==max)?1:secim;
				secim=(secim==0)?max-1:secim;
				}
				else if(tus==13){
					if(secim==1){
						Temizle();
						git(22,5);printf("Chapter 0'a giriliyor");Sleep(60);
						Chapter0();
					}
					else if(secim==2){
						Temizle();
						git(22,5);printf(" Chapter 1'e giriliyor");Sleep(60);	
						Chapter1();
					}
					else if(secim==3){
						Temizle();
						git(22,5);printf(" Chapter 2'ye giriliyor");Sleep(60);
						Chapter2();
					}
					else if(secim==4){
						Temizle();
						git(22,5);printf(" Chapter 3'e giriliyor");Sleep(60);
						Chapter3();
					}
					else if(secim==5){
						Temizle();
						git(22,5);printf("Sehir Menu a��l�yor");Sleep(60);
						SehirMenu(SehirMenuYazilar,6);
					}
					else if(secim==6){
						Temizle();
						git(22,5);printf("Han Menu a��l�yor");Sleep(60);
						HanciMenu();
					}
					else if(secim==7){
						struct Enemy a; char isim[7]="Hacker";
						Temizle();
						git(22,5);printf("Sava� a��l�yor");Sleep(60);
						Savas(a,isim);
					}
					else if(secim==8){
						Temizle();
						exit(0);
					}
				}
			}
		short x;
		for (x=1;x<max;x++){
		git(secim+12+x,5);printf(" ");
		git(secim+12-x,5);printf(" ");
		}
		git(secim+12,5);printf(">");
	}
	devMenu();
}

void Temizle(){
	int x,y;
			git(3,3);
		for(x=3;x<50;x++){
			for(y=3;y<79;y++){
			printf(" ");
			}
		git(x,3);	
		}
}
void SavasYazilar(){
	char bilgi[]="HUBC";
  	char menu1[]="Sald�r";
  	char menu2[]="Envanter";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
	
}
void Savas(struct Enemy x,char ad[]){
srand(time(0));
if(player.Location==C0){
strcpy(x.AD,ad);
x.ATK=rand()%3+(player.level+2);
x.DEF=rand()%3+(player.level)+3;
x.CAN=rand()%15+7+(player.level);}
if(player.Location==C1){
strcpy(x.AD,ad);
x.ATK=rand()%5+(player.level)+2;
x.DEF=rand()%5+(player.level)+3;
x.CAN=rand()%20+7+(player.MCAN/2)+1;}
else{
strcpy(x.AD,ad);
x.ATK=rand()%5+player.level+5;
x.DEF=rand()%5+player.level+6;
x.CAN=rand()%25+6+player.level+1;}
SavasMenu(x);
};


void HealMenu(){
			Temizle();
				int i,secim=0;
	git(5,5);printf("T�ketilebilir E�yalar: ");
	for(i=0;i<5;i++){
		git(i+8,5);printf(" %s ",player.CONS[i].ADI);git(i+8,25);printf("(%d Adet)",player.CONS[i].ADT);
	}
	durum=T;
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==5)?0:secim;
				secim=(secim==-1)?4:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // a�a�� y�n tu�u
						secim++; 
						git(secim+7,5);printf(" ");						
				secim=(secim==5)?0:secim;
				secim=(secim==-1)?4:secim;
						git(secim+8,5);printf(">");						
						break;
				}		
			}else if(tus==13){
				switch(secim){
					case 0:	
						if(player.CONS[0].ADT>=1){
							player.CONS[0].ADT-=1;
							player.CAN+=player.CONS[0].HEL;
							git(15,5);printf("%d kadar iyile�tin",player.CONS[0].HEL);Sleep(1000);}							
						else{
							git(15,5);printf("Yetersiz E�ya");Sleep(1000);
								}	
							durum=F;	
					break;
					case 1:
						if(player.CONS[1].ADT>=1){
							player.CONS[1].ADT-=1;
							player.CAN+=player.CONS[1].HEL;
							git(15,5);printf("%d kadar iyile�tin",player.CONS[1].HEL);Sleep(1000);}							
						else{
							git(15,5);printf("Yetersiz E�ya");Sleep(1000);
								}	
							durum=F;
					break;						
					case 2:
						if(player.CONS[2].ADT>=1){
							player.CONS[2].ADT-=1;
							player.CAN+=player.CONS[2].HEL;
							git(15,5);printf("%d kadar iyile�tin",player.CONS[2].HEL);Sleep(1000);}							
						else{
							git(15,5);printf("Yetersiz E�ya");Sleep(1000);
								}	
							durum=F;
					break;
					case 3:
						if(player.CONS[3].ADT>=1){
							player.CONS[3].ADT-=1;
							player.CAN+=player.CONS[3].HEL;
							git(15,5);printf("%d kadar iyile�tin",player.CONS[3].HEL);Sleep(1000);}
						else{
							git(15,5);printf("Yetersiz E�ya");Sleep(1000);
								}	
							durum=F;
					break;							
					case 4:
						if(player.CONS[4].ADT>=1){
							player.CONS[4].ADT-=1;
							player.CAN+=player.CONS[4].HEL;
							git(15,5);printf("%d kadar iyile�tin",player.CONS[4].HEL);Sleep(1000);	}						
						else{
							git(15,5);printf("Yetersiz E�ya");Sleep(1000);
								}	
							durum=F;
					break;																																																									
				}
			}	
		}
		
					player.CAN=(player.CAN<0)?0:player.CAN;	
			if(durum==F){
									Temizle();
									break;
			}

}
}



void SavasMenu(struct Enemy enemy){
			SavasYazilar();	
	srand(time(0));
	int secim=1,yedek=0,yedek1=0,TP=0,AL=0,heal=0;
	int def;
	def=(int)(player.DEF+player.DITM.IDEF)/10;
	int eatk=enemy.ATK-def;
	while(enemy.CAN>0){
		eatk=(eatk<0)?0:eatk;
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;	
			}else if(tus==13){
				if (secim==1){
					yedek=enemy.CAN;
					enemy.CAN-=player.AITM.IATK+player.ATK-(enemy.DEF/100);enemy.CAN=(enemy.CAN<0)?0:enemy.CAN;
					git(15,5);printf("%d hasar verdin            ",yedek-enemy.CAN);Sleep(1000);
					if(enemy.CAN==0) break;
					git(15,5);printf("D��man Saldirdi            ");Sleep(1000);
					player.CAN=player.CAN-eatk;
					git(15,5);printf("%d hasar ald�n             ",eatk);Sleep(1000);
					player.CAN=(player.CAN<0)?0:player.CAN;	
					Death();				
				}else if(secim==2){
					HealMenu();
					player.CAN=player.CAN-eatk;
					if(player.CAN>player.MCAN)player.CAN=player.MCAN;
					git(15,5);printf("D��man Saldirdi             ");Sleep(1000);					
					git(15,5);printf("%d hasar ald�n.             ",eatk);Sleep(1000);
					player.CAN=(player.CAN<0)?0:player.CAN;	
					Death();}
				}
			}
		
		Isaretle(secim);
		git(5,5);printf("%s'in Can�: %d  ",player.AD,player.CAN);git(5,40);printf("%s'in Can�: %d  ",enemy.AD,enemy.CAN);
		git(6,5);printf("%s'in G�c�: %d  ",player.AD,player.ATK);git(6,40);printf("%s'in G�c�: %d  ",enemy.AD,enemy.ATK);
		git(7,5);printf("%s'in Defans�: %d  ",player.AD,player.DEF);git(7,40);printf("%s'in Defans�: %d  ",enemy.AD,enemy.DEF);
				SavasYazilar();
		Sleep(60);
	}
	TP=rand()%5+enemy.ATK-1;
	AL=rand()%20+15+enemy.ATK-1;
	player.EXP+=TP;
	player.GLD+=AL;
	Temizle();
	git(10,25);printf("K A Z A N D I N !");
	git(20,5);printf("%d TP ve %d Alt�n kazanadin",TP,AL);
	int EsyaSansi,f,k=rand()%2,LootSlot=0,j;
	struct Item Loot;
	if(k==0){
	strcpy(Loot.AD,AttackItem[rand()%30]);
		Loot.IATK=rand()%3+player.level;
		Loot.IDEF=0;
		Loot.IVLU=rand()%5+15+player.level+Loot.IATK;
	}else{
	strcpy(Loot.AD,DefansItem[rand()%10]);
		Loot.IATK=0;
		Loot.IDEF=rand()%3+player.level;
		Loot.IVLU=rand()%5+15+player.level+Loot.IDEF;
	}
	f=rand()%10+1;
	EsyaSansi=rand()%50+f;
	for(j=0;j<10;j++){
		if(player.UITM[j].IVLU!=0)LootSlot++;
	}
	if(LootSlot<=9){
		if(player.Location>=C1){
	if(EsyaSansi==1 || EsyaSansi==10 || EsyaSansi==20 || EsyaSansi==30 || EsyaSansi==40 || EsyaSansi==49){
	player.UITM[LootSlot]=Loot;
	git(22,5);printf(" %s Den bir %s buldun.(E�yalar� �ehirde Donanabilirsin.)",enemy.AD,Loot.AD);	
	}}}
	getch();
}

void LvlUP(){
	if(player.EXP>=20 && player.level<2){
	Temizle();
	git(5,25);printf("S E V � Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("G�c defeans ve max can�n arrt� ve tamamen iyile�tin");Sleep(60);
	git(8,5);printf("Yeni De�erlerin:");
	git(10,5);printf("G�c: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Alt�n: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecr�be puan�: %d",player.EXP);
	git(16,5);printf("Sald�r� E�yan: ");
	git(17,5);printf("%s        Hasar�: %d       De�eri: %d Alt�n",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma E�yan: ");	
	git(19,5);printf("%s        Defans�: %d       De�eri: %d Alt�n",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();		
	}
	else if(player.EXP>=40 && player.level<3){
	Temizle();
	git(5,25);printf("S E V � Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("G�c defeans ve max can�n arrt� ve tamamen iyile�tin");Sleep(60);
	git(8,5);printf("Yeni De�erlerin:");
	git(10,5);printf("G�c: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Alt�n: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecr�be puan�: %d",player.EXP);
	git(16,5);printf("Sald�r� E�yan: ");
	git(17,5);printf("%s        Hasar�: %d       De�eri: %d Alt�n",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma E�yan: ");	
	git(19,5);printf("%s        Defans�: %d       De�eri: %d Alt�n",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();		
	}
	else if(player.EXP>=60 && player.level<4){
	Temizle();
	git(5,25);printf("S E V � Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("G�c defeans ve max can�n arrt� ve tamamen iyile�tin");Sleep(60);
	git(8,5);printf("Yeni De�erlerin:");
	git(10,5);printf("G�c: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Alt�n: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecr�be puan�: %d",player.EXP);
	git(16,5);printf("Sald�r� E�yan: ");
	git(17,5);printf("%s        Hasar�: %d       De�eri: %d Alt�n",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma E�yan: ");	
	git(19,5);printf("%s        Defans�: %d       De�eri: %d Alt�n",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();;	
	}
	else if(player.EXP>=80 && player.level<5){
	Temizle();
	git(5,25);printf("S E V � Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("G�c defeans ve max can�n arrt� ve tamamen iyile�tin");Sleep(60);
	git(8,5);printf("Yeni De�erlerin:");
	git(10,5);printf("G�c: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Alt�n: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecr�be puan�: %d",player.EXP);
	git(16,5);printf("Sald�r� E�yan: ");
	git(17,5);printf("%s        Hasar�: %d       De�eri: %d Alt�n",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma E�yan: ");	
	git(19,5);printf("%s        Defans�: %d       De�eri: %d Alt�n",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();
	}
	else if(player.EXP>=100 && player.level<6){
	Temizle();
	git(5,25);printf("S E V � Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("G�c defeans ve max can�n arrt� ve tamamen iyile�tin");Sleep(60);
	git(8,5);printf("Yeni De�erlerin:");
	git(10,5);printf("G�c: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Alt�n: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecr�be puan�: %d",player.EXP);
	git(16,5);printf("Sald�r� E�yan: ");
	git(17,5);printf("%s        Hasar�: %d       De�eri: %d Alt�n",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma E�yan: ");	
	git(19,5);printf("%s        Defans�: %d       De�eri: %d Alt�n",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();
	}
}
void Death(){
	if(player.CAN==0 && player.Location==0){
	Temizle();
	durum=T;
	char menu1[]="Tekrar Dene";
	char baslik[]="� L D � N";
	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					player=playerOnDeath;
					durum=F;Temizle();Sleep(1000);
					Chapter0();				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}	
	}
	else if(player.CAN==0 && player.Location==1){
		Temizle();
	durum=T;
	char menu1[]="Tekrar Dene";
	char baslik[]="� L D � N";
	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					player=playerOnDeath;
					durum=F;Temizle();Sleep(1000);
					Chapter1();				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}	
	}	else if(player.CAN==0 && player.Location==2){
		Temizle();
	durum=T;
	char menu1[]="Tekrar Dene";
	char baslik[]="� L D � N";
	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					player=playerOnDeath;
					durum=F;Temizle();Sleep(1000);
					Chapter2();				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}	
	}	else if(player.CAN==0 && player.Location==3){
		Temizle();
	durum=T;
	char menu1[]="Tekrar Dene";
	char baslik[]="� L D � N";
	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					player=playerOnDeath;
					durum=F;Temizle();Sleep(1000);
					Chapter3();				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}	
	}	else{
		durum=F;
	}	
}

void Chapter0(){
	git(5,5);printf("G�zlerini yava��a a��yorusun.Bir yatakta uyand�n. Ancak buraya nas�l ");Sleep(60);
	git(6,5);printf("geldi�in hakk�nda hi� bir fikrin yok.Yava��a kalk�yorsun. Yaralar�n ");Sleep(60);
	git(7,5);printf("oldu�unu fark ediyorsun. Biraz zorlanarak da olsa aya�a kalk�yorsun.");Sleep(60);
{	durum=T;
	char menu1[]="Etraf� Arast�r";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
Temizle();
	git(8,5);printf("Etrafa Bakindin. Yatti�in Yerin Yakininda bir not buldun.");
{	durum=T;
	char menu1[]="Notu Oku";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
Temizle();
	git(8,5);printf("Seni yaral� halde ana yolun �st�nde buldum. Ben yak�ndaki �ehirdeki");Sleep(60);
	git(9,5);printf("bir t�ccar�m. Uzun zamand�r uyuyorsun. Ben �ehre gitmek zorunday�m.");Sleep(60);
	git(10,5);printf("L�tfen �ehre gelmeye �al��ma yollarda haydutlar tuzak kuruyor.");Sleep(60);
	git(11,5);printf("E�er nerden gitmen gerekti�i bilmiyorsan kesin bir tuza�a d��ersin.");Sleep(60);
	git(12,5);printf("�stelik bir ma�aradan da ge�men gerekli. Ben gelene kadar bekle.");Sleep(60);
{	durum=T;
	char menu1[]=">>>   �ehre Do�ru Yola ��k   <<<";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Sleep(60);	
		}
}
Temizle();
	git(8,5);printf("Yolda etrafa dikkatlice bakarak y�r�ken birinin elinde k�l��la sana");Sleep(60);
	git(9,5);printf("do�ru ko�tu�unu farkediyorsun. Sald�racak gibi duruyor. Yakla�ma diye");Sleep(60);
	git(10,5);printf("ba�r�yorsun. Adam biraz daha ko�up duruyor.");Sleep(60);
	git(11,5);printf("Haydut: Ya paran� verirsin yada zorla al�r�m");Sleep(60);
{	struct Enemy a;durum=T;int secim=1;char isim[7]="Haydut";
git(13,5);printf("  Sana tek kuru� vermeyece�im");Sleep(60);
git(14,5);printf("  Tamam ge�i� i�in para �deyece�im (75 Alt�n)");Sleep(60);
durum=T;	
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72: 
						secim--;
						break;
					case 80: 
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){
					Temizle();
					durum=F;
					Savas(a,isim);	
					}else if(secim==2){
						if(player.GLD>=75){
					git(22,5);printf("75 altin �dedin");
					player.GLD-=75;
						}else{
							git(17,5);printf("Yeteri kadar paran yok. Saldirmak zorundasin.");Sleep(70);
							getch();
							Temizle();
							Savas(a,isim);
							 }
					durum=F;	
					}
				}
			}
		git(secim+11,5);printf(" ");	
		git(secim+12,5);printf(">");
		git(secim+13,5);printf(" ");	
		}
git(1+12,5);printf(" ");
git(2+12,5);printf(" ");		
}
LvlUP();
Temizle();
	git(5,5);printf("Haydutdan kurtulduktan sonra yoluna devam ediyorusun.Ancak biraz ilerde");Sleep(60);
	git(6,5);printf("ba�ka bir haydut �n�n� kesiyor.");Sleep(60);	
{	struct Enemy a;durum=T;int secim=1;char isim[7]="Haydut";
git(13,5);printf("  Sana tek kuru� vermeyece�im");Sleep(60);
git(14,5);printf("  Tamam ge�i� i�in para �deyece�im (75 Alt�n)");Sleep(60);
durum=T;	
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72: 
						secim--;
						break;
					case 80: 
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){
					Temizle();
					durum=F;
					Savas(a,isim);	
					}else if(secim==2){
						if(player.GLD>=75){
					git(22,5);printf("75 altin �dedin");
					player.GLD-=75;
						}else{
							git(17,5);printf("Yeteri kadar paran yok. Saldirmak zorundasin.");Sleep(70);
							getch();
							Temizle();
							Savas(a,isim);
							 }
					durum=F;	
					}
				}
			}
		git(secim+11,5);printf(" ");	
		git(secim+12,5);printf(">");
		git(secim+13,5);printf(" ");	
		}
git(1+12,5);printf(" ");
git(2+12,5);printf(" ");		
}	
LvlUP();
Temizle();
	git(5,5);printf("2. hayduttan da kurtulktan sonra yoluna devam ediyorusun. Biraz daha");Sleep(60);
	git(6,5);printf("ilerledikten sonra bir ma�ara giri�ine rastl�yorsun. Bu notta bahsedilen");Sleep(60);
	git(7,5);printf("Ma�ara olmal� diye d���n�yorsun. Biraz bir a�a� g�lgesinde dinlektikten");Sleep(60);
	git(8,5);printf("sonra ma�aran�n i�ine do�ru ilerliyorsun. Ma�arada y�r�ken ad�mlar�na");Sleep(60);
	git(9,5);printf("dikkat ederek, olabilidi�ince az ses ��kararak y�r�yorsun. Ancak bir");Sleep(60);
	git(10,5);printf("kurt seni fark ediyor. Olduk�a a� g�r�nen kurt sana do�ru ko�uyor");Sleep(600);
	getch();
	Temizle();
{
	struct Enemy kurt;char kurtad[5]="Kurt";
	Savas(kurt,kurtad);
}		
LvlUP();
Sleep(250);
Temizle();
	git(5,5);printf("Kurtun icab�na bakt�ntan sonra ilerde bir ���k g�r�yorsun. I���a do�ru");Sleep(60);
	git(6,5);printf("yakla�t�k�a sesler duymaya ba�l�yorsun. I����n ma�aran�n ��k��� oldu�unu");Sleep(60);
	git(7,5);printf("anlaman uzun s�rm�yor. Ma�aradan ��k�nca ilerdeki �ehri g�r�yorsun");Sleep(60);
{	durum=T;
	char menu1[]="�ehre Git";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);	
		Sleep(60);	
		}
}
	Temizle();
	git(5,5);printf("�ok ge�meden �ehre var�yorsun. �ehrin sokakalr�nda dola�maya ba�l�yorsun.");Sleep(60);
	git(6,5);printf("Kalabal�k bir sokakata gezerken birisi sana sesleniyor. Sesin ne taraftan");Sleep(60);
	git(7,5);printf("geldi�ini anlamaya �al���rken biri seni kolundan tutup demirci d�kkan�na");Sleep(60);
	git(8,5);printf("g�t�r�yor. Biraz sinirli  bir tonla konu�maya ba�l�yor.");Sleep(60);
	git(10,5);printf("Demirci: Sana beni beklemni s�ylememi� miydim? Neden beni dinlemiyorsun?");Sleep(60);	
{	int secim=1;
	git(13,5);printf(" Beni sen mi kurtard�n?");
	git(14,5);printf(" Beni tan�yor musun?");
durum=T;	
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72: 
						secim--;
						break;
					case 80: 
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){
						git(11,5);printf("Beni sen mi kurtard�n?");Sleep(500);
						git(13,5);printf("                        ");
						git(14,5);printf("                        ");
					durum=F;	
					}else if(secim==2){
						git(11,5);printf("Beni tan�yor musun?");Sleep(500);
						git(13,5);printf("                        ");
						git(14,5);printf("                        ");
						
					durum=F;	
					}
				}
			}
		git(secim+11,5);printf(" ");	
		git(secim+12,5);printf(">");
		git(secim+13,5);printf(" ");	
		}
git(1+12,5);printf(" ");
git(2+12,5);printf(" ");
Sleep(250);		
}
	Sleep(500);git(12,5);printf("Demrici: Notumu okumad�n m�. Seni yolda buldum. Yaral�yd�n. Hatta");Sleep(60);
	git(13,5);printf("seni �l� san�p orda b�racakt�m. Ancak say�klamaya ba�lad�n. Bo�alar");Sleep(60);
	git(14,5);printf("gibi bir �ey diyordun. bunun sana bo�alar m� yapt�?");Sleep(60);
{	int secim=1;
	git(16,5);printf(" Bo�alar?");
	git(17,5);printf(" Hat�rlayam�yorum.");
	git(18,5);printf(" Buralarda vah�i bo�a m� var?");
durum=T;	
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72:
						secim--;
						git(secim+16,5);printf(" "); 						
				secim=(secim==4)?1:secim;
				secim=(secim==0)?3:secim;						
						git(secim+15,5);printf(">");
						break;
					case 80: 
						secim++;
						git(secim+14,5);printf(" ");						
				secim=(secim==4)?1:secim;
				secim=(secim==0)?3:secim;
						git(secim+15,5);printf(">");
						break;
				}
				secim=(secim==4)?1:secim;
				secim=(secim==0)?3:secim;
				}
				else if(tus==13){
					if(secim==1){
						git(15,5);printf("Bo�alar?");
						git(16,5);printf("                              ");Sleep(500);
						git(17,5);printf("                              ");
						git(18,5);printf("                              ");
					durum=F;	
					}else if(secim==2){
						git(15,5);printf("Hat�rlayam�yorum.");Sleep(500);
						git(16,5);printf("                              ");
						git(17,5);printf("                              ");
						git(18,5);printf("                              ");
					durum=F;	
					}else if(secim==3){
						git(15,5);printf("Buralarda vah�i bo�a m� var?");Sleep(500);
						git(16,5);printf("                              ");
						git(17,5);printf("                              ");
						git(18,5);printf("                              ");	
					durum=F;						
					}
				}
			}	
		}
	Sleep(200);			
}
	git(16,5);printf("Bo�alar buralar�n en bilinen haydut grubudur. Bu �ehride bir doktor var.");Sleep(60);
	git(17,5);printf("Onu bul. Belki hat�rlamana yard�mc� olabilir. Doktordan sonra bana tekrar");Sleep(60);
	git(18,5);printf("bir u�ra. Senin i�in k�l�� ve z�rh yapaca��m. Belki sana �zel bir indirim");Sleep(60);
	git(19,5);printf("bile yapar�m. Doktor muhtemlen handad�r.");Sleep(60);
	
{	durum=T;
	char menu1[]="Hana Git";
	YaziYaz(22,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(2);
	git(19,5);printf("bile yapar�m. Doktor muhtemlen handad�r.");Sleep(1000);				
		}
}
	Sleep(250);
	Temizle();
	git(5,5);printf("Han� bulup i�eri giriyorsun. Etrafa bir g�z gezdirip hanc�ya do�ru");Sleep(60);
	git(6,5);printf("ilerliyorsun. Hanc�dan i�ecek isteyip dokturu soruyorsun. hanc� kafas�yla");Sleep(60);
	git(7,5);printf("Bir adam� i�aret ediyor. i�ece�ini i�ip doktora gidiyorsun. Demircinin");Sleep(60);
	git(8,5);printf("s�ylediklerini ona anlat�yorsun. Doktor arkas� d�n�k \"Yinebir pusu vakas�\"");Sleep(60);
	git(9,5);printf("diyor ve d�n�yor. Doktorun surat�nda bir �a�k�nl�k ifadesi g�r�yorsun.");Sleep(60);
	git(10,5);printf("Doktor: %s bu sen misin? Ne oldu sana? Gel de bana her�eyi anlat.",player.AD);Sleep(60);
	git(11,5);printf("(bir s�re sonra)");Sleep(60);
	git(12,5);printf("Doktor: Ah pardon hat�rlam�yordun de�il mi? �u ila�lar� i�ip biraz");Sleep(60);
	git(13,5);printf("dinlenirsen yava� yava� hat�rlamaya ba�lars�n.");Sleep(60);
{	durum=T;
	char menu1[]="�la�lar� i�";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);	
		Sleep(60);	
		}
		
}
	player.CAN=player.MCAN;
	git(16,5);printf("�la�lar�n� i�ip uykuya dal�yorsun. Uyand���nda her hafta doktora erzak");Sleep(60);
	git(17,5);printf("ve ila� getirip yard�m etti�ni hat�rl�yorsun. onun �ocukluk arkada��n");Sleep(60);
	git(18,5);printf("oldu�u akl�na geliyor. Bir s�re sonra sald�r�ld���n g�n� hat�rl�yorsun.");Sleep(60);
	git(19,5);printf("Ailenle birlikte oldupunu hat�rl�yorsun. onlar� korumaya �al���rken");Sleep(60);
	git(20,5);printf("A��r yaralanm��t�n. neyseki seni �l� san�p yolda atm��lard�. Ancak");Sleep(60);
	git(21,5);printf("ailen hala onlar�n elindeydi. en k�sa zamanda yola ��kman gerekiyordu.");Sleep(60);
	git(22,5);printf("Doktoru �a��r�p en yak�nda Bo�a s���na��n� sordun.");Sleep(60);
	git(23,5);printf("Doktor: �ehrin biraz kuzeyinde ama oras� iyi korunur. g�neyde k���k");Sleep(60);
	git(24,5);printf("bir erzak depolar� var orda arad��n cevaplar� bulabilirsin belki");Sleep(60);
	git(25,5);printf("gitmeden bunlar� da al.(5 ila� ald�n)");Sleep(60);
	player.CONS[0].ADT+=5;
{
struct Item BasicSword, BasicArmor;
BasicSword.IATK=2;							BasicArmor.IATK=0;	
BasicSword.IDEF=0;							BasicArmor.IDEF=5;		
BasicSword.IVLU=25;							BasicArmor.IVLU=25;		
strcpy(BasicSword.AD,"Basit K�l�c");		strcpy(BasicArmor.AD,"Basit Z�rh");	
	int secim=1;durum=T;
	char menu1[]="Demirciye Git";
	char menu2[]="�ehirden ��k";
	YaziYaz(28,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
	YaziYaz(31,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
		do{
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72: 
						secim--;
						break;
					case 80: 
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){
					Sleep(250);Temizle();Sleep(250);
					git(5,5);printf("Demirci Ah ho�geldin! Z�rh�n Ve k�lc�n haz�r. Toplamda 100");Sleep(60);
					git(6,5);printf("alt�n ediyor ama sen 50 alt�na alabilirsin.");Sleep(60);
					git(8,5);printf(">Te�ekk�rler");Sleep(60);
					getch();
					player.GLD-=50;
					player.AITM=BasicSword;
					player.DITM=BasicArmor;		
					durum=F;	
					}else if(secim==2){	
					durum=F;	
					}
				}
			}
	if(durum==F)
		break;		
	Isaretle(secim+3);
	git(19,5);printf("Ailenle birlikte oldu�unu hat�rl�yorsun. onlar� korumaya �al���rken");
	git(22,5);printf("Doktoru �a��r�p en yak�nda Bo�a s���na��n� sordun.");
	git(25,5);printf("gitmeden bunlar� da al.(5 ila� ald�n)");Sleep(1000);			
		}while(durum);	
}
Temizle();
player.EXP+=20;
LvlUP();
Chapter1();								
}


void SehirMenuYazilar(){
	char bilgi[]="HUBC";
  	char baslik[]="A�a�� A��l";
  	char menu1[]="DEM�RC�YE G�T";
  	char menu2[]="SATI� YAP";
  	char menu3[]="HANA G�T";
  	char menu4[]="ENVANTER";
  	char menu5[]="�EH�RDEN �IK";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
  	YaziYaz(25,(kolon-4-strlen(menu3))/2,menu3,strlen(menu3));
  	YaziYaz(28,(kolon-4-strlen(menu4))/2,menu4,strlen(menu4));
  	YaziYaz(31,(kolon-4-strlen(menu5))/2,menu5,strlen(menu5));	
}
void SehirMenu(void x(),int max){
	int secim=1,i;	
struct Item x1[10];
for(i=0;i<10;i++){
int a;
a=rand()%2;
if(a==0){
strcpy(x1[i].AD,AttackItem[rand()%30]);	
x1[i].IATK=rand()%5+1+player.level;	
x1[i].IDEF=0;
x1[i].IVLU=rand()%20+21+x1[i].IATK+player.level;	
}else{
strcpy(x1[i].AD,DefansItem[rand()%10]);	
x1[i].IDEF=rand()%5+1+player.level;	
x1[i].IATK=0;
x1[i].IVLU=rand()%10+21+x1[i].IDEF+player.level;	
}
}
	durum=T;
	Temizle();
			x();
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;						
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						break;
				}
				secim=(secim==max)?1:secim;
				secim=(secim==0)?max-1:secim;	
			}else if(tus==13){
				if (secim==1){
				Temizle();	
				TuccarMenu(x1);
					durum=F;
				}else if(secim==2){
				Temizle();
				SatisMenu();	
					durum=F;
				}else if(secim==3){
				Temizle();
				HanMenu();
					durum=F;
				}else if(secim==4){
				Temizle();
				Envanter();
					durum=F;	
				}else if(secim==5){
				Temizle();
					durum=F;
				}
			}
		}
		if(durum==F)break;
		Isaretle(secim);
		Sleep(60);	
	}
	
}
void EnvanterYazdir(){
		int j,i;
	slot=0;
	for(j=0;j<10;j++){
		if(player.UITM[j].IVLU!=0)
	slot++;		
	}
	git(5,5);printf("%s'nin Envanteri:		Alt�n�n: %d ",player.AD,player.GLD);
	for(i=0;i<slot;i++){
	git(i+8,5);printf("  %s ",player.UITM[i].AD);git(i+8,25);printf("Hasar: %d ",player.UITM[i].IATK);git(i+8,40);printf("Defans: %d ",player.UITM[i].IDEF);git(i+8,55);printf("De�er: %d Alt�n",player.UITM[i].IVLU);	
	}
}
void CEnvanterYazdir(){
	int i;
	git(20,5);printf("T�ketilebilir E�yalar: ");
	for(i=0;i<5;i++){
		git(i+22,5);printf(" %s ",player.CONS[i].ADI);git(i+22,25);printf("(%d Adet)",player.CONS[i].ADT);
	}
}

void Equiped(){
	git(28,5);printf("Donan�lm�� E�yalar: ");
	git(30,5);printf(" %s ",player.AITM.AD);git(30,25);printf("Hasar�: %d",player.AITM.IATK);
	git(31,5);printf("% s ",player.DITM.AD);git(31,25);printf("Defans�: %d",player.DITM.IDEF);
}

void Envanter(){
Temizle();	
	Equiped();
	CEnvanterYazdir();
	EnvanterYazdir();
	int s=slot-1;	
	struct Item yedek;
	int i,secim=0;
	git(slot+8,5);printf("  �ehir Meyadan�na Geri D�n ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==slot+1)?0:secim;
				secim=(secim==-1)?slot:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // a�a�� y�n tu�u
						secim++; 
						git(secim+7,5);printf(" ");						
				secim=(secim==slot+1)?0:secim;
				secim=(secim==-1)?slot:secim;
						git(secim+8,5);printf(">");						
						break;
				}		
			}else if(tus==13){
				if(secim==slot)SehirMenu(SehirMenuYazilar,6);
				else{
				switch(secim){
					case 0:
								if(player.UITM[0].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[0];
								player.UITM[0]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[0];
								player.UITM[0]=yedek;				Envanter();									
								}		
					break;
					case 1:
								if(player.UITM[1].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[1];
								player.UITM[1]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[1];
								player.UITM[1]=yedek;				Envanter();									
								}	
					break;						
					case 2:
								if(player.UITM[2].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[2];
								player.UITM[2]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[2];
								player.UITM[2]=yedek;				Envanter();									
								}
					break;
					case 3:
								if(player.UITM[3].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[3];
								player.UITM[3]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[3];
								player.UITM[3]=yedek;				Envanter();									
								}
					break;							
					case 4:
								if(player.UITM[4].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[4];
								player.UITM[4]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[4];
								player.UITM[4]=yedek;				Envanter();									
								}	
					break;							
					case 5:
								if(player.UITM[5].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[5];
								player.UITM[5]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[5];
								player.UITM[5]=yedek;				Envanter();									
								}
					break;							
					case 6:
								if(player.UITM[6].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[6];
								player.UITM[6]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[6];
								player.UITM[6]=yedek;				Envanter();									
								}	
					break;
					case 7:
								if(player.UITM[7].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[7];
								player.UITM[7]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[7];
								player.UITM[7]=yedek;				Envanter();									
								}
					break;
					case 8:
								if(player.UITM[8].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[8];
								player.UITM[8]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[8];
								player.UITM[8]=yedek;				Envanter();									
								}
					break;
					case 9:
								if(player.UITM[9].IDEF==0){
								yedek=player.AITM;
								player.AITM=player.UITM[9];
								player.UITM[9]=yedek;				Envanter();	}
								else{
								yedek=player.DITM;
								player.DITM=player.UITM[9];
								player.UITM[9]=yedek;				Envanter();									
								}	
					break;																																																		
				}}
			}	
}
}
}



void SatisMenu(){
	Temizle();
	EnvanterYazdir();
	int s=slot-1;	
	struct Item yedek;
	int i,secim=0;
	git(slot+8,5);printf("  �ehir Meyadan�na Geri D�n ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==slot+1)?0:secim;
				secim=(secim==-1)?slot:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // a�a�� y�n tu�u
						secim++; 
						git(secim+7,5);printf(" ");						
				secim=(secim==slot+1)?0:secim;
				secim=(secim==-1)?slot:secim;
						git(secim+8,5);printf(">");						
						break;
				}		
			}else if(tus==13){
				if(secim==slot)SehirMenu(SehirMenuYazilar,6);
				else{
				switch(secim){
					case 0:
								player.GLD+=player.UITM[0].IVLU;
								yedek=player.UITM[0];
								player.UITM[0]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();			
					break;
					case 1:
								player.GLD+=player.UITM[1].IVLU;
								player.UITM[1]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;						
					case 2:
								player.GLD+=player.UITM[2].IVLU;
								player.UITM[2]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;
					case 3:
								player.GLD+=player.UITM[3].IVLU;
								player.UITM[3]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;							
					case 4:
								player.GLD+=player.UITM[4].IVLU;
								player.UITM[4]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;							
					case 5:
								player.GLD+=player.UITM[5].IVLU;
								player.UITM[5]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;							
					case 6:
								player.GLD+=player.UITM[6].IVLU;
								player.UITM[6]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;
					case 7:
								player.GLD+=player.UITM[7].IVLU;
								player.UITM[7]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;
					case 8:
								player.GLD+=player.UITM[8].IVLU;
								player.UITM[8]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;
					case 9:
								player.GLD+=player.UITM[9].IVLU;
								player.UITM[9]=player.UITM[s];
								player.UITM[s]=DefalutI;				SatisMenu();
					break;																																																		
				}}
			}	
}
}
}

void TuccarMenu(struct Item x[10]){
	int j;
	durum=T;
	slot=0;
	for(j=0;j<10;j++){
		if(player.UITM[j].IVLU!=0)
	slot++;		
	}
	if(slot>=10){
		Temizle();git(15,15);printf("DOLU ENVANTER!");Sleep(1000);SehirMenu(SehirMenuYazilar,6);
	}
	int i,secim=0;
	Temizle();
	git(5,5);printf("T�ccar�n Envanteri:		Alt�n�n: %d ",player.GLD);
	for(i=0;i<10;i++){
	git(i+8,5);printf("  %s  ",x[i].AD);git(i+8,25);printf("Hasar: %d ",x[i].IATK);git(i+8,40);printf("Defans: %d ",x[i].IDEF);git(i+8,55);printf("De�er: %d Alt�n",x[i].IVLU);	
	}
	git(18,5);printf("  �ehir Meyadan�na Geri D�n ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==11)?0:secim;
				secim=(secim==-1)?10:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						git(secim+7,5);printf(" ");						
				secim=(secim==11)?0:secim;
				secim=(secim==-1)?10:secim;
						git(secim+8,5);printf(">");						
						break;
				}		
			}else if(tus==13){
				switch(secim){
					case 0:
							durum=F;
							if(player.GLD>=x[0].IVLU){
								player.UITM[slot]=x[0];
								player.GLD-=x[0].IVLU;
												TuccarMenu(x);
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}					
					break;
					case 1:
							durum=F;
							if(player.GLD>=x[1].IVLU){
								player.UITM[slot]=x[1];
								player.GLD-=x[1].IVLU;
												TuccarMenu(x);
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}						
					break;
					case 2:
							durum=F;
							if(player.GLD>=x[2].IVLU){
								player.UITM[slot]=x[2];
								player.GLD-=x[2].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 3:
							durum=F;
							if(player.GLD>=x[3].IVLU){
								player.UITM[slot]=x[3];
								player.GLD-=x[3].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;							
					case 4:
							durum=F;
							if(player.GLD>=x[4].IVLU){
								player.UITM[slot]=x[4];
								player.GLD-=x[4].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;							
					case 5:
							durum=F;
							if(player.GLD>=x[5].IVLU){
								player.UITM[slot]=x[5];
								player.GLD-=x[5].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;							
					case 6:
							durum=F;
							if(player.GLD>=x[6].IVLU){
								player.UITM[slot]=x[6];
								player.GLD-=x[6].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 7:
							durum=F;
							if(player.GLD>=x[7].IVLU){
								player.UITM[slot]=x[7];
								player.GLD-=x[7].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 8:
							durum=F;
							if(player.GLD>=x[8].IVLU){
								player.UITM[slot]=x[8];
								player.GLD-=x[8].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 9:
							durum=F;
							if(player.GLD>=x[9].IVLU){
								player.UITM[slot]=x[9];
								player.GLD-=x[9].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 10:
						durum=F;
						SehirMenu(SehirMenuYazilar,6);
					break;																																																			
				}
			durum=F;	
			}
}
}
}


void HanMenu(){
	char bilgi[]="HUBC";
  	char baslik[]=" ";
  	char menu1[]="Hanc�ya Git";
  	char menu2[]="Doktorla Konu�";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
	git(22,50);printf("(15 Alt�n)");  
	int secim=1;
	durum=T;
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;	
			}else if(tus==13){
				if (secim==1){
					durum=F;
					HanciMenu();				
				}else if(secim==2){
					durum=F;
					Temizle();
		git(5,5);printf("%s : Yaralar�ma bak�m gerekli.",player.AD);getch();
		git(6,5);printf("Doktor: Belirli bir �cret kar��l���nda olur.(15 Alt�n)");
		if(player.GLD>=15){git(7,5);printf("��te Alt�n�n.(Can�n Tamamen doldu)");player.GLD-=15;player.CAN=player.MCAN;Sleep(1800);SehirMenu(SehirMenuYazilar,6);}
		else{git(7,5);printf("Yeterli Alt�n�m Yok");Sleep(1500);SehirMenu(SehirMenuYazilar,6);}			
				}
			}
		}
		if(durum==F)break;
		Isaretle(secim);
		Sleep(60);	
	}	  	
}

void HanciMenu(){
	durum=T;
	struct CItem x[5];
	strcpy(x[0].ADI,"�la�");	strcpy(x[1].ADI,"Elma");	strcpy(x[2].ADI,"Bandaj");  strcpy(x[3].ADI,"Portakal");	strcpy(x[4].ADI,"Mantar");
	x[0].VLU=20;x[0].HEL=5;x[0].ADT=1	;x[1].VLU=15;x[1].HEL=1;x[1].ADT=1;	x[2].VLU=19;x[2].HEL=4;x[2].ADT=1;	x[3].VLU=17;x[3].HEL=3;x[3].ADT=1;	x[4].VLU=16;x[4].HEL=2;x[4].ADT=1;
	int j;
	int i,secim=0;
	Temizle();
	git(5,5);printf("Hanc�n�n Envanteri:		Alt�n�n: %d ",player.GLD);
	git(6,5);printf("(Not: T�ketilebilir e�yalar� satamazs�n!)");
	for(i=0;i<5;i++){
	git(i+8,5);printf("  %s  ",x[i].ADI);git(i+8,25);printf("�yile�tirme: %d ",x[i].HEL);git(i+8,40);printf("De�er: %d Alt�n",x[i].VLU);
	}
	git(13,5);printf("  �ehir Meyadan�na Geri D�n ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukar� y�n tu�u
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==6)?0:secim;
				secim=(secim==-1)?5:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // a�a�� y�n tu�u
						secim++;
						git(secim+7,5);printf(" ");						
				secim=(secim==6)?0:secim;
				secim=(secim==-1)?5:secim;
						git(secim+8,5);printf(">");						
						break;
				}		
			}else if(tus==13){
				switch(secim){
					case 0:
							durum=F;
							if(player.GLD>=x[0].VLU){
								player.CONS[0].ADT++;
								player.GLD-=x[0].VLU;
												HanciMenu(x);
							}else{						
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												HanciMenu(x);	}					
					break;
					case 1:
							durum=F;
							if(player.GLD>=x[1].VLU){
								player.CONS[1].ADT++;
								player.GLD-=x[1].VLU;
												HanciMenu(x);
							}else{						
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												HanciMenu(x);	}						
					break;
					case 2:
							durum=F;
							if(player.GLD>=x[2].VLU){
								player.CONS[2].ADT++;
								player.GLD-=x[2].VLU;
												HanciMenu(x);								
							}else{						
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												HanciMenu(x);	}
					break;
					case 3:
							durum=F;
							if(player.GLD>=x[3].VLU){
								player.CONS[3].ADT++;
								player.GLD-=x[3].VLU;
												HanciMenu(x);								
							}else{						
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												HanciMenu(x);	}
					break;							
					case 4:
							durum=F;
							if(player.GLD>=x[4].VLU){
								player.CONS[4].ADT++;
								player.GLD-=x[4].VLU;
												HanciMenu(x);								
							}else{						
						git(22,22);printf("YETERS�Z ALTIN");Sleep(1000);
												HanciMenu(x);	}
					break;							
					case 5:
							durum=F;
						SehirMenu(SehirMenuYazilar,6);
					break;																																																			
				}
			durum=F;	
			}
}
}	
	
}
void sonMenu(){
	char menu1[]="Yap�mc�lar";
  	char menu2[]="Berra Sar�";
  	char menu3[]="Umut Enes Uzun";
  	char menu4[]="Hakan Tekir";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
  	YaziYaz(25,(kolon-4-strlen(menu3))/2,menu3,strlen(menu3));
  	YaziYaz(28,(kolon-4-strlen(menu4))/2,menu4,strlen(menu4));
  	getch();
}
void Chapter1(){
	Temizle();
	playerOnDeath=player;
	player.Location=C1;
	git(5,5);printf("Bo�a s���na��na do�ru yola ��kt�n ve uzun bir s�redir y�r�yorsun.");Sleep(60);
	git(6,5);printf("Kendine geceyi atlatacak kadar s���nacak bir yer bulman laz�m.");Sleep(60);
	
{	durum=T;
	char menu1[]="Etraf� Arast�r";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
Temizle();
	git(7,5);printf("Etraf� dola�t�ktan sonra s���n�labilecek bir ma�ara buldun. ");
	

{	durum=T;
	char menu1[]="  Ma�araya Gir  ";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);	
		Sleep(60);	
		}
}
Temizle();
	git(5,5);printf("Ma�araya usulca ilerledin.");Sleep(60);
	git(6,5);printf("��eri r�zgar�n girmedi�i bir b�l�m aramaya ba�lad�n.");Sleep(60);
	git(7,5);printf("Burada ya�ayan bir yerli oldu�unu fark ettin.");Sleep(60);
	git(8,5);printf("Yerliden ma�arada kalmak i�in izin istedin.");Sleep(60);
	git(9,5);printf("Yerli: Kalmak istiyorsan 10 alt�n isterim yoksa izinsiz girdi�in i�in");Sleep(60);
	git(10,5);printf("can�n� al�r�m");Sleep(60);
{	struct Enemy a;durum=T;int secim=1;char isim[7]="Yerli";
git(13,5);printf("  Sana alt�n vermeyece�im");Sleep(60);
git(14,5);printf("  Tamam ,kalmak i�in para �deyece�im (10 Alt�n)");Sleep(60);
durum=T;	
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72: 
						secim--;
						break;
					case 80: 
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){
					Temizle();
					durum=F;
					Savas(a,isim);	
					}else if(secim==2){
						if(player.GLD>=10){
					git(22,5);printf("10 altin �dedin");
					player.GLD-=10;
					Sleep(1000);
						}else{
							git(17,5);printf("Yeteri kadar paran yok. Sana sald�rmak �zere olan yerliye");Sleep(70);
							git(18,5);printf("kar�� kendini korumak zorundas�n!");Sleep(60);
							getch();
							Temizle();
							Savas(a,isim);
							 }
					durum=F;	
					}
				}
			}
		git(secim+11,5);printf(" ");	
		git(secim+12,5);printf(">");
		git(secim+13,5);printf(" ");	
		}
git(1+12,5);printf(" ");
git(2+12,5);printf(" ");		
}
LvlUP();
Temizle();
	git(5,5);printf("Yoluna devam ediyorusun.Geceyi orda ge�iriyorsun.");Sleep(60);
	git(6,5);printf("Sabah oluyor ve Bo�a s���na��na do�ru yola ��k�yorsun.");Sleep(60);
	git(7,5);printf("Karn�n ac�kt� ve susad�n.Yiyecek ve su bulmal�s�n.");Sleep(60);
	{	durum=T;
	char menu1[]="Yiyecek ve su ara";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
Temizle();
	git(5,5);printf("Etraf� ara�t�rd�ktan sonra bir su birikintisi ve elma a�ac� buldun.");Sleep(60);
	git(6,5);printf("Su i�tikten sonra elma toplamak i�in a�aca y�neldin.");Sleep(60);
	git(7,5);printf("Ve sana do�ru h�zla gelen bir kurt oldu��n� g�rd�n.");Sleep(600);
	getch();
	Temizle();
{
	struct Enemy kurt;char kurtad[5]="Kurt";
	Savas(kurt,kurtad);
}		
LvlUP();
Sleep(250);
Temizle();
	git(5,5);printf("Kurtun icab�na bakt�ntan sonra karn�n� elmalarla doyurdun.");Sleep(60);
	git(6,5);printf("Arkan� d�nd���nde az �nce kurtuldu�un kurtun e�iyle g�z g�ze geldin.");Sleep(600);
	getch();
	Temizle();
{
	struct Enemy kurt;char kurtad[5]="Kurt";
	Savas(kurt,kurtad);
}		
LvlUP();
Sleep(250);
Temizle();
	git(7,5);printf("Geri d�n�p elmalar�n biraz�n� da yan�na al�p y�r�meye ");Sleep(60);
	git(8,5);printf("devam ettin.�leride bir �ehir oldu�unu g�rd�n.");Sleep(60);
	player.CONS[1].ADT+=5;
{	durum=T;
	char menu1[]="�ehre Git";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);	
		Sleep(60);	
		}
}
	Temizle();
	SehirMenu(SehirMenuYazilar,6);
	Chapter2();
}
void Chapter2(){
	Temizle();
	player.Location=C2;
	playerOnDeath=player;
	git(11,5);printf("�ehirden ayr�lmaya haz�rlan�rken bir dilencinin seni");Sleep(60);
	git(12,5);printf("takip etti�ini fark ettin. Bir s�re sonra �n�ne");Sleep(60);
	git(13,5);printf("��kt� ve senden para istedi.");Sleep(60);
	git(15,6);printf("Alt�n verme");Sleep(60);
	git(16,6);printf("5 Alt�n ver");Sleep(60);
	durum=T; int secim=1;
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==224){
				tus=getch();
				switch(tus){
					case 72: 
						secim--;
						break;
					case 80: 
						secim++;
						break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){
					durum=F;
					Temizle();
					git(12,5);printf("Dilenciye para veremedin.");Sleep(70);
					git(13,5);printf("Dilenci s�ylenerek giderken sana bir ka��t par�as� uzatt�.");Sleep(60);	
					}else if(secim==2){
						if(player.GLD>=5){
							Temizle();
							git(12,5);printf("5 altin verdin"); Sleep(60);
							git(13,5);printf("Alt�n� verirken dilenci sana bir ka��t par�as� uzatt�."); Sleep(60);
							player.GLD-=5;
							Sleep(1000);
						}
						else{
							Temizle();
							git(12,5);printf("Yeteri kadar paran yok. Dilenciye para veremedin.");Sleep(70);
							git(13,5);printf("Dilenci s�ylenerek giderken sana bir ka��t par�as� uzatt�.");Sleep(60);
							getch();
							Temizle();
							 }
						durum=F;	
					}
				}
			}
		git(secim+13,5);printf(" ");	
		git(secim+14,5);printf(">");
		git(secim+15,5);printf(" ");	
		}
{	durum=T;
	char menu1[]="Notu oku";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
	Temizle();	
	git(11,5);printf("Ka��d� a��p okuyorsun. Ka��tta �unlar yaz�yor:");Sleep(60);
	git(12,5);printf("--------------------------------------------------------------------------");Sleep(60);
	git(13,5);printf("Hana git ve hanc�ya  \"G�ne� do�du�nda ve batt���nda orman bizi korur\" de.");Sleep(60);
	git(14,5);printf("Kolayl�kla gelmezsen zorla getiririz.");Sleep(60);
	git(15,5);printf("--------------------------------------------------------------------------");Sleep(60);//Yapabilirsem ka��t gibi g�r�ns�n diye bunu bir karenin i�ine yazaca��m
{	durum=T;
	char menu1[]="Hana git";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
	Temizle();
	git(11,5);printf("Hana gitmeye karar verdin.");Sleep(60);
	getch();
	paraYok:
	git(11,5);printf("Hanc�: �yi g�nler. Nas�l yard�mc� olabilirim.");Sleep(60);
	git(13,6);printf("G�ne� do�du�nda ve batt���nda orman bizi korur");Sleep(60);
	git(14,6);printf("Bira ver hanc�.");Sleep(60);
	secim=1; durum=T;
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
			tus=getch();
			switch(tus){
				case 72: 
					secim--;
					break;
				case 80: 
					secim++;
					break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){
					durum=F;
					Temizle();
					git(12,6);printf("G�ne� do�du�nda ve batt���nda orman bizi korur");Sleep(70);//D�zeltmeyi unutma
					git(13,6);printf("Notta yazan �eyleri okuduktan sonra hanc� seni gizli bir odaya g�t�rd�.");Sleep(60);	
					}else if(secim==2){
						if(player.GLD>=10){
							Temizle();
							git(12,6);printf("10 alt�n verdin"); Sleep(60);
							git(13,6);printf("��kini i�erken hanc�n�n birine seni i�aret etti�ini g�rd�n."); Sleep(60);
							player.GLD-=10;
							getch();
							git(12,6);printf("Bir s�re sonra bir grup elf masana oturdu.");Sleep(60);//Ba�ka bir �rk olabilir
							git(13,6);printf("Elflerden biri: Sana zorluk ��karma demi�tik.");Sleep(60);
							git(14,6);printf("��kini i�tikten sonra handaki gizli bir odaya gittiniz.");Sleep(60);
						}
						else{
							Temizle();
							git(12,6);printf("Yeterli paran yok.");Sleep(70);
							getch();
							Temizle();
							goto paraYok;
							}
						durum=F;	
					}
				}
			}
		git(secim+11,5);printf(" ");	
		git(secim+12,5);printf(">");
		git(secim+13,5);printf(" ");	
		}
	getch();
	Temizle();
	git(12,5);printf("Elflerin ba��: Merhaba. Ben Orman Gardiyanlar� grubunun ba��.");Sleep(60);
	git(13,5);printf("Bo�alar senin k�y�n gibi gibi bizim ormanlar�m�za de sald�rd�.");Sleep(60);
	git(14,5);printf("Bizde Bo�alara kar�� Orman Gardiyanlar�n� kurduk.");Sleep(60);
	git(15,5);printf("Seni Bo�alara kar�� birle�meye davet ediyorum.");Sleep(60);
{	durum=T;
	char menu1[]="Elflere kat�l";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
	Temizle();
	git(12,5);printf("Orman Gardiyanlar�na kat�ld�n.");Sleep(60);
	git(13,5);printf("Havan�n kararmak �zere oldu�unu fark ettin. Elflerden");Sleep(60);
	git(14,5);printf("bug�n kalmak i�in bir yer istedin.");Sleep(60);
{	durum=T;
	char menu1[]="Uyu";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
	Temizle();
	git(12,5);printf("Sabah oldu�unda Bo�alar�n bug�n kervanla silah ve z�rh");Sleep(60);
	git(13,5);printf("ta��yacaklar�n� ��rendin. Bunun i�in �ehir d���nda bir");Sleep(60);
	git(14,5);printf("pusu kurmaya karar verdiniz.");Sleep(60);
{	durum=T;
	char menu1[]="Pusuya git";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
	Temizle();
	git(12,5);printf("Bo�alar�n pusu noktas�na yakla�t���n� farkettiniz.");Sleep(60);
	git(13,5);printf("Atlar�n �n�n� kestiniz. Elflerden yay kullananlar kervan�"); Sleep(60);
	git(14,5);printf("ok ya�muruna tuttu. Sende k�l�� kullananlar ile beraber"); Sleep(60);
	git(15,5);printf("Bo�alara h�cum ettin. Kar��na Baltac� Bo�a ��kt�."); Sleep(60);
	getch();
	Temizle();
	struct Enemy a; char baltaci[13]="Baltac� Bo�a";
	Savas(a,baltaci);
	Temizle();
	git(12,5);printf("Baltac� Bo�a'y� �ld�rd�kten sonra ba�ka bir Bo�an�n");Sleep(60);
	git(13,5);printf("�st�ne ko�tu�unu fark ettin.");Sleep(60);
	getch();
	Temizle();
	struct Enemy b; char kilicli[13]="K�l��l� Bo�a";
	Savas(b,kilicli);
	Temizle();
	struct Item BogasSword, BogasArmor;
	BogasSword.IATK=5;							BogasArmor.IATK=0;	
	BogasSword.IDEF=0;							BogasArmor.IDEF=8;		
	BogasSword.IVLU=75;							BogasArmor.IVLU=75;		
	strcpy(BogasSword.AD,"Bo�a K�l�c�");		strcpy(BogasArmor.AD,"Bo�a Z�rh�");	
	slot=0;int i;
	for(i=0;i<10;i++){
		if(player.UITM[i].IVLU!=0)slot++;
	}
	if(slot<=9){
	player.UITM[slot]=BogasSword;slot++;}
	if(slot<=8){
	player.UITM[slot]=BogasArmor;}
	git(12,5);printf("Kervandan Bo�a K�l�c� ve Bo�a Z�rh� buldun.");Sleep(60);
	git(13,5);printf("Dinlenmek i�in �ehire d�nmeye karar verdiniz.");Sleep(60);
{	durum=T;
	char menu1[]="�ehire d�n";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
}
	SehirMenu(SehirMenuYazilar,6);
	Chapter3();
}
void Chapter3(){
	player.Location=C3;
	playerOnDeath=player;
	Temizle();
	git(12,5);printf("En sonunda bo�a s���na��na sald�rmak �zere �ehirden ayr�ld�n�z.");Sleep(60);
	git(13,5);printf("Bir ma�aran�n �n�nde durdunuz. Bo�a'lar�n Ma�aran�n i�ine girdi�ini");Sleep(60);
	git(14,5);printf("farkettiniz. Ma�aran�n ba��nda iki tane n�bet�i oldu�unu g�rd�n�z.");Sleep(60);
	{	durum=T;
	char menu1[]="N�bet�ilereSald�r";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
	}
	Temizle();
	struct Enemy a; char enemy[13]="N�betci Bo�a";
	Savas(a,enemy);
	LvlUP();
	Temizle();
	git(12,5);printf("�teki n�betciyi Elfler halleti.");Sleep(60);
	{	durum=T;
	char menu1[]="Ma�araya Gir";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
	}
	git(13,5);printf("Me�aleler ile ayd�nlat�lm�� bir koridorda y�r�yorsunuz.");Sleep(60);
	git(14,5);printf("�lerlerken tuza�a yakal�n�yorsun. Aya��na b�y�k bir ta� d���yor.");Sleep(60);
	player.CAN-=5;
	Death();
	git(15,5);printf("5 can�n azald�. Bundan sonra daha dikkatli ilerlemeye ba�lad�n.");Sleep(60);
	getch();
	Temizle();
	git(12,5);printf("Bir zindan buldunuz. Zindan�n ba��nda bir n�bet�i g�rd�n�z. Tam n�bet�i");Sleep(60);
	git(13,5);printf("sizi fark etti�i an kafas�na ok yedi ve yere y���ld�.");Sleep(60);
	{	durum=T;
	char menu1[]="Zindana Gir";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
	}
	Temizle();
	git(12,5);printf("H�creleri tek tek aramaya ba�lad�n. Fakat aileni bulamad�n.");Sleep(60);
	git(13,5);printf("Zindandan ��kt�n�z. Koridorda ilerlemeye devam ettiniz.");Sleep(60);
	git(14,5);printf("S���na��n yemekhanesini buldunuz. ��eridekiler sizi fark etmedi.");Sleep(60);	
	git(15,5);printf("Elflerin lideri: ��eride �ok fazla Bo�a var. Plan yapmal�y�z.");Sleep(60);
	git(17,5);printf("Plan yapmal�y�z.");Sleep(60);
	git(18,5);printf("Bekleyecek vakit yok hemen sald�rmal�y�z.");Sleep(60);	
	short secim=1; durum=T;
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
			tus=getch();
			switch(tus){
				case 72: 
					secim--;
					break;
				case 80: 
					secim++;
					break;
				}
				secim=(secim==3)?1:secim;
				secim=(secim==0)?2:secim;
				}
				else if(tus==13){
					if(secim==1){//plan
						durum=F;
						git(16,5);printf("Plan yapmal�y�z.");Sleep(60);
						git(17,4);printf(" ��eridekileri zehirlemeye karar verdiniz.");Sleep(60);
						git(18,5);printf("A��� fark etmeden �orba kazan�n�n i�ine zehir att�n�z.");Sleep(60);
						git(19,5);printf("Bo�alar yemek yedikten bir s�re sonra i�erideki herkes bay�ld�.");Sleep(60);
						getch();
					}
					else if(secim==2){//saldiri
						durum=F;
						git(16,5);printf("Bekleyecek vakit yok hemen sald�rmal�y�z.  ");Sleep(60);
						git(17,5);printf("Sald�rmaya karar verdiniz.  ");Sleep(60);
						git(18,4);printf(" Elflerin lideri sana bir iksir verdi.         ");Sleep(60);
						player.MCAN+=10;
						player.CAN=player.MCAN;
						player.ATK+=2;
						player.DEF+=2;
						git(19,4);printf(" �ksiri i�ince kendini daha cesur hissettin. Yemekhanenin kap�s�n�");Sleep(60);
						git(20,5);printf("a�t�n, ba��rarak i�eri girdin ve �n�ne gelene sald�rmaya ba�lad�n.");Sleep(60);
						getch();
						Temizle();
						strcpy(enemy,"Sinirli Bo�a");
						Savas(a,enemy);
						Temizle();
						strcpy(enemy,"A�c� Bo�a");
						Savas(a,enemy);
						Temizle();
						strcpy(enemy,"A� Bo�a");
						Savas(a,enemy);
						Temizle();
					}
				}
			}
		if(durum==F)break;	
		git(secim+15,4);printf(" ");	
		git(secim+16,4);printf(">");
		git(secim+17,4);printf(" ");	
		}
	Temizle();
	git(12,5);printf("Herkesi hallettikten sonra ilerlemeye devam ettiniz.");Sleep(60);
	git(13,5);printf("S���na��n erzak odas�n� buldunuz. ��eride z�rhl� bir");Sleep(60);
	git(14,5);printf("bo�a g�rd�n�z. Z�rhtan zor y�r�yen Bo�a sana bakt� ve");Sleep(60);
	git(15,5);printf("Tank Bo�a: Seni d�elloya davet ediyorum.");Sleep(60);
	{	durum=T;
	char menu1[]="D�ello yap";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
	}
	struct Enemy tank;
	strcpy(tank.AD,"Tank Bo�a");
	tank.ATK=2;
	tank.CAN=50;
	tank.DEF=20;
	Temizle();
	SavasMenu(tank);
	Temizle();
	LvlUP();
	Temizle();
	git(12,5);printf("�lerlemeye devam ettiniz. Koridorun sonuna geldiniz.");Sleep(60);
	git(13,5);printf("Aileni bulamad�n. Umutsuzlu�a kap�l�p duvara vurdun.");Sleep(60);
	git(14,5);printf("Birden gizli bir ge�it a��ld�.");Sleep(60);
	{	durum=T;
	char menu1[]="Ge�ite Gir";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
	}
	Temizle();
	git(12,5);printf("�lerlerken buran�n bir zindan oldu�unu anlad�n.");Sleep(60);
	git(13,5);printf("Zindan�n sonunda Bo�alar�n Ba��n� g�rd�n. Sana bakt� ve");Sleep(60);
	git(14,5);printf("Bo�alar�n Ba��: Sen b�t�n planlar�m� mahvettin. Bunun bedelini �deyeceksin");Sleep(60);
	{	durum=T;
	char menu1[]="Sald�r";
	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
		while(durum){
			if(kbhit()){
				tus=getch();
				if(tus==13){
					durum=F;				
				}
			}
		Isaretle(1);
		Sleep(60);	
		}
	}
	Temizle();
	struct Enemy lider;
	strcpy(lider.AD,"Bo�alar�n Ba��");
	lider.ATK=15;
	lider.CAN=40;
	lider.DEF=10;
	SavasMenu(lider);
	git(12,5);printf("Bo�alar�n Ba��n� �ld�rd�kten sonra aileni aramaya ba�lad�n");Sleep(60);
	git(13,5);printf("Biraz ilerledikten sonra aileni buldun. Sonunda aileni kurtarm��t�n.");Sleep(60);
	git(14,5);printf("Beraber �ehire d�nd�n�z.");Sleep(60);
	Temizle();
	sonMenu();
}

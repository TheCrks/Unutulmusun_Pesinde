#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#define developerMode 0


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



char *AttackItem[30]={"Basit Kýlýç","Basit Balta","Basit Mýzýrak","Ýyi Kýlýç","Ýyi Balta","Ýyi Mýzýrak","Ork Kýlýçý","Ork Baltasý","Ork Mýzýraðý","Elf Kýlýcý","Elf Baltasý","Elf Mýzýraðý","Cüce Kýlýcý","Cüce Baltasý","Cüce Mýzýraðý","Büyük Kýlýc","Büyük Balta","Büyük Mýzýrak","Küçük Kýlýc","Küçük Balta","Küçük Mýzýrak","Çelik Kýlýc","Çelik Balta","Çelik Mýzýrak","Kýlýc","Balta","Mýzýrak","Özel Kýlýc","Özel Balta","Özel Mýzýrak",};
char *DefansItem[10]={"Basit Zýrh","Ýyi Zýrh","Çelik Zýrh","Ork Zýrhý","Elf Zýrhý","Cüce iþi Zýrh","Kalýn Zýrh","Ýnce Zýrh","Taþ Zýrh","Zincir Zýrh"};


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
	strcpy(player.CONS[0].ADI,"Ýlaç");	strcpy(player.CONS[1].ADI,"Elma");	strcpy(player.CONS[2].ADI,"Bandaj");  strcpy(player.CONS[3].ADI,"Portakal");	strcpy(player.CONS[4].ADI,"Mantar");
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
	satir = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;  // Concole ekran yüksekliði alýnýyor  63
	kolon = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Console ekran geniþliði alýnýyor 237
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
  	char baslik[]="Unutulmuþun Peþinde";
  	char menu1[]="B A Þ L A";
  	char menu2[]="Ç I K I Þ";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
}
void Isaretle(short sec){
	int i, konum[]={19,22,25,28,31,34,37,40};
	for(i=0;i<sizeof(konum)/sizeof(int);i++){
		if((i+1)==sec){
			git(konum[i],(kolon-4-strlen("B A Þ L A"))/2-7);
			printf("%c%c%c",16,16,16);
			git(konum[i],(kolon-4-strlen("B A Þ L A"))/2+13);
			printf("%c%c%c",17,17,17);
		}else{
			git(konum[i],(kolon-4-strlen("B A Þ L A"))/2-7);
			printf("   ");
			git(konum[i],(kolon-4-strlen("B A Þ L A"))/2+13);
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
					case 72:   //yukarý yön tuþu
						secim--;
						break;
					case 80:  // aþaðý yön tuþu
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
  	char baslik[]="S I N I F	S E Ç";
  	char menu1[]="SAVAÞÇI";
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
  	char baslik[]="I R K	S E Ç";
  	char menu1[]="ÝNSAN";
  	char menu2[]="ORK";
  	char menu3[]="ELF";
  	char menu4[]="CÜCE";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
  	YaziYaz(25,(kolon-4-strlen(menu3))/2,menu3,strlen(menu3));
  	YaziYaz(28,(kolon-4-strlen(menu4))/2,menu4,strlen(menu4));
	
}
void CreationYazilar3(){
	char bilgi[]="HUBC";
  	char baslik[]="AÝLEN";
  	char menu1[]="ASKERLERDÝ";
  	char menu2[]="DEMÝRCÝLERDÝ";
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
					case 72:   //yukarý yön tuþu
						secim--;
						break;
					case 80:  // aþaðý yön tuþu
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
					case 72:   //yukarý yön tuþu
						secim--;
						break;
					case 80:  // aþaðý yön tuþu
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
					case 72:   //yukarý yön tuþu
						secim--;
						break;
					case 80:  // aþaðý yön tuþu
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
	printf("Ý S M Ý N");
	Isaretle(3);
	git(25,35);
	scanf("%s",player.AD);
	Temizle();
	EkranTaslak();
	git(5,5);
	printf("%s'in Deðerleri:",player.AD);
	git(7,5);
	printf("Güc:%d",player.ATK);
	git(8,5);
	printf("Defans:%d",player.DEF);
	git(9,5);
	printf("Altýn:%d",player.GLD);
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
	git(20,6);printf("Çýkýþ");
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
						git(22,5);printf("Sehir Menu açýlýyor");Sleep(60);
						SehirMenu(SehirMenuYazilar,6);
					}
					else if(secim==6){
						Temizle();
						git(22,5);printf("Han Menu açýlýyor");Sleep(60);
						HanciMenu();
					}
					else if(secim==7){
						struct Enemy a; char isim[7]="Hacker";
						Temizle();
						git(22,5);printf("Savaþ açýlýyor");Sleep(60);
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
  	char menu1[]="Saldýr";
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
	git(5,5);printf("Tüketilebilir Eþyalar: ");
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
					case 72:   //yukarý yön tuþu
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==5)?0:secim;
				secim=(secim==-1)?4:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // aþaðý yön tuþu
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
							git(15,5);printf("%d kadar iyileþtin",player.CONS[0].HEL);Sleep(1000);}							
						else{
							git(15,5);printf("Yetersiz Eþya");Sleep(1000);
								}	
							durum=F;	
					break;
					case 1:
						if(player.CONS[1].ADT>=1){
							player.CONS[1].ADT-=1;
							player.CAN+=player.CONS[1].HEL;
							git(15,5);printf("%d kadar iyileþtin",player.CONS[1].HEL);Sleep(1000);}							
						else{
							git(15,5);printf("Yetersiz Eþya");Sleep(1000);
								}	
							durum=F;
					break;						
					case 2:
						if(player.CONS[2].ADT>=1){
							player.CONS[2].ADT-=1;
							player.CAN+=player.CONS[2].HEL;
							git(15,5);printf("%d kadar iyileþtin",player.CONS[2].HEL);Sleep(1000);}							
						else{
							git(15,5);printf("Yetersiz Eþya");Sleep(1000);
								}	
							durum=F;
					break;
					case 3:
						if(player.CONS[3].ADT>=1){
							player.CONS[3].ADT-=1;
							player.CAN+=player.CONS[3].HEL;
							git(15,5);printf("%d kadar iyileþtin",player.CONS[3].HEL);Sleep(1000);}
						else{
							git(15,5);printf("Yetersiz Eþya");Sleep(1000);
								}	
							durum=F;
					break;							
					case 4:
						if(player.CONS[4].ADT>=1){
							player.CONS[4].ADT-=1;
							player.CAN+=player.CONS[4].HEL;
							git(15,5);printf("%d kadar iyileþtin",player.CONS[4].HEL);Sleep(1000);	}						
						else{
							git(15,5);printf("Yetersiz Eþya");Sleep(1000);
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
					case 72:   //yukarý yön tuþu
						secim--;
						break;
					case 80:  // aþaðý yön tuþu
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
					git(15,5);printf("Düþman Saldirdi            ");Sleep(1000);
					player.CAN=player.CAN-eatk;
					git(15,5);printf("%d hasar aldýn             ",eatk);Sleep(1000);
					player.CAN=(player.CAN<0)?0:player.CAN;	
					Death();				
				}else if(secim==2){
					HealMenu();
					player.CAN=player.CAN-eatk;
					if(player.CAN>player.MCAN)player.CAN=player.MCAN;
					git(15,5);printf("Düþman Saldirdi             ");Sleep(1000);					
					git(15,5);printf("%d hasar aldýn.             ",eatk);Sleep(1000);
					player.CAN=(player.CAN<0)?0:player.CAN;	
					Death();}
				}
			}
		
		Isaretle(secim);
		git(5,5);printf("%s'in Caný: %d  ",player.AD,player.CAN);git(5,40);printf("%s'in Caný: %d  ",enemy.AD,enemy.CAN);
		git(6,5);printf("%s'in Gücü: %d  ",player.AD,player.ATK);git(6,40);printf("%s'in Gücü: %d  ",enemy.AD,enemy.ATK);
		git(7,5);printf("%s'in Defansý: %d  ",player.AD,player.DEF);git(7,40);printf("%s'in Defansý: %d  ",enemy.AD,enemy.DEF);
				SavasYazilar();
		Sleep(60);
	}
	TP=rand()%5+enemy.ATK-1;
	AL=rand()%20+15+enemy.ATK-1;
	player.EXP+=TP;
	player.GLD+=AL;
	Temizle();
	git(10,25);printf("K A Z A N D I N !");
	git(20,5);printf("%d TP ve %d Altýn kazanadin",TP,AL);
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
	git(22,5);printf(" %s Den bir %s buldun.(Eþyalarý Þehirde Donanabilirsin.)",enemy.AD,Loot.AD);	
	}}}
	getch();
}

void LvlUP(){
	if(player.EXP>=20 && player.level<2){
	Temizle();
	git(5,25);printf("S E V Ý Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("Güc defeans ve max canýn arrtý ve tamamen iyileþtin");Sleep(60);
	git(8,5);printf("Yeni Deðerlerin:");
	git(10,5);printf("Güc: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Altýn: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecrübe puaný: %d",player.EXP);
	git(16,5);printf("Saldýrý Eþyan: ");
	git(17,5);printf("%s        Hasarý: %d       Deðeri: %d Altýn",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma Eþyan: ");	
	git(19,5);printf("%s        Defansý: %d       Deðeri: %d Altýn",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();		
	}
	else if(player.EXP>=40 && player.level<3){
	Temizle();
	git(5,25);printf("S E V Ý Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("Güc defeans ve max canýn arrtý ve tamamen iyileþtin");Sleep(60);
	git(8,5);printf("Yeni Deðerlerin:");
	git(10,5);printf("Güc: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Altýn: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecrübe puaný: %d",player.EXP);
	git(16,5);printf("Saldýrý Eþyan: ");
	git(17,5);printf("%s        Hasarý: %d       Deðeri: %d Altýn",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma Eþyan: ");	
	git(19,5);printf("%s        Defansý: %d       Deðeri: %d Altýn",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();		
	}
	else if(player.EXP>=60 && player.level<4){
	Temizle();
	git(5,25);printf("S E V Ý Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("Güc defeans ve max canýn arrtý ve tamamen iyileþtin");Sleep(60);
	git(8,5);printf("Yeni Deðerlerin:");
	git(10,5);printf("Güc: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Altýn: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecrübe puaný: %d",player.EXP);
	git(16,5);printf("Saldýrý Eþyan: ");
	git(17,5);printf("%s        Hasarý: %d       Deðeri: %d Altýn",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma Eþyan: ");	
	git(19,5);printf("%s        Defansý: %d       Deðeri: %d Altýn",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();;	
	}
	else if(player.EXP>=80 && player.level<5){
	Temizle();
	git(5,25);printf("S E V Ý Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("Güc defeans ve max canýn arrtý ve tamamen iyileþtin");Sleep(60);
	git(8,5);printf("Yeni Deðerlerin:");
	git(10,5);printf("Güc: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Altýn: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecrübe puaný: %d",player.EXP);
	git(16,5);printf("Saldýrý Eþyan: ");
	git(17,5);printf("%s        Hasarý: %d       Deðeri: %d Altýn",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma Eþyan: ");	
	git(19,5);printf("%s        Defansý: %d       Deðeri: %d Altýn",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();
	}
	else if(player.EXP>=100 && player.level<6){
	Temizle();
	git(5,25);printf("S E V Ý Y E	A T L A D I N !");Sleep(60);
	player.ATK+=1;
	player.DEF+=1;
	player.level+=1;
	player.MCAN+=3;
	player.CAN=player.MCAN;
	git(6,5);printf("Güc defeans ve max canýn arrtý ve tamamen iyileþtin");Sleep(60);
	git(8,5);printf("Yeni Deðerlerin:");
	git(10,5);printf("Güc: %d",player.ATK);
	git(11,5);printf("Defans: %d",player.DEF);
	git(12,5);printf("Can: %d",player.MCAN);
	git(13,5);printf("Altýn: %d",player.GLD);
	git(14,5);printf("Seviye: %d",player.level);
	git(15,5);printf("Tecrübe puaný: %d",player.EXP);
	git(16,5);printf("Saldýrý Eþyan: ");
	git(17,5);printf("%s        Hasarý: %d       Deðeri: %d Altýn",player.AITM.AD,player.AITM.IATK,player.AITM.IVLU);
	git(18,5);printf("Savunma Eþyan: ");	
	git(19,5);printf("%s        Defansý: %d       Deðeri: %d Altýn",player.DITM.AD,player.DITM.IDEF,player.DITM.IVLU);						
	getch();
	}
}
void Death(){
	if(player.CAN==0 && player.Location==0){
	Temizle();
	durum=T;
	char menu1[]="Tekrar Dene";
	char baslik[]="Ö L D Ü N";
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
	char baslik[]="Ö L D Ü N";
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
	char baslik[]="Ö L D Ü N";
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
	char baslik[]="Ö L D Ü N";
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
	git(5,5);printf("Gözlerini yavaþça açýyorusun.Bir yatakta uyandýn. Ancak buraya nasýl ");Sleep(60);
	git(6,5);printf("geldiðin hakkýnda hiç bir fikrin yok.Yavaþça kalkýyorsun. Yaralarýn ");Sleep(60);
	git(7,5);printf("olduðunu fark ediyorsun. Biraz zorlanarak da olsa ayaða kalkýyorsun.");Sleep(60);
{	durum=T;
	char menu1[]="Etrafý Arastýr";
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
	git(8,5);printf("Etrafa Bakindin. Yattiðin Yerin Yakininda bir not buldun.");
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
	git(8,5);printf("Seni yaralý halde ana yolun üstünde buldum. Ben yakýndaki þehirdeki");Sleep(60);
	git(9,5);printf("bir tüccarým. Uzun zamandýr uyuyorsun. Ben þehre gitmek zorundayým.");Sleep(60);
	git(10,5);printf("Lütfen þehre gelmeye çalýþma yollarda haydutlar tuzak kuruyor.");Sleep(60);
	git(11,5);printf("Eðer nerden gitmen gerektiði bilmiyorsan kesin bir tuzaða düþersin.");Sleep(60);
	git(12,5);printf("Üstelik bir maðaradan da geçmen gerekli. Ben gelene kadar bekle.");Sleep(60);
{	durum=T;
	char menu1[]=">>>   Þehre Doðru Yola Çýk   <<<";
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
	git(8,5);printf("Yolda etrafa dikkatlice bakarak yürüken birinin elinde kýlýçla sana");Sleep(60);
	git(9,5);printf("doðru koþtuðunu farkediyorsun. Saldýracak gibi duruyor. Yaklaþma diye");Sleep(60);
	git(10,5);printf("baðrýyorsun. Adam biraz daha koþup duruyor.");Sleep(60);
	git(11,5);printf("Haydut: Ya paraný verirsin yada zorla alýrým");Sleep(60);
{	struct Enemy a;durum=T;int secim=1;char isim[7]="Haydut";
git(13,5);printf("  Sana tek kuruþ vermeyeceðim");Sleep(60);
git(14,5);printf("  Tamam geçiþ için para ödeyeceðim (75 Altýn)");Sleep(60);
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
					git(22,5);printf("75 altin ödedin");
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
	git(6,5);printf("baþka bir haydut önünü kesiyor.");Sleep(60);	
{	struct Enemy a;durum=T;int secim=1;char isim[7]="Haydut";
git(13,5);printf("  Sana tek kuruþ vermeyeceðim");Sleep(60);
git(14,5);printf("  Tamam geçiþ için para ödeyeceðim (75 Altýn)");Sleep(60);
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
					git(22,5);printf("75 altin ödedin");
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
	git(6,5);printf("ilerledikten sonra bir maðara giriþine rastlýyorsun. Bu notta bahsedilen");Sleep(60);
	git(7,5);printf("Maðara olmalý diye düþünüyorsun. Biraz bir aðaç gölgesinde dinlektikten");Sleep(60);
	git(8,5);printf("sonra maðaranýn içine doðru ilerliyorsun. Maðarada yürüken adýmlarýna");Sleep(60);
	git(9,5);printf("dikkat ederek, olabilidiðince az ses çýkararak yürüyorsun. Ancak bir");Sleep(60);
	git(10,5);printf("kurt seni fark ediyor. Oldukça aç görünen kurt sana doðru koþuyor");Sleep(600);
	getch();
	Temizle();
{
	struct Enemy kurt;char kurtad[5]="Kurt";
	Savas(kurt,kurtad);
}		
LvlUP();
Sleep(250);
Temizle();
	git(5,5);printf("Kurtun icabýna baktýntan sonra ilerde bir ýþýk görüyorsun. Iþýða doðru");Sleep(60);
	git(6,5);printf("yaklaþtýkça sesler duymaya baþlýyorsun. Iþýðýn maðaranýn çýkýþý olduðunu");Sleep(60);
	git(7,5);printf("anlaman uzun sürmüyor. Maðaradan çýkýnca ilerdeki þehri görüyorsun");Sleep(60);
{	durum=T;
	char menu1[]="Þehre Git";
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
	git(5,5);printf("Çok geçmeden þehre varýyorsun. Þehrin sokakalrýnda dolaþmaya baþlýyorsun.");Sleep(60);
	git(6,5);printf("Kalabalýk bir sokakata gezerken birisi sana sesleniyor. Sesin ne taraftan");Sleep(60);
	git(7,5);printf("geldiðini anlamaya çalýþýrken biri seni kolundan tutup demirci dükkanýna");Sleep(60);
	git(8,5);printf("götürüyor. Biraz sinirli  bir tonla konuþmaya baþlýyor.");Sleep(60);
	git(10,5);printf("Demirci: Sana beni beklemni söylememiþ miydim? Neden beni dinlemiyorsun?");Sleep(60);	
{	int secim=1;
	git(13,5);printf(" Beni sen mi kurtardýn?");
	git(14,5);printf(" Beni tanýyor musun?");
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
						git(11,5);printf("Beni sen mi kurtardýn?");Sleep(500);
						git(13,5);printf("                        ");
						git(14,5);printf("                        ");
					durum=F;	
					}else if(secim==2){
						git(11,5);printf("Beni tanýyor musun?");Sleep(500);
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
	Sleep(500);git(12,5);printf("Demrici: Notumu okumadýn mý. Seni yolda buldum. Yaralýydýn. Hatta");Sleep(60);
	git(13,5);printf("seni ölü sanýp orda býracaktým. Ancak sayýklamaya baþladýn. Boðalar");Sleep(60);
	git(14,5);printf("gibi bir þey diyordun. bunun sana boðalar mý yaptý?");Sleep(60);
{	int secim=1;
	git(16,5);printf(" Boðalar?");
	git(17,5);printf(" Hatýrlayamýyorum.");
	git(18,5);printf(" Buralarda vahþi boða mý var?");
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
						git(15,5);printf("Boðalar?");
						git(16,5);printf("                              ");Sleep(500);
						git(17,5);printf("                              ");
						git(18,5);printf("                              ");
					durum=F;	
					}else if(secim==2){
						git(15,5);printf("Hatýrlayamýyorum.");Sleep(500);
						git(16,5);printf("                              ");
						git(17,5);printf("                              ");
						git(18,5);printf("                              ");
					durum=F;	
					}else if(secim==3){
						git(15,5);printf("Buralarda vahþi boða mý var?");Sleep(500);
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
	git(16,5);printf("Boðalar buralarýn en bilinen haydut grubudur. Bu þehride bir doktor var.");Sleep(60);
	git(17,5);printf("Onu bul. Belki hatýrlamana yardýmcý olabilir. Doktordan sonra bana tekrar");Sleep(60);
	git(18,5);printf("bir uðra. Senin için kýlýç ve zýrh yapacaðým. Belki sana özel bir indirim");Sleep(60);
	git(19,5);printf("bile yaparým. Doktor muhtemlen handadýr.");Sleep(60);
	
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
	git(19,5);printf("bile yaparým. Doktor muhtemlen handadýr.");Sleep(1000);				
		}
}
	Sleep(250);
	Temizle();
	git(5,5);printf("Haný bulup içeri giriyorsun. Etrafa bir göz gezdirip hancýya doðru");Sleep(60);
	git(6,5);printf("ilerliyorsun. Hancýdan içecek isteyip dokturu soruyorsun. hancý kafasýyla");Sleep(60);
	git(7,5);printf("Bir adamý iþaret ediyor. içeceðini içip doktora gidiyorsun. Demircinin");Sleep(60);
	git(8,5);printf("söylediklerini ona anlatýyorsun. Doktor arkasý dönük \"Yinebir pusu vakasý\"");Sleep(60);
	git(9,5);printf("diyor ve dönüyor. Doktorun suratýnda bir þaþkýnlýk ifadesi görüyorsun.");Sleep(60);
	git(10,5);printf("Doktor: %s bu sen misin? Ne oldu sana? Gel de bana herþeyi anlat.",player.AD);Sleep(60);
	git(11,5);printf("(bir süre sonra)");Sleep(60);
	git(12,5);printf("Doktor: Ah pardon hatýrlamýyordun deðil mi? Þu ilaçlarý içip biraz");Sleep(60);
	git(13,5);printf("dinlenirsen yavaþ yavaþ hatýrlamaya baþlarsýn.");Sleep(60);
{	durum=T;
	char menu1[]="Ýlaçlarý iç";
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
	git(16,5);printf("Ýlaçlarýný içip uykuya dalýyorsun. Uyandýðýnda her hafta doktora erzak");Sleep(60);
	git(17,5);printf("ve ilaç getirip yardým ettiðni hatýrlýyorsun. onun çocukluk arkadaþýn");Sleep(60);
	git(18,5);printf("olduðu aklýna geliyor. Bir süre sonra saldýrýldýðýn günü hatýrlýyorsun.");Sleep(60);
	git(19,5);printf("Ailenle birlikte oldupunu hatýrlýyorsun. onlarý korumaya çalýþýrken");Sleep(60);
	git(20,5);printf("Aðýr yaralanmýþtýn. neyseki seni ölü sanýp yolda atmýþlardý. Ancak");Sleep(60);
	git(21,5);printf("ailen hala onlarýn elindeydi. en kýsa zamanda yola çýkman gerekiyordu.");Sleep(60);
	git(22,5);printf("Doktoru çaðýrýp en yakýnda Boða sýðýnaðýný sordun.");Sleep(60);
	git(23,5);printf("Doktor: Þehrin biraz kuzeyinde ama orasý iyi korunur. güneyde küçük");Sleep(60);
	git(24,5);printf("bir erzak depolarý var orda aradýðn cevaplarý bulabilirsin belki");Sleep(60);
	git(25,5);printf("gitmeden bunlarý da al.(5 ilaç aldýn)");Sleep(60);
	player.CONS[0].ADT+=5;
{
struct Item BasicSword, BasicArmor;
BasicSword.IATK=2;							BasicArmor.IATK=0;	
BasicSword.IDEF=0;							BasicArmor.IDEF=5;		
BasicSword.IVLU=25;							BasicArmor.IVLU=25;		
strcpy(BasicSword.AD,"Basit Kýlýc");		strcpy(BasicArmor.AD,"Basit Zýrh");	
	int secim=1;durum=T;
	char menu1[]="Demirciye Git";
	char menu2[]="Þehirden Çýk";
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
					git(5,5);printf("Demirci Ah hoþgeldin! Zýrhýn Ve kýlcýn hazýr. Toplamda 100");Sleep(60);
					git(6,5);printf("altýn ediyor ama sen 50 altýna alabilirsin.");Sleep(60);
					git(8,5);printf(">Teþekkürler");Sleep(60);
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
	git(19,5);printf("Ailenle birlikte olduðunu hatýrlýyorsun. onlarý korumaya çalýþýrken");
	git(22,5);printf("Doktoru çaðýrýp en yakýnda Boða sýðýnaðýný sordun.");
	git(25,5);printf("gitmeden bunlarý da al.(5 ilaç aldýn)");Sleep(1000);			
		}while(durum);	
}
Temizle();
player.EXP+=20;
LvlUP();
Chapter1();								
}


void SehirMenuYazilar(){
	char bilgi[]="HUBC";
  	char baslik[]="Aþaðý Aðýl";
  	char menu1[]="DEMÝRCÝYE GÝT";
  	char menu2[]="SATIÞ YAP";
  	char menu3[]="HANA GÝT";
  	char menu4[]="ENVANTER";
  	char menu5[]="ÞEHÝRDEN ÇIK";

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
					case 72:   //yukarý yön tuþu
						secim--;						
						break;
					case 80:  // aþaðý yön tuþu
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
	git(5,5);printf("%s'nin Envanteri:		Altýnýn: %d ",player.AD,player.GLD);
	for(i=0;i<slot;i++){
	git(i+8,5);printf("  %s ",player.UITM[i].AD);git(i+8,25);printf("Hasar: %d ",player.UITM[i].IATK);git(i+8,40);printf("Defans: %d ",player.UITM[i].IDEF);git(i+8,55);printf("Deðer: %d Altýn",player.UITM[i].IVLU);	
	}
}
void CEnvanterYazdir(){
	int i;
	git(20,5);printf("Tüketilebilir Eþyalar: ");
	for(i=0;i<5;i++){
		git(i+22,5);printf(" %s ",player.CONS[i].ADI);git(i+22,25);printf("(%d Adet)",player.CONS[i].ADT);
	}
}

void Equiped(){
	git(28,5);printf("Donanýlmýþ Eþyalar: ");
	git(30,5);printf(" %s ",player.AITM.AD);git(30,25);printf("Hasarý: %d",player.AITM.IATK);
	git(31,5);printf("% s ",player.DITM.AD);git(31,25);printf("Defansý: %d",player.DITM.IDEF);
}

void Envanter(){
Temizle();	
	Equiped();
	CEnvanterYazdir();
	EnvanterYazdir();
	int s=slot-1;	
	struct Item yedek;
	int i,secim=0;
	git(slot+8,5);printf("  Þehir Meyadanýna Geri Dön ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukarý yön tuþu
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==slot+1)?0:secim;
				secim=(secim==-1)?slot:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // aþaðý yön tuþu
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
	git(slot+8,5);printf("  Þehir Meyadanýna Geri Dön ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukarý yön tuþu
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==slot+1)?0:secim;
				secim=(secim==-1)?slot:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // aþaðý yön tuþu
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
	git(5,5);printf("Tüccarýn Envanteri:		Altýnýn: %d ",player.GLD);
	for(i=0;i<10;i++){
	git(i+8,5);printf("  %s  ",x[i].AD);git(i+8,25);printf("Hasar: %d ",x[i].IATK);git(i+8,40);printf("Defans: %d ",x[i].IDEF);git(i+8,55);printf("Deðer: %d Altýn",x[i].IVLU);	
	}
	git(18,5);printf("  Þehir Meyadanýna Geri Dön ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukarý yön tuþu
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==11)?0:secim;
				secim=(secim==-1)?10:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // aþaðý yön tuþu
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
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}					
					break;
					case 1:
							durum=F;
							if(player.GLD>=x[1].IVLU){
								player.UITM[slot]=x[1];
								player.GLD-=x[1].IVLU;
												TuccarMenu(x);
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}						
					break;
					case 2:
							durum=F;
							if(player.GLD>=x[2].IVLU){
								player.UITM[slot]=x[2];
								player.GLD-=x[2].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 3:
							durum=F;
							if(player.GLD>=x[3].IVLU){
								player.UITM[slot]=x[3];
								player.GLD-=x[3].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;							
					case 4:
							durum=F;
							if(player.GLD>=x[4].IVLU){
								player.UITM[slot]=x[4];
								player.GLD-=x[4].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;							
					case 5:
							durum=F;
							if(player.GLD>=x[5].IVLU){
								player.UITM[slot]=x[5];
								player.GLD-=x[5].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;							
					case 6:
							durum=F;
							if(player.GLD>=x[6].IVLU){
								player.UITM[slot]=x[6];
								player.GLD-=x[6].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 7:
							durum=F;
							if(player.GLD>=x[7].IVLU){
								player.UITM[slot]=x[7];
								player.GLD-=x[7].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 8:
							durum=F;
							if(player.GLD>=x[8].IVLU){
								player.UITM[slot]=x[8];
								player.GLD-=x[8].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												TuccarMenu(x);	}
					break;
					case 9:
							durum=F;
							if(player.GLD>=x[9].IVLU){
								player.UITM[slot]=x[9];
								player.GLD-=x[9].IVLU;
												TuccarMenu(x);								
							}else{
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
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
  	char menu1[]="Hancýya Git";
  	char menu2[]="Doktorla Konuþ";

  	YaziYaz(satir-3,(kolon-4-strlen(bilgi))/2,bilgi,strlen(bilgi));
  	YaziYaz(12,(kolon-4-strlen(baslik))/2,baslik,strlen(baslik));
  	YaziYaz(19,(kolon-4-strlen(menu1))/2,menu1,strlen(menu1));
  	YaziYaz(22,(kolon-4-strlen(menu2))/2,menu2,strlen(menu2));
	git(22,50);printf("(15 Altýn)");  
	int secim=1;
	durum=T;
	while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukarý yön tuþu
						secim--;
						break;
					case 80:  // aþaðý yön tuþu
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
		git(5,5);printf("%s : Yaralarýma bakým gerekli.",player.AD);getch();
		git(6,5);printf("Doktor: Belirli bir ücret karþýlýðýnda olur.(15 Altýn)");
		if(player.GLD>=15){git(7,5);printf("Ýþte Altýnýn.(Canýn Tamamen doldu)");player.GLD-=15;player.CAN=player.MCAN;Sleep(1800);SehirMenu(SehirMenuYazilar,6);}
		else{git(7,5);printf("Yeterli Altýným Yok");Sleep(1500);SehirMenu(SehirMenuYazilar,6);}			
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
	strcpy(x[0].ADI,"Ýlaç");	strcpy(x[1].ADI,"Elma");	strcpy(x[2].ADI,"Bandaj");  strcpy(x[3].ADI,"Portakal");	strcpy(x[4].ADI,"Mantar");
	x[0].VLU=20;x[0].HEL=5;x[0].ADT=1	;x[1].VLU=15;x[1].HEL=1;x[1].ADT=1;	x[2].VLU=19;x[2].HEL=4;x[2].ADT=1;	x[3].VLU=17;x[3].HEL=3;x[3].ADT=1;	x[4].VLU=16;x[4].HEL=2;x[4].ADT=1;
	int j;
	int i,secim=0;
	Temizle();
	git(5,5);printf("Hancýnýn Envanteri:		Altýnýn: %d ",player.GLD);
	git(6,5);printf("(Not: Tüketilebilir eþyalarý satamazsýn!)");
	for(i=0;i<5;i++){
	git(i+8,5);printf("  %s  ",x[i].ADI);git(i+8,25);printf("Ýyileþtirme: %d ",x[i].HEL);git(i+8,40);printf("Deðer: %d Altýn",x[i].VLU);
	}
	git(13,5);printf("  Þehir Meyadanýna Geri Dön ");
						git(8,5);printf(">");	
		while(durum){
		if(kbhit()){
			tus=getch();
			if(tus==224){
				tus=getch();
				switch(tus){
					case 72:   //yukarý yön tuþu
						secim--;
						git(secim+9,5);printf(" "); 					
				secim=(secim==6)?0:secim;
				secim=(secim==-1)?5:secim;	
						git(secim+8,5);printf(">");									
						break;
					case 80:  // aþaðý yön tuþu
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
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												HanciMenu(x);	}					
					break;
					case 1:
							durum=F;
							if(player.GLD>=x[1].VLU){
								player.CONS[1].ADT++;
								player.GLD-=x[1].VLU;
												HanciMenu(x);
							}else{						
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												HanciMenu(x);	}						
					break;
					case 2:
							durum=F;
							if(player.GLD>=x[2].VLU){
								player.CONS[2].ADT++;
								player.GLD-=x[2].VLU;
												HanciMenu(x);								
							}else{						
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												HanciMenu(x);	}
					break;
					case 3:
							durum=F;
							if(player.GLD>=x[3].VLU){
								player.CONS[3].ADT++;
								player.GLD-=x[3].VLU;
												HanciMenu(x);								
							}else{						
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
												HanciMenu(x);	}
					break;							
					case 4:
							durum=F;
							if(player.GLD>=x[4].VLU){
								player.CONS[4].ADT++;
								player.GLD-=x[4].VLU;
												HanciMenu(x);								
							}else{						
						git(22,22);printf("YETERSÝZ ALTIN");Sleep(1000);
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
	char menu1[]="Yapýmcýlar";
  	char menu2[]="Berra Sarý";
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
	git(5,5);printf("Boða sýðýnaðýna doðru yola çýktýn ve uzun bir süredir yürüyorsun.");Sleep(60);
	git(6,5);printf("Kendine geceyi atlatacak kadar sýðýnacak bir yer bulman lazým.");Sleep(60);
	
{	durum=T;
	char menu1[]="Etrafý Arastýr";
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
	git(7,5);printf("Etrafý dolaþtýktan sonra sýðýnýlabilecek bir maðara buldun. ");
	

{	durum=T;
	char menu1[]="  Maðaraya Gir  ";
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
	git(5,5);printf("Maðaraya usulca ilerledin.");Sleep(60);
	git(6,5);printf("Ýçeri rüzgarýn girmediði bir bölüm aramaya baþladýn.");Sleep(60);
	git(7,5);printf("Burada yaþayan bir yerli olduðunu fark ettin.");Sleep(60);
	git(8,5);printf("Yerliden maðarada kalmak için izin istedin.");Sleep(60);
	git(9,5);printf("Yerli: Kalmak istiyorsan 10 altýn isterim yoksa izinsiz girdiðin için");Sleep(60);
	git(10,5);printf("canýný alýrým");Sleep(60);
{	struct Enemy a;durum=T;int secim=1;char isim[7]="Yerli";
git(13,5);printf("  Sana altýn vermeyeceðim");Sleep(60);
git(14,5);printf("  Tamam ,kalmak için para ödeyeceðim (10 Altýn)");Sleep(60);
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
					git(22,5);printf("10 altin ödedin");
					player.GLD-=10;
					Sleep(1000);
						}else{
							git(17,5);printf("Yeteri kadar paran yok. Sana saldýrmak üzere olan yerliye");Sleep(70);
							git(18,5);printf("karþý kendini korumak zorundasýn!");Sleep(60);
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
	git(5,5);printf("Yoluna devam ediyorusun.Geceyi orda geçiriyorsun.");Sleep(60);
	git(6,5);printf("Sabah oluyor ve Boða sýðýnaðýna doðru yola çýkýyorsun.");Sleep(60);
	git(7,5);printf("Karnýn acýktý ve susadýn.Yiyecek ve su bulmalýsýn.");Sleep(60);
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
	git(5,5);printf("Etrafý araþtýrdýktan sonra bir su birikintisi ve elma aðacý buldun.");Sleep(60);
	git(6,5);printf("Su içtikten sonra elma toplamak için aðaca yöneldin.");Sleep(60);
	git(7,5);printf("Ve sana doðru hýzla gelen bir kurt olduðýný gördün.");Sleep(600);
	getch();
	Temizle();
{
	struct Enemy kurt;char kurtad[5]="Kurt";
	Savas(kurt,kurtad);
}		
LvlUP();
Sleep(250);
Temizle();
	git(5,5);printf("Kurtun icabýna baktýntan sonra karnýný elmalarla doyurdun.");Sleep(60);
	git(6,5);printf("Arkaný döndüðünde az önce kurtulduðun kurtun eþiyle göz göze geldin.");Sleep(600);
	getch();
	Temizle();
{
	struct Enemy kurt;char kurtad[5]="Kurt";
	Savas(kurt,kurtad);
}		
LvlUP();
Sleep(250);
Temizle();
	git(7,5);printf("Geri dönüp elmalarýn birazýný da yanýna alýp yürümeye ");Sleep(60);
	git(8,5);printf("devam ettin.Ýleride bir þehir olduðunu gördün.");Sleep(60);
	player.CONS[1].ADT+=5;
{	durum=T;
	char menu1[]="Þehre Git";
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
	git(11,5);printf("Þehirden ayrýlmaya hazýrlanýrken bir dilencinin seni");Sleep(60);
	git(12,5);printf("takip ettiðini fark ettin. Bir süre sonra önüne");Sleep(60);
	git(13,5);printf("çýktý ve senden para istedi.");Sleep(60);
	git(15,6);printf("Altýn verme");Sleep(60);
	git(16,6);printf("5 Altýn ver");Sleep(60);
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
					git(13,5);printf("Dilenci söylenerek giderken sana bir kaðýt parçasý uzattý.");Sleep(60);	
					}else if(secim==2){
						if(player.GLD>=5){
							Temizle();
							git(12,5);printf("5 altin verdin"); Sleep(60);
							git(13,5);printf("Altýný verirken dilenci sana bir kaðýt parçasý uzattý."); Sleep(60);
							player.GLD-=5;
							Sleep(1000);
						}
						else{
							Temizle();
							git(12,5);printf("Yeteri kadar paran yok. Dilenciye para veremedin.");Sleep(70);
							git(13,5);printf("Dilenci söylenerek giderken sana bir kaðýt parçasý uzattý.");Sleep(60);
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
	git(11,5);printf("Kaðýdý açýp okuyorsun. Kaðýtta þunlar yazýyor:");Sleep(60);
	git(12,5);printf("--------------------------------------------------------------------------");Sleep(60);
	git(13,5);printf("Hana git ve hancýya  \"Güneþ doðduðnda ve battýðýnda orman bizi korur\" de.");Sleep(60);
	git(14,5);printf("Kolaylýkla gelmezsen zorla getiririz.");Sleep(60);
	git(15,5);printf("--------------------------------------------------------------------------");Sleep(60);//Yapabilirsem kaðýt gibi görünsün diye bunu bir karenin içine yazacaðým
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
	git(11,5);printf("Hancý: Ýyi günler. Nasýl yardýmcý olabilirim.");Sleep(60);
	git(13,6);printf("Güneþ doðduðnda ve battýðýnda orman bizi korur");Sleep(60);
	git(14,6);printf("Bira ver hancý.");Sleep(60);
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
					git(12,6);printf("Güneþ doðduðnda ve battýðýnda orman bizi korur");Sleep(70);//Düzeltmeyi unutma
					git(13,6);printf("Notta yazan þeyleri okuduktan sonra hancý seni gizli bir odaya götürdü.");Sleep(60);	
					}else if(secim==2){
						if(player.GLD>=10){
							Temizle();
							git(12,6);printf("10 altýn verdin"); Sleep(60);
							git(13,6);printf("Ýçkini içerken hancýnýn birine seni iþaret ettiðini gördün."); Sleep(60);
							player.GLD-=10;
							getch();
							git(12,6);printf("Bir süre sonra bir grup elf masana oturdu.");Sleep(60);//Baþka bir ýrk olabilir
							git(13,6);printf("Elflerden biri: Sana zorluk çýkarma demiþtik.");Sleep(60);
							git(14,6);printf("Ýçkini içtikten sonra handaki gizli bir odaya gittiniz.");Sleep(60);
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
	git(12,5);printf("Elflerin baþý: Merhaba. Ben Orman Gardiyanlarý grubunun baþý.");Sleep(60);
	git(13,5);printf("Boðalar senin köyün gibi gibi bizim ormanlarýmýza de saldýrdý.");Sleep(60);
	git(14,5);printf("Bizde Boðalara karþý Orman Gardiyanlarýný kurduk.");Sleep(60);
	git(15,5);printf("Seni Boðalara karþý birleþmeye davet ediyorum.");Sleep(60);
{	durum=T;
	char menu1[]="Elflere katýl";
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
	git(12,5);printf("Orman Gardiyanlarýna katýldýn.");Sleep(60);
	git(13,5);printf("Havanýn kararmak üzere olduðunu fark ettin. Elflerden");Sleep(60);
	git(14,5);printf("bugün kalmak için bir yer istedin.");Sleep(60);
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
	git(12,5);printf("Sabah olduðunda Boðalarýn bugün kervanla silah ve zýrh");Sleep(60);
	git(13,5);printf("taþýyacaklarýný öðrendin. Bunun için þehir dýþýnda bir");Sleep(60);
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
	git(12,5);printf("Boðalarýn pusu noktasýna yaklaþtýðýný farkettiniz.");Sleep(60);
	git(13,5);printf("Atlarýn önünü kestiniz. Elflerden yay kullananlar kervaný"); Sleep(60);
	git(14,5);printf("ok yaðmuruna tuttu. Sende kýlýç kullananlar ile beraber"); Sleep(60);
	git(15,5);printf("Boðalara hücum ettin. Karþýna Baltacý Boða çýktý."); Sleep(60);
	getch();
	Temizle();
	struct Enemy a; char baltaci[13]="Baltacý Boða";
	Savas(a,baltaci);
	Temizle();
	git(12,5);printf("Baltacý Boða'yý öldürdükten sonra baþka bir Boðanýn");Sleep(60);
	git(13,5);printf("üstüne koþtuðunu fark ettin.");Sleep(60);
	getch();
	Temizle();
	struct Enemy b; char kilicli[13]="Kýlýçlý Boða";
	Savas(b,kilicli);
	Temizle();
	struct Item BogasSword, BogasArmor;
	BogasSword.IATK=5;							BogasArmor.IATK=0;	
	BogasSword.IDEF=0;							BogasArmor.IDEF=8;		
	BogasSword.IVLU=75;							BogasArmor.IVLU=75;		
	strcpy(BogasSword.AD,"Boða Kýlýcý");		strcpy(BogasArmor.AD,"Boða Zýrhý");	
	slot=0;int i;
	for(i=0;i<10;i++){
		if(player.UITM[i].IVLU!=0)slot++;
	}
	if(slot<=9){
	player.UITM[slot]=BogasSword;slot++;}
	if(slot<=8){
	player.UITM[slot]=BogasArmor;}
	git(12,5);printf("Kervandan Boða Kýlýcý ve Boða Zýrhý buldun.");Sleep(60);
	git(13,5);printf("Dinlenmek için þehire dönmeye karar verdiniz.");Sleep(60);
{	durum=T;
	char menu1[]="Þehire dön";
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
	git(12,5);printf("En sonunda boða sýðýnaðýna saldýrmak üzere þehirden ayrýldýnýz.");Sleep(60);
	git(13,5);printf("Bir maðaranýn önünde durdunuz. Boða'larýn Maðaranýn içine girdiðini");Sleep(60);
	git(14,5);printf("farkettiniz. Maðaranýn baþýnda iki tane nöbetçi olduðunu gördünüz.");Sleep(60);
	{	durum=T;
	char menu1[]="NöbetçilereSaldýr";
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
	struct Enemy a; char enemy[13]="Nöbetci Boða";
	Savas(a,enemy);
	LvlUP();
	Temizle();
	git(12,5);printf("Öteki nöbetciyi Elfler halleti.");Sleep(60);
	{	durum=T;
	char menu1[]="Maðaraya Gir";
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
	git(13,5);printf("Meþaleler ile aydýnlatýlmýþ bir koridorda yürüyorsunuz.");Sleep(60);
	git(14,5);printf("Ýlerlerken tuzaða yakalýnýyorsun. Ayaðýna büyük bir taþ düþüyor.");Sleep(60);
	player.CAN-=5;
	Death();
	git(15,5);printf("5 canýn azaldý. Bundan sonra daha dikkatli ilerlemeye baþladýn.");Sleep(60);
	getch();
	Temizle();
	git(12,5);printf("Bir zindan buldunuz. Zindanýn baþýnda bir nöbetçi gördünüz. Tam nöbetçi");Sleep(60);
	git(13,5);printf("sizi fark ettiði an kafasýna ok yedi ve yere yýðýldý.");Sleep(60);
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
	git(12,5);printf("Hücreleri tek tek aramaya baþladýn. Fakat aileni bulamadýn.");Sleep(60);
	git(13,5);printf("Zindandan çýktýnýz. Koridorda ilerlemeye devam ettiniz.");Sleep(60);
	git(14,5);printf("Sýðýnaðýn yemekhanesini buldunuz. Ýçeridekiler sizi fark etmedi.");Sleep(60);	
	git(15,5);printf("Elflerin lideri: Ýçeride çok fazla Boða var. Plan yapmalýyýz.");Sleep(60);
	git(17,5);printf("Plan yapmalýyýz.");Sleep(60);
	git(18,5);printf("Bekleyecek vakit yok hemen saldýrmalýyýz.");Sleep(60);	
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
						git(16,5);printf("Plan yapmalýyýz.");Sleep(60);
						git(17,4);printf(" Ýçeridekileri zehirlemeye karar verdiniz.");Sleep(60);
						git(18,5);printf("Aþçý fark etmeden çorba kazanýnýn içine zehir attýnýz.");Sleep(60);
						git(19,5);printf("Boðalar yemek yedikten bir süre sonra içerideki herkes bayýldý.");Sleep(60);
						getch();
					}
					else if(secim==2){//saldiri
						durum=F;
						git(16,5);printf("Bekleyecek vakit yok hemen saldýrmalýyýz.  ");Sleep(60);
						git(17,5);printf("Saldýrmaya karar verdiniz.  ");Sleep(60);
						git(18,4);printf(" Elflerin lideri sana bir iksir verdi.         ");Sleep(60);
						player.MCAN+=10;
						player.CAN=player.MCAN;
						player.ATK+=2;
						player.DEF+=2;
						git(19,4);printf(" Ýksiri içince kendini daha cesur hissettin. Yemekhanenin kapýsýný");Sleep(60);
						git(20,5);printf("açtýn, baðýrarak içeri girdin ve önüne gelene saldýrmaya baþladýn.");Sleep(60);
						getch();
						Temizle();
						strcpy(enemy,"Sinirli Boða");
						Savas(a,enemy);
						Temizle();
						strcpy(enemy,"Aþcý Boða");
						Savas(a,enemy);
						Temizle();
						strcpy(enemy,"Aç Boða");
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
	git(13,5);printf("Sýðýnaðýn erzak odasýný buldunuz. Ýçeride zýrhlý bir");Sleep(60);
	git(14,5);printf("boða gördünüz. Zýrhtan zor yürüyen Boða sana baktý ve");Sleep(60);
	git(15,5);printf("Tank Boða: Seni düelloya davet ediyorum.");Sleep(60);
	{	durum=T;
	char menu1[]="Düello yap";
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
	strcpy(tank.AD,"Tank Boða");
	tank.ATK=2;
	tank.CAN=50;
	tank.DEF=20;
	Temizle();
	SavasMenu(tank);
	Temizle();
	LvlUP();
	Temizle();
	git(12,5);printf("Ýlerlemeye devam ettiniz. Koridorun sonuna geldiniz.");Sleep(60);
	git(13,5);printf("Aileni bulamadýn. Umutsuzluða kapýlýp duvara vurdun.");Sleep(60);
	git(14,5);printf("Birden gizli bir geçit açýldý.");Sleep(60);
	{	durum=T;
	char menu1[]="Geçite Gir";
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
	git(12,5);printf("Ýlerlerken buranýn bir zindan olduðunu anladýn.");Sleep(60);
	git(13,5);printf("Zindanýn sonunda Boðalarýn Baþýný gördün. Sana baktý ve");Sleep(60);
	git(14,5);printf("Boðalarýn Baþý: Sen bütün planlarýmý mahvettin. Bunun bedelini ödeyeceksin");Sleep(60);
	{	durum=T;
	char menu1[]="Saldýr";
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
	strcpy(lider.AD,"Boðalarýn Baþý");
	lider.ATK=15;
	lider.CAN=40;
	lider.DEF=10;
	SavasMenu(lider);
	git(12,5);printf("Boðalarýn Baþýný öldürdükten sonra aileni aramaya baþladýn");Sleep(60);
	git(13,5);printf("Biraz ilerledikten sonra aileni buldun. Sonunda aileni kurtarmýþtýn.");Sleep(60);
	git(14,5);printf("Beraber þehire döndünüz.");Sleep(60);
	Temizle();
	sonMenu();
}

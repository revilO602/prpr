#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct zaznam {
	char kategoria[51];
	char miesto[51];
	char ulica[101];
	int rozloha;
	int cena;
	char popis[201];
	struct zaznam* dalsi;
}ZAZNAM;

void strToUpp(char *str){
	int i=0;
	
	while (*(str+i)!='\0'){
		*(str+i)=toupper(*(str+i));
		i++;
	}
}

void nacitajZaznam(ZAZNAM *akt, FILE *f){
		fgets(akt->kategoria, 51, f);
		akt->kategoria[strlen(akt->kategoria) - 1] = '\0';
		fgets(akt->miesto, 51, f);
		akt->miesto[strlen(akt->miesto) - 1] = '\0';
		fgets(akt->ulica, 101, f);
		akt->ulica[strlen(akt->ulica) - 1] = '\0';
		fscanf(f,"%d ", &(akt->rozloha));
		fscanf(f, "%d ", &(akt->cena));
		fgets(akt->popis, 201, f);
		akt->popis[strlen(akt->popis) - 1] = '\0';
	}
void vypisZaznam(ZAZNAM*akt){
	printf("kategoria ponuky: %s\n", akt->kategoria);
	printf("miesto ponuky: %s\n", akt->miesto);
	printf("ulica: %s\n", akt->ulica);
	printf("rozloha v m2: %d\n", akt->rozloha);
	printf("cena: %d\n", akt->cena);
	printf("popis: %s\n", akt->popis);
}
void zmazZoznam(ZAZNAM **prvy){
	ZAZNAM *zmaz;
	while(*prvy!=NULL){
		zmaz=*prvy;
		*prvy=(*prvy)->dalsi;
		free(zmaz);
	}
}

void copyZaznam(ZAZNAM *from,ZAZNAM *to){
	strcpy(to->kategoria,from->kategoria);
	strcpy(to->miesto,from->miesto);
	strcpy(to->ulica,from->ulica);
	to->cena=from->cena;
	to->rozloha=from->rozloha;
	strcpy(to->popis,from->popis);	
}

void n(ZAZNAM **prvy) {
	FILE* f;
	char c;
	int sum=0;
	ZAZNAM* akt=NULL;
	if ((f = fopen("reality.txt", "r")) == NULL) {
		printf("Zaznamy neboli nacitane");
		return;
	}
	if (*prvy!=NULL){
		zmazZoznam(prvy);
	}
	// prvy prvok
	if ((c = fgetc(f)) == '&') {
		c = fgetc(f);
		*prvy=(ZAZNAM*)malloc(sizeof(ZAZNAM));
		akt = *prvy;
		nacitajZaznam(akt,f);
		akt->dalsi = NULL;
		sum++;
	}
	// ostatne prvky
	while ((c = fgetc(f)) == '&') {
		c = fgetc(f); //precitanie konca riadka
		akt->dalsi=(ZAZNAM*)malloc(sizeof(ZAZNAM));
		akt=akt->dalsi;
		nacitajZaznam(akt,f);
		akt->dalsi = NULL;
		sum++;
	}
	printf("Nacitalo sa %d zaznamov\n",sum);
	fclose(f);
}

void v(ZAZNAM *prvy) {
	int i=1;
	while (prvy != NULL) {
		printf("%d.\n", i++);
		vypisZaznam(prvy);
		prvy = prvy->dalsi;
		
	}
}

void p(ZAZNAM **prvy){
	int poz,i;
	ZAZNAM* akt=*prvy,*vloz;
	scanf("%d ",&poz);
	vloz=(ZAZNAM*)malloc(sizeof(ZAZNAM));
	nacitajZaznam(vloz,stdin);
	if (poz==1 || *prvy==NULL){
		vloz->dalsi=*prvy;
		*prvy=vloz;
		return;
	}
	for (i=1;i<poz-1;i++){
		if (akt->dalsi==NULL)
			break;
		akt=akt->dalsi;
	}
	vloz->dalsi=akt->dalsi;
	akt->dalsi=vloz;
}

void z(ZAZNAM **prvy){
	ZAZNAM *akt,*zmaz;
	char hladanyStr[51],aktMiesto [51];
	int n=0;
	if (*prvy==NULL){
		printf("Vymazalo sa %d zaznamov\n",n);
		return;
	}
	scanf(" %s",hladanyStr);
	strToUpp(hladanyStr);
	akt=*prvy;
	strcpy(aktMiesto,akt->miesto);
	strToUpp(aktMiesto);
	while (strstr(aktMiesto,hladanyStr)!=NULL){
		n++;
    	zmaz=*prvy;
    	akt=akt->dalsi;
    	*prvy=akt;
    	free(zmaz);
    	if (akt==NULL){
    		printf("Vymazalo sa %d zaznamov\n",n);
      		return;
      	}
    	strcpy(aktMiesto,akt->miesto);
		strToUpp(aktMiesto);
    }
	while(akt->dalsi!=NULL){
		strcpy(aktMiesto,akt->dalsi->miesto);
	    strToUpp(aktMiesto);
		zmaz=akt->dalsi;
		if (strstr(aktMiesto,hladanyStr)!=NULL){
			akt->dalsi=zmaz->dalsi;
			free(zmaz);
			n++;
		}
		else akt=akt->dalsi;
	}
	printf("Vymazalo sa %d zaznamov\n",n);
}

void h(ZAZNAM *prvy){
	int hlCena, najdene=0, i=1;
	ZAZNAM *akt=prvy;
	scanf(" %d", &hlCena);
	while (akt!=NULL){
		if((akt->cena)<=hlCena){
			printf("%d.\n",i++);
			vypisZaznam(akt);
			najdene=1;
		}
		akt=akt->dalsi;
	}
	if (najdene==0)
		printf("V ponuke su len reality s vyssou cenou");
}

void a(ZAZNAM **prvy){
	char hladaneMiesto[51], aktMiesto[51];
	ZAZNAM *vloz,*zmaz,*akt;
	int n=0;
	if (*prvy==NULL)
		return;
	scanf(" %s\n",hladaneMiesto);
	strToUpp(hladaneMiesto);
	vloz=(ZAZNAM*)malloc(sizeof(ZAZNAM));
	nacitajZaznam(vloz,stdin); //vytvorenie pomocneho prvku z ktoreho kopirujeme
	akt=*prvy;
	strcpy(aktMiesto,akt->miesto);
	strToUpp(aktMiesto);
	//zmeni prvy
	if (strstr(aktMiesto,hladaneMiesto)!=NULL){
    	zmaz=*prvy;
    	*prvy=(ZAZNAM*)malloc(sizeof(ZAZNAM));
    	copyZaznam(vloz,*prvy);
    	(*prvy)->dalsi=zmaz->dalsi;
    	free(zmaz);
		n++;
		akt=*prvy;
    }
    //zmeni ostatne
	while(akt->dalsi!=NULL){
		memset(aktMiesto,'\0',sizeof(aktMiesto));
		strcpy(aktMiesto,akt->dalsi->miesto);
	    strToUpp(aktMiesto);
		zmaz=akt->dalsi;
		if (strstr(aktMiesto,hladaneMiesto)!=NULL){
			akt->dalsi=(ZAZNAM*)malloc(sizeof(ZAZNAM));
			copyZaznam(vloz,akt->dalsi);
			akt->dalsi->dalsi=zmaz->dalsi;
			free(zmaz);
			n++;
		}
		akt=akt->dalsi;
	}    
	free(vloz); 
	printf("Aktualizovalo sa %d zaznamov\n",n);
}

void u(ZAZNAM **prvy){
	ZAZNAM *akt,*predmin,*min,*novy,*novyprvy=NULL;
	
	if (*prvy==NULL){
		printf("Zoznam nie je mozne usporiadat");
		return;
	}
	if ((*prvy)->dalsi==NULL){
		printf("Zaznamy boli usporiadane\n");
		return;
	}
	akt=*prvy;
	while(akt->dalsi!=NULL){
		predmin=*prvy;
		min=*prvy;
		while (akt->dalsi!=NULL){
			if (strcmp(akt->dalsi->miesto,min->miesto)<=0){
				if (strcmp(akt->dalsi->miesto,min->miesto)<0 || 
					akt->dalsi->cena<min->cena)
					{
						predmin=akt;
						min=predmin->dalsi;
					}
			}
			akt=akt->dalsi;
		}
		if (novyprvy==NULL){
			novyprvy=min;
			novy=novyprvy;
		}
		else{
		 novy->dalsi=min;
		 novy=novy->dalsi;
		}
		predmin->dalsi=min->dalsi;
		if (novy==*prvy)*prvy=(*prvy)->dalsi;
		akt=*prvy;
	}
	*prvy=novyprvy;
	novy->dalsi=akt;
	printf("Zaznamy boli usporiadane\n");
}


int main() {
	ZAZNAM* prvy=NULL;
	char funkcia;
	while (scanf(" %c", &funkcia) > 0) {
		switch (funkcia)
		{
		case 'n':
			n(&prvy);
			break;
		case 'v':
			v(prvy);
			break;
		case 'p':
			p(&prvy);
			break;
		case 'z':
			z(&prvy);
			break;
		case 'h':
			h(prvy);
			break;
		case 'a':
			a(&prvy);
			break;
		case 'u':
			u(&prvy);
			break;
		case 'k':
			if (prvy!=NULL)
				zmazZoznam(&prvy);
			return 0;
			break;
		}
	}
	return 0;
}

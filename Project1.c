// Oliver Leontiev
// Projekt 1, PrPr
// 2019
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DLZKA 51
#define SPZ_DLZKA 7
#define POLOZKY 6
#define ODMENA_STR 0.051 //koeficient pre stare auto
#define ODMENA_NOV 0.023 //koeficient pre nove auto

typedef struct zaznam{
	char meno[MAX_DLZKA];
	char SPZ[SPZ_DLZKA+1];
	int typ;
	double cena;
	int datum;
} ZAZNAM;

void spocitajZaznamy(FILE* subor, int *pocet_zaznamov){
	char pom[MAX_DLZKA];
	
	if (subor == NULL)
		return;
	
	rewind(subor);
	*pocet_zaznamov = 0;
	
	while (fgets(pom, MAX_DLZKA, subor) != NULL){
		(*pocet_zaznamov)++;
	}
	
	*pocet_zaznamov = ( (*pocet_zaznamov) + 1 ) / POLOZKY;
	rewind(subor);
}

ZAZNAM* nacitajZaznamy(FILE **subor, int pocet_zaznamov){
	ZAZNAM* p_ZAZNAMY = NULL;
	int zaznam;
	
	rewind(*subor);
	p_ZAZNAMY = (ZAZNAM *) malloc (pocet_zaznamov * sizeof(ZAZNAM));
	
	for (zaznam = 0; zaznam<pocet_zaznamov; zaznam++) {
		fgets(p_ZAZNAMY[zaznam].meno, MAX_DLZKA, *subor);
		p_ZAZNAMY[zaznam].meno[strlen(p_ZAZNAMY[zaznam].meno)-1] = '\0'; // odstranenie znaku konca riadku
		fgets(p_ZAZNAMY[zaznam].SPZ, SPZ_DLZKA+1, *subor);
		fscanf(*subor, "%d  ",  &(p_ZAZNAMY[zaznam].typ));
		fscanf(*subor, "%lf  ", &(p_ZAZNAMY[zaznam].cena));
		fscanf(*subor, "%d ",   &(p_ZAZNAMY[zaznam].datum));
	}
	return p_ZAZNAMY;
}

ZAZNAM* vypis( int *pocet_zaznamov ) {
	FILE* subor;
	int zaznam;
	ZAZNAM* p_ZAZNAMY = NULL;
	
	if ((subor = fopen("autobazar.txt", "r")) == NULL) {
		printf("Neotvoreny subor\n");
		return NULL;
	}
	spocitajZaznamy(subor, pocet_zaznamov);
	p_ZAZNAMY = nacitajZaznamy(&subor, *pocet_zaznamov);
	for (zaznam = 0; zaznam<*pocet_zaznamov; zaznam++){
		printf("meno priezvisko: %s\n", p_ZAZNAMY[zaznam].meno);
		printf("SPZ: %s\n",             p_ZAZNAMY[zaznam].SPZ);
		printf("typ auta: %d\n",        p_ZAZNAMY[zaznam].typ);
		printf("cena: %.2lf\n",         p_ZAZNAMY[zaznam].cena);
		printf("datum: %d\n",           p_ZAZNAMY[zaznam].datum);
		printf("\n");
	}
	if (subor != NULL)
		fclose(subor);
	return p_ZAZNAMY;
}
int patriOdmena(int dnes_datum, int nastup_datum){
		int rok = 10000;
		
		if (dnes_datum - rok > nastup_datum )
			return 1;
		else
			return 0;	
}

int odmena(ZAZNAM *p_ZAZNAMY, int pocet_zaznamov) {
	int zaznam, dnes_datum; 
	
	scanf("%d", &dnes_datum);
	for (zaznam = 0; zaznam < pocet_zaznamov; zaznam++) {

		if (patriOdmena(dnes_datum, p_ZAZNAMY[zaznam].datum)) {
			printf("%s %s %.2lf\n", p_ZAZNAMY[zaznam].meno, p_ZAZNAMY[zaznam].SPZ, 
				   p_ZAZNAMY[zaznam].typ ? p_ZAZNAMY[zaznam].cena * ODMENA_NOV : p_ZAZNAMY[zaznam].cena * ODMENA_STR);
		}
	}
	return 0;
}

void nacitaniePola(ZAZNAM* p_ZAZNAMY, char ***p_SPZ, int pocet_SPZ) {
	int SPZ, znak;
	
	if (p_ZAZNAMY != NULL) {
		if (*p_SPZ != NULL)
			free(*p_SPZ);
			
		*p_SPZ = (char **) malloc (pocet_SPZ * sizeof(char *));
		for (SPZ = 0; SPZ < pocet_SPZ; SPZ++) {
			(*p_SPZ)[SPZ] = (char *) malloc (SPZ_DLZKA);
			
			for (znak = 0; znak < SPZ_DLZKA; znak++) {
				(*p_SPZ)[SPZ][znak] = p_ZAZNAMY[SPZ].SPZ[znak];
			}
		}
	}
}

int jePole(char **pole){
	if (pole == NULL) {
		printf("Pole nie je vytvorene\n");
		return 0;
	}
	else 
		return 1;
}

void SPZvypis(char** p_SPZ, int pocet_SPZ) {
	int SPZ, znak;
	
	if (!jePole(p_SPZ))
		return;
		
	for (SPZ = 0; SPZ < pocet_SPZ; SPZ++) {
		for (znak = 0; znak < SPZ_DLZKA; znak++) {
			putchar(p_SPZ[SPZ][znak]);
			if (znak == 1 || znak == 4) //medzery medzi pismenami a cislami v SPZ
				putchar(' ');
		}
		putchar('\n');
	}
}

void maxZnak(char** p_SPZ, int pocet_SPZ) {
	int porZnak, porSPZ, nxtSPZ, nxtZnak, max = 0, pocetnost;
	char maxZnak;
	
	if (!jePole(p_SPZ))
		return;

	for (porSPZ = 0; porSPZ < pocet_SPZ; porSPZ++) {		
		for (porZnak = 0; porZnak < SPZ_DLZKA; porZnak++) {
			pocetnost = 0;
			for (nxtSPZ = 0; nxtSPZ < pocet_SPZ; nxtSPZ++) {		
				for (nxtZnak = 0; nxtZnak < SPZ_DLZKA; nxtZnak++) {
					if (p_SPZ[porSPZ][porZnak] == p_SPZ[nxtSPZ][nxtZnak])
						pocetnost++;
				}
			}
			if (pocetnost > max) {
				max = pocetnost;
				maxZnak = p_SPZ[porSPZ][porZnak];
			}
		}
	}
	printf("%c %d\n", maxZnak, max);
}
int jePalindrom (char* str){
	int pozicia = 0, len;
	
	len = strlen(str);
	
	for (pozicia = 0; pozicia < len / 2; pozicia++) {
		if ( str[pozicia] != str[len-1-pozicia] ) 
			return 0;
	}
	return 1;
}

void palindromOkres(char** p_SPZ, int pocet_SPZ) {
	int SPZ;
	
	if (!jePole(p_SPZ))
		return;
	
	for (SPZ = 0; SPZ < pocet_SPZ; SPZ++) {
		if (jePalindrom(p_SPZ[SPZ]))
			printf("%c%c\n", p_SPZ[SPZ][0], p_SPZ[SPZ][1] );
	}
}

void maxOkresy(char** p_SPZ, int pocet_SPZ) {
	int porOkres, nxtOkres, max = 1, pocetnost;
	
	if (!jePole(p_SPZ))
		return;
	// zistenie maximalneho vyskitu jedneho okresu v poli SPZ
	for (porOkres = 0; porOkres < pocet_SPZ; porOkres++) {
		pocetnost = 1;
		for (nxtOkres = porOkres + 1; nxtOkres < pocet_SPZ-porOkres; nxtOkres++) {
			if ( p_SPZ[porOkres][0] == p_SPZ[nxtOkres][0] && 
				 p_SPZ[porOkres][1] == p_SPZ[nxtOkres][1] )
				pocetnost++;
		}
		if (pocetnost > max) {
			max = pocetnost;
		}
	}
	// vypis vsetkych okresov vyskytujucich sa max-krat
	for (porOkres = 0; porOkres < pocet_SPZ; porOkres++) {
		pocetnost = 1;
		for (nxtOkres = porOkres + 1; nxtOkres < pocet_SPZ - porOkres; nxtOkres++) {
			if ( p_SPZ[porOkres][0] == p_SPZ[nxtOkres][0] && 
			     p_SPZ[porOkres][1] == p_SPZ[nxtOkres][1] )
				pocetnost++;
		}
		if(pocetnost == max)
			printf("%c%c %d\n", p_SPZ[porOkres][0], p_SPZ[porOkres][1], max);	
	}
}

void cezarSifra (char ***pole_SPZ, int pocet_SPZ, int posun){
	int SPZ, poz_space;
	char char1, char2;
	for (SPZ=0; SPZ < pocet_SPZ; SPZ += 2) {
		char1 = (*pole_SPZ)[SPZ][0]; 
		char2 = (*pole_SPZ)[SPZ][1]; 
		if (char1 + posun <= 'Z')
			(*pole_SPZ)[SPZ+1][0] = char1 + posun;
		else
			//ak prejdeme za Z vraciame sa na zaciatok abecedy
			(*pole_SPZ)[SPZ+1][0] = 'A' - 1 + ((char1 + posun) - 'Z'); 
			
		if (char2 + posun <= 'Z')
			(*pole_SPZ)[SPZ+1][1] = char2 + posun;
		else
			(*pole_SPZ)[SPZ+1][1] = 'A' - 1 + ((char2 + posun) - 'Z');
		// vyplnenie prazdeho miesta medzerami pre zachovanie struktury p_SPZ	
		for (poz_space=2; poz_space <= 6; poz_space++){
			(*pole_SPZ)[SPZ+1][poz_space] = ' ';
		}
	}	
}

void zdvojPole( char ***pole, int *pocet_riadkov){
		char **novePole;
		int strRiadok, stlpec, novRiadok;
		
		novePole = (char **) malloc (2 * *pocet_riadkov * sizeof(char *));
		for(novRiadok = 0; novRiadok < 2 * *pocet_riadkov; novRiadok++){
			novePole[novRiadok]= (char *) malloc (SPZ_DLZKA);
		}
		novRiadok = 0;
		for(strRiadok = 0; strRiadok < *pocet_riadkov; strRiadok++){
			for (stlpec=0; stlpec < SPZ_DLZKA; stlpec++){
				novePole[novRiadok][stlpec]=(*pole)[strRiadok][stlpec];
		    }
			novRiadok += 2;
		}
		free(*pole);
		*pole=novePole;
		*pocet_riadkov *= 2;
}

void sifraOkresy(char ***p_SPZ, int *pocet_SPZ){
	int posun=0;

	if (!jePole(*p_SPZ))
		return;

	scanf("%d", &posun);
	zdvojPole(p_SPZ, pocet_SPZ);
	cezarSifra(p_SPZ, *pocet_SPZ, posun);	
}

void histCisla(char **p_SPZ, int pocet_SPZ){
	int cislica, SPZ, pozicia, sum;
	
	if (!jePole(p_SPZ))
		return;
		
	for(cislica = 0; cislica < 9; cislica++){
		sum = 0;
		for (SPZ = 0; SPZ < pocet_SPZ; SPZ++){
			for (pozicia = 2; pozicia < 5; pozicia++){
				if (p_SPZ[SPZ][pozicia] == '0' + cislica)
					sum++;
			}
		}
		if(sum != 0){
			printf("%d:%d\n", cislica, sum);
		}
	}
}

int main(){
	ZAZNAM *p_ZAZNAMY = NULL;
	char **p_SPZ = NULL, funkcia;
	int pocet_zaznamov = 0, zasifrovane = 0;
	
	while (scanf("%c", &funkcia) > 0) {
		switch (funkcia)
		{
		case 'v':
			if (p_ZAZNAMY != NULL)
				free(p_ZAZNAMY);
			p_ZAZNAMY = vypis(&pocet_zaznamov);
			if (zasifrovane)
				pocet_zaznamov *= 2;
			break;
			
		case 'o':
			if (zasifrovane)
				odmena(p_ZAZNAMY, pocet_zaznamov / 2);
			else 
				odmena(p_ZAZNAMY, pocet_zaznamov);
			break;
			
		case 'n':
			if (zasifrovane)
				pocet_zaznamov /= 2;
			nacitaniePola(p_ZAZNAMY, &p_SPZ, pocet_zaznamov);
			zasifrovane = 0;
			break;
			
		case 's':
			SPZvypis(p_SPZ, pocet_zaznamov);
			break;
			
		case 'm':
			maxZnak(p_SPZ, pocet_zaznamov);
			break;
			
		case 'p':
			palindromOkres(p_SPZ, pocet_zaznamov);
			break;
			
		case 'z':
			maxOkresy(p_SPZ, pocet_zaznamov);
			break;
			
		case 'a':
			if (zasifrovane)
				printf("SPZ uz su zasifrovane!");
			else{
			sifraOkresy(&p_SPZ, &pocet_zaznamov);
			zasifrovane = 1;
			}
			break;
			
		case 'b':
			histCisla(p_SPZ, pocet_zaznamov);
			break;
			
		case 'k':
			free(p_SPZ);
			free(p_ZAZNAMY);
			return 0;
			break;
			
		default:
			break;
		}
	}
	return 0;
}

// Oliver Leontiev
// Projekt 1, PrPr
// 2019
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* v(int *pocet_zaznamov) {
	char s[50];
	FILE* fr;
	*pocet_zaznamov=0;
	if ((fr = fopen("autobazar.txt", "r")) == NULL) {
		printf("Neotvoreny subor\n");
	}
	else{
		while (fgets(s, 50, fr) != NULL){
			printf("meno priezvisko: %s", s);
			fgets(s, 50, fr);
			printf("SPZ: %s", s);
			fgets(s, 50, fr);
			printf("typ auta: %s", s);
			fgets(s, 50, fr);
			printf("cena: %s", s);
			fgets(s, 50, fr);
			printf("datum: %s", s);
			fgets(s, 50, fr);
			printf("\n");
			(*pocet_zaznamov)++;
		}
	}
	return fr;
}
int o(FILE *fr) {
	char meno[50], SPZ[8];
	int datum, typ,rok,mesiac,den,d_rok, d_mesiac, d_den, odmena;
	double cena;
	int d_datum;
	scanf("%d", &d_datum);
	if (fr != NULL) {
		rewind(fr);
		while (fgets(meno, 50, fr) != NULL) {
			meno[strlen(meno) - 1] = '\0'; // odstranenie znaku konca riadku
			fgets(SPZ, 8, fr);
			fscanf(fr, "%d", &typ);
			fscanf(fr, "%lf", &cena);
			fscanf(fr, "%d", &datum);

			rok = datum / 10000;
			mesiac = (datum - rok * 10000) / 100;
			den = (datum - mesiac * 100 - rok * 10000);

			d_rok = d_datum / 10000;
			d_mesiac = (d_datum - d_rok * 10000) / 100;
			d_den = (d_datum - d_mesiac * 100 - d_rok * 10000);
			
			odmena = 0;
			if (rok + 1 < d_rok)
				odmena = 1;
			else if (rok < d_rok) {
				if (mesiac < d_mesiac)
					odmena = 1;
				if (mesiac == d_mesiac) {
					if (den <= d_den)
						odmena = 1;
				}
			}
			if (odmena) {
				printf("%s %s %.2lf\n", meno, SPZ, typ ? cena * 0.023 : cena * 0.051);
			}
			// nacitanie konca riadku a prazdneho riadku
			fgets(meno, 50, fr);
			fgets(meno, 50, fr);
		}
	}
	return 0;
}
void n(FILE* fr, char **p_SPZ, int pocet_zaznamov) {
	char pom[50];
	int i;
	if (fr != NULL) {
		if (*p_SPZ!=NULL)
			free(*p_SPZ);
		*p_SPZ = (char *)malloc(pocet_zaznamov * 7);
		rewind(fr);
		while (fgets(pom, 50, fr) != NULL) {
			for (i = 0;i < 7;i++) {
				*(*p_SPZ + i) = getc(fr);
			}
			*p_SPZ += 7;
			for (i = 0;i < 5;i++) {   // presun na dalsiu spz
				fgets(pom, 50, fr);
			}
		}
		*p_SPZ = *p_SPZ - (7 * pocet_zaznamov);
	}
}
void s(char* p_SPZ, int pocet_zaznamov) {
	int i,j;
	if (p_SPZ == NULL) {
		printf("Pole nie je vytvorene\n");
	}
	else {
		for (i = 0;i < pocet_zaznamov;i++) {
			for (j = 0;j < 9;j++) {
				if (j==2 || j==6)
					putchar(' ');
				else {
					putchar(*p_SPZ);
					p_SPZ++;
				}
			}
			putchar('\n');
		}
	}
}
void m(char* p_SPZ, int pocet_zaznamov) {
	int i, j, max=1, pos_max=0, pom;
	if (p_SPZ == NULL) {
		printf("Pole nie je vytvorene\n");
	}
	else {
		for (i = 0;i < pocet_zaznamov * 7;i++) {
			pom = 1;
			for (j = i + 1;j < pocet_zaznamov * 7;j++) {
				if (*(p_SPZ + i) == *(p_SPZ + j))
					pom++;
			}
			if (pom > max) {
				max = pom;
				pos_max = i;
			}
		}
		printf("%c %d\n", *(p_SPZ + pos_max), max);
	}
}
void p(char* p_SPZ, int pocet_zaznamov) {
	int i, j, pal;
	if (p_SPZ == NULL) {
		printf("Pole nie je vytvorene\n");
	}
	else {
		for (i = 0;i < pocet_zaznamov;i++) {
			pal = 1;
			for (j = 0;j < 3;j++) {
				if (*(p_SPZ + j) != *(p_SPZ + (6 - j))) 
					pal=0;
			}
			if (pal)
			printf("%c%c\n",*(p_SPZ), *(p_SPZ+1));
			p_SPZ+=7;
		}
	}
}
void z(char* p_SPZ, int pocet_zaznamov) {
	int i, j, max = 1, pom;
	
	if (p_SPZ != NULL) {
		// zistenie max
		for (i = 0;i < pocet_zaznamov * 7;i+=7) {
			pom = 1;
			for (j = i + 7;j < pocet_zaznamov * 7-i;j+=7) {
				if (*(p_SPZ + i) == *(p_SPZ + j) && *(p_SPZ + i+1) == *(p_SPZ + j+1))
					pom++;
			}
			if (pom > max) {
				max = pom;
			}
		}
		// vypis vsetkych prvkov vyskytujucich sa max-krat
		for (i = 0;i < pocet_zaznamov * 7;i+=7) {
			pom = 1;
			for (j = i + 7;j < pocet_zaznamov * 7;j+=7) {
				if (*(p_SPZ + i) == *(p_SPZ + j) && *(p_SPZ + i+1) == *(p_SPZ + j+1))
					pom++;
			}
			if(pom==max)
				printf("%c%c %d\n", *(p_SPZ + i), *(p_SPZ + i + 1), max);	
		}
	}
}
int main(){
	FILE *fr=NULL;
	char *p_SPZ=NULL , funkcia;
	int pocet_zaznamov=0;
	
	while (scanf("%c", &funkcia) > 0) {
		switch (funkcia)
		{
		case 'v':
			if (fr!=NULL)fclose(fr);
			fr = v(&pocet_zaznamov);
			break;
		case 'o':
			o(fr);
			break;
		case 'n':
			n(fr, &p_SPZ, pocet_zaznamov);
			break;
		case 's':
			s(p_SPZ, pocet_zaznamov);
			break;
		case 'm':
			m(p_SPZ, pocet_zaznamov);
			break;
		case 'p':
			p(p_SPZ, pocet_zaznamov);
			break;
		case 'z':
			z(p_SPZ, pocet_zaznamov);
			break;
		case 'k':
			if (fr!=NULL)fclose(fr);
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#define TAILLE 10
typedef struct{
	int tab[4][4];
}Piece;

int* mmalloc(int size){ // attribution malloc + erreur
	int* att;
	att =NULL;
	att = malloc(size);
	if(att == NULL){ // message d'erreur
		printf("erreur d'allocation\n");
		exit(1);}
	return(att);}



int ** init_game (int** init){  // fonction initiation tablaeux
	int i,x;
	init = malloc(TAILLE*sizeof(int*));
	if(init == NULL){ // message d'erreur
		printf("erreur d'allocation\n");
		exit(1);}
		for(i = 0;i<TAILLE;i++){
			*(init+i)= mmalloc(TAILLE*sizeof(int));
				for(x = 0;x<TAILLE;x++){
					*(*(init+i)+x)= 0;
			}
	}
return init;}

void aff_t (int** sd){ // affiche Tableaux
	int i,x;
    printf("\nVoici votre grille :\n");
        for(x=65;x<75;x++){
            printf(" ");
            printf("%c",x);
    }

		printf("\n");
		for(i = TAILLE-1; i>-1; i=i-1){
			printf("|");
			for(x = 0;x<TAILLE;x++){
				if(*(*(sd+i)+x)== 0){
					printf(" |");}
				else{ // affichage bloc
					printf("o|");}
				}
		printf("\n");}
 }

void pripie(Piece j){  // imprime piece
	int w,x;
	printf("\n");
	for(w = 4;w>-1;w--){
		for(x = 0 ;x<4;x++){
			if(j.tab[w][x] == 0){
                    printf(" |");}
            else{ // affichage bloc
                        printf("o|");}
		}
    printf("\n");}
}



Piece* chargepie(int* a){ // chargement pi�ce a partir d'un int*a forme "piecea.txt" renvoi : tableau piece ,*a = orientation possible
	FILE* pie = NULL;
    Piece* j = NULL;
    int v,x;
    char c[5]  = "\0";
    c[0] = 48 +*a;
	char f[20]="piece\0";
	strcat(f,c);
	c[0] = '.';
	c[1] = 't';
	c[2] = 'x';
	c[3] = 't';
	c[4] = '\0';
    strcat(f,c);
	pie = fopen(f,"r");
	v = fgetc(pie)-48;
    j = malloc(v*sizeof(Piece)); //assignement espace variation
    if(j == NULL){ // message d'erreur
		printf("erreur d'alloocation\n");
		exit(1);}
    for (x=0;x<v;x++){ // assignement varation de piece
            fread(j+x,sizeof(Piece),1,pie);
    }
    *a = v;
    fclose(pie);
	return(j);}

Piece* tir(int* a){ //tir et chargement de piece
Piece* j = NULL;
*a = 1+rand()%6;
j = chargepie(a);

}





void affichech(Piece* j, int* a){ // affichage choix
int v,x,i;
printf("Choisir orientation de la piece\n");
for(x = 0;x<*a;x++){
        printf(" ");
        printf(" ");
        printf("%d",x+1);
        printf(" ");
        printf(" ");
    }
printf("\n");
for(i = 3;i>-1;i--){
    for(v=0; v<*a;v++){
		for(x = 0 ;x<4;x++){
			if((*(j+v)).tab[i][x] == 0){
                    printf(" ");}
            else{ // affichage bloc
                        printf("@");}
		}
    printf("|");}
printf("\n");}



}







int* inilim(){// innitiation limite
    int* lm = NULL;
    int x;
    lm = malloc(TAILLE*sizeof(int));
    if(lm == NULL){ // message d'erreur
		printf("erreur d'allocation\n");
		exit(1);}
    for(x=0;x<TAILLE;x++){
        *(lm+x)=0;
    }

	return lm;}




int place(int** tab,int* lim,int*a,Piece* pi,int p,int o){ //! placment selon case en bas a gauche de la pi�ce
    int x,i,dc,dl,cc,cl,st,l,op,ln;
    cl = 0; // variable lié aux idendificateur
    cc = 0;
    dl = -1;
    dc = 0-1;
    op = 0;
    for(x=0;x<4;x++){    // recherche des point identificateur de la piece orienter
        if ((*(pi+o)).tab[x][0] == 1 && op == 0){
            cl = x;
            if(cl >= 3){cl = 0;}
                op = 1;
        }
        for(i=0;i<4;i++){
        if((*(pi+o)).tab[x][i] == 0     ){  // id point plus bas
                if(dl == -1){
                cl = x+1;}
                if(dc == -1){
                cc = i+1;}}
                if(cl >= 4){cl = 0;}
                if(cc >= 4){cc = 0;
            ln = 1;
        }

        if((*(pi+o)).tab[x][i] == 1){ // id point plus haut pi�ce
           if(dl<x){
                dl = x;}
            if(dc<i){
                dc = i;

            }
        }
    if((*(pi+o)).tab[0][i] == 1){
                ln = 0;
        }
    }
    }
     //printf("\n %d \n",*(lim+p));
    // printf("   %d  %d  %d  %d  %d %d %d",dl,dc,cc,cl,ln,op,*(lim+p)); // ok
    st = 0;
    l=*(lim+p)-cl; // id point plus bas tab colonne
     //printf("\n limite%d",l);
    if(l+dl > 9){ // condition de fin d epartie d�passe en haut
         printf("\n Perdu!\n");
         return (1);

    }
    if(ln == 0 && (l<0 || (*(*(tab+l)+dc+p) == 1 )|| (*(*(tab+l)+cc+p) == 1 ))){
        l = l+cl;
        //printf("   m %d",l);
        while(l+1<10 && ((*(*(tab+l)+dc+p) == 1  && (*(pi+o)).tab[cl][dc] == 1)) || (*(*(tab+l)+cc+p) == 1 && (*(pi+o)).tab[cl][cc]== 1)){
            l = l+1;
        }
        }



// d�but v�rif
    for(x = dl;x>=0;x--){
        for(i=cc;i>=0;i--){
            if((*(pi+o)).tab[x][i]== 0){}
            else if((*(pi+o)).tab[x][i]== (*(*(tab+l+x)+p+i))){
                st = st+1;
               // printf("%d ==\n",st);
            }
            else if (l+x <0 || p+i<0 || l+x>9 ||p+i>9){
                st = st+1;
               // printf("%d depassement\n",st);
            }
        }
    for(i=cc;i<=dc;i++){
            if((*(pi+o)).tab[x][i]== 0){}
            else if((*(pi+o)).tab[x][i]== (*(*(tab+l+x)+p+i))){
                st = st+1;
                // printf("%d ==\n",st);
            }
            else if (l+x <0 || p+i<0 || l+x>9 ||p+i>9){
                st = st+1;
               // printf("%d depassement\n",st);

            }
        }

    }

    if(st == 0){ // comfirm� debut placement
         for(x = dl;x>=0;x--){
        for(i=cc;i<=dc;i++){
             if((*(pi+o)).tab[x][i]== 1){
            *(*(tab+l+x)+p+i) = (*(pi+o)).tab[x][i];
            if(*(lim+p+i) <= l+x+1){
            *(lim+p+i) = l+x+1;
            // printf("lim %d %d",p+i,l+x);
            }
            }

        }
        for(i=cc-1;i>=0;i--){
             if((*(pi+o)).tab[x][i]== 1){
            *(*(tab+l+x)+p+i) = (*(pi+o)).tab[x][i];
            if(*(lim+p+i) <= l+x+1){
            *(lim+p+i) = l+x+1;
            // printf("lime %d %d",p+i,l+x+1);
            }
            }
        }
         }


    }

    else{ // placement invaldie -> plcment aléatoire
    // printf("al�a place");
    p = rand()%10;
    o = rand()%*a;
    st =place(tab,lim,a,pi,p,o);
    if(st == 1){
        return (1);

    }
    }


return (0);}



int choixplace(int** tab,int* lim,int*a,Piece* pi){
    int o,p,b;
    clock_t begin;
    clock_t end;
    printf("Choisir la Colonne\n"); // début prise coordonner de placement
    p = 0;
    o=0;
    begin = clock();
    scanf(" %c",&p);
    scanf(" %d",&o);
    end = clock();
    p = p-65;
    o = o-1;
    if ((end-begin)/1000 > 10){ // temp de prise ->    > nombre de seconde
    printf("\nPlus de 10 s pour repondre");
    p = rand()%10;
    o = rand()%*a;
    }
    // printf("\n %d %d \n",p,o);
    b = place(tab,lim,a,pi,p,o);
    return (b);
}



int verifili(int ** sd,int*lim, int score){   //v�rification ligne et gestion destruction ligne remplie
    int i,x,d,c,compt,ligne;
    compt = 0;
    ligne = 0;
    for(i = 0;i<TAILLE;i++){
        for(x=0;x<TAILLE;x++){ // verification ligne remplie?
            compt = compt+*(*(sd+i)+x);
            //printf(" %d ",compt);
            if(compt == TAILLE){ // cas ligne remplie
                //printf("ILLUMUNT");
                free(*(sd+i));
              for(d=i;d<TAILLE-1;d++){ // gestion remplacment ligne
                *(sd+d)=*(sd+d+1);}
                *(sd+TAILLE-1)= mmalloc(TAILLE*sizeof(int));
				//printf("ILLLUMQ");
				for(c = 0;c<TAILLE;c++){
					*(*(sd+TAILLE-1)+c)= 0;
					*(lim+c) =*(lim+c)-1;
					while(*(lim+c) != 0 && *(*(sd+*(lim+c)-1)+c) == 0 ){
                        *(lim+c) = *(lim+c)-1;}

					}
                i=i-1;
                ligne = ligne+1;
              //printf("arret");

              }
            }
            compt = 0;}
            switch(ligne){ // gestion score
                case 1:
                    score += 40;
                    break;
                case 2:
                    score += 100;
                    break;
                case 3:
                    score += 300;
                    break;
                case 4:
                    score += 1200;
                    break;
                default:
                    break;}
            printf("\n score:%d\n", score);

        return(score);}



void tour(int **sd,int*lm,int*a,Piece*p,int score){
    int b;
    b =0; // condition fin de partie
    while(b == 0){ // boucle d'un tour
    aff_t(sd);
	p = tir(a);
	affichech(p,a);
	b = choixplace(sd,lm,a,p);
	free(p);
    score = verifili(sd,lm,score);
    }
    FILE* file = NULL; // debut gestion des score
	char nom[256];
	int sc = 0;
	int c = EOF + 1;
	if(score < 0) {
		printf("score error\n");
		exit(0);
	}
	file = fopen("highscore.txt","r+"); // ecriture score + nom
	if(file == NULL) {
		printf("opening file error \n");
		exit(1);
	}
	printf("\nentrer votre pseudo: ");
	sc = scanf("%s", nom);
	if(sc != 1) {
		printf("scanf error\n");
		exit(2);
	}
	fseek(file, 0, SEEK_END);
	fprintf(file, "\nname: %s / score: %d",nom, score);
	rewind(file);
	while(c != EOF) { // affichage score
		printf("%c",c);
		c = fgetc(file);
		if(c == EOF) {
			if(feof(file)) {
				break;
			}
			else{
				printf("fgetc error \n");
				exit(1);
			}
		}
	}
	fclose(file);
	exit(0);



}




int main (){
    int score;
    score = 0;
	srand(time(NULL));
    int ** sd = NULL; //initiation pointeur tableau
	int * lm = NULL,*a = NULL; // limite haute
    int v;// initiation nbr form pi�ce
    Piece* p = NULL; // initiation pointeeur pi�ce tire
	a = &v;
	lm = inilim();
	sd = init_game(sd);
    tour(sd,lm,a,p,score);
return 0;}

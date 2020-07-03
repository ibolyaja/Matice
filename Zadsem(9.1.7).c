#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ELEM(mat,i,j) (mat->elem[i*mat->cols+j])
#define MAT_POSDEF 0
#define MAT_POSSEMDEF 1
#define MAT_NOTPOSDEF 2

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

void mat_swap_row(MAT *mat,unsigned int i,unsigned int j) // výmena dvoch riadkov
{
	unsigned int k;
	double temp;
    for (k=0; k<mat->cols; k++) 
    { 
        temp = ELEM(mat,i,k); 
        ELEM(mat,i,k) = ELEM(mat,j,k); 
        ELEM(mat,j,k) = temp; 
    }
}

int mat_gauss(MAT *mat) 
{
	unsigned int i,j,k,i_max,v_max;
	float f;
    for (k=0; k<mat->cols; k++) 
    {  
        // inicializujeme maximalnu hodnotu a index pivota
        i_max = k; 
        v_max = ELEM(mat,i_max,k); 
 
		// najdeme vacsiu hodnotu pivota ak existuje
		for (i=k+1;i<mat->cols;i++)
		{ 
            if (abs(ELEM(mat,i,k))>v_max)
        	{
                v_max = ELEM(mat,i,k);
				i_max = i; 
  			}
		}
        if (!ELEM(mat,k,i_max))
		{ 
            return k; // Matica je singularna 
  		}
  		
		// riadok s najvyššou hodnotou vymenime s aktuálnym riadkom
        if (i_max!=k)
        {
            mat_swap_row(mat,k,i_max); 
  		}
  		
        for (i=k+1;i<mat->cols;i++) 
        { 
            // vynulujeme k-ty prvok riadku a ostatné prvky v k-tom stlpci 
            f = ELEM(mat,i,k)/ELEM(mat,k,k); 
            
            // odcítame f-násobnú hodnotu zodpovedajúceho prvku k-teho riadku
			for (j=k+1;j<mat->cols;j++)
			{ 
                ELEM(mat,i,j)-=ELEM(mat,k,j)*f; 
  			}
            // naplnime lower triangular maticu nulami
            ELEM(mat,i,k) = 0; 
        }     
    } 
    return -1; 
} 

void mat_destroy(MAT *mat)
{
	// uvolnime pamat premennej mat->elem
	free(mat->elem);
	// uvolnime pamat premennej mat
	free(mat);
}

MAT *mat_create_with_type(unsigned int rows, unsigned int cols)
{
	MAT *mat = (MAT*)malloc(sizeof(MAT)); // alokacie pamate
	
	// osetrenie uspesnosti alokacie pamate
	if(mat==NULL)
	{
		return NULL;
	}
	mat->rows=rows;
	mat->cols=cols;
	mat->elem=(float*)malloc(sizeof(float)*(rows*cols)); // alokacie pamate hustej matice
	
	if(mat->elem==NULL)
	{
		free(mat); // uvolnenie pamate v pripade neuspesnosti
		return NULL;
	}
	return mat;
}

void mat_random(MAT *mat)
{
	unsigned int i,j;
	
	for(i=0;i<mat->rows;i++)
	{
		for(j=0;j<mat->cols;j++)
		{
			ELEM(mat,i,j)=((float)rand()/(float)RAND_MAX*2)+(-1); // vygenerovanie nahodneho cisla v intervale <-1,1>
		}
	}
}

void mat_print(MAT *mat)
{
	unsigned int i;
	
	for(i=0; i<mat->rows*mat->cols; i++)
	{
		if(i%mat->cols == 0 && i > 0)
		{
			printf("\n");
		}
		printf("%2.2f ",mat->elem[i]);
	}
	printf("\n");
}

char mat_test_positive_definiteness(MAT *mat)
{
	unsigned int i,j,k,semiflag;
	semiflag=0;
	
	// v pripade, ze matica nie je typu nxn, neexistuje definitnost
	if(mat->rows!=mat->cols)
	{
		return MAT_NOTPOSDEF;
	}
	
	// transformujeme maticu do tvaru upper triangular
	mat_gauss(mat);
	
	for(k=0;k<mat->rows;k++)
	{
		// ak na diagonale sa nachadza zaporny prvok, matica nemoze byt pozitivne definitna 
		if(ELEM(mat,k,k)<0.0f)
		{
			return MAT_NOTPOSDEF;
		}
		// ak na diagonale sa nachadza aspon jedna nula, potom matica bude bud pozitivne semidefinitna alebo nebude pozitivne definitna
		if(ELEM(mat,k,k)==0.0f)
		{
			semiflag=1;
		}
	}
	// ak sme tu, potom na diagonale upravenej matice sa nenachadzal zaporny prvok
	if(semiflag)
	{
		return MAT_POSSEMDEF; // nasli sme aspon jednu nulu ==> matica je pozitivne semidefinovana
	}
	// kazdy prvok na diagonale bol kladny ==> matica je pozitivne definovana
	return MAT_POSDEF;
}

int main(void)
{
	srand(time(NULL));
	MAT *m=mat_create_with_type(5,5);
	mat_print(m);
	mat_random(m);
	
	printf("\n");
	mat_print(m);
	char result=mat_test_positive_definiteness(m);
	
	printf("%i\n",result);
	printf("\n");
	mat_print(m);
	
	return 0;
}


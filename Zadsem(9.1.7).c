#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define ELEM(mat,i,j) (mat->elem[i*mat->cols+j])

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;


void mat_destroy(MAT *mat)
{
	free(mat->elem);
	free(mat);
}

MAT *mat_create_with_type(unsigned int rows, unsigned int cols)
{
	MAT *mat = (MAT*)malloc(sizeof(MAT));
	if(mat==NULL)
	{
		return NULL;
	}
	mat->rows=rows;
	mat->cols=cols;
	mat->elem=(float*)malloc(sizeof(float)*(rows*cols));
	if(mat->elem==NULL)
	{
		free(mat);
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
			ELEM(mat,i,j)=((float)rand()/(float)RAND_MAX*2)+(-1);
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
		printf("%f",mat->elem[i]);
	}
	printf("\n");
}

char mat_test_positive_definiteness(MAT *mat)
{
	return 'a';
}


int main(void)
{
	char mat_test_positive_definiteness(MAT *mat);
	MAT *m=mat_create_with_type(5,5);
	mat_print(m);
	mat_random(m);
	mat_print(m);
	return 0;
}


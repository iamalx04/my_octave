// Copyright Istrate Alexandru-Daniel 314CAa 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// definesc constanta pentru a evita overflow-ul
#define modulo 10007

// functia de adunare a doua matrice
int **sum_mat(int **m1, int **m2, int dim)
{
int **sum;
sum = (int **)malloc(dim * sizeof(int *));
for (int i = 0; i < dim; i++)
	sum[i] = (int *)malloc(dim * sizeof(int));

for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++) {
		sum[i][j] = (m1[i][j] + m2[i][j]) % modulo;
		if (sum[i][j] < 0)
			sum[i][j] = sum[i][j] + modulo;
	}
return sum;
}

// functia de scadere a doua matrice
int **dif_mat(int **m1, int **m2, int dim)
{
int **dif;
dif = (int **)malloc((dim) * sizeof(int *));
for (int i = 0; i < dim; i++)
	dif[i] = (int *)malloc((dim) * sizeof(int));

for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++) {
		dif[i][j] = (m1[i][j] - m2[i][j]) % modulo;
		if (dif[i][j] < 0)
			dif[i][j] = dif[i][j] + modulo;
		}
return dif;
}

// citire matrice in memorie
void citire_mat(int ***vecpoint, int *n, int d1, int d2)
{
int **mat = (int **)malloc(d1 * sizeof(int *));
for (int i = 0; i < d1; i++) {
	mat[i] = (int *)malloc(d2 * sizeof(int));
	for (int j = 0; j < d2; j++)
		scanf("%d", &mat[i][j]);
}

vecpoint[*n] = mat;
*n = *n + 1;
}

// afisare matrice
void afisare_mat(int ***vect, int nr, int nr_linii, int nr_coloane)
{
int **mat;
mat = vect[nr];
for (int j = 0; j < nr_linii; j++) {
	for (int k = 0; k < nr_coloane; k++)
		printf("%d ", mat[j][k]);
printf("\n");
}

//
}

// redimensionarea matricei
void redim_mat(int ***vect, int nr, int *nr_linii, int *nr_coloane, int n)
{
int l1, c1, *v, *v1, **new = NULL;
//citirea elementelor dupa care se face redimensionarea
scanf("%d", &l1);
v = (int *)malloc(l1 * sizeof(int));
for (int i = 0; i < l1; i++)
	scanf("%d", &v[i]);
scanf("%d", &c1);
v1 = (int *)malloc(c1 * sizeof(int));
for (int i = 0; i < c1; i++)
	scanf("%d", &v1[i]);
if (nr >= n || nr < 0) {
	printf("No matrix with the given index\n");
} else {
	//redimensionarea prin copierea elementelor in matricea noua
	new = (int **)malloc(l1 * sizeof(int *));
	for (int i = 0; i < l1; i++) {
		new[i] = (int *)malloc(c1 * sizeof(int));
		for (int j = 0; j < c1; j++)
			new[i][j] = vect[nr][v[i]][v1[j]];
	}
for (int i = 0; i < *nr_linii; i++)
	free(vect[nr][i]);
free(vect[nr]);
*nr_linii = l1;
*nr_coloane = c1;
vect[nr] = new;
}

free(v);
free(v1);
}

// inmultirea matricelor
void inmultire_mat(int **left, int **right, int ***rez,
				   int l1, int c1, int c2)
{
	int **rezultat = *rez;
	for (int i = 0; i < l1; i++)
		for (int j = 0; j < c2; j++) {
			rezultat[i][j] = 0;
			for (int k = 0; k < c1; k++)
				rezultat[i][j] = (rezultat[i][j] + (left[i][k] * right[k][j])
			% modulo) % modulo;

			if (rezultat[i][j] < 0)
				rezultat[i][j] = rezultat[i][j] + modulo;
		}
}

// sortarea matricelor
void sort_mat(int ***vect, int *linii, int *coloane, int n)
{
int cpy, **cpy1;
int *s; // vector de sume
s = (int *)malloc(n * sizeof(int));
//calcularea sumelor
for (int i = 0; i < n; i++) {
	s[i] = 0;
	for (int j = 0; j < linii[i]; j++)
		for (int k = 0; k < coloane[i]; k++)
			s[i] = s[i] + vect[i][j][k];

	s[i] = s[i] % modulo;

	if (s[i] < 0)
		s[i] = s[i] + modulo;
}

// ordonarea propriu-zisa a matricelor
for (int i = 0 ; i < n - 1; i++)
	for (int j = i + 1 ; j < n; j++)
		if (s[i] > s[j]) {
			cpy = s[i];
			s[i] = s[j];
			s[j] = cpy;
			cpy1 = vect[i];
			vect[i] = vect[j];
			vect[j] = cpy1;
			int cp = linii[i];
			linii[i] = linii[j];
			linii[j] = cp;
			int cp1 = coloane[i];
			coloane[i] = coloane[j];
			coloane[j] = cp1;
		}

free(s);
}

// transpusa unei matrice
void transp_mat(int ***vect, int nr, int *d1, int *d2)
{
int **mat = vect[nr], **aux;
aux = (int **)malloc(*d2 * sizeof(int *));
//copierea elementelor in matricea transpusa
for (int i = 0; i < *d2; i++) {
	aux[i] = (int *)malloc(*d1 * sizeof(int));
		for (int j = 0; j < *d1; j++)
			aux[i][j] = mat[j][i];
}

for (int i = 0; i < *d1; i++)
	free(vect[nr][i]);
free(vect[nr]);
vect[nr] = aux;
int cp = *d2;
*d2 = *d1;
*d1 = cp;
}

// functia de inmultire a doua matrice independente de vectorul tridimensional
void inmultire_mat2(int **m1, int **m2, int **rez, int d)
{
for (int i = 0; i < d; i++)
	for (int j = 0; j < d; j++) {
		rez[i][j] = 0;
		for (int k = 0; k < d; k++) {
			rez[i][j] = (rez[i][j] + (m1[i][k] * m2[k][j]) % modulo) % modulo;
			if (rez[i][j] < 0)
				rez[i][j] = rez[i][j] + modulo;
		}
	}
}

// ridicarea la putere a unei matrice
void putere_mat(int **mat, int **rez, int dim, int p)
{
int **mat_aux;
if (p == 0) {
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			if (i == j)
				rez[i][j] = 1;
			else
				rez[i][j] = 0;
} else {
	if (p % 2 == 0) {
		mat_aux = (int **)malloc(dim * sizeof(int *));
		for (int i = 0; i < dim; i++)
			mat_aux[i] = (int *)malloc(dim * sizeof(int));
		putere_mat(mat, mat_aux, dim, p / 2);
		inmultire_mat2(mat_aux, mat_aux, rez, dim);
		for (int i = 0; i < dim; i++)
			free(mat_aux[i]);
		free(mat_aux);
		} else {
			mat_aux = (int **)malloc(dim * sizeof(int *));
			for (int i = 0; i < dim; i++)
				mat_aux[i] = (int *)malloc(dim * sizeof(int));
			putere_mat(mat, mat_aux, dim, p - 1);
			inmultire_mat2(mat_aux, mat, rez, dim);
			for (int i = 0; i < dim; i++)
				free(mat_aux[i]);
			free(mat_aux);
			}
	}
}

// eliberarea memoriei unei singure matrice
void free_mat(int ***vect, int *n, int nr, int *l, int *c)
{
// mutarea matricei la final
for (int i = nr; i < *n - 1; i++) {
	int **aux = vect[i];
	vect[i] = vect[i + 1];
	vect[i + 1] = aux;
	int a_l = l[i];
	l[i] = l[i + 1];
	l[i + 1] = a_l;
	int a_c = c[i];
	c[i] = c[i + 1];
	c[i + 1] = a_c;
}

// eliberarea memoriei si modificarea numarului total de matrice
for (int i = 0; i < l[*n - 1]; i++)
	free(vect[*n - 1][i]);
free(vect[*n - 1]);
*n = *n - 1;
}

// eliberarea memoriei unei matrice independenta de vectorul tridimensional
void free_mat2(int **mat, int dim)
{
for (int i = 0; i < dim; i++)
	free(mat[i]);
free(mat);
}

// initializarea inmultirii matricelor
void inmultire(int ****vec, int **lines, int **columns, int *n)
{
	int index1, index2;
	int k = *n;

	scanf("%d", &index1);
	scanf("%d", &index2);

	if (index1 >= *n || index2 >= *n || index1 < 0 || index2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	if ((*columns)[index1] != (*lines)[index2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	*lines = (int *)realloc((*lines), (k + 1) * sizeof(int));

	*columns = (int *)realloc((*columns), (k + 1) * sizeof(int));

	*vec = (int ***)realloc(*vec, (k + 1) * sizeof(int **));

	(*lines)[*n] = (*lines)[index1]; // pune numarul de linii in locatie
	(*columns)[*n] = (*columns)[index2]; // pune numarul de coloane in locatie

	int **left = (*vec)[index1];
	int **right = (*vec)[index2];
	int **rezultat;

	rezultat = malloc((*lines)[index1] * sizeof(int *));

	for (int i = 0 ; i < (*lines)[index1] ; i++)
		rezultat[i] = malloc((*columns)[index2] * sizeof(int));

	inmultire_mat(left, right, &rezultat, (*lines)[index1],
				  (*columns)[index1], (*columns)[index2]);
	(*vec)[k] = rezultat;
	(*n)++;
}

/*
// Inmultirea prin algoritmul lui Strassen

// Functia recursiva
void strassen_rec(int **m1, int **m2, int dim, int **rez)
{
if(dim==1){
	int **mat = (int **) malloc(dim * sizeof(int*));
	for(int i = 0; i < dim; i++)
		mat[i] = (int *)malloc(dim * sizeof(int));
	mat[0][0] = (m1[0][0] * m2[0][0]) % modulo;
	if(mat[0][0] < 0)
	mat[0][0]+= modulo;
	rez=mat;
} else {
	int ***matrici;
	matrici = (int ***)malloc(21 * sizeof(int**));
	for (int i = 0; i < 8; i++) {
		matrici[i] = (int **)malloc(dim/2 * sizeof(int *));
		for (int j = 0; j < dim/2; j++)
			matrici[i][j] = (int *)malloc(dim/2 * sizeof(int *));
	}
	for(int j = 0; j < dim / 2; j++)
		for(int k = 0; k < dim / 2; k++) {
			matrici[0][j][k] = m1[j][k]; //A1
			matrici[1][j][k] = m1[j][k+dim/2]; //A2
			matrici[2][j][k] = m1[j+dim/2][k]; //A3
			matrici[3][j][k] = m1[j+dim/2][k+dim/2]; //A4
			matrici[4][j][k] = m2[j][k]; //B1
			matrici[5][j][k] = m2[j][k+dim/2]; //B2
			matrici[6][j][k] = m2[j+dim/2][k]; //B3
			matrici[7][j][k] = m2[j+dim/2][k+dim/2]; //B4
			}
	printf("1\n");
	matrici[19] = sum_mat(matrici[0], matrici[3], dim/2);
	matrici[20] = sum_mat(matrici[4], matrici[7], dim/2);
	strassen_rec(matrici[19], matrici[20], dim/2, matrici[12]); //M1
	free_mat2(matrici[19], dim/2);
	free_mat2(matrici[20], dim/2);
	matrici[19] = sum_mat(matrici[2], matrici[3], dim/2);
	strassen_rec(matrici[19], matrici[4], dim/2, matrici[13]); //M2
	free_mat2(matrici[19], dim/2);
	matrici[19] = dif_mat(matrici[5], matrici[7], dim/2);
	strassen_rec(matrici[0], matrici[19], dim/2, matrici[14]); //M3
	free_mat2(matrici[19], dim/2);
	matrici[19] = dif_mat(matrici[6], matrici[4], dim/2);
	strassen_rec(matrici[3], matrici[19], dim/2, matrici[15]); //M4
	free_mat2(matrici[19], dim/2);
	matrici[19] = sum_mat(matrici[0], matrici[1], dim/2);
	strassen_rec(matrici[19], matrici[7], dim/2, matrici[16]); //M5
	free_mat2(matrici[19], dim/2);
	matrici[19] = dif_mat(matrici[2], matrici[0], dim/2);
	matrici[20] = sum_mat(matrici[4], matrici[5], dim/2);
	strassen_rec(matrici[19], matrici[20], dim/2, matrici[17]); //M6
	free_mat2(matrici[19], dim/2);
	free_mat2(matrici[20], dim/2);
	matrici[19] = dif_mat(matrici[1], matrici[3], dim/2);
	matrici[20] = sum_mat(matrici[6], matrici[7], dim/2);
	strassen_rec(matrici[19], matrici[20], dim/2, matrici[18]); //M7
	free_mat2(matrici[19], dim/2);
	free_mat2(matrici[20], dim/2);
	matrici[9] = sum_mat(matrici[14], matrici[16], dim/2); //C2
	matrici[10] = sum_mat(matrici[13], matrici[15], dim/2); //C3
	matrici[19] = sum_mat(matrici[12], matrici[15], dim/2);
	matrici[20] = dif_mat(matrici[19], matrici[16], dim/2);
	matrici[8] = sum_mat(matrici[20], matrici[18], dim/2); //C1
	free_mat2(matrici[19], dim/2);
	free_mat2(matrici[20], dim/2);
	matrici[19] = dif_mat(matrici[12], matrici[13], dim/2);
	matrici[20] = dif_mat(matrici[19], matrici[14], dim/2);
	matrici[11] = sum_mat(matrici[20], matrici[17], dim/2); //C4
	free_mat2(matrici[19], dim/2);
	free_mat2(matrici[20], dim/2);

	for (int i = 0; i < dim/2; i++)
		for (int j = 0; j < dim/2; j++)
			rez[i][j] = matrici[8][i][j];

	for (int i = 0; i < dim/2; i++)
		for (int j = dim/2; j < dim; j++)
			rez[i][j] = matrici[9][i][j - (dim / 2)];

	for (int i = dim/2; i < dim; i++)
		for (int j = 0; j < dim/2; j++)
			rez[i][j] = matrici[10][i - (dim / 2)][j];

	for (int i = dim/2; i < dim; i++)
		for (int j = dim/2; j < dim; j++)
			rez[i][j] = matrici[11][i - (dim /2)][j - (dim / 2)];

	for (int i = 0; i < 21; i++) { //eliberarea totala a memoriei
		for (int j = 0; j < dim; j++)
		free(matrici[i][j]);
	free(matrici[i]);
}
	free(matrici);
}

}

// Functia de initializare
void strassen(int ***v, int *linii, int *coloane, int *n)
{
int nr_mat, nr_mat1, dim, **rezultat = NULL;
scanf("%d %d", &nr_mat, &nr_mat1);
if (nr_mat >= *n || nr_mat1 >= *n || nr_mat < 0 || nr_mat1 < 0) {
	printf("No matrix with the given index\n");
	return;
}
if (coloane[nr_mat] != linii[nr_mat1]) {
	printf("Cannot perform matrix multiplication\n");
	return;
}

dim = linii[nr_mat];

strassen_rec(v[nr_mat], v[nr_mat1], dim, rezultat);

}
*/

int main(void)
{
int ***v, *linii, *coloane, *linii1, *coloane1, ***v1; char op;
int nr_mat, n = 0, d1, d2, putere = 0;
v = (int ***)malloc(sizeof(int **)); linii = (int *)malloc(sizeof(int));
coloane = (int *)malloc(sizeof(int)); scanf(" %c", &op);
// meniul pentru introducerea comenzii
while (op != 'Q') {
	if (op == 'L') { // introducere matrice in memorie
		scanf("%d%d", &d1, &d2);
		linii[n] = d1; coloane[n] = d2;
		citire_mat(v, &n, d1, d2);
		linii1 = (int *)malloc((n + 1) * sizeof(int));
		for (int i = 0; i < n; i++)
			linii1[i] = linii[i];
		free(linii); linii = linii1;
		coloane1 = (int *)malloc((n + 1) * sizeof(int));
		for (int i = 0; i < n; i++)
			coloane1[i] = coloane[i];
		free(coloane); coloane = coloane1;
		v1 = (int ***)malloc((n + 1) * sizeof(int **));
		for (int i = 0; i < n; i++)
			v1[i] = v[i];
		free(v); v = v1;
	} else if (op == 'D') {// afisare dimensiuni
		scanf("%d", &nr_mat);
		if (nr_mat >= n || nr_mat < 0)
			printf("No matrix with the given index\n");
		else
			printf("%d %d\n", linii[nr_mat], coloane[nr_mat]);
	} else if (op == 'P') { // afisare matrice
		scanf("%d", &nr_mat);
		if (nr_mat >= n || nr_mat < 0)
			printf("No matrix with the given index\n");
		else
			afisare_mat(v, nr_mat, linii[nr_mat], coloane[nr_mat]);
	} else if (op == 'C') { // redimensionare
		scanf("%d", &nr_mat);
		redim_mat(v, nr_mat, &linii[nr_mat], &coloane[nr_mat], n);
	} else if (op == 'M') { // inmultirea matricilor
		inmultire(&v, &linii, &coloane, &n);
	} else if (op == 'O') { // sortarea matricilor
		sort_mat(v, linii, coloane, n);
	} else if (op == 'T') { // transpusa unei matrice
		scanf("%d", &nr_mat);
		if (nr_mat >= n || nr_mat < 0)
			printf("No matrix with the given index\n");
		else
			transp_mat(v, nr_mat, &linii[nr_mat], &coloane[nr_mat]);
	} else if (op == 'R') { // ridicarea la putere
		// verificarea datelor citite
		scanf("%d %d", &nr_mat, &putere);
		if (nr_mat >= n || nr_mat < 0) {
			printf("No matrix with the given index\n");
		} else if (putere < 0) {
			printf("Power should be positive\n");
			} else if (linii[nr_mat] != coloane[nr_mat]) {
				printf("Cannot perform matrix multiplication\n");
				} else if (putere != 1) {
					int liniimat = linii[nr_mat];
					int **mat_putere = (int **)malloc(liniimat * sizeof(int *));
					for (int i = 0; i < liniimat; i++)
						mat_putere[i] = (int *)malloc(liniimat * sizeof(int));
					putere_mat(v[nr_mat], mat_putere, liniimat, putere);
					for (int i = 0; i < liniimat; i++)
						free(v[nr_mat][i]);
					free(v[nr_mat]); v[nr_mat] = mat_putere;
					}
	} else if (op == 'F') { // eliberarea memoriei pentru o singura matrice
		scanf("%d", &nr_mat);
		if (nr_mat >= n || nr_mat < 0)
			printf("No matrix with the given index\n");
		else
			free_mat(v, &n, nr_mat, linii, coloane);
	} else if (op == 'S') { // inmultirea matricilor cu algortimul lui Strassen
		// strassen(v, linii, coloane, &n);
	} else {
		printf("Unrecognized command\n");
	}
	scanf(" %c", &op);
}

for (int i = 0; i < n; i++) { // eliberarea totala a memoriei
	for (int j = 0; j < linii[i]; j++)
		free(v[i][j]);
	free(v[i]);
}

free(v); free(linii); free(coloane); return 0;
}

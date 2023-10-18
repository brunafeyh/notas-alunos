#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100
#define MAXC 100
#define MAXB 10

typedef struct {
   int n; 
   float v[MAXB]; //vetor de notas
   float media;
} VETOR;

typedef struct { //struct maior para guardar o nome e as notas
   char nome[MAXC]; 
   VETOR notas; //segunda struct para guardar as notas, n e media
} ALUNO;

void zerarvet (VETOR *vet) {
  int i;
  for (i = 0; i < vet->n; i++)
    vet->v[i] = 0; //zerando o vetor
}

void calcmediabim (ALUNO va[], int na, VETOR *mg) {
  int i, j; float s;
  zerarvet (mg); //zerar o vetor pois ele tem lixo no começo
  mg->n = va[0].notas.n; //o tamanho de mg vau ser o n de bimestres
  for (j = 0; j < mg->n; j++) { //passando as colunas
    for (s = i = 0; i < na; i++)  //passando as linhas
      s += va[i].notas.v[j]; //soma recebe v[j] na linha i
    mg->v[j] = s/na;  //v[j] recebe soma dividido por numero de alunos
  }
}

void calcmediavetor (VETOR *p) { //struct vetor notas
  int i; float s;
  for (s=i=0; i < p->n; i++)  //de i até n
    s += p->v[i]; //s recebe nota no indice do vetor
  
  p->media = s/p->n; //media do aluno recebe a soma dividido pelo n de bimestres
}

void calcmediaaluno (ALUNO va[], int na) {
  int i;
  for (i = 0; i < na; i++) //na é o n de alunos
    calcmediavetor (&va[i].notas);
    //cada struct notas em struct va[i]
}

void pheader (int nb) {
  int i;
  printf ("NUM %-20s", "ALUNO");  //estrutura do cabeçario
  for (i = 1; i <= nb; i++)
    printf ("%4s%d", "N", i);
  printf ("   Med\n");
}

void pvetor (VETOR *p) {
   int i;
   for (i = 0; i < p->n; i++)  //para cada coluna
     printf ("%5.1f", p->v[i]); //printa as notas
   printf ("%5.1f\n", p->media); //printa a media
}

void pmbimestral (VETOR *p) {
   printf ("%-25s", "MEDIA BIMESTRAL");
   pvetor (p); //printa a struct bimestral
}

void pdados (ALUNO *p) { //ponteiro pois é a struct no indice i
    printf ("%-20s ", p->nome); //printa o nome
    pvetor (&p->notas); //printa as notas
}

void palunos (ALUNO va[], int na) {
  int i; 
  pheader (va[0].notas.n);
  for (i = 0; i < na; i++) { //para cada linha
    printf ("%3d ", i+1); //printa o numero do aluno
    pdados (&va[i]); //printa os dados do aluno na struct va[i]
  }
}

void getnotas (ALUNO *p) {
   int i;
   for (i = 0; i < p->notas.n; i++)  
     scanf ("%f", &p->notas.v[i]);
   
   scanf ("%*c"); //proximo que vai ser lido em lerdados é uma struct
   // o i nessa função vai de 0 ao n de bimestres n lendo as notas em cada coluna
}

void lerdados (ALUNO va[], int *pn) {
  int i, nb;
  scanf ("%d%*c", &nb); //lendo nb que é o n de bimestres
  for (i = 0; scanf ("%[^;]%*c", va[i].nome) != EOF; i++) {
    //para i começando em 0 vc vai ler uma tring e guardar em va[i].nome enquanto ela é diferente de EOF
    va[i].notas.n = nb; //n recebe nb
    getnotas (&va[i]); //le as notas
  }
  *pn = i; //n de alunos recebe i

  //o 1 nessa função vai de 0 a pn percorendo as linhas da struct guardando o nome
}

int main() {
  ALUNO va[MAXL]; int na; //va é um vetor de struct com indice para cada aluno
  VETOR mbim; //na é a qde de alunos e mbim é uma struct do tipo VETOR que guarda as notas bimestrais

  lerdados       (va, &na); //lendo va que é um vetor e na ponteiro pois vai ser gerado na função
  calcmediaaluno (va, na);
  calcmediabim   (va, na, &mbim);
  calcmediavetor (&mbim);
  palunos        (va, na);
  pmbimestral    (&mbim);

  return 0;

}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


//Declarons des variables

sem_t semMen;
sem_t semWome;
sem_t semaCapacite;

int nombre_homme;
int nombre_femme;

pthread_t thread_Men_Ids[];
pthread_t thread_Women_Ids[];
pthread_t thread_P_Ids[];


int genrechrch=1;//Pour controler le genre dans la bouche (1 pour femme et 0 pour homme)
pthread_mutex_t mutex_semCherch= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_genrecherch= PTHREAD_MUTEX_INITIALIZER;
/**
Cette variable contiendra les genres de ceux qui sont dans la douche.
Si un homme rentre, il laissera 1 et 0 pour femme. Il ne doit pas avoir deux des ces chiffres dans le tableau
**/
int tab_entrer[];


int verifier_tab_enter(){

  return 1;
}




//Quand les hommes entrent dans la douche

void man_enter_in_bathroom(){
  //Recuperons le numero du garcon qui rentre dans la douche
  int id=get_thread_id(pthread_self(),0);
  printf("HOMME %d essaie de rentrer \n",id );

  if (genrechrch==1) {//Verifions s ya un homme dans la douche
    /* code */
      //Il faut nous assurer que c'est un seul qui change le genre
    pthread_mutex_lock(&mutex_genrecherch);
    genrechrch=1;

    pthread_mutex_unlock(&mutex_genrecherch);

      //Verrouillons pour etre sur que ce un seul thred qui effectue cette operation
      pthread_mutex_lock(&mutex_semCherch);
     printf("HOMME %d entre \n",id );
     //Deverrouillons maintenant
     pthread_mutex_unlock(&mutex_semCherch);

  }else{
    while (genrechrch==2) {//Ca veut dire que ya une femme dedans. Donc il ne peut pas entrer . Il faut quil patiente
      /* code */

    }
    man_enter_in_bathroom();
    //man_enter_in_bathroom();
      //man_enter_in_bathroom();
  }

}


void man_leave_bathroom(){
  //Recuperons le numero du garcon qui rentre dans la douche
  int id=get_thread_id(pthread_self(),0);
  printf("Homme thread %d quitte la douche\n",id );
}


void person_use_bathroom(int genre){
  if (genre==1) {
    /* code */
    printf("Femme %d thread utlse la douche ...\n",get_thread_id(pthread_self(),1) );
  //  sleep(2);
  }else if (genre==0) {

    /* code */
    printf("Homme thread %d utilise la douche ...\n",get_thread_id(pthread_self(),0) );
    //sleep(2);
  }
  //sleep(1);
  wait(1);
}



void women_enter_in_bathroom(){
  //Recuperons le numero dde la femme qui rentre dans la douche
  int id=get_thread_id(pthread_self(),1);
    printf("FEMME THREAD %d essa de rentrer ...\n",id );
  if (genrechrch==2) {
    /* code */

    pthread_mutex_lock(&mutex_semCherch);
    printf("FEMME THREAD %d Entre ...\n",id );

    pthread_mutex_unlock(&mutex_semCherch);
  }else{
    //women_enter_in_bathroom();
    while (genrechrch==1) {//Dans ce cas il ya un homme dans la douche.Elle doit attendre que lees hommes sortent avant de pouvoir entrer
    //Ne ren fare et attendre que genrechrch sot 2
    }
    women_enter_in_bathroom();
  }


}
void woman_leave_bathroom(){
  //Recuperons le numero dde la femme qui rentre dans la douche
  int id=get_thread_id(pthread_self(),1);

  printf("Femme thread %d quitte la doche....\n",id );

  //pthread_mutex_unlock(&mutex_semCherch);
}



void Work(int genre){

  //Verifions si cest un homme ou passé

  if (genre==0) {//Cest un homme
    /* code */

    printf("Thread homme %d  works ...\n",get_thread_id(pthread_self(),0));//get_thread_id(pthread_self(),0) );

  }else if (genre==1) {//Cest une femme
    /* code */

    printf("Female Thread  %d works ... \n",get_thread_id(pthread_self(),1));//,get_thread_id(pthread_self(),1));
  }
  //printf("I'm a main \n");
}

int get_thread_id(pthread_t thread,int genre){

  int i;
  if (genre==0) {
    /* code */

    for (i=0;i <nombre_homme; i++) {
      /* code */
      //Verifier sil sagit du meme thread
      if (pthread_equal(thread,thread_Men_Ids[i])) {
        /* code */
        return i;
      }
    }

  }else if (genre==1) {
    /* code */

    for (i = 0; i < nombre_femme; i++) {
      /* code */

      if (pthread_equal(thread,thread_Women_Ids[i])) {
        /* code */
        return i;
      }
    }
  }
}





//Woman thread
void* Woman(void *arg){

  int id=(int)arg;
  thread_Women_Ids[id]=pthread_self();


  while (1) {
    /* code */
    //Working
    Work(1);
    women_enter_in_bathroom();
    person_use_bathroom(1);
    woman_leave_bathroom();
    //use the bathroom
  }
}

//Man thread
void* Man(void *arg){//arg permettra dobtenir le numero du thread homme
  int th_id_num=(int)arg;
  //printf("APRES %d\n",th_id_num );

  thread_Men_Ids[th_id_num]=pthread_self();//Obtenir le ID du Thread
    //printf("AVSNT %d\n",th_id_num );
  while (1) {
    /* code */

    //Working
    Work(0);
    man_enter_in_bathroom();
    person_use_bathroom(0);
    man_leave_bathroom();

    //use the bathroom
  }
}






int main(int argc, char **argv) {
  /* code */
  int i,j,k,l;

  int *thread_id_men;
  int *thread_id_women;
  pthread_t thread_men[k];
  pthread_t thread_women[l];
  pthread_attr_t attribs;

  //Initialisation des mutex
  pthread_mutex_init(&mutex_genrecherch,0);
  pthread_mutex_init(&mutex_semCherch,0);

  //attributs
  pthread_attr_init(&attribs);
  int nb_men;
  int nb_wmen;
if (argc>2) {
  if (atoi(argv[1])>=1 && atoi(argv[2])>=1) {
    /* code */

    nb_men=atoi(argv[1]);
    nb_wmen=atoi(argv[2]);
  }else{

    do {
      /* code */

      printf("Erreur!! veuillez reessayer svp!\n");
      printf("Saisir nombre d'hommes :");
      scanf("%d",&nb_men );

      printf("Saisir nombre de femmes :");
      scanf("%d",&nb_wmen );
    } while(nb_men<=0 && nb_wmen<=0);
  }
}else{
  do {
    /* code */

    printf("Erreur!! veuillez reessayer svp!\n");
    printf("Saisir nombre d'hommes :");
    scanf("%d",&nb_men );
    printf("Saisir nombre de femmes :\n");
    scanf("%d",&nb_wmen );
  } while(nb_men<=0 && nb_wmen<=0);
}

    /* code */

  //  printf("OKKKK!!!\n");
    //printf("%s\n",argv[0] );


    nombre_femme=nb_wmen;
    nombre_homme=nb_men;
    thread_Men_Ids[nombre_homme];
    thread_Women_Ids[nombre_femme];
    tab_entrer[nombre_femme+nombre_homme];

  //  printf("%d\n",nb_wmen );

    //Creons les threads femmes
    for ( j = 0; j < nb_wmen; j++) {
      //printf("FFFFFF\n" );
      /* code */
      //thread_id_women[j]=j;
      //printf("%d WOMEN  \n",nb_wmen );

      pthread_create(&thread_women[j],&attribs,Woman,(void*)j);
      //  pthread_join(thread_women[j],NULL);
    //  printf("fdddfgfgdf\n" );
    }
      //Creons les threads hommes
    for(i=0;i<nb_men;i++){

    //  printf("%d Men\n",nb_men );
      //thread_id_men[i]=i;

      pthread_create(&thread_men[i],&attribs,Man,(void*)i);
      //pthread_join(thread_men[i],NULL);
      //Joindre le thread cree

    }

    for(i=0;i<nb_men;i++){


      pthread_join(thread_men[i],NULL);
      }

      for ( j = 0; j < nb_wmen; j++) {

          pthread_join(thread_women[j],NULL);
      }
  //eturn 0;
}

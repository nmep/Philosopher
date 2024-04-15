
# Philosopher

## Disclamer
Je ne certifie pas que le projet est parfait et je pense qu'a mon niveau il y a des notions que je n'ai pas completement saisis.  
Je fais ce readme parce que c'est un projet qui me plait et je comprend qu'il ne soit pas friendly.  
Mais ce n'est pas une raison pour ne pas pousser la reflection des sujets qui ne sont pas evident et ecouter les bruits de couloir.  
Mais si tu souhaite apprendre le sujet par toi meme alors tu peux quitter.
Je m'excuse a l'avance s'il y a des fautes et je n'ai pas d'accent avec mon clavier.  

## Table des matières
- [Resume du projet](##Resume-du-projet)
----------------
- [Mandatory](#Mandatory)
- [Fonction autorisees](##Fonction-autorisees)
- [Definition / Prototype  [sauf mutex] 1/2](Definition-/-Prototype-[sauf-mutex]-1/2)
- [Data race](#Data-race)
- [Variable atomique](#Variable-atomique)
- [Definitions / prototype [mutex] 2/2](#Definitions-/-prototype-[mutex]-2/2)
- [Pilier du projet qui m'ont embete](#Pilier-du-projet-qui-m'ont-embete)
- [1) la gestion du temp](#1-la-gestion-du-temp)
- [2) Gestion des fourchettes](#2-Gestion-des-fourchettes)
- [2.1) Dead lock:](#2.1-Dead-lock)
- [2.2) Solution propose de gestion des fourchettes](#2.2-Solution-propose-de-gestion-des-fourchettes)
- [3) Les mutex / data race](#3-Les-mutex-/-data-race)
- [4) La muerta](#4-La-muerta)
-----------------
- [Bonus](#Bonus)
- [Regles du sujet](#Regles-du-sujet)
- [Fonctions autorisees](#Fonctions-autorisees)
- [Definition / Protoype](#Definition-/-Protoype)
- [Semaphore](#Semaphore)
- [la muerta bonus](#la-muerta-bonus)
- [Bonus](#Bonus-leak-(que-j'ai-rencontre-ca-ne-veut-pas-dire-que-vous-n'allez-pas-reussir))
- [Semaphore](#Semaphore)

## Resume du projet
Realiser le **diner des philosophes** qui representerait x philosophes avec comme parametres:  
&emsp;- Nombre de philosophes: (millisecondes)  
&emsp;- Temp pour mourrir: (millisecondes)  
&emsp;- Temp pour manger: (millisecondes)  
&emsp;- Temp pour dormir: (millisecondes)  
&emsp;- *Nombre de repas*: (optionnel)  
(Si le nombre de repas n'est pas precise alors les philos devront realiser leurs routine (reflechir manger dormir ...ect) jusqu'a un temps non determine ou, qu'un philo soit mort).

Il faut les faires manger *Nombre de repas* fois et s'il meurt alors tout le monde s'arretent.  

Au millieu de la table il y a un grand plat de spaghetti.  
Chaque philos posedent une fourchette et ont besoin de **deux fourchettes pour manger** il faudrait donc qu'ils utilisent leurs fourchette et la fourchette du voisin de droite pour manger.


![representation du dinner des philosophes]()

Donc:  
* Philo x Reflechit temps que ses fourchettes ne sont pas dispo
* Philo x Arrive et prend sa fourchette de gauche et celle de droite
* Philo x Mange
* Philo x Repose ses fourchettes
* Philo x Va dormir


# Mandatory

## Fonction autorisees
memset  
printf  
malloc  
free  
write  
usleep  
gettimeofday  
pthread_create  
pthread_detach  
pthread_join  
pthread_mutex_init  
pthread_mutex_destroy  
pthread_mutex_lock  
pthread_mutex_unlock

(Elles ont toute etaient utilise sauf pthread_detach et memset car je n'en ai pas trouve l'interet, je ne parlerais que de celles utilise et pthread_detach). 

## Definition / Prototype  [sauf mutex] 1/2

- **gettimeofday**  
    **int gettimeofday(struct timeval \*tv, struct timezone \*tz)**  

    struct timeval {  
    &emsp;&emsp;time_t      tv_sec;&emsp;&emsp;/* seconds */  
    &emsp;&emsp;suseconds_t tv_usec;&emsp;&emsp;/* microseconds */  
    };  

    Va prendre le temps T en seconde et en millisecondes durant l'appel systeme et nous le donner dans une variable de type *struct timeval <nom de la variable>*  
    **Example:**
    ```c
    #include <sys/time.h>
    #include <stdio.h>

    // struct	timeval
    // {
    // 	time_t		tv_sec;     /* seconds */
    // 	suseconds_t	tv_usec;    /* microseconds */
    // };

    int	main(int ac, char **av)
    {
        struct timeval	tv;

        gettimeofday(&tv, NULL);
        printf("temps en seconde = %ld\n", tv.tv_sec);
        printf("temps en micro seconde = %ld\n", tv.tv_usec);
    }
    ```
- **usleep**  
    **int usleep(useconds_t usec);**  

    Va suspendre l'execution du thread courant pour **au moins usec microsecondes**  
    Le "**au moins**" est a garder sous le coude ont le reverra plus tard...

*Pour les fonctions concernant les threads je recommande fortement la chaine youtube code vault qui est une bonne entree en la matiere -> [playlist de thread](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)*

- **pthread_create**  
    **int pthread_create(pthread_t \*thread, const pthread_attr_t \*attr,  
    &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;void \*(\*start_routine) (void \*), void \*arg);**  

    Va creer un thread aditionnel de main thread, lorsque l'on creer un thread il se rattache automatiquement au process courant, il lancera la fonction *routine* qui peut etre de type 
    - (void *) si elle ne revoint revient
    - int  si elle veut renvoyer un int
    - char si elle veut renvoyer un char
    - ect
    *le seul changement est que dans l'appel de fonction il faudra la caste du bon type, (void \*)*  

    **Example:**
    ```c
    #include <stdio.h>
    #include <pthread.h>
    #include <unistd.h>
    #include <stdlib.h>

    void*	function_1()
    {
        printf("hello\n");
        sleep(3);
        printf("bye\n");
        return (NULL);
    }

    int	main()
    {
        pthread_t t1;
        pthread_t t2;

        if (pthread_create(&t1, NULL, &function_1, NULL) != 0)
            return (2);
        if (pthread_create(&t2, NULL, &function_1, NULL) != 0)
            return (2);
        if (pthread_join(t1, NULL) != 0)
            return (2);
        if (pthread_join(t2, NULL) != 0)
            return (2);
    }
    ```

- **pthread_detach**  
    **int pthread_detach(pthread_t thread);**  

    Un thread qui est detach signifie qu'il est **detache du main principale**.  
    **Pourquoi et quand l'utilise ?**  
    Imaginons un contexte ou on ferait tourner un serveur **constant** et que chaque requete que le serveur recoit soient traite par un **thread**, le temps que prendra la gestion de la requete sera **minime compare a la tache du serveur qui tournerais de maniere constante**.  

    C'est donc la qu'est l'utilite d'un thread detache du main thread car il fera sera action et une fois que son action est finit avec ou sans succes alors il rendera au main thread les ressources emprunte...  
    Si le main thread vas constament tourner et quand parralles plusieurs thread peuvent tourner sur un temps l'imiter autant utiliser un thread detache qui vas permettre une gestion plus fluide de la memoire qu'avec un philo; 

- **pthread_join**  
    **int pthread_join(pthread_t thread, void \*\*retval);**  

    Join permet au main thread **d'attendre** que *thread* soit attendu a la fin de son execution, donc si un thread est lance il faudra le join pour attendre qu'il se finissent et qu'il soit **free** par la fonction *pthread join*.  
    *Comme vu dans l'example de pthread create cette fois ci voici un example de creation et de join de plusieurs threads dans une boucle*  

    ```c
    #include <stdio.h>
    #include <unistd.h>
    #include <pthread.h>

    int	x = 0;
    pthread_mutex_t mutex;

    void	*function()
    {
        int	i = 0;

        pthread_mutex_lock(&mutex);
        while (x < 400000 && i++ < 40000000)
        {
            x++;
        }
        pthread_mutex_unlock(&mutex);
        return (NULL);
    }

    int	main()
    {
        pthread_t	th[4];
        int			i = 0;

        pthread_mutex_init(&mutex, NULL);
        while (i < 4)
        {
            printf("thread %d created\n", i);
            pthread_create(&th[i], NULL, function, NULL);
            i++;
        }
        i = 0;
        while (i < 4)
        {
            printf("thread %d started\n", i);
            pthread_join(th[i], NULL);
            printf("thread %d finish\n", i);
            i++;
        }
        printf("x = %d\n", x);
        pthread_mutex_destroy(&mutex);
    }
    ```
    Dans cette exemple l'initalisations des threads et des joins se fait dans une boucle.
    Attention : Si vous voulez lancer des threads dans un ordre precis il faudra les faires separement (dans notre cas c'est pas utile on les lances tous et ils se debrouillent c'est surtout pour montrer qu'on peut le faire dans une boucle)

 ## Data race

Avant de parler des mutexs ils faut comprendrea a quoi ils servent.  
Dans un programme qui a implemente le multi threading il faut saisir que chaque thread peut avoir acces en leecture / ecriture  a une meme variable donc si  
- thread 1 vas **incrementer** une variable mais **au meme moment**  
- thread 2 est entrain de **lire** la donnee de la variable, elle l'ira la valeur que thread 1 lui a ajoute.  
il peut y avoir des sauts d'actions.  
    C'est comme si la variable existait dans deux programme a la fois et que les deux programmes essaiyaient de la modifier c'est ce qu'on appelle une **data race / (course de donee)**.    
    **Example d'une data race:**  

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	x = 0;
pthread_mutex_t mutex;

void*	routine()
{
    int	i = 0;

    // pthread_mutex_lock(&mutex);
    while (i++ < 2000000)
    {
        x++;
    }
    // pthread_mutex_unlock(&mutex);
    return (NULL);
}

int	main()
{
    pthread_t t1;
    pthread_t t2;

    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&t1, NULL, routine, NULL) != 0)
        return (2);
    if (pthread_create(&t2, NULL, routine, NULL) != 0)
        return (2);
    if (pthread_join(t1, NULL) != 0)
        return (2);
    if (pthread_join(t2, NULL) != 0)
        return (2);
    pthread_mutex_destroy(&mutex);
    printf("x = %d\n", x);
}
```

   **Suivez les etapes on va voir ca enssemble.**  
     Si vous lancez le code au dessus vous verrez que x n'a pas atteint la valeurs voulue mais n'hesitait pas la dimminuer vers 1000 et vous verrez que le data race n'a pas lieu visuelement.   
     Mais comment savoir qu'un data race a lieux ? **valgrind**, avec les otptions suivante vous verez qu'il y a une data race sur telle variable.
```bash
     valgrind --tool=helgrind ./a.out
     valgrind --tool=drd ./a.out
     cc [flags] --fsanitize=threads ./a.out <- mettre se flag dans le makefile
     ne pas lancer un tool avec fsanitize ! (mais essaye juste pour voir)
     je conseil d'utiliser les trois parce qu'il font des recherches differente et peuvent apporte des informations que d'autre n'apporte pas.
```
**output:**  

```c    
    ==11689== Helgrind, a thread error detector  
    ==11689== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.  
    ==11689== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info  
    ==11689== Command: ./a.out  
    ==11689==   
    xclip: -selction: No such file or directory  
    ==11689== ---Thread-Announcement------------------------------------------  
    ==11689==   
    ==11689== Thread #3 was created  
    ==11689==    at 0x499C9F3: clone (clone.S:76)  
    ==11689==    by 0x499D8EE: __clone_internal (clone-internal.c:83)  
    ==11689==    by 0x490B6D8: create_thread (pthread_create.c:295)    
    ==11689==    by 0x490C1FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)  
    ==11689==    by 0x4853767: ??? (in /usr/libexec/valgrind/  vgpreload_helgrind-amd64-linux.so)
    ==11689==    by 0x109296: main (data_race.c:29)  
    ==11689==  
    ==11689== ---Thread-Announcement------------------------------------------  
    ==11689==   
    ==11689== Thread #2 was created   
    ==11689==    at 0x499C9F3: clone (clone.S:76)  
    ==11689==    by 0x499D8EE: __clone_internal (clone-internal.c:83)  
    ==11689==    by 0x490B6D8: create_thread (pthread_create.c:295)  
    ==11689==    by 0x490C1FF: pthread_create@@GLIBC_2.34 (pthread_create.c:828)  
    ==11689==    by 0x4853767: ??? (in /usr/libexec/valgrind/  vgpreload_helgrind-amd64-linux.so)  
    ==11689==    by 0x10926B: main (data_race.c:27)  
    ==11689==   
    ==11689== ----------------------------------------------------------------  
    **LES LIGNES AU DESSUS INDIQUENT QUE DEUX THREADS ONT ETE INITIALISE**   
    ==11689==   
    ==11689== **Possible data race during read of size 4 at 0x10C040 by thread #3**   
    ==11689== Locks held: none  
    ==11689==    at 0x1091FA: **routine (data_race.c:15)** **DATA RACE A LIEU ICI**  
    ==11689==    by 0x485396A: ??? (in /usr/libexec/valgrind/  vgpreload_helgrind-amd64-linux.so)
    ==11689==    by 0x490BAC2: start_thread (pthread_create.c:442)  
    ==11689==    by 0x499CA03: clone (clone.S:100)  
    ==11689==   
    ==11689== **This conflicts with a previous write of **size 4** **donc un int** by thread #2**  

    **On comprend donc que le data race a lieu entre le thread et 2 sur une valeur de size 4 et qu'elle a lieu.. ligne 15**   
    ==11689== Locks held: none  
    ==11689==    at 0x109203: routine (data_race.c:15) **ICI**  
    ==11689==    by 0x485396A: ??? (in /usr/libexec/valgrind/  vgpreload_helgrind-amd64-linux.so)
    ==11689==    by 0x490BAC2: start_thread (pthread_create.c:442)  
    ==11689==    by 0x499CA03: clone (clone.S:100)  
    ==11689==  Address 0x10c040 is 0 bytes inside data symbol "x"  
    ==11689==   
    ==11689== ----------------------------------------------------------------  
    ==11689==   
    ==11689== **Possible data race during write of size 4 at 0x10C040 by thread #3**  
    ==11689== **Locks held: none**   
    **Il a acces a une memoire en lecture ecriture qui n'a pas ete lock ce qui creer le data race**    
    ==11689==    at 0x109203: routine (data_race.c:15)  
    ==11689==    by 0x485396A: ??? (in /usr/libexec/valgrind/  vgpreload_helgrind-amd64-linux.so)
    ==11689==    by 0x490BAC2: start_thread (pthread_create.c:442)  
    ==11689==    by 0x499CA03: clone (clone.S:100)  
    ==11689==   
    ==11689== This conflicts with a previous write of size 4 by thread #2  
    ==11689== **Locks held: none**  
    ==11689==    at 0x109203: routine (data_race.c:15)  
    ==11689==    by 0x485396A: ??? (in /usr/libexec/valgrind/  vgpreload_helgrind-amd64-linux.so)
    ==11689==    by 0x490BAC2: start_thread (pthread_create.c:442)  
    ==11689==    by 0x499CA03: clone (clone.S:100)  
    ==11689==  Address 0x10c040 is 0 bytes inside data symbol "x"  
    ==11689==   
    ==11689==   
    ==11689== Use --history-level=approx or =none to gain increased speed, at  
    ==11689== the cost of reduced accuracy of conflicting-access information  
    ==11689== For lists of detected and suppressed errors, rerun with: -s  
    ==11689== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)  
```


Mais si je decommente les deux mutex qu'est ce que ca change ?  
        Et bien essayont.
```c
    ==13366== Helgrind, a thread error detector
    ==13366== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
    ==13366== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
    ==13366== Command: ./a.out
    ==13366== 
    x = 4000000 <- sortie sur le terminal
    ==13366== 
    ==13366== Use --history-level=approx or =none to gain increased speed, at
    ==13366== the cost of reduced accuracy of conflicting-access information
    ==13366== For lists of detected and suppressed errors, rerun with: -s
    ==13366== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)
```
On remarque deux chose :  
    - pas de data race  
    - le x a bien atteint la valeur souhaite

Mais pourquoi il n'y en a plus ?  

## Variable atomique

Comme vous l'avez compris quand deux threads utilise la meme variable ils apliquent des changements simultannement et finit par corompre le but final. Pour regler le soucis il faut utiliser une **variable atomique** qui pourrait definir si oui ou non je peux utiliser une variable en lecture ou ecrire ou les deux.  
Une variable atomique est une variable qui meme si le programme est multi threading ou multi processing, il n'existerait qu'une seul representation de cette variable donc **si cette variable est a 1 dans l'autre thread / process elle sera a 1 aussi dans l'autre thread / process** et une variable atomique ne creer pas de data race.  

Donc oui un mutex est une variable atomique binaire, elle peut soit etre a 0 soit a un. 
 - Si je lock un mutex il passe a 1 et j'aurais la priorite sur la section critique du code (section qui pourrait causer du data race)  
 - Pour dire que j'ai finit d'utilier la section critique j'unlock le mutex

Pour le deuxieme type de mutex on le verra dans les bonus mais je ne veux pas trop parler de chose non neccessaire maintenant et si vous comprenez les mutex maintenant vous comprendrez l'utilisation de l'autre type de variable atomique n'aura pas de soucis.

 Voila j'espere que ca a ete clair sur cette partie on continue l'explication des fonctions

## Definitions / prototype [mutex] 2/2
- **pthread_mutex_init**  
    **int pthread_mutex_init(pthread_mutex_t \*restrict mutex,  
    &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
    const pthread_mutexattr_t \*restrict attr);**  
    Cette fonction permet d'init le mutex *mutex* et pour l'attribut SI j'ai compris correctement il s'agirait attribuer un type de mutex car il existe des mutex **bloquant** et des mutexs **non bloquant**
    - Mutex bloquant :  
    Si un thread accede a un mutex qui est lock il est mit en etat d'attente sur le *pthread_mutex_lock* ne peut pas acceder a la suite du code et va attendre que le mutex soit de-lock pour continuer. (au moment ou il arrive sur le mutex lock il ne peut rien faire d'autre et aucun code ne peut etre appliquer)
    - Mutex non bloquant :  
    Si un thread arrive sur un mutex non bloquant et qu'il est lock, il va sauter toute   la section critique pour passer a la suite (comme une condition de if)  
Un mutex bloquant se declare avec un NULL sur l'attr pour un non bloquant je vous laisse trouver mais ce n'ai pas neccessaire (j'ai pas trouve (j'ai cherche 5 min))

- **pthread_mutex_destroy**  
    **int pthread_mutex_destroy(pthread_mutex_t \*mutex);**  
    
    Va liberer la memoire du mutex *mutex*

- **pthread_mutex_lock**  
    **int pthread_mutex_lock(pthread_mutex_t \*mutex);**  
    Lock *mutex* et le met a 1, (sert a empecher les autres threads d'entrer dans une section critique et de causer des data race) si le mutex est deja a 1 est qu'il est bloquant alors le thread va attendre dans une file d'attente q'il soit liberer,  
    premier arriver a la file d'attente premier sur la file d'attente  
    deuxieme suir la file d'attente deuxieme sur la file d'attente ect ...

- **pthread_mutex_unlock**  
    **int pthread_mutex_unlock(pthread_mutex_t \*mutex);**
    Unlock *mutex* et le met a 0 (sert a prevenir les autres threads qu'il a finit la section critique et que le premier sur la file d'attente peut rentrer)

## Pilier du projet qui m'ont embete

 ## 1) la gestion du temp  
    
Elle n'etait pas parfaite a cause de ceci [lien mendum](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315) <- voir la partie sur la gestion du temps et ce qui pose probleme.  
Pour resumer un usleep de 200 ne fera pas un usleep de 200 mais un usleep de 250 - 300. Pourquoi ?  
Parce que usleep utilise un systeme de check pour verifier si le temps a ete atteint et va check tout les x micro seconde si le temps voulue a ete atteint et ce qui finit par creer un decallage.  
On peut voir le probleme dans l'autre sens, au lieu de faire un usleep sur le temps voulu on prendre en le temps T1 et tant que le temps t1 moins le temps t2 qui sera prit constament.

```c
    void	ft_usleep(int elapsed, t_philo *philo)
    {
        long	time;

        time = ft_timestamp();
        while (1)
        {
            if (ft_timestamp() - time >= elapsed)
                break ;
            usleep(1);
        }
    }
```
Sur un point de vue de performance je ne suis pas sure que le usleep 1 soit recommande car il ferait trop d'appel systeme donc autant en faire de quelque micro seconde voir uniquement une boucle infinit qui ne fait rien.

## 2) Gestion des fourchettes 

 Une mauvaise gestion des fourchettes cause quelque soucis  
    
- Un philo pourrait prendre la fourchette de son voisin alors que ce n'est pas encore a lui de manger, ce qui resulte a la mort du philo qui s'est fait prendre ses fourchettes
###  2.1) Dead lock  

Un dead lock est une situation ou tout les philos aurait prit une fourchette et serait tous en attente de la deuxieme, comment ca arrive ?  

Imaginons que tout les threads soient lance en meme temps et qu'en arrivant ils prendraient tous la fourchette a leurs droite  

Puis ils decident de prendre la fourchette qui est a leurs gauche,  
    et bien vu que la fourchette a leurs gauche est la fourchette de droite du voisin de gauche et que le voisin de gauche a deja prit sa fourchette de droite,  
    du point du philo ou nous somme la fourchette de gauche est prise et on doit attendre qu'elle soit disponible pour la prendre  
    tant que la fourchette de gauche est prise je ne lache pas ma fourchette de droite  
    car une fois qu'une fourchette est prise et que je suis dans l'attente du mutex je ne peux pas executer du code donc je serais bloquer.  


Oui on pourrait regarder dans le structure et observer directement si la variable est a 0 ou 1 mais c'est contre le reglement et je pense que si dans un sujet comme celui la on doit rajouter des condition optionnel c'est qu'on a rater quelque chose.  
      Avec valgrind ou fsanitize ou voit que "l'ordre des fourchettes a ete viole", ce qui veut dire qu'il faut appliquer un ordre de **lock de nos mutex** a nos thread pour eviter un deadlock ou tout pottentiel dead lock.

un deadlock se voit visuellement, etant donnee que les threads sont tous en attente le philo tournera dans le vide sur le terminal

### 2.2) Solution propose de gestion des fourchettes

Pour avoir une gestion des fourchettes qui eviterais un deadlock il faut appliquer une strategie au choix (vous pouvez aussi faire la votre),  
je vais montrer celle du cas **paire impaire**. (wikipedia)  

On numerote dabord la position a la table du philo si celle si est paire on lui attribue en premier sa fourchette gauche puis sa fourchette droite et inversement s'il est impaire on lui attribue d'abord sa fourchette droite puis sa fourchette gauche.  
    **explication**  
    Étudions le cas d'un philosophe qui prend d'abord sa fourchette gauche. S'il y arrive, il ne lui reste plus qu'à prendre sa fourchette droite.  
    Celle-ci ne peut être définitivement bloquée :  
        si le philosophe de droite la tient, c'est qu'il est en train de manger (il tient dans ce cas ses deux fourchettes). Ainsi nos philosophes ne se bloqueront jamais.  

La compréhension de cette solution est plus aisée en prenant pour exemple la présence de deux philosophes.  

Ce que je conseille pour faciliter l'utilisation, est de predefinir a l'avance dans un tableau de structure les index des deux fourchettes de chaque philo  
    qui sera utiliser pour cibler le mutex de chaque fourchette, cela evite a avoir a rajouter des calculs dans le threads et de le rendre plus lent,  
    et ne pas faire une structure trop grosse (il est plus simple de se deplacer avec un sac a dos qu'un lave linge).

## 3) Les mutex / data race

Il faut comprendre que si un mutex verouille l'acces a une variable en ecriture **elle doit aussi** verouiller l'acces a cette variable en lecture et vise versa  
donc oui on peut **rajouter des mutex** (sinon ca marche pas de toute facon).   
**Donc s'il y a un mutex pour l'utilisation de printf quelque part dans le code, ca doit etre le meme mutex partout dans le code et pas un autre mutex et c'est pareil pour d'autre variable**

Voici un cas concret  

Disons que j'ai une varaible X un mutex A et un mutex B et deux thread 2 et 3 (parce que le thread 1 c'est le main process du proc qui est tout le temps present)  
Si je lock mutex A pour utiliser variable X dans thread 2  
Mais qu'en paralle je lock mutex B pour acceder a variable X et bien oui le mutex me laisse passer mais je touche a la variable dans deux thread en meme temps ce qui cause  
    un data race.
    **pour resumer on utilise un mutex par section critique**.

## 4) La muerta

La gestion de la mort peut se faire de deux facon differente qui fonctionne mais l'une ne respecte pas les regles du sujet.  
    
- Faire une fonction qui sera appliqer par les differents philos pour qu'il regarde eux meme s'ils sont mort.  
        ce qui va changer c'est le moment de la mort qui va changer, si celle si est fait par les philo eux meme elle sera decaller de x temps  
        parce qu'il arrivera que le philo est sence etre mort mais va d'abord prendre une fourchette qui ne sera pas dispo, mais au lorsqu'il prend la fourchette celle ci est deja prise il sera donc en etat d'attente jusqu'a ce que le philo qui detient la fourchette est finit de manger.  
        La mort du philo sera donc decalle d'u temps pour mourrir, et le resultat n'est pas bon  

- Utiliser un thread qui fera office de serveur autour de la table et qui indirquerait que x philo est mort.  
        Ce qui change c'est que le thread tournera en parrallele tout le temp moins le decallage autorise (pour eviter une surconssomation des resources), est au moment ou il detecte qu'un philo sera mort il aura le bon temps de mort sans etre bloquer par une attente de fourchette.  
        En contrepartie dans la routine il faudra appliquer des verfications et si un philo est mort alors, on peut s'en sortir de la routine, il faudra aussi appliquer des verifictations lorsque un philo est dans une actions du style, losqu'il fait une boucle pour manger / dormir.

Voila voila gl hf.

# Bonus

Il est important de d'abord comprendre les forks puis de comprendre les semaphores

## Regles du sujet
La partie bonus garde le meme principe que le mandatory a deux details crucial.  
- Toute les fourchettes disponible sont place au millieu de la table (on peut les visualiser comme si elles etaient places dans un bol).  
- Tous les philos sont representees 
Les fourchettes seront representees par un semaphore.

## Fonctions autorisees

memset  
printf  
malloc  
free  
write  
fork  
kill  
exit  
pthread_create  
pthread_detach    
pthread_join  
usleep  
gettimeofday  
waitpid    
sem_open  
sem_close
sem_post  
sem_wait  
sem_unlink  

Je vais expliquer les fonctions des samphores et des process
 
## Definition / Protoype

- **fork**  
    Lorsque la fonction fork est appelle elle creer un process enfant au process parent le process parent se termine avant le process enfant et le parent devrais attendre le process enfant en cours avec la fonction waitpid, sinon les process enfant deviendront des process zombies.  
    Un code multi processing permet d'avoir plusieurs alternatif differents dans un seul code.  
    Si j'ai un code qui doit s'arreter pour x ou y raison mais que le process parents continuerais d'etre lancer pour lancer d'autre process.
    Mais comme dit pour les threads je reconseille les videos de la chaine youtube [code vault](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY).

a partir de la je concidere que les fork est la gestion de memoire des process enfant est acquis. Si c'est pas acquis allez voir les videos.

## Semaphore
 **int sem_init(sem_t \*sem, int pshared, unsigned int value);**  
    Un semaphore est une variable atomique non binaire avec un conteur dans son protoype *value* pour definir combien de process pourront rentrer dans la section critique.  

Partons du principe qu'il commence a 3.  
Pour chaque process voulant entrez dans la section critique il va d'abord diminuer *value* de 1 a deux pour dire qu'il reste deux places dans la section critique et lorsqu'il a finit, il rajoute 1 a *value*.

la diminution de 1 se fait a partir de sem_wait  
    &emsp;**int sem_wait(sem_t \*sem);**  

l'ajout de 1 avec sem_post  
    &emsp;**int sem_post(sem_t \*sem);**  

Un semaphore est un fd qui se trouve dans /dev/je_sais_plus mais ce qui est important a s'avoir  
c'est que son fd doit etre nettoie / suprrimer de dossier avec **sem_unlink** et sa memoire libere avec **sem_close**.  

Si le unlink ce trouve a la fin de la fonction principale et qu'un philo meurt il faudra exit donc le unlink passe a la trape,  
pour ma part j'ai mit un second unlink avant l'initialisation de mon semaphore car sinon il va utiliser l'ancien semaphore  
et peut arriver a un dead_lock (sem wait qui n'a ete post et le semaphore est a 0).  

Si vous vous posez la question, oui on peut verifier directement dans la structure du sempahore comben de *value* il reste avec *sem.__align* mais ce n'est pas autorise.  
Mis a part ca le reste est tout comme la partie mandatory est c'est plus votre comprehension avec les forks et comment la donee peut etre partage qui vous aidera.

## la muerta bonus  
Le check de mort dans les bonus est un peu different car les philos sont des fork et la memoire est gereer sur une plage d'adressage virtuel.  
Donc, ce qui se passe dans un fork reste dans un fork a moins d'utiliser une pipe ou de la memoire partagee... bref pas necessaire dans notre cas.  

Le "last meal qu'on utilisaient et verifions avant etait accessible car nous etions constamment dans le meme process. La on est dans *nombre de philo* process differents et la memoire entre ces process n'est pas partagees.  

Pour verifier que x philo est mort il faudrait appliquer un thread par philo et lui faire check en parrallele de son execution.  
Comment faire la difference entre le cas ou un philo et mort ou non.  
Parce que oui, la memoire entre un process enfant et parent ne peux pas etre partager mais ! grace a **waitpid** un process peut renvoyer un **exit status** et en fonction de l'exit status le parent peut s'avoir si un philo est mort et reagir en concequence.

# Bonus leak (que j'ai rencontre ca ne veut pas dire que vous n'allez pas reussir)
si un thread est mort il faudra comme dans le mandatory exit le process correctement et au bon moment mais cela pose un probleme.  

Un leak aura lieu si un philo meurt car le thread qui est lance en parrallele declare que son philo est alors il devra exit dans le thread, mais, si j'exit dans le thread je ne peux pas le join parce que le join mettra fin au thread donc je ne pourrais pas l'exit. Je repete..  

dans le cas ou x philo est mort 
- Si je join dans le thread pour arreter l'arreter et liberer sa memoire  mais je ne pourrais pas exit correctement.
- Sinon je decide d'exit dans le thread pour faire exit le philo, mais si j'exit cela va me faire exit le process en cours donc je ne pourrais pas le join, et un leak a lieu

une petite visualisation de haute qualite.



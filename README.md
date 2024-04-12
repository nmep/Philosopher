
# Philosopher

## Disclamer
Je ne certifie pas que le projet est parfait et je pense qu'a mon niveau il y a des notions que je n'ai pas completement saisis.  
Je fais ce readme parce que c'est un projet qui me plait et je comprend qu'il ne soit pas friendly.  
Mais ce n'est pas une raison pour ne pas pousser la reflection des sujets qui ne sont pas limpide des le debuts..  
Mais si tu souhaite apprendre le sujet par toi meme alors tu peux quitter.

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

(Elles ont toute etaient utilise sauf pthread_detach et memset car je n'en ai pas trouve l'interet). 

## Definition / Prototype  

- **gettimeofday**  
    **int gettimeofday(struct timeval \*tv, struct timezone \*tz)**  

    struct timeval {  
    &emsp;&emsp;time_t      tv_sec;&emsp;&emsp;/* seconds */  
    &emsp;&emsp;suseconds_t tv_usec;&emsp;&emsp;/* microseconds */  
    };  

    Va prendre le temps T en seconde et en millisecondes durant l'appel systeme et nous le donner dans une variable de type *struct timeval <nom de la variable>*  

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
    *le seul changement est que dans l'appel de fonction il faudra la caste du bon type qui est (void \*)*

- **pthread_detach**  
    **int pthread_detach(pthread_t thread);**  

    Un thread qui est detach signifie qu'il est **detache du main principale**.  
    **Pourquoi et quand l'utilise ?**  
    Imaginons un contexte ou on ferait tourner un serveur **constant** et que chaque requete que le serveur recoit soient traite par un **thread**, le temps que prendra la gestion de la requete sera **minime compare a la tache du serveur qui tournerais de maniere constante**.  

    C'est donc la qu'est l'utilite d'un thread detache du main thread car il fera sera action et une fois que son action est finit avec ou sans succes alors il rendera au main thread les ressources emprunte...  
    Si le main thread vas constament tourner et quand parralles plusieurs thread peuvent tourner sur un temps l'imiter autant utiliser un thread detache qui vas permettre une gestion plus fluide de la memoire qu'avec un philo; 

- **pthread_join**  
    **int pthread_join(pthread_t thread, void \*\*retval);**  

    Join permet au main thread **d'attendre** que *thread* soit attendu a la fin de son execution, donc si un thread est lance il faudra le join pour attendre qu'il se finissent et qu'il soit **free** par la fonction *pthread join*

- **pthread_mutex_init**  
    **int pthread_mutex_init(pthread_mutex_t \*restrict mutex,  
    &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
    const pthread_mutexattr_t \*restrict attr);**  

    Avant d'observer les mutex ils faut comprendre dans qu'elle cas ils sont utilise.  
    Dans un programme qui a implemente le multi threading il faut saisir que chaque thread peut avoir acces aux donnes d'une meme variable donc si  
    thread 1 vas **incrementer** une variable mais **au meme moment**  
    thread 2 est entrain de **lire** la donnee de la variable, elle l'ira la valeur que thread 1 lui a ajoute.  
    C'est comme si la variable existait dans deux programme a la fois et que les deux programmes essaiyaient de la modifier c'est ce qu'on appelle une **data race**.  
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
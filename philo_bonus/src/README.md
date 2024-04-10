il faut utilser un thread par philo (fork) pour regarder en parrallele s'il est mort ou non
	parce que si on decide de faire check les philos eux meme on aura besoin de la valeurs
	du dernier repas de chaque philo donc si c'est fait depuis un fork la variable ne sera pas modifier.

le point de vue de monitoring sur les bonus reste le meme que celui du mandatory mais il est m'ultiplie par le nombre de philo
pour permettre de modifier telle ou telle donner il faut utiliser des samaphores, pourquoi ?

ils feront office de mutex car entre a la difference du mandatory qui utilise des threads la partie bonus se fera avec des fork ce qui fera que la donne en memoire restera differente est que si x variable est a 1 dans un enfants, elle restera telle qu'elle dans la parent, ce qui est le cas de n'importe qu'elle variable 
	mais un semaphore est atomique !
ce qui fait que si un semaphore est a 1 dans un enfant, elle sera aussi a 1 dans son parent ce qui est parfait pour la communication dans notre cas.

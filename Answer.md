### Gestion de threads et de processus

#### 1. Indiquer ce qui doit être sauvegardé lors d’un changement de contexte.  
Lors d'un changement de contexte, nous devons sauvegarder le contexte du Thread.

#### 2. Quelle variable est utilisée pour mémoriser la liste des threads prêts `a s’exécuter ? Est-ce que le thread élu (actif) appartient `a cette liste ? Comment accéder à ce thread ?  
readyList. Le thread actif n'est pas dans cette liste. Scheduler::FindNextToRun ()

#### 3. A quoi sert la variable g_alive ? Quelle est la diff´erence avec le champ readyList de l’objet g_scheduler ?
g_alive est la liste des Threads existants. Le champ readyLIst ne contient que les Threads non lancés alors que g_alive contient tout les Threads.

#### 4. Comment se comportent les routines de gestion de listes vis `a vis de l’allocation de m´emoire ? Est-ce qu’elles se chargent d’allouer/d´esallouer les objets chaˆın´es dans la liste ? Pourquoi ?  
Les routines de gestion de listes ne s'occupent pas de l'allocation mémoire et n'alloue/désalloue pas les objets chaînés dans la liste. Les objets dans la liste sont des pointeurs vers des objets, la mémoire est donc gérée à l'extérieur.

#### 5. A quel endroit est placé un objet thread quand il est bloqué sur un sémaphore ?
L'objet thread est placé dans une file d'attente.

#### 6. Comment faire en sorte qu’on ne soit pas interrompu lors de la manipulation des structures de données du noyau ?
On désactive les interruptions avec la méthode IntStatus SetStatus(IntStatus level); #INTERRUPTSOFF de la class interrupt.

#### 7. A quoi sert la méthode SwitchTo de l’objet g scheduler ? Quel est le rôle des variables thread context et simulator context de l’objet thread ? Que font les m´ethodes Save-SimulatorState et RestoreSimulatorState ? Que devront (à terme) faire les méthodes SaveProcessorState et RestoreProcessorState de l’objet thread ?
La méthode SwitchTo permet de lancer le prochain Thread prêt dans le processeur tout en sauvegardant l'état de l'ancien Thread. La variable ThreadContext définie le contexte de la machine virtuelle et initialise les registres du processeurs. La variable SimulatorContext définie le contexte du simulateur Nachos et le remplit avec les valeurs appropriées, de sorte que le changement de contexte de bas niveau exécute la fonction StartThreadExecution(). Sauvegarder les registres du processeur et restorer les registres du processeur d'un contexte.

#### 8. Expliquer l’utilité du champ type de tous les objets manipulés par le noyau (sémaphores, tâches, threads, etc.).
Chaque syscall s'assure que l'objet que l'utilisateur lui transmet est du type attendu, en vérifiant le champ typeId par rapport à ces identifiants.

### Environnement de développement
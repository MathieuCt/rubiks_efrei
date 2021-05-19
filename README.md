# Références et liens utiles au projet rubiks_efrei
## Liens utiles et debuggage
* [Formation C OpenClassRoom](https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c) 
* [Gestion des conflits de variables dans fichier .h](https://openclassrooms.com/forum/sujet/probleme-de-definitions-multiples)
* Nous développons sous Linux, en utilisant la librairie ncurses. De base, Clion ne peut pas debugger des programmes C utilisant ncurses :
  * https://youtrack.jetbrains.com/issue/CPP-822
  * https://youtu.be/2R3OSGmUmoU?t=2015
* Documentation pour debugger et utiliser ncurses dans Clion est dans le répertoire Doc
* Comment ajouter des librairies dans Clion pour pouvoir compiler : [Lien](https://stackoverflow.com/questions/40710903/undefined-reference-during-linking-using-ncurses-and-cmake) <br />
## Documentation et aides nCurses
* [Tutoriel ncurses](https://arnaud-feltz.developpez.com/tutoriels/ncurses/?page=premier_pas)
* [Ncurses Programming Guide](www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html)
* [NCURSES Programming HOWTO Menus](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html)
## CMake
* Dans notre cas, pour l'instant, le fichier CMakeLists.txt doit contenir, si le nom du projet est XXXX :  
  cmake_minimum_required(VERSION 3.20) <br />
  project(XXXX C) <br />
  set(CMAKE_C_STANDARD 99) <br />
  add_executable(XXXX main.c) <br />
  target_link_libraries(XXXX curses) <br />
  target_link_libraries(XXXX menu) <br />
## Librairies
* [Librairie standard pour gérer des menus (basée sur ncurses)](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html)
## Documentation avec Doxygen
* [Comment documenter son code, avec Doxygen dans Clion](https://blog.jetbrains.com/clion/2016/05/keep-your-code-documented/)
* [Comment utiliser Doxygen pour générer de la documentation](https://lugatgt.org/2002/05/30/using-doxygen/) 
* [Doc officielle](https://www.doxygen.nl)

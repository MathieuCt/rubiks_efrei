# rubiks_efrei

* Nous développons sous Linux, en utilisant la librairie ncurses. De base, Clion ne peut pas débugguer des programmes C utilisant ncurses :
  * https://youtrack.jetbrains.com/issue/CPP-822
  * https://youtu.be/2R3OSGmUmoU?t=2015
* A suivre : comment mettre en place le debug avec clion :)

* Comment ajouter des librairies dans Clion pour pouvoir compiler : https://stackoverflow.com/questions/40710903/undefined-reference-during-linking-using-ncurses-and-cmake <br />

* Dans notre cas, pour l'instant, le fichier CMakeLists.txt doit contenir, si le nom du projet est XXXX :  
  cmake_minimum_required(VERSION 3.20) <br />
  project(XXXX C) <br />
  set(CMAKE_C_STANDARD 99) <br />
  add_executable(XXXX main.c) <br />
  target_link_libraries(XXXX curses) <br />
  target_link_libraries(XXXX menu) <br />
* Pour débugguer ncurses : https://youtrack.jetbrains.com/issue/CPP-822
* Librairie standard pour gérer des menus (basée sur ncurses) : https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html

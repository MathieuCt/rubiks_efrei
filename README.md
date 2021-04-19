# rubiks_efrei

* Nous développons sous Linux. De base, Clion ne peut pas débugguer des programmes C utilisant ncurses : https://youtrack.jetbrains.com/issue/CPP-822 <br />

* Comment ajouter des librairies dans Clion pour pouvoir compiler : https://stackoverflow.com/questions/40710903/undefined-reference-during-linking-using-ncurses-and-cmake <br />

* Dans notre cas, pour l'instant, le fichier CMakeLists.txt doit contenir, si le nom du projet est XXXX :  
  cmake_minimum_required(VERSION 3.20)
  project(XXXX C)

  set(CMAKE_C_STANDARD 99)

  add_executable(XXXX main.c)

  target_link_libraries(XXXX curses)
  target_link_libraries(XXXX menu)

* Pour débugguer ncurses : https://youtrack.jetbrains.com/issue/CPP-822

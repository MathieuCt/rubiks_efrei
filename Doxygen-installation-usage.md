# Doxygen
* Doxygen permet de générer de la documentation automatiquement.
* Le logiciel se base sur le code et ses commentaires pour générer la doc.
## Installation
### Ubuntu
* Installer dans un terminal : ```sudo apt install doxygen```
* Pour générer un PDF à partir de l'export Latex, il faut ajouter les packages : ```sudo apt install texlive-latex-extra texlive-latex-recommended texlive-pictures telxcc```
### Manjaro
* Installer dans un terminal : ```pamac install doxygen```
* Pour générer un PDF à partir de l'export Latex, il faut ajouter le package texlive-latexextra : ```pamac install texlive-latexextra```
## Utilisation et configuration
* Doxygen se base sur un fichier de configuration (et des fichiers de types, mais que nous n'utilisons pas ici).
* Le premier fichier de configuration peut se créer via un Wizard : ```doxywizard```
* Le fichier de configuration s'appelle, par défaut, Doxyfile.
* Une fois le fichier créé, on peut facilement le modifier dans un éditeur de texte quelconque, y compris dans Clion.
* Un fichier Doxyfile a été créé pour ce projet, ainsi qu'un fichier header.tex que ne nous utilisons pour changer le pied de page du document PDF.
* Pour créer un fichier vierge header.tex (pour le modifier en fonction de nos besoins), il faut faire ```doxygen -w latex header.tex footer.tex doxygen.sty```. Il suffit de récupérer le fichier header.tex, le déplacer dans ```Doc\doxygen\``` et le modifier en conséquence.
* Enfin, on référence le fichier header.tex dans le fichier Doxyfile : ```LATEX_HEADER           = header.tex```
## Génération de la documentation :
  * Se déplacer dans le répertoire Doc/doxygen du projet.
  * Et lancer la commande ```doxygen```
  * La commande va générer la documentation dans Doc/doxygen/output.
  * La commande va sortir des logs, dont potentiellement des erreurs. Il est important de vérifier.
  * Elle est, pour le moment, aux formats HTML, et Latex.
  * Pour lire, par exemple, la documentation au format HTML, il suffit d'aller dans le répertoire ./Doc/doxygen/Ouput/html et d'ouvrir le fichier index.html. Le résultat va s'ouvrir dans le navigateur par défaut.
  * Pour générer une documentation PDF, aller dans le répertoire Latex ```cd Doc/doxygen/output/latex``` et lancer la commande ```make```. Il suffira d'ouvrir le fichier refman.pdf généré dans ce même répertoire.
## Références
* [Using Doxygen](https://lugatgt.org/2002/05/30/using-doxygen/)
* [Liens vers divers articles](https://www.doxygen.nl/articles.html)
* [Examples de documentation](https://wiki.scilab.org/Doxygen%20documentation%20Examples)
* [Documentation du code avec Doxygen](http://tvaira.free.fr/projets/activites/activite-documentation-doxygen.html)
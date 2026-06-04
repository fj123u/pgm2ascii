//Sert à importer les bibliothèque nécessaire au bon fonctionnemant du programme
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "fonctions.h"



//Foction qui permet d'ouvrir un fichier pgm à parir d'un lien
void OpenFile(std::string lien)
{
	std::ifstream img(lien, std::ios_base::binary); //Permet de lire le code pgm de l'image
	if (!img.is_open()) //Vérifie si le fichier c'est bien ouvert sinon erreur
	{
		std::cout << "Problème Le fichier ne s'est pas ouvert" << '\n'; //Renvoie un message d'erreur
		std::exit(EXIT_FAILURE); //Ferme de programme si le fichier ne c'est pas ouvert
	}
}

//Fonction qui renvoie un vecteur de string qui stock tout les caractères d'une palette à partir de son lien
std::vector<std::string> GeneratePalette(std::string lienPalette)
{
	std::string lignePalette;
	std::vector<std::string> retourPalette; //Vector qui va être retourner par la fonction à la fin
	std::ifstream fichierPalette(lienPalette); //Lis le fichier
	if(fichierPalette.is_open()) //Vérifie que le fichier c'est bien ouvert
	{
		while (std::getline(fichierPalette, lignePalette)) //Boucle temps qu'il y a des lignes à lires
		{
			retourPalette.push_back(lignePalette); //Ajoute dans le vecteur à la fin le caractère
		}
	}
	else
	{
		std::cerr << "Le fichier Palette ne s'est pas ouvert" << '\n'; //Renvoie une erreur
		std::exit(EXIT_FAILURE); //Ferme le programme en cas d'erreur
	}
	/*Retourne le vecteur pour qu'il soit stocké dans le "main" 
	pour être utliser par la fonction "CreateFileOutput*/
	return retourPalette;
}


//Fonction qui permet de récuperer et de renvoyé les dimensions X et Y de l'image pgm à partir d'un lien
std::pair<int, int> GetImageSize(std::string lien)
{	
	std::ifstream img(lien); //Permet de lire le code pgm de l'image
	std::string entete;
	int imgSizeX; //Stock dimension X
	int imgSizeY; //stock dimension Y
	std::string test;
	std::getline(img, entete); //Stock dans "entete"" la premier ligne du code pgm
	if (entete == "P5") //Permet de vérifier que le fichier est bien un pgm
	{
		std::getline(img, test); //Permet de sauter la ligne commentaire qui sont dans tout les codes pgm
		std::getline(img, test, ' '); //Lis la ligne jusqu'au prochain espace pour sotcker X dans test
		imgSizeX = std::stoi(test); //Permet de convertir un string en integer pour stocker X dans "imgSizeX"
		if (imgSizeX <= 0) //Vérifie que l'image na pas de dimension incorrect
		{
			std::cerr << "Les Dimensions de l'image sont incorrect" << '\n'; //Renvoie une erreur de se cas
			std::exit(EXIT_FAILURE); //Ferme le programme en cas d'erreur
		}
		else
		{
			std::getline(img, test, ' '); //Lis la ligne jusqu'au prochain espace pour sotcker Y dans test
			imgSizeY = std::stoi(test); //Permet de convertir un string en integer pour stocker X dans "imgSizeY"
		}
	}
	else
	{
		std::cout << "Le fichier n'est pas un pgm" << '\n'; //Renvoie une erreur
		std::exit(EXIT_FAILURE); //Ferme de programme en cas d'erreur
	}
	return {imgSizeX, imgSizeY}; //Retourne sous ferme de deux variable les dimensions X et Y
}



//Fonction qui créer l'image ASCII et la stock dans un fichier
void CreateFileOutput(int imgSizeX, int imgSizeY, std::string lien, std::vector<std::string> palette, std::string lienOutput)
{
    std::ifstream img(lien, std::ios_base::binary); //Permet de lire le code pgm de l'image en binaire
    if (img.is_open()) //Vérifie que le fichier c'est bien ouvert
    {
        std::vector<char> donnees;
        std::string line;
        std::getline(img, line); //Saut les 4 premier ligne d'entete, car il ne font pas partis de l'image
        std::getline(img, line);
        std::getline(img, line);
        std::getline(img, line);
        std::string lettre;
        int dec;
        donnees.resize(imgSizeX * imgSizeY); //Permet de définir la taille du vecteur en fonction des dimensions de l'image
        img.read(donnees.data(), imgSizeX * imgSizeY); //Permet de lire sous forme d'octet le code binaire de tout l'image
        std::ofstream convert(lienOutput); //Permet d'écrir dans un fichier
        if (convert.is_open()) //vérifie que le fichier c'est bien ouvert
        {
            for (int i = 0; i < donnees.size(); ++i) //Boucle temps que la fin du tableau n'est pas atteinte
            {
                unsigned char byte = donnees[i]; //Permet de convertir un octet binaire en un char
                int decimal = (int)(byte); //Permet de convertir un char en decimal (entre 0 et 255)


                int nb_couleurs = palette.size(); //Permet de stocker le nombre de couleurs en fonction de la taille du vecteur
                int ecart = 256 / nb_couleurs; //Calcule l'écart pour écrire telle caractère en fonction de telle nuance de gris
				int current_ecart = ecart; //Permet de stocker l'écart courrant

				//Ecrit les caractères pour créer l'image ASCII
                for (int j = 1; j < nb_couleurs + 1; ++j)
                {
                    if (decimal < current_ecart)
                    {
                        lettre = palette[j - 1]; //Selectionne le caractère en fonction des caractères de la pallete
                        break;
                    }
                    else
                    {
						current_ecart += ecart; //Augmente l'écart courrant
                    }
                }
                convert << lettre;
                if ((i + 1) % imgSizeX == 0) //Vérifie si on atteints la largueur X
                {
                    convert << "\n"; //Si oui alors on fait un retour a la ligne
                }

            }
            std::cout << "-------------------------------------------------------------------------\n";
			std::cout << "Image converti en ASCII" << '\n'; //Message pour dire que l'image est converti
			std::cout << "-------------------------------------------------------------------------\n";
        }
        else
        {
            for (int i = 0; i < donnees.size(); ++i) //Boucle temps que la fin du tableau n'est pas atteinte
            {
                unsigned char byte = donnees[i]; //Permet de convertir un octet binaire en un char
                int decimal = (int)(byte); //Permet de convertir un char en decimal (entre 0 et 255)


                int nb_couleurs = palette.size(); //Permet de stocker le nombre de couleurs en fonction de la taille du vecteur
                int ecart = 256 / nb_couleurs; //Calcule l'écart pour écrire telle caractère en fonction de telle nuance de gris
				int current_ecart = ecart; //Permet de stocker l'écart courrant

                //Ecrit les caractères pour créer l'image ASCII
                for (int j = 1; j < nb_couleurs + 1; ++j)
                {
                    if (decimal < current_ecart)
                    {
                        lettre = palette[j - 1]; //Selectionne le caractère en fonction des caractères de la pallete
                        break;
                    }
                    else
                    {
						current_ecart += ecart; //Augmente l'écart courrant
                    }
                }
                std::cout << lettre;
                if ((i + 1) % imgSizeX == 0) //Vérifie si on atteints la largueur X
                {
                    std::cout << "\n"; //Si oui alors on fait un retour a la ligne
                }

            }
            std::cout << "-------------------------------------------------------------------------\n";
            std::cout << "Image converti en ASCII" << '\n'; //Message pour dire que l'image est converti
            std::cout << "-------------------------------------------------------------------------\n";
        }
    }
    else
    {
        std::cout << "Problème Le fichier ne s'est pas ouvert" << '\n'; //Renvoie une erreur
        std::exit(EXIT_FAILURE); //Ferme de programme en cas d'erreur
    }
}
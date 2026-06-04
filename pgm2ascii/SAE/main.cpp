//Sert à importer les bibliothèque nécessaire au bon fonctionnemant du programme
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include "fonctions.h"
#include "menu.h"
#ifdef _WIN32
#include <Windows.h>
#endif



int main(int argc, char* argv[])
{
#ifdef _WIN32 //Vérifie si le programme est ouvert sur Windows
	SetConsoleCP(CP_UTF8); //Change la norme d'encodage de la console
	SetConsoleOutputCP(CP_UTF8);

#endif

	std::vector<std::string> liens = GestionProg(argc, argv); //Vecteur qui stockent les liens (img, palette..)
	std::string lien_image = liens[0]; //Stock les liens individuelement dans chaque variable
	std::string lien_output = liens[1];
	std::string lien_palette = liens[2];
	if (liens[2] == "") //Si la palette n'est pas renseigner alors la palette par défaut est utilisé
	{
		lien_palette = "palette.txt";
	}
	OpenFile(lien_image); //Permet de vérifier que le fichier peut être ouvert
	auto dimensions = GetImageSize(lien_image); //Stock les dimensions de l'image
	int imgSizeX = dimensions.first; //Stock la dimension X de l'image
	int imgSizeY = dimensions.second; //Sotck la dimension Y de l'image
	//Stock chaque caractères de la palette dans un vector à partir d'un lien 
	std::vector<std::string> palette = GeneratePalette(lien_palette);
	//Permet de générer l'image en ASCII et de la sauvegarder dans un fichier
	CreateFileOutput(imgSizeX, imgSizeY, lien_image, palette, lien_output);
}
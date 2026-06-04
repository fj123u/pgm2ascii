//Sert à importer les bibliothèque nécessaire au bon fonctionnemant du programme
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <array>

//Fonction qui sert lancer le main avec des arguments qui font différentes actions
std::vector<std::string> GestionProg(int argc, char* argv[])
{
	if (argc > 7) //Nombre max d'arguments
	{
		std::cerr << "Erreur : Trop d'arguments entré" << '\n'; //Renvoie une erreur
		std::exit(EXIT_FAILURE); //Ferme le programme
	}
	std::vector<std::string> tabRetour(3); //Vecteur de retour
	for (int i = 0; i <= argc-1; ++i)
	{
		std::string arg = argv[i]; //Récupere l'argument actuel
		if (arg == "--help")
		{
			std::cout << //Affiche le menu "--help"
				"Usage :\n"
				"SAE [options]\n"
				"Options :\n"
				"--input fichier          Spécifie le fichier image à convertir\n"
				"                         Si ce paramètre n'est pas spécifié, le fichier est demandé via la console.\n\n"
				"--output fichier         Spécifie le fichier texte qui contiendra l'Ascii Art.\n"
				"                         Si ce paramètre n'est pas spécifié, l'Ascii Art est envoyé dans la console.\n\n"
				"--palette fichier        Spécifie un fichier texte contenant la palette de caractères Ascii.\n"
				"                         Chaque ligne du fichier contient un caractère en UTF-8, du plus sombre au plus clair.\n"
				"                         Si ce paramètre n'est pas spécifié, la palette par défaut est \"Wwli:,.\".\n\n"
				"--help                   Affiche cette aide.\n\n";
			exit(EXIT_SUCCESS); //Ferme le programme
		}
		else if (argv[i + 1] == NULL && i != argc - 1) //Vérifie si l'argument a bien un lien associer
		{
			std::cerr << "Argument pas de lien" << '\n'; //Renvoie une erreur sinon
			std::exit(EXIT_FAILURE); //Ferme le programme
		}
		else if (arg == "--input") //Cas ou l'argument est "--input"
		{
				std::string fichier_input = argv[i + 1]; //Recupère le prochaine argument qui est un lien
				tabRetour[0] = fichier_input; // Stock le lien dans le vecteur
		}
		else if (arg == "--output")
		{
				std::string fichier_output = argv[i + 1]; //Recupère le prochaine argument qui est un lien
				tabRetour[1] = fichier_output; // Stock le lien dans le vecteur
		}
		else if (arg == "--palette") //Cas ou l'argument est "--palette"
		{
			std::string lien_palette = argv[i + 1]; //Recupère le prochaine argument qui est un lien
			tabRetour[2] = lien_palette; // Stock le lien dans le vecteur
		}
	}
	return tabRetour;
}
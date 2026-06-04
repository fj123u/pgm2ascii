//Foction qui permet d'ouvrir un fichier pgm à parir d'un lien
void OpenFile(std::string lien);
//Fonction qui permet de récuperer et de renvoyé les dimensions X et Y de l'image pgm à partir d'un lien
std::pair<int, int> GetImageSize(std::string lien);
//Fonction qui créer l'image ASCII et la stock dans un fichier
void CreateFileOutput(int imgSizeX, int imgSizeY, std::string lien, std::vector<std::string> palette, std::string lienOutput);
//Fonction qui renvoie un vecteur de string qui stock tout les caractères d'une palette à partir de son lien
std::vector<std::string> GeneratePalette(std::string lienPalette);
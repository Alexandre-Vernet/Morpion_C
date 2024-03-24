// ------------------------------------------------
// Fichier : App.cpp
// Description : Gestion de l'application
// Créé par : Alexandre VERNET
// Le 31/03/19
// MàJ le 09/05/2019
// ------------------------------------------------

#include "App.h"

// Icone de l'application

const char* Application::Icone_xpm[] =
{
"16 16 4 1",
"  c #000000",      // Fond Noir
"# c Red",          // Croix Rouge
"* c #0064FF",
"$ c #4080FF",

"                ",
"##            ##",
" ##          ## ",
"  ##        ##  ",
"   ##      ##   ",
"    ##    ##    ",
"     ##  ##     ",
"      ####      ",
"      ####      ",
"     ##  ##     ",
"    ##    ##    ",
"   ##      ##   ",
"  ##        ##  ",
" ##          ## ",
"##            ##",
"                ",
};


bool Application::OnInit()
{
  objFenetre =  new Fenetre;
  objFenetre->Show();

  return true;
}


wxIMPLEMENT_APP( Application );




// ************************************************
// Fichier : App.h
// Description : Gestion de l'application
// Créé par : Alexandre VERNET
// Le 31/03/19
// MàJ le 09/05/2019
// ************************************************

#pragma once

#include <wx/wx.h>

#include "Fen.h"

class Application : public wxApp
{
public:
  static const char* Icone_xpm[];       // Icone de l'application
  virtual bool OnInit();

private:
  Fenetre* objFenetre;
};

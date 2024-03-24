// ************************************************
// Fichier : Fen.h
// Description : Gestion de la fenêtre
// Créé par : Alexandre VERNET
// Le 31/03/19
// MàJ le 09/05/2019
// ************************************************

#pragma once

#include <wx/wx.h>

class Fenetre : public wxFrame
{
public:
  Fenetre();
  void demarrerPartie();
  void placementPion();
  void afficherNbPartie();
  void Stats();

private:

  // Police

  wxColour couleurCroix, couleurRond;

  // Barre de menu

  wxMenuBar* barreMenu;
  wxMenu* menuFichier;        void nouvellePartie( wxCommandEvent& );
                              void quitter( wxCommandEvent& );

  wxMenu* menuAide;          void aPropos( wxCommandEvent& );

  // Bouton

  wxButton bt[9];

  void appuiBt0( wxCommandEvent& evt );
  void appuiBt1( wxCommandEvent& evt );
  void appuiBt2( wxCommandEvent& evt );
  void appuiBt3( wxCommandEvent& evt );
  void appuiBt4( wxCommandEvent& evt );
  void appuiBt5( wxCommandEvent& evt );
  void appuiBt6( wxCommandEvent& evt );
  void appuiBt7( wxCommandEvent& evt );
  void appuiBt8( wxCommandEvent& evt );

  // Scores

  bool croix[9];
  bool rond[9];
  bool box[9];           // Pour définir une éventuelle égalité

  // Nombre de partie jouée

  wxString partie;
  int nbPartie = 0;

  // Choix du pion

  wxString pion;
  int choixPion = 0;    // pour mettre à 0 l'algorithme qui place les pions

};

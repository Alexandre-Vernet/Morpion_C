// ------------------------------------------------
// Fichier : Fen.cpp
// Description : Gestion de la fenêtre
// Créé par : Alexandre VERNET
// Le 31/03/19
// MàJ le 09/05/2019
// ------------------------------------------------

#include <wx/aboutdlg.h>    // Boite de dialogue

#include <string>

#include "App.h"
#include "Fen.h"

// Création de la fenêtre

//------------------------------
Fenetre::Fenetre() : wxFrame( NULL, wxID_ANY, "Jeu du Morpion",
        wxDefaultPosition, wxSize(315,380), wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER  )
{

  // Afficher l'icone de l'application

  this->SetIcon( wxIcon( Application::Icone_xpm ) );

  // Centrer la fenêtre

  this->Center();

  // Barre de texte qui affiche le nombre de partie

  this->CreateStatusBar();
  this->SetStatusText( "Morpion" );

  // Préparation du menu

  wxMenuItem*  item;
  #define Item( menu, fctEvenement, texte, aide )                  \
      item = menu->Append( wxID_ANY, texte, aide );                \
      menu->Bind( wxEVT_MENU, fctEvenement, this, item->GetId() );

  // Créer le menu

  menuFichier = new wxMenu;
  Item( menuFichier, nouvellePartie, "&Nouvelle partie \tAlt-N", "Créer une nouvelle partie" );
  Item( menuFichier, quitter, "&Quitter \tAlt-Q", "Quitter l'application" );

  menuAide = new wxMenu;
  Item( menuAide, aPropos, "&A propos ... \tAlt-P", "Afficher les détails de l'application" );

  // Afficher le menu

  barreMenu = new wxMenuBar;
  barreMenu->Append( menuFichier, "&Fichier" );
  barreMenu->Append( menuAide,    "&?" );
  this->SetMenuBar( barreMenu );

  // Placer les boutons

  // ------------- 1 ère ligne -------------------------

  bt[0].Create( this, wxID_ANY, "",
                                        wxPoint(5,5), wxSize(100,100) );
  bt[0].Bind( wxEVT_BUTTON, appuiBt0, this );


  bt[1].Create(this, wxID_ANY, "",
                                        wxPoint(105, 5), wxSize(100,100) );
  bt[1].Bind( wxEVT_BUTTON, appuiBt1, this );


  bt[2].Create(this, wxID_ANY, "",
                                        wxPoint(205, 5), wxSize(100,100) );
  bt[2].Bind( wxEVT_BUTTON, appuiBt2, this );

  // ------------- 2 ème ligne -------------------------

  bt[3].Create( this, wxID_ANY, "",
                                        wxPoint(5,105), wxSize(100,100) );
  bt[3].Bind( wxEVT_BUTTON, appuiBt3, this );


  bt[4].Create( this, wxID_ANY, "",
                                        wxPoint(105,105), wxSize(100,100) );
  bt[4].Bind( wxEVT_BUTTON, appuiBt4, this );


  bt[5].Create( this, wxID_ANY, "",
                                        wxPoint(205,105), wxSize(100,100) );
  bt[5].Bind( wxEVT_BUTTON, appuiBt5, this );

    // ------------- 3 ème ligne -------------------------

  bt[6].Create( this, wxID_ANY, "",
                                        wxPoint(5,205), wxSize(100,100) );
  bt[6].Bind( wxEVT_BUTTON, appuiBt6, this );


  bt[7].Create(this, wxID_ANY, "",
                                        wxPoint(105, 205), wxSize(100,100) );
  bt[7].Bind( wxEVT_BUTTON, appuiBt7, this );


  bt[8].Create(this, wxID_ANY, "",
                                        wxPoint(205, 205), wxSize(100,100) );
  bt[8].Bind( wxEVT_BUTTON, appuiBt8, this );

  // Couleur & police

  couleurCroix = wxColour (255, 0, 0);
  couleurRond = wxColour (0, 0, 255);

  for ( int i = 0; i <= 8; i ++ )
  {
    bt[i].SetFont( wxFont( wxFontInfo(15) ) );
  }

}

//---------------------

  // Evenement du menu fichier

void Fenetre::nouvellePartie( wxCommandEvent& )
{
  int answer = wxMessageBox( "Voulez-vous recommencer une partie ?", "Recommencer ?",
                            wxYES_NO | wxCENTRE );

  if ( answer == wxYES )
  {
    demarrerPartie();
  }
  else if ( answer == wxNO )
  {
    // Annuler
  }
}

void Fenetre::quitter ( wxCommandEvent& )
{
  int answer = wxMessageBox( "Voulez-vous quitter le jeu ?", "Quitter ?",
                            wxYES_NO | wxCENTRE );

  if (answer == wxYES)
  {
    this->Close();
  }
  else if ( answer == wxNO )
  {
    // Retour au jeu
  }
}

// Evenement du menu A propos

void Fenetre::aPropos( wxCommandEvent& )
{
  wxAboutDialogInfo infoAPropos;
  infoAPropos.SetName("Morpion");
  infoAPropos.SetIcon(wxIcon( Application::Icone_xpm ) );
  infoAPropos.AddDeveloper("Alexandre VERNET");
  infoAPropos.SetWebSite("http://alexandre-vernet.000webhostapp.com");
  infoAPropos.SetCopyright("(C) 2019");
  infoAPropos.SetDescription("Jeu du Morpion");
  wxAboutBox( infoAPropos );
}

// Intialisation des pions

void Fenetre::demarrerPartie()
{
  // Reset l'algo qui définit croix ou rond

  choixPion = 0;

  // Afficher le nombre de partie

  nbPartie++;
  afficherNbPartie();

  // Reset le tableau pour avoir tous les booléens à false

  for ( int i = 0; i <= 8; i++ )
  {
    croix[i] = false;
    rond[i] = false;
    box[i] = false;
  }

  // Supprime tous les pions sur le plateau

  for ( int i = 0; i <= 8; i++ )
  {
    bt[i].SetLabel("");
  }
}

// Affiche la barre d'état avec le nombre de partie

void Fenetre::afficherNbPartie()
{
  switch ( nbPartie )
  {
    case 0:   partie =  "Nombre de partie : 0"; break;
    case 1:   partie =  "Nombre de partie : 1"; break;
    case 2:   partie =  "Nombre de partie : 2"; break;
    case 3:   partie =  "Nombre de partie : 3"; break;
    case 4:   partie =  "Nombre de partie : 4"; break;
    case 5:   partie =  "Nombre de partie : 5"; break;
    case 6:   partie =  "Nombre de partie : 6"; break;
    case 7:   partie =  "Nombre de partie : 7"; break;
    case 8:   partie =  "Nombre de partie : 8"; break;
    case 9:   partie =  "Nombre de partie : 9"; break;
    case 10:  partie =  "Nombre de partie : 10"; break;
    case 11:  partie =  "Nombre de partie : 11"; break;
    case 12:  partie =  "Nombre de partie : 12"; break;
    case 13:  partie =  "Nombre de partie : 13"; break;
    case 14:  partie =  "Nombre de partie : 14"; break;
    case 15:  partie =  "Nombre de partie : 15"; break;
    case 16:  partie =  "Nombre de partie : 16"; break;
    case 17:  partie =  "Nombre de partie : 17"; break;
    case 18:  partie =  "Nombre de partie : 18"; break;
    case 19:  partie =  "Nombre de partie : 19"; break;
    case 20:  partie =  "Nombre de partie : 20"; break;
    case 21:  partie =  "Nombre de partie : 21"; break;
    case 22:  partie =  "Nombre de partie : 22"; break;
    case 23:  partie =  "Nombre de partie : 23"; break;
    case 24:  partie =  "Nombre de partie : 24"; break;
    case 25:  partie =  "Nombre de partie : 25"; break;
    case 26:  partie =  "Nombre de partie : 26"; break;
    case 27:  partie =  "Nombre de partie : 27"; break;
    case 28:  partie =  "Nombre de partie : 28"; break;
    case 29:  partie =  "Nombre de partie : 29"; break;
    default: partie =   "Nombre de partie : ..."; break;
  }

  this->SetStatusText( partie );
}

void Fenetre::placementPion()
{
  switch ( choixPion )
  {
  case 0: pion = "X"; break;
  case 1: pion = "O"; break;
  case 2: pion = "X"; break;
  case 3: pion = "O"; break;
  case 4: pion = "X"; break;
  case 5: pion = "O"; break;
  case 6: pion = "X"; break;
  case 7: pion = "O"; break;
  case 8: pion = "X"; break;
  default: pion = ""; break;
  }
  choixPion++;
}

// Gestion des boutons


void Fenetre::appuiBt0( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[0].SetLabel( message );

  if ( pion == "X" ) { croix[0] = true; bt[0].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[0] = true;  bt[0].SetForegroundColour( couleurRond ); }
  box[0] = true;
  Stats();
}

void Fenetre::appuiBt1( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[1].SetLabel( message );

  if ( pion == "X" ) { croix[1] = true; bt[1].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[1] = true;  bt[1].SetForegroundColour( couleurRond ); }
  box[1] = true;
  Stats();
}

void Fenetre::appuiBt2( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[2].SetLabel( message );

  if ( pion == "X" ) { croix[2] = true; bt[2].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[2] = true;  bt[2].SetForegroundColour( couleurRond ); }
  box[2] = true;
  Stats();
}
void Fenetre::appuiBt3( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[3].SetLabel( message );

  if ( pion == "X" ) { croix[3] = true; bt[3].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[3] = true;  bt[3].SetForegroundColour( couleurRond ); }
  box[3] = true;
  Stats();
}
void Fenetre::appuiBt4( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[4].SetLabel( message );

  if ( pion == "X" ) { croix[4] = true; bt[4].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[4] = true;  bt[4].SetForegroundColour( couleurRond ); }
  box[4] = true;
  Stats();
}
void Fenetre::appuiBt5( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[5].SetLabel( message );

  if ( pion == "X" ) { croix[5] = true; bt[5].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[5] = true;  bt[5].SetForegroundColour( couleurRond ); }
  box[5] = true;
  Stats();
}
void Fenetre::appuiBt6( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[6].SetLabel( message );

  if ( pion == "X" ) { croix[6] = true; bt[6].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[6] = true;  bt[6].SetForegroundColour( couleurRond ); }
  box[6] = true;
  Stats();
}
void Fenetre::appuiBt7( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[7].SetLabel( message );

  if ( pion == "X" ) { croix[7] = true; bt[7].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[7] = true;  bt[7].SetForegroundColour( couleurRond ); }
  box[7] = true;
  Stats();
}
void Fenetre::appuiBt8( wxCommandEvent& evt )
{
  placementPion();
  wxString message;
  message << pion;
  bt[8].SetLabel( message );

  if ( pion == "X" ) { croix[8] = true; bt[8].SetForegroundColour( couleurCroix ); }
  if ( pion == "O" ) { rond[8] = true;  bt[8].SetForegroundColour( couleurRond ); }
  box[8] = true;
  Stats();
}

// Statistique du jeu

void Fenetre::Stats()
{

  // Croix

       // Ligne

  if (
       ( croix[0] == true && croix[1] == true && croix[2] == true ) ||
       ( croix[3] == true && croix[4] == true && croix[5] == true ) ||
       ( croix[6] == true && croix[7] == true && croix[8] == true ) ||

       // Colonne

       ( croix[0] == true && croix[3] == true && croix[6] == true ) ||
       ( croix[1] == true && croix[4] == true && croix[7] == true ) ||
       ( croix[2] == true && croix[5] == true && croix[8] == true ) ||

       // Diagonale gauche vers droite

       ( croix[0] == true && croix[4] == true && croix[8] == true ) ||

       // Diagonale droite vers gauche

       ( croix[2] == true && croix[4] == true && croix[6] == true )
     )

  {
    wxMessageBox( "Le joueur 1 gagne !", "Victoire" );
    demarrerPartie();
    afficherNbPartie();
  }

  // Rond

      // Ligne

  if (
       ( rond[0] == true && rond[1] == true && rond[2] == true ) ||
       ( rond[3] == true && rond[4] == true && rond[5] == true ) ||
       ( rond[6] == true && rond[7] == true && rond[8] == true ) ||

       // Colonne

       ( rond[0] == true && rond[3] == true && rond[6] == true ) ||
       ( rond[1] == true && rond[4] == true && rond[7] == true ) ||
       ( rond[2] == true && rond[5] == true && rond[8] == true ) ||

       // Diagonale gauche vers droite

       ( rond[0] == true && rond[4] == true && rond[8] == true ) ||

       // Diagonale droite vers gauche

       ( rond[2] == true && rond[4] == true && rond[6] == true )
     )
  {
    wxMessageBox ( "Le joueur 2 gagne !", "Victoire" );
    demarrerPartie();
    afficherNbPartie();
  }

  // Egalité

  if ( box[0] == true && box[1] == true && box[2] == true &&
       box[3] == true && box[4] == true && box[5] == true &&
       box[6] == true && box[7] == true && box[8] == true )
  {
    wxMessageBox("Egalité !", "Egalité");
    demarrerPartie();
    afficherNbPartie();
  }
}

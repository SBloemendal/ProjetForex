/**
 * \file principal.h
 * \brief Fenetre principale de l'application.
 *
 * Affiche une vue des valeurs les plus récentes des couples de devises sélectionnés,
 * et un graphique de l'évolution d'un couple de devises sélectionné.
 * A l'initialisation, crée une base de donnée SQLite, envoie une requète HTTP au site du Forex,
 * récupère les infos dans la réponse du Forex et les stocke dans la base de donnée pour les afficher
 * dans l'affichage principale. Un timer est lancé pour répéter la requete toutes les x secondes, paramétrable
 * par l'utilisateur.
 */


#ifndef PRINCIPAL_H
#define PRINCIPAL_H


#include <QApplication>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSettings>
#include <QModelIndex>

class QWebView ;
class QSqlQueryModel ;
class QTableView ;
class QHBoxLayout ;
class QVBoxLayout ;

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal();

    /** Crée une base de donnée si inexistente et s'y connecte */
    bool creerBdd() ;

    /** Indique au modele de se mettre a jour avec la nouvelle URL qu'on lui fournit.
     * Rafraichit le QSqlQuery pour appliquer les parametres
     * contenue dans 'urlFiltreDevises' définie dans 'DialogueChoixDevises'.
     */
    void rafraichitSQLQueryModel() ;


public slots:
    /** Fonction pour recuperer les données de la requete HTTP
     * Pour chaque couple de devises, on crée un objet 'CoupleDevise'
     * et on y stocke les valeurs récupéré du web service.
     * On accède aux valeurs par le biais des CSSselector grace à un QWebElement
     */
    void recupereDonnees() ;


private slots:
    /** Mise a jour de la requete a la base de donnée pour appliquer les choix d'affichage de cotations.
     *  Le slot attend un QString contenant les noms des couples de cotation à afficher.
     */
    inline void setUrlChoixDevises(QString url) { urlChoixDevises = url ; }

    /** Mise a jour de la requette HTTP permettant de recevoir les données de cotation depuis le site FOREX.
     *  Le slot attend un QString contenant les numéros des couples de devises à récuperer.
     */
    inline void setUrlFiltreDevises(QString url) { urlFiltreDevises = url ; }

    /** Envoi de la requette HTTP par l'intermédiaire du QWebView. */
    void connexionHttp() ;

    /** Ouvre la fenetre d'option 'Choix d'affichage des couples de devises' */
    void choixCoupleDevises() ;

    /** Ouvre une fenetre de dialogue 'Choix d'intervalle de temps' */
    void intervalleTemps() ;

    /** Ouvre une fenetre de dialogue 'simulation de transaction' */
    void simulationTransaction() ;

    /** Selection du couple de devises a afficher dans le graphique de la fenetre principale. */
    void requeteGraph(QModelIndex index) ;

    /** Ouvre une fenetre 'Transaction automatique' */
    void transactionAuto() ;

    /** Ouvre une fenetre 'Options' */
    void options() ;

    /** Affiche ou masque le graphique dans la fenetre principale */
    void afficheGraphique();


private:
    QWidget *zoneCentrale ;
    QHBoxLayout* layout ;
    QVBoxLayout* layoutGauche ;
    QVBoxLayout* layoutDroit ;
    QWebView* webView ;
    QWebView* graph ;
    QSqlQueryModel* modeleQ ;
    QTableView* tableView ;
    QSqlDatabase db ;
    QString urlPourModele ;
    QString urlChoixDevises ;
    QString urlFiltreDevises ;
    QString serveur ;
    QString nomBdd ;
    QString loginBdd ;
    QString passwordBdd ;
    QString urlForex ;
    int delaiTimer ;
};

#endif // PRINCIPAL_H


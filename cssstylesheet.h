/**
 * \file cssstylesheet.h
 * \brief Fichier qui contient toutes les règles CSS à appliquer à l'ensemble de l'application.
 */

#ifndef CSSSTYLESHEET
#define CSSSTYLESHEET


/** Feuille de style de l'application.
 * Gère l'apparence de toutes les fenetres.
 */
QString stylesheet ="QDialog   {"
                    "           border: 3px solid gray;"
                    "           background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f2f3f4, stop: 1 #b2beb5);"
                    "          }"
                    "QLabel, QGroupBox, QComboBox, QCheckBox  {"
                    "           font-weight: bold;"
                    "           font-size: 11px;"
                    "          }"
                    "QLineEdit {"
                    "            padding: 1px;"
                    "            border-style: solid;"
                    "            border: 2px solid gray;"
                    "            border-radius: 8px;"
                    "            font-weight: bold;"
                    "            font-size: 11px;"
                    "          }"
                    "QPushButton {"
                    "            color: white;"
                    "            background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #68C, stop: 0.1 #79D, stop: 0.49 #57B, stop: 0.5 #46A, stop: 1 #57B);"
                    "            border-width: 1px;"
                    "            border-color: #339;"
                    "            border-style: solid;"
                    "            border-radius: 7;"
                    "            padding: 3px;"
                    "            font-size: 10px;"
                    "            padding-left: 5px;"
                    "            padding-right: 5px;"
                    "            min-width: 100px;"
                    "            max-width: 100px;"
                    "            min-height: 15px;"
                    "            max-height: 60px;"
                    "          }"
                    "QPushButton:hover {"
                    "            background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);"
                    "          }"
                    "QMainWindow {"
                    "            border-width: 0px 0px 0px 500px;"
                    "            border-image: url(:/images/Uk-Forex.jpg) 0 0 0 700 repeat stretch;"
                    "          }"
                    "QHeaderView, QWebView, QTableView#view, QMenuBar, QMenuBar::item {"
                    "            background-color: transparent;"
                    "            font-weight: bold;"
                    "            font-size: 11px;"
                    "          }"
                    "QMenu  {"
                    "            background-color: #F1F1F1;"
                    "            font-weight: bold;"
                    "            font-size: 11px;"
                    "          }"
                    "QMenu::selected, QMenuBar::selected  {"
                    "            color: #457DBB;"
                    "            background-color: white;"
                    "            font-weight: bold;"
                    "            font-size: 11px;"
                    "          }"
                    "QHeaderView::section {"
                    "            background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #68C, stop: 0.1 #79D, stop: 0.49 #57B, stop: 0.5 #46A, stop: 1 #57B);"
                    "            color: white;"
                    "            padding:2px;"
                    "            border: 0px;"
                    "            margin: 0px;"
                    "          }";


#endif // CSSSTYLESHEET


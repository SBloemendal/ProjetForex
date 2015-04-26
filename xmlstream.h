/**
 * \file xmlstream.h
 * \brief Fichier qui rassemble les deux fonctions permettant au QSettings de manipuler un fichier XML.
 */


#ifndef XMLSTREAM
#define XMLSTREAM

#include <QXmlStreamWriter>
#include <QDebug>


/** Permet a QSettings de lire un fichier XML
 */
static bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map) {
  QXmlStreamReader xmlReader(&device);
  QStringList elements;

  // Tant que la fin n'est pas atteinte et qu'aucune erreur ne s'est produite
  while (!xmlReader.atEnd() && !xmlReader.hasError()) {
    // Lire l'élément suivant
    xmlReader.readNext();

    // Si l'élément est un StartElement mais pas "settings"
    if (xmlReader.isStartElement() && xmlReader.name() != "Settings") {
      // Ajoute l'element à la liste
      elements.append(xmlReader.name().toString());
    // Sinon si c'est un EndElement
    } else if (xmlReader.isEndElement()) {
      // et que la liste n'est pas vide, on supprime le dernier élément
      if(!elements.isEmpty()) elements.removeLast();
    // Si l'element contient une valeur
    } else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
      QString key;

      // On ajoute des éléments à 'key'
      for(int i = 0; i < elements.size(); i++) {
        if(i != 0) key += "/";
        key += elements.at(i);
      }

      // Puis on donne à QSettings la valeur pour ces elements
      map[key] = xmlReader.text().toString();
    }
  }

  // Affiche un warning si erreur
  if (xmlReader.hasError()) {
    qWarning() << xmlReader.errorString();
    return false;
  }

  return true;
}



/** Permet a QSettings d'ecrire dans un fichier XML
 */
static bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map) {
  QXmlStreamWriter xmlWriter(&device);

  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("Settings");

  QStringList prev_elements;
  QSettings::SettingsMap::ConstIterator map_i;

  // On lit tous les éléments de la map
  for (map_i = map.begin(); map_i != map.end(); map_i++) {

    QStringList elements = map_i.key().split("/");

    int x = 0;
    // Pour déterminer le nombre d'éléments de fermeture, compare les elements deja ouverts avec ceux a ouvrir
    // Si on en a 2 identiques, on fermera le dernier.
    while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x)) {
      x++;
    }

    // Fermer le dernier element ouvert
    for(int i = prev_elements.size() - 1; i >= x; i--) {
      xmlWriter.writeEndElement();
    }

    // Ouvrir tous les elements dans 'elements'
    for (int i = x; i < elements.size(); i++) {
      xmlWriter.writeStartElement(elements.at(i));
    }

    // entrer la valeur
    xmlWriter.writeCharacters(map_i.value().toString());

    prev_elements = elements;
  }


  // Une fois qu'il n'y a plus d'elements, fermer  les derniers éléments ouverts
  for(int i = 0; i < prev_elements.size(); i++) {
    xmlWriter.writeEndElement();
  }

  // Puis on ferme l'elements 'settings' et on ferme le document
  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  return true;
}

#endif // XMLSTREAM


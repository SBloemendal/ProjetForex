#ifndef XMLSTREAM
#define XMLSTREAM

#include <QXmlStreamWriter>
#include <QDebug>


/** Permet a QSettings de lire un fichier XML
 */
static bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map) {
  QXmlStreamReader xmlReader(&device);
  QStringList elements;

  // Tant que la fin ne est pas atteint et aucune erreur ne se est produite
  while (!xmlReader.atEnd() && !xmlReader.hasError()) {
    // Lire le jeton suivant
    xmlReader.readNext();

    // Quand l'objet est un StartElement
    if (xmlReader.isStartElement() && xmlReader.name() != "Settings") {
      // Ajouter un article à la liste
      elements.append(xmlReader.name().toString());
    // Quand l'objet est un EndElement
    } else if (xmlReader.isEndElement()) {
      // Pour supprimer le dernier élément
      if(!elements.isEmpty()) elements.removeLast();
    // Si jeton contient une valeur
    } else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
      QString key;

      // Ajouter des éléments à string
      for(int i = 0; i < elements.size(); i++) {
        if(i != 0) key += "/";
        key += elements.at(i);
      }

      // Entrer la valeur map
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

  // Grâce à tous les éléments de la carte
  for (map_i = map.begin(); map_i != map.end(); map_i++) {

    QStringList elements = map_i.key().split("/");

    int x = 0;
    // Pour déterminer les éléments de fermeture
    while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x)) {
      x++;
    }

    // Fermer Articles
    for(int i = prev_elements.size() - 1; i >= x; i--) {
      xmlWriter.writeEndElement();
    }

    // Ouvrir Tous les documents
    for (int i = x; i < elements.size(); i++) {
      xmlWriter.writeStartElement(elements.at(i));
    }

    // entrer la valeur
    xmlWriter.writeCharacters(map_i.value().toString());

    prev_elements = elements;
  }

  // Fermer éléments exceptionnels
  for(int i = 0; i < prev_elements.size(); i++) {
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  return true;
}

#endif // XMLSTREAM


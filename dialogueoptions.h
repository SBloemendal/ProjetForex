#ifndef DIALOGUEOPTIONS_H
#define DIALOGUEOPTIONS_H

#include "principal.h"
#include <QDialog>

class QCheckBox ;

class DialogueOptions : public QDialog
{
    Q_OBJECT

public:
    DialogueOptions();
    ~DialogueOptions();
};

#endif // DIALOGUEOPTIONS_H

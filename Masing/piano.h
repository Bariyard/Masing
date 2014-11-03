#ifndef PIANO_H
#define PIANO_H

#include <QWidget>
#include "ui_piano.h"


#define kNumPointsInMyBuffer 1024



class Piano : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Note_Name);

public:

    Piano(QWidget *parent = 0);
    ~Piano();

    enum Note_Name {C5 = 0,C6};

public:
    Ui::PianoRoll piano_ui;

private slots:
	void createPianoKeyAction();
    void piano_press();
    void piano_release();




};

#endif // PIANO_H

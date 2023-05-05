#ifndef MSDWIDGET_H
#define MSDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "../MSDScript/parser.h"
#include "../MSDScript/env.h"
#include "../MSDScript/val.h"

class MSDWidget : public QWidget
{
    Q_OBJECT
    QGridLayout* mainLayout;

    QLabel* expressionLabel;
    QTextEdit* expressionEdit;
    QGroupBox* modeGroup;
    QVBoxLayout* modeLayout;
    QPushButton* fileB;
    QRadioButton* interpB;
    QRadioButton* prettyPrintB;
    QPushButton* submitB;

    QLabel* resultLabel;
    QTextEdit* resultEdit;
    QPushButton* resetB;

public:
    explicit MSDWidget(QWidget *parent = nullptr);
    void parse();
    void reset();
    void loadFile();
signals:

};

#endif // MSDWIDGET_H

#include "msdwidget.h"

MSDWidget::MSDWidget(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QGridLayout;

    expressionLabel = new QLabel("Expression: ");
    expressionEdit = new QTextEdit;
    modeGroup = new QGroupBox;
    modeLayout = new QVBoxLayout;
    fileB = new QPushButton("Input From File");
    interpB = new QRadioButton("Interp");
    prettyPrintB = new QRadioButton("Pretty Print");
    modeLayout->addWidget(interpB);
    modeLayout->addWidget(prettyPrintB);
    modeGroup->setLayout(modeLayout);
    submitB = new QPushButton("Submit");

    mainLayout->addWidget(expressionLabel, 0, 0);
    mainLayout->addWidget(expressionEdit, 0, 1);
    mainLayout->addWidget(modeGroup, 1, 1);
    mainLayout->addWidget(fileB, 2, 1);
    mainLayout->addWidget(submitB, 3, 1);


    resultLabel = new QLabel("Result: ");
    resultEdit = new QTextEdit;
    resetB = new QPushButton("Reset");

    mainLayout->addWidget(resultLabel, 4, 0);
    mainLayout->addWidget(resultEdit, 4, 1);
    mainLayout->addWidget(resetB, 5, 1);

    setLayout(mainLayout);

    QObject::connect(submitB, &QPushButton::clicked, this, &MSDWidget::parse);
    QObject::connect(resetB, &QPushButton::clicked, this, &MSDWidget::reset);
    QObject::connect(fileB, &QPushButton::clicked, this, &MSDWidget::loadFile);
    setWindowTitle("MSDScript");
}

void MSDWidget::parse() {
    PTR(Expr) expr = parse_str(expressionEdit->toPlainText().toUtf8().constData());
    std::string result;
    if (interpB->isChecked()) {
        result = expr->interp(Env::empty)->to_string();
    } else {
        result = expr->to_pretty_string();
    }
    resultEdit->setText(QString::fromStdString(result));
}

void MSDWidget::reset() {
    expressionEdit->clear();
    resultEdit->clear();
    QList<QRadioButton*> buttons = modeGroup->findChildren<QRadioButton*>();
    for (QRadioButton* button : buttons) {
        button->setAutoExclusive(false);
        button->setChecked(false);
        button->setAutoExclusive(true);
    }
}

void MSDWidget::loadFile() {
    QString filename = QFileDialog::getOpenFileName(this);
    QFile file(filename);
    if (!file.exists()) {
        qCritical() << "File Not Found!";
    }
    if (!file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        qCritical() << "Could not open the file!";
        qCritical() << file.errorString();
        return;
    }
    QTextStream stream(&file);
    QString data = stream.readAll();
    expressionEdit->setText(data);
    file.close();
}

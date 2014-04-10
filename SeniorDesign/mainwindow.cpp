#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "runningdialog.h"
#include "exampleprogram.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    runDialog(NULL)
{
    createLog();
    createOptions();
    createMenu();
    createLayout();
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createLog()
{
    outputLog = new QTextEdit;
    outputLog->setReadOnly(true);
}

void MainWindow::createLayout()
{
    mainWidget = new QWidget(this);
    layout = new QHBoxLayout;
    leftLayout = new QVBoxLayout;
    leftLayout->addWidget(outputLog);
    leftLayout->addLayout(inputLayout);
    leftLayout->addLayout(outputLayout);
    layout->addLayout(leftLayout);
    mainWidget->setLayout(layout);
}

void MainWindow::createMenu()
{
    fileMenu = new QMenu("&File");
    actInputOpen = new QAction("&Open", this);
    actClose = new QAction("&Close", this);
    actRun = new QAction("&Run", this);

    connect(actInputOpen, SIGNAL(triggered()), this, SLOT(onInputOpen()));
    connect(actClose, SIGNAL(triggered()), this, SLOT(onClose()));
    connect(actRun, SIGNAL(triggered()), this, SLOT(onStart()));

    fileMenu->addAction(actInputOpen);
    fileMenu->addAction(actRun);
    fileMenu->addAction(actClose);

    menuBar()->addMenu(fileMenu);
}

void MainWindow::createOptions()
{
    inputLayout = new QHBoxLayout;
    outputLayout = new QHBoxLayout;
    optionKLabel = new QLabel("# points within circle?");
    optionK = new QSpinBox(this);
    optionK->setFixedSize(50,25);
    //TODO: range 0-# of points
    optionK->setRange(0,100);

    optionNumCirclesLabel = new QLabel("# circles?");
    optionNumCircles = new QSpinBox(this);
    optionNumCircles->setFixedSize(50,25);

    startButton = new QPushButton("GO");
    connect(startButton, SIGNAL(clicked()), this, SLOT(onStart()));

    saveButton = new QPushButton("Save");
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSave()));

    inputFileEdit = new QLineEdit;
    inputBrowseButton = new QPushButton("Browse");
    connect(inputBrowseButton, SIGNAL(clicked()), this, SLOT(onInputOpen()));

    outputFileEdit = new QLineEdit;
    outputBrowseButton = new QPushButton("Browse");
    connect(outputBrowseButton, SIGNAL(clicked()), this, SLOT(onOutputOpen()));

    QLabel * input = new QLabel ("Input:   ");
    QLabel * output = new QLabel("Output: ");
    inputLayout->addWidget(input);
    inputLayout->addWidget(inputFileEdit);
    inputLayout->addWidget(inputBrowseButton);
    inputLayout->addWidget(optionNumCirclesLabel);
    inputLayout->addWidget(optionNumCircles);
    inputLayout->addWidget(optionKLabel);
    inputLayout->addWidget(optionK);
    outputLayout->addWidget(output);
    outputLayout->addWidget(outputFileEdit);
    outputLayout->addWidget(outputBrowseButton);
    outputLayout->addWidget(startButton);
}

void MainWindow::onStart()
{
    startButton->setEnabled(false);

    runDialog = new RunningDialog();
    QString programName = "longexample.exe";
    runDialog->setProgramName(qApp->applicationDirPath() + "/" + programName);
    runDialog->setInputFilename(inputFileEdit->text());
    runDialog->setOutputFilename(outputFileEdit->text());
    connect(runDialog, SIGNAL(accepted()), this, SLOT(onProgramFinished()));
    connect(runDialog, SIGNAL(canceled()), this, SLOT(onProgramCancelled()));
    runDialog->exec();
}

void MainWindow::onProgramFinished()
{
    //qDebug() << "Finished";
    runDialog->hide();
    QString filename = outputFileEdit->text();
    if(filename != "") {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
        outputLog->append(file.readAll());
        outputLog->append("Result has been saved to " + filename);
        file.close();
    }
    startButton->setEnabled(true);
}

void MainWindow::onProgramCancelled()
{
    outputLog->append("Program has been terminated.");
    if(runDialog && runDialog->getProc()->state() == QProcess::Running) {
        runDialog->getProc()->kill();
        QMessageBox errorBox;
        errorBox.critical(0, "", "Program has been terminated");
    }
    startButton->setEnabled(true);
}

void MainWindow::onInputOpen()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                "Select Input File",
                QDir::homePath(),
                "Text files (*.txt);;All files (*.*)"
            );
    if(filename != "")
        inputFileEdit->setText(filename);
}

void MainWindow::onOutputOpen()
{
    QString filename = QFileDialog::getSaveFileName(
                this,
                "Select Output Filename",
                QDir::homePath(),
                "Text files (*.txt);;All files (*.*)"
            );
    if(filename != "")
        outputFileEdit->setText(filename);
}

void MainWindow::onClose()
{
    QApplication::quit();
}

void MainWindow::onSave()
{
    QString filename = outputFileEdit->text();
    if(filename != "") {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_1);
        out << outputLog->toPlainText().trimmed();
        outputLog->append("Log has been saved to " + filename);
        file.close();
    }
}

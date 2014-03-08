#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    layout = new QVBoxLayout;
    layout->addWidget(outputLog);
    layout->addLayout(optionsLayout);
    mainWidget->setLayout(layout);
}

void MainWindow::createMenu()
{
    fileMenu = new QMenu("&File");
    actOpen = new QAction("&Open", this);

    connect(actOpen, SIGNAL(triggered()), this, SLOT(onOpen()));

    fileMenu->addAction(actOpen);

    menuBar()->addMenu(fileMenu);
}

void MainWindow::createOptions()
{
    optionsLayout = new QHBoxLayout;
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

    inputFileEdit = new QLineEdit;
    browseButton = new QPushButton("Browse");
    connect(browseButton, SIGNAL(clicked()), this, SLOT(onOpen()));

    optionsLayout->addWidget(inputFileEdit);
    optionsLayout->addWidget(browseButton);
    optionsLayout->addWidget(optionNumCirclesLabel);
    optionsLayout->addWidget(optionNumCircles);
    optionsLayout->addWidget(optionKLabel);
    optionsLayout->addWidget(optionK);
    optionsLayout->addWidget(startButton);
}

void MainWindow::onStart()
{
    startButton->setEnabled(false);
}

void MainWindow::onOpen()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                "select input file",
                NULL,
                "All files (*.*)"
            );
    //program.exe K_param input_filename
    //QProcess *proc = new QProcess();
    //proc->start(filename);
    inputFileEdit->setText(filename);
}

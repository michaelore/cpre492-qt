#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSpinBox>
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMenu>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onOpen();
    void onStart();

private:
    Ui::MainWindow *ui;

    QTextEdit *outputLog;
    QWidget *mainWidget;
    QMenu *fileMenu;
    QAction *actOpen;
    QAction *actSave;

    QLabel *optionKLabel;
    QSpinBox *optionK;

    QLabel *optionNumCirclesLabel;
    QSpinBox *optionNumCircles;

    QVBoxLayout *layout;
    QHBoxLayout *optionsLayout;

    QPushButton *startButton;
    QLineEdit *inputFileEdit;
    QPushButton *browseButton;

    void createLog();
    void createMenu();
    void createLayout();
    void createOptions();
};

#endif // MAINWINDOW_H

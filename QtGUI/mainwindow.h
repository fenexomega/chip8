#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <atomic>
#include "chip8emulator.h"

namespace Ui {
class MainWindow;
}

constexpr const char* defaultBackgroundImage = "./bkg";


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


private slots:
	void printErrorMessage(const QString errorMsg);
	void loadRom();


private:
	Ui::MainWindow *ui;
	std::atomic<bool> m_interruptEmulator;
	Chip8Emulator m_emulator;

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <atomic>
#include "chip8emulator.h"

namespace Ui {
class MainWindow;
}





class MainWindow final : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();


private slots:
	void printErrorMessage(const QString errorMsg) const;
	void loadRom();


private:
	Ui::MainWindow *ui;
	std::atomic<bool> m_interruptEmulator;
	Chip8Emulator m_emulator;
	static constexpr const char* defaultBackgroundImage = "./bkg";
	static constexpr unsigned defaultWindowWidth        = 512;
	static constexpr unsigned defaultWindowHeight       = 256;

};

#endif // MAINWINDOW_H

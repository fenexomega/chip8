#ifndef CHIP8EMULATOR_H
#define CHIP8EMULATOR_H
#include <QMainWindow>
#include <QThread>
#include <atomic>




class Chip8Emulator final : public QThread
{

public:
	Chip8Emulator(QMainWindow &win, std::atomic<bool> &interrupt);
	void run() override;
	inline void setRomFile(QString fileName);


private:
	QMainWindow &m_mainWin;
	std::atomic<bool> &m_interrupt;		// when true the run method returns at once.
	QString m_currentRom;
	static constexpr unsigned defaultWidth  = 512;
	static constexpr unsigned defaultHeight = 256;
};



inline
void Chip8Emulator::setRomFile(QString fileName){
		m_currentRom = std::move(fileName);
}







#endif // CHIP8EMULATOR_H




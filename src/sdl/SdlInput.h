#ifndef SDLINPUT_H
#define SDLINPUT_H
#include <vector>
#include "../chip8/interfaces/iInput.h"
class SdlInput final : public iInput
{
	using KeyPair = std::pair<EmulatorKey, int>;
public:
	SdlInput();
	SdlInput(const SdlInput&) = delete;
	SdlInput& operator=(const SdlInput&) = delete;
	~SdlInput();

	bool Initialize() override;
	void Dispose() noexcept override;

	void SetKey(EmulatorKey key, int value) override;
	bool IsKeyPressed(const EmulatorKey key) const override;
	EmulatorKey GetPressedKey() const override;
	bool UpdateKeys() override;
	EmulatorKey WaitKeyPress() override;

	void SetWaitKeyPressCallback(WaitKeyPressCallback callback, void* arg) override;
	void SetResetCallback(ResetCallback resetClbk, void* arg) override;
	void SetEscapeCallback(EscapeCallback escapeClbk, void* arg) override;
	
private:
	const unsigned char* m_keyboardState;
	std::vector<KeyPair> m_keyPairs;
	WaitKeyPressCallback m_waitClbk;
	ResetCallback m_resetClbk;
	EscapeCallback m_escapeClbk;
	void* m_waitClbkArg;
	void* m_resetClbkArg;
	void* m_escapeClbkArg;
	
};










#endif // SDLINPUT_H

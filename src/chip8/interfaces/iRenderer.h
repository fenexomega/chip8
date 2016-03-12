#ifndef IRENDERER_H
#define IRENDERER_H


enum class WindowMode
{
	RESIZABLE,
	BORDLESS
};



class iRenderer
{
public:
	using WinCloseCallback = void(*)(void*);
	using WinResizeCallback = void(*)(void*);

	virtual ~iRenderer() = default;
	
	virtual bool Initialize(const int w, const int h) = 0;
	virtual void Dispose() noexcept = 0;

	virtual bool IsWinClosed() const = 0;
	virtual WindowMode GetMode() const = 0;

	virtual bool UpdateEvents() = 0;
	virtual void RenderBuffer() = 0;
	virtual void Render(const uint32_t *gfx) = 0;
	
	virtual void SetBuffer(const uint32_t *gfx) = 0;
	virtual bool SetWinPosition(const unsigned x, const unsigned y) = 0;
	virtual bool SetWinSize(const unsigned width, const unsigned height) = 0;
	
	virtual void SetWinCloseCallback(WinCloseCallback callback, void* arg = nullptr) = 0;
	virtual void SetWinResizeCallback(WinResizeCallback callback, void* arg = nullptr) = 0;
};



#endif

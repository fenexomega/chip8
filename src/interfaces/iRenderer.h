#ifndef IRENDERER_H
#define IRENDERER_H


constexpr unsigned int FPS =  1000 / 120;
enum class WindowMode
{
	RESIZABLE,
	BORDLESS
};



class iRenderer
{

public:
	virtual ~iRenderer() = default;
	
	virtual bool Initialize(const int w, const int h, WindowMode mode) = 0;
	
	virtual bool IsWindowClosed() const = 0;
	virtual WindowMode GetMode() const = 0;

	
	virtual void UpdateEvents() = 0;
	virtual void Render(const uint32_t *gfx) = 0;
	virtual bool SetWindowPosition(const unsigned x, const unsigned y) = 0;
	virtual bool SetWindowSize(const unsigned width, const unsigned height) = 0;
	
	virtual void Dispose() noexcept = 0;


	

};



#endif

#ifndef IRENDERER_H
#define IRENDERER_H


constexpr unsigned int FPS =  1000 / 70 ;
enum class WindowMode
{
	RESIZABLE,
	BORDLESS
};



class iRenderer
{

public:
	virtual ~iRenderer() = default;
	
	virtual bool Initialize(const int w, const int h, WindowMode mode) noexcept = 0;
	virtual void Render(const uint32_t *gfx) noexcept = 0;
	virtual bool IsWindowClosed() const noexcept = 0;
	virtual bool SetWindowPosition(const unsigned x, const unsigned y) noexcept = 0;
	virtual bool SetWindowSize(const unsigned width, const unsigned height) noexcept = 0;
	virtual void Dispose() noexcept = 0;


	

};



#endif

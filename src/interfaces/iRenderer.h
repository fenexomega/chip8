#ifndef IRENDERER_H
#define IRENDERER_H


constexpr unsigned int FPS =  1000/ 60 ;

class iRenderer
{

public:
	virtual bool Initialize(const int,const int) noexcept = 0; 

		
	virtual void Render(const void *gfx) noexcept = 0;


	virtual bool IsWindowClosed() const noexcept = 0;


	virtual void Dispose() noexcept = 0;


	virtual ~iRenderer() {}

};



#endif

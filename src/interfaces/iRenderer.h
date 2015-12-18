#ifndef IRENDERER_H
#define IRENDERER_H


constexpr unsigned int FPS =  1000/ 70 ;

class iRenderer
{

public:
	virtual ~iRenderer() {}
	
	virtual bool Initialize(const int,const int) noexcept = 0; 

		
	virtual void Render(const uint32_t *gfx) noexcept = 0;


	virtual bool IsWindowClosed() const noexcept = 0;


	virtual void Dispose() noexcept = 0;


	

};



#endif

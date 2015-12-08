#ifndef IRENDERER_H
#define IRENDERER_H




class iRenderer
{

public:
	virtual bool Initialize(const int,const int) = 0; 

		
	virtual void Render(const void *gfx) = 0;


	virtual bool IsWindowClosed() = 0;


	virtual void Dispose() = 0;


	virtual ~iRenderer(){} // needed for destroying an object from a iRenderer pointer.

};



#endif

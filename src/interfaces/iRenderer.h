#ifndef IRENDERER_H
#define IRENDERER_H

/*
 * =====================================================================================
 *
 *       Filename:  iRenderer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26-09-2015 15:50:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (fgm), mehner.fritz@fh-swf.de
 *   Organization:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <iostream>
#define LOG(X) std::cout << X << std::endl


class iRenderer
{
public:
	virtual bool Initialize()
	{
		LOG("Inicializando Renderizador");
	}

	
	virtual void Render(const unsigned char *gfx)
	{
		LOG("Renderizando tela");
	}

	
	virtual void Dispose()
	{
		LOG("Destruindo Renderizador");			
	}

	virtual bool IsWindowClosed() = 0;





};



#endif

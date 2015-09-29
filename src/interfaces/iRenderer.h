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
// pure abstract class, better for VCPP build, and performance.
public:
	virtual bool Initialize(const int,const int) = 0; 
		
	virtual void Render(const unsigned int *gfx) = 0;


	virtual bool IsWindowClosed() = 0;


	virtual void Dispose() = 0;


	virtual ~iRenderer(){}; // needed for destroying an object from a iRenderer pointer.



};



#endif

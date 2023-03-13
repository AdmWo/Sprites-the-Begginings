#define GOD_GRAPHICS
#include "Graphics.h"

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	memset( pSysBuffer,0u,sizeof( Color ) * Graphics::ScreenHeight * Graphics::ScreenWidth );
}

void Graphics::drawCircle(int xc, int yc, int x, int y, Color c)
{
	PutPixel(xc+x, yc+y, c);
	PutPixel(xc-x, yc+y, c);
	PutPixel(xc+x, yc-y, c);
	PutPixel(xc-x, yc-y, c);
	PutPixel(xc+y, yc+x, c);
	PutPixel(xc-y, yc+x, c);
	PutPixel(xc+y, yc-x, c);
	PutPixel(xc-y, yc-x, c);
}

void Graphics::circleBres(int xc, int yc, int r, Color c)
{
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;
	drawCircle(xc, yc, x, y, c);
	while( y >= x )
	{
		// for each pixel we will
		// draw all eight pixels

		x++;

		// check for decision parameter
		// and correspondingly
		// update d, x, y
		if( d > 0 )
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		drawCircle(xc, yc, x, y, c);
		
	}
}

bool Graphics::InFrame( int x,int y )
{
	return x < ScreenWidth && x > 0 && y < ScreenHeight && y > 0;
}

void Graphics::PutPixel( int x,int y,Color c )
{
	assert( x >= 0 );
	assert( x < int( Graphics::ScreenWidth ) );
	assert( y >= 0 );
	assert( y < int( Graphics::ScreenHeight ) );
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

Color Graphics::GetPixel( int x,int y ) const
{
	assert( x >= 0 );
	assert( x < int( Graphics::ScreenWidth ) );
	assert( y >= 0 );
	assert( y < int( Graphics::ScreenHeight ) );
	return pSysBuffer[Graphics::ScreenWidth * y + x];
}

void dummy( Graphics& gfx )
{
	gfx.DrawSprite( 0,0,RectI{ 0,0,0,0 },RectI{ 0,0,0,0 },Surface{},SpriteEffect::Copy{} );
	gfx.DrawSprite( 0,0,RectI{ 0,0,0,0 },RectI{ 0,0,0,0 },Surface{},SpriteEffect::Chroma{ Colors::Black } );
	gfx.DrawSprite( 0,0,RectI{ 0,0,0,0 },RectI{ 0,0,0,0 },Surface{},SpriteEffect::Substitution{ Colors::Black,Colors::Black } );
}

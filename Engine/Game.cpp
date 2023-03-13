/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include "SpriteEffect.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::mt19937 rng( 69 );
	std::uniform_int_distribution<int> xd( 0,Graphics::ScreenWidth - s.GetWidth() - 1 );
	std::uniform_int_distribution<int> yd( 0,Graphics::ScreenHeight - s.GetHeight() - 1 );

	for( int i = 0; i < 50; i++ )
	{
		positions.push_back( { xd( rng ),yd( rng ) } );
	}

	
	

	
}

void Game::Go()
{
	gfx.BeginFrame();	
	DrawExtras();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	gfx.WindowPos = wnd.GetSize();

	gfx.PutPixel( gfx.WindowPos.right-gfx.WindowPos.left-5, 10, Colors::Green );

	Vec2_<> posf = {1.0f,2.0f};
	Vec2_<> spd1 = {0.0f,0.0f};
	Vec2_<> spd2 = {100.0f,-25.5f};


	if( wnd.mouse.LeftIsPressed() )
	{

		Vec2_<> posMouse = {(float)wnd.mouse.GetPosX(),(float)wnd.mouse.GetPosY()};
		Particle_<int> prt2 ( gfx, posMouse, spd1, 2, 5,6,7,Colors::White);
		partsI.push_back( prt2 );

	}

	if( wnd.mouse.RightIsPressed() )
	{
			
				Vec2_<float> posMouse = {(float)wnd.mouse.GetPosX(),(float)wnd.mouse.GetPosY()};
				Particle_<int> prt2 ( gfx, posMouse, spd2, 1, 5,6,7,Colors::Yellow);
				partsI.push_back( prt2 );
			
	}

	//Particle_<> prtf ( gfx, posf, spdf, 5.0f,6.0f,7.0f,Colors::Blue);

	
}

void Game::ComposeFrame()
{
	
	for( auto& ppp : partsI )
	{
		ppp.DisplayParticle();
		ppp.UpdatePostion();
	}
	for( auto& ppp : partsF )
	{
		ppp.DisplayParticle();
		ppp.UpdatePostion();
	}

	bencher.Start();

	if( bencher.End() )
	{
		OutputDebugString( (std::wstring( bencher ) + L"\n").c_str() );
	}
}

void Game::DrawExtras()
{
	for( int j = 0; j < Graphics::ScreenHeight; j++ ) 
		for( int i = 0; i < Graphics::ScreenWidth; i++ )
			gfx.PutPixel( i, j, Colors::Background );
}

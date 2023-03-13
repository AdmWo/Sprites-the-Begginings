#pragma once

#include "Graphics.h"
#include "Vec2.h"



//class Element_
//{
//public:
//
//	
//
//
//	Element_( class Graphics& key );
//
//	Element_( const Element_& ) = delete;
//	Element_& operator=( const Element_& ) = delete;
//
//
//
//public:



	template<typename T = float>
	class Particle_
	{	
	public:
		Particle_<T>( Graphics& gfx_, Vec2_<float> pos_, Vec2_<float> spd_,T r_, T k_, T w_, T lt_, Color c_ )
			:
			gfx( gfx_ ),
			pos( pos_ ),
			spd( spd_ ),
			r( r_ ),
			k( k_ ),
			w( w_ ),
			lt( lt_ ),
			c( c_ )
		{
		}

	public:
		
		void DisplayParticle( )
		{
			for( int i = 0; i <= r; i++ )
				gfx.circleBres( (int)pos.x, (int)pos.y, i, c );
		}

	  
		
		bool isFreeFalling = true;

		void UpdatePostion()
		{
			if( gfx.InFrame( (int)(pos.x + r + spd.x / WorldSpeed), (int)(pos.y + r + spd.y / WorldSpeed) ) )
				if( gfx.InFrame( (int)(pos.x - r + spd.x / WorldSpeed), (int)(pos.y - r + spd.y / WorldSpeed) ) )
				{
				pos.x += spd.x / WorldSpeed;
				pos.y += spd.y / WorldSpeed;
				}

			GravityParticle( );
			//applyConstraint( );
		}

	private:

		void applyConstraint( )
		{
			const Vec2_<> constraintCenter = { constraintX, constraintY };

			const Vec2_<> v = { constraintCenter.x - pos.x, constraintCenter.y - pos.y } ;


			const float dist = sqrt(v.x * v.x + v.y * v.y);

			if( dist > ( constraintRadius  ) )
			{
				const Vec2_<> n = { v.x / dist, v.y / dist };
			
				pos.x = constraintCenter.x - n.x * ( constraintRadius );
				pos.y = constraintCenter.y - n.y * ( constraintRadius );
			}

		}

		void GravityParticle( )
		{
			if( isFreeFalling )
				spd.y += GravityConst;
		}
	


	public:
		T k, w, lt, r;
		Vec2_<float> pos;
		Vec2_<float> spd;
		Color c;
		float constraintX = 500.0f;
		float constraintY = 300.0f;
		float constraintRadius = 200.0f;
		float XBounceFriction = 0.2f;
		float XFriction = 0.3f;
		float YBounceFriction = 0.6f;
		float WorldSpeed = 22.0f;
		float GravityConst = 9.8f;
		//const int id;

	private:
		Graphics& gfx;
	

	};
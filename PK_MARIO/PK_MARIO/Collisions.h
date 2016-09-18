#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__
#include "StdAfx.h"


/// <summary>	Axis-Aligned Bounding Box Class. </summary>
class Collisions {
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="min_x">	The minimum x coordinate of testing object. </param>
	/// <param name="min_y">	The minimum y coordinate of testing object. </param>
	/// <param name="max_x">	The maximum x coordinate of testing object. </param>
	/// <param name="max_y">	The maximum y coordinate of testing object. </param>
	///-------------------------------------------------------------------------------------------------

	Collisions(double min_x, double min_y, double max_x, double max_y) :
		m_min_x(min_x), m_min_y(min_y), m_max_x(max_x), m_max_y(max_y) {

	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Collides the given box. </summary>
	///
	/// <param name="box">	[in,out] The box. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	///-------------------------------------------------------------------------------------------------

	bool Collides(  Collisions& box)  ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if 'box' is over. </summary>
	///
	/// <param name="box">	[in,out] The box. </param>
	///
	/// <returns>	true if over, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsOver(  Collisions& box)  ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if 'box' is under. </summary>
	///
	/// <param name="box">	[in,out] The box. </param>
	///
	/// <returns>	true if under, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsUnder(  Collisions& box)  ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Is on left of the given box. </summary>
	///
	/// <param name="box">	[in,out] The box. </param>
	///
	/// <returns>	true if on left of, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsOnLeftOf(  Collisions& box)  ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Is on right of the given box. </summary>
	///
	/// <param name="box">	[in,out] The box. </param>
	///
	/// <returns>	true if on right of, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsOnRightOf(  Collisions& box)  ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets minimum x coordinate. </summary>
	///
	/// <returns>	The minimum x coordinate. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetMinX();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets minimum y coordinate. </summary>
	///
	/// <returns>	The minimum y coordinate. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetMinY();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets maximum x coordinate. </summary>
	///
	/// <returns>	The maximum x coordinate. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetMaxX();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets maximum y coordinate. </summary>
	///
	/// <returns>	The maximum y coordinate. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetMaxY();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Moves te collison box by the offset. </summary>
	///
	/// <param name="min_x_offset">	The minimum x coordinate offset. </param>
	/// <param name="min_y_offset">	The minimum y coordinate offset. </param>
	/// <param name="max_x_offset">	The maximum x coordinate offset. </param>
	/// <param name="max_y_offset">	The maximum y coordinate offset. </param>
	///
	/// <returns>	The Collisions. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions Move(double min_x_offset, double min_y_offset, double max_x_offset, double max_y_offset);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Stream insertion operator. </summary>
	///
	/// <param name="os"> 	[in,out] ostream. </param>
	/// <param name="box">	[in,out] The box. </param>
	///
	/// <returns>	The shifted result. </returns>
	///-------------------------------------------------------------------------------------------------

	friend std::ostream& operator<< (std::ostream& os,   Collisions& box);

private:
	
	/// <summary>	The minimum x coordinate. </summary>
	double m_min_x;
	/// <summary>	The minimum y coordinate. </summary>
	double m_min_y;

	/// <summary>	The maximum x coordinate. </summary>
	double m_max_x;
	/// <summary>	The maximum y coordinate. </summary>
	double m_max_y;
};


#endif
/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Scalar.h"

#include <iosfwd>

namespace nix {

//! Closed Interval
/*!
 * A closed interval \f$[a,b]\f$.
 */
class Interval
{
public:
	/*!
	 * Default constructor.
	 * \return Returns an empty Interval.
	 */
	Interval();
	Interval(const Interval& I);	//!< copy constructor
	virtual ~Interval() = default;	//!< destructor

	/**
	 * Set the values of the interval.
	 * If sMin > sMax, then the values are swapped, rather than having the
	 * Interval be set to empty. If either of the values is not a number, then
	 * the interval is set to be empty.
	 *
	 * @param sMin One of the two interval values. It need not be the minimum.
	 * @param sMax One of the two interval values. It need not be the maximum.
	 */
	void Set(Scalar sMin, Scalar sMax);
	void SetEmpty();

	/**
	 * Assignment operator for the Interval class.
	 * Makes use of the Set(Scalar, Scalar) method to initialize the left-hand
	 * side values.
	 * \sa Set(Scalar, Scalar)
	 *
	 * @param rhs The right-hand side has its values copied and verified.
	 * @return Returns a reference to this for chaining.
	 */
	Interval & operator=(const Interval& rhs);

	static const Interval Empty;	///< The empty interval.
};

/// Prints an Interval in readable form.
/// \sa Interval::print()
/// \param os output stream to write to.
/// \param i The Interval to stream.
/// \returns Return the input output stream after writing for chaining.
std::ostream & operator<<(std::ostream & os, const Interval & i);

}


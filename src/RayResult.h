/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <type_traits>

namespace nix {

/// An enum that specifies whether a ray was reflected, trasmitted, or absorbed.
enum class Interaction
{
	reflected,		///< The ray was reflected.
	transmitted,	///< The ray was trasmitted.
	absorbed		///< The ray was absorbed.
};

/// Keep a set of flags for the various aspects that affect a ray.
enum class RayFlags : unsigned {
	none =					0x000,	///< No special flags.
	mirror =				0x001,	///< Mirror reflection off material surface.
};

/// Bitwise *and* operator for the RayFlags enum.
/// \param lhs The left-hand side of the bitwise and operation.
/// \param rhs The right-hand side of the bitwise and operation.
/// \return Returns the bitwise and of the \c lhs and \c rhs.
constexpr RayFlags operator& (RayFlags lhs, RayFlags rhs)
{
	using T = std::underlying_type<RayFlags>::type;
	return static_cast<RayFlags>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

/// A simple helper class that describes what happened to a Ray while ineracting
/// with a sample.
class RayResult
{
  public:

	/// No default constructor.
	RayResult() = delete;

	/// Construct an instance specifying the ultimate result of the ray.
	/// \param i The ray must have been reflected, transmitted, or absorbed.
	RayResult(Interaction i);

	/// Default destructor.
	~RayResult() = default;

	/// Default copy constructor.
	/// \param other The copied object.
	RayResult(const RayResult & other) = default;

	/// Default assignment operator.
	/// \param other The right-hand side of the assignment.
	/// \return Returns the moved object.
	RayResult & operator=(const RayResult & other) = default;

	/// Default move constructor.
	/// \param other The moved object.
	RayResult(RayResult && other) = default;

	/// Default move assignment operator.
	/// \param other The right-hand side of the move assignment.
	/// \return Returns the moved object.
	RayResult & operator=(RayResult && other) = default;

	/// Test if this was a mirror reflection off the material surface.
	/// \return Returns true if this reflection was off the material boundary
	///         surface, instead of undergoing subscattering.
	bool isMirror() const;

	RayFlags _flags;		///< Properties of the RayResult instance.
};

} // namespace nix


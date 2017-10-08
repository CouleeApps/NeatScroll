#pragma once

//-----------------------------------------------------------------------------
// Bezier curves
// Grats to http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-der.html
//-----------------------------------------------------------------------------

/**
* Calculates the factorial of a number.
* @arg val The number whose factorial to get.
* @return The factorial of val.
*/
inline uint64_t _factorial(const uint32_t &val) {
	uint32_t ret = 1;
	for (uint32_t i = 2; i <= val; i++) {
		ret *= i;
	}
	return ret;
}

/**
* Get the bezier curve coefficient for a point
* @param n The order of the curve
* @param i The point's index on the curve
* @param u The current distance on the curve (normalized)
* @return The factor by which this point's influence should be scaled
*/
template<typename T>
inline T _bezier(const uint32_t &n, const uint32_t &i, const T &u) {
	//              n!
	//B_n,i(u) = --------  u^i (1-u)^(n-i)
	//           i!(n-i)!

	return T(_factorial(n)) / T(_factorial(i) * _factorial(n - i)) * std::pow(static_cast<T>(u), static_cast<T>(i)) * std::pow(T(1) - u, static_cast<T>(n - i));
}

/**
* Bezier curve between points
* @param u      The current distance on the curve (normalized)
* @param points A vector of control points for the curve
* @return The point on the curve at the given distance
*/
template<typename T, glm::precision P>
inline glm::tvec2<T, P> bezier(const T &u, const std::vector<glm::tvec2<T, P>> &points) {
	//Order of the bezier curve is (point count - 1)
	uint32_t n = points.size() - 1;

	//Store everything into here
	glm::tvec2<T, P> ret(0);

	for (uint32_t i = 0; i <= n; i++) {
		//P_i - The control point at i
		glm::tvec2<T, P> p_i = points[i];

		//         n
		// C(u) =  ∑ B_n,i(u)*P_i
		//        i=0
		ret += p_i * _bezier(n, i, u);
	}
	return ret;
}

/**
* Bezier curve derivative between points
* @param u      The current distance on the curve (normalized)
* @param points A vector of control points for the curve
* @return The derivative of the curve at the given distance
*/
template<typename T, glm::precision P>
inline glm::tvec2<T, P> bezier_derivative(const T &u, const std::vector<glm::tvec2<T, P>> &points) {
	//Order of the bezier curve is (point count - 1)
	uint32_t n = points.size() - 1;

	//Store everything into here
	glm::tvec2<T, P> ret(0);

	for (uint32_t i = 0; i < n; i++) {
		//P_i - The control point at i
		glm::tvec2<T, P> p_i = points[i];

		//P_i+1 - Point at i+1
		glm::tvec2<T, P> p_i1 = points[i + 1];

		//Q_i = n(P_i+1 - P_i)
		glm::tvec2<T, P> q_i = (p_i1 - p_i) * static_cast<T>(n);

		//       n-1
		//C'(u) = ∑  B_n-1,i(u) * Q_i
		//       i=0
		ret += q_i * _bezier(n - 1, i, u);
	}
	return ret;
}

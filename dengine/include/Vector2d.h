#ifndef _DENGINE_VECTOR2D_INCL
#define _DENGINE_VECTOR2D_INCL

#include <math.h>

namespace dengine {
    /**
     * \brief Simple two-dimensional euclidean vector.
     */
    class Vector2d {
        public:
            /**
             * \brief Vector2d with given displacement expressed at x,y coordinates in cartesian plane.
             *
             * \param x double describing the x coordinate.
             * \param y double describing the y coordinate.
             */
            Vector2d(double x, double y) : _x{x}, _y{y} {}

            /**
             * \brief Initialze new Vector2d given magnitud and angle.
             *
             * When initializing a Vector2d using magnitude and angle, the (x,y) coordinates are
             * calculated using their established relationships.
             *
             * The angle of the vector, theta, is represented in radians.
             *
             * \param mag double describing the magnitude of the vector.
             * \param theta double radian value representing the angle of the vector.
             */
            static Vector2d magnitude_direction(double mag, double theta);

            /**
             * \brief x coordinate.
             */
            double x() const { return _x; }

            /**
             * \brief y coordinate.
             */
            double y() const { return _y; }

            /**
             * \brief Magnitude of the vector.
             */
            double magnitude() const;

            /**
             * \brief Angle of the vector.
             */
            double theta() const;

            /**
             * \brief Apply the given unit vectors and return a new Vector2d representing the change.
             *
             * \param i double representing the x dimension of the unit vector.
             * \param j double representing the y dimension of the unit vector.
             */
            Vector2d unit(double i, double j) const {
                auto xi = _x * i;
                auto yj = _y * j;

                Vector2d u{xi, yj};

                return u;
            }

            /**
             * \brief Addition of Vector2d
             *
             * \param rhs Vector2d on the right-hand-side of the addition.
             */
            Vector2d& operator+=(const Vector2d& rhs) {
                _x += rhs._x;
                _y += rhs._y;
                _mag = NAN;
                _theta = NAN;

                return *this;
            }

            /**
             * \brief Subtraction of Vector2d
             *
             * \param rhs Vector2d on the right-hand-side of the subtraction.
             */
            Vector2d& operator-=(const Vector2d& rhs) {
                _x -= rhs._x;
                _y -= rhs._y;
                _mag = NAN;
                _theta = NAN;

                return *this;
            }

            /**
             * \brief Add scalar to Vector2d
             *
             * \param rhs double scalar on the right-hand-side of the addition.
             */
            Vector2d& operator+=(const double rhs) {
                _x += rhs;
                _y += rhs;
                _mag = NAN;
                _theta = NAN;

                return *this;
            }

            /**
             * \brief Subtract scalar from Vector2d
             *
             * \param rhs double scalar on the right-hand-side of the subtraction.
             */
            Vector2d& operator-=(const double rhs) {
                _x -= rhs;
                _y -= rhs;
                _mag = NAN;
                _theta = NAN;

                return *this;
            }

            /**
             * \brief Multiplication of a scalar and Vector2d
             *
             * \param rhs double scalar on the right-hand-side of the multiplication.
             */
            Vector2d& operator*=(const double rhs) {
                _x *= rhs;
                _y *= rhs;
                _mag = NAN;
                _theta = NAN;

                return *this;
            }

            friend Vector2d operator+(Vector2d lhs, const Vector2d& rhs) {
                lhs += rhs;
                return lhs;
            }

            friend Vector2d operator-(Vector2d lhs, const Vector2d& rhs) {
                lhs -= rhs;
                return lhs;
            }

            friend Vector2d operator+(Vector2d lhs, const double rhs) {
                lhs += rhs;
                return lhs;
            }

            friend Vector2d operator-(Vector2d lhs, const double rhs) {
                lhs -= rhs;
                return lhs;
            }

            friend Vector2d operator*(Vector2d lhs, const double rhs) {
                lhs *= rhs;
                return lhs;
            }

        private:
            /**
             * \brief x coordinate.
             */
            double _x;

            /**
             * \brief y coordinate.
             */
            double _y;

            /**
             * \brief Magnitude.
             */
            mutable double _mag{NAN};

            /**
             * \brief Angle.
             */
            mutable double _theta{NAN};
    };
}
#endif

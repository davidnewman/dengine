#ifndef _DENGINE_MOTION_INCL
#define _DENGINE_MOTION_INCL

#include "DMath.h"

namespace dengine {
    /**
     * \brief Combination of vectors to describe basic 2d motion.
     *
     * This class combines displacement, velocity, and acceleration
     * vectors in order to calculate basic 2-dimensional motion.
     */
    class Motion {
        public:
            /**
             * \brief Motion in which all vectors are zero.
             */
            Motion();

            /**
             * \brief Motion with no initial velocity or acceleration.
             *
             * \param d Vector2d describing initial displacement.
             */
            Motion(Vector2d d);

            /**
             * \brief Motion with initial displacement and velocity, but no acceleration.
             * \param d Vector2d describing initial displacement.
             * \param v Vector2d describing initial velocity.
             */
            Motion(Vector2d d, Vector2d v);

            /**
             * \brief Motion with initial displacement, velocity, and acceleration.
             *
             * \param d Vector2d describing initial displacement.
             * \param v Vector2d describing initial velocity.
             * \param a Vector2d describing initial acceleration.
             */
            Motion(Vector2d d, Vector2d v, Vector2d a);

            /**
             * \brief Return the current displacement.
             */
            Vector2d displacement() const;

            /**
             * \brief Return the current velocity.
             */
            Vector2d velocity() const;

            /**
             * \brief Return the current acceleration.
             */
            Vector2d acceleration() const;

            /**
             * \brief Calculate new displacement under current forces for t seconds.
             *
             * \param t double representing seconds in the future to calculate displacement.
             */
            Vector2d move(double t);

            /**
             * \brief Displace by a static amount.
             *
             * \param d Vector2d describing the amount of displacement.
             */
            void displace(Vector2d d);

            /**
             * \brief Apply an acceleration to the object.
             *
             * \param a Vector2d describing new acceleration.
             */
            void accelerate(Vector2d a);

            /**
             * \brief Halt all acceleration and existing velocity.
             *
             */
            void stop();

        private:

            /**
             * \brief Current displacement.
             */
            Vector2d disp;

            /**
             * \brief Current velocity.
             */
            Vector2d vel;

            /**
             * \brief Current acceleration.
             */
            Vector2d accel;
    };
}

#endif

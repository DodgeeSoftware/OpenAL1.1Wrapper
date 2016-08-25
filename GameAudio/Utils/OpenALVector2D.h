// ********************************
// * COMPANY: Dodgee Software     *
// * AUTHOR: Shem Taylor          *
// * Written 2016 Dodgee Software *
// * GPLv3                        *
// ********************************

#ifndef OPENALVECTOR2D_H
#define OPENALVECTOR2D_H

// C/C++ Includes
#include <cmath>

/** @class OpenALVector2D
  * @brief A simple class for for a mathematical 2D Vector
  * @detail The OpenALVector2D contains an x,y co-ordinate pair
  * and overloaded operations to support vector comparison
  * addition, subtraction. It also has standard functions for
  * vector maginitude and dot product aswell as normalisation **/
class OpenALVector2D
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Constructor
        OpenALVector2D()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }
        OpenALVector2D(float x, float y)
        {
            this->x = x;
            this->y = y;
        }
        // Copy Constructor
        OpenALVector2D(const OpenALVector2D& other)
        {
            this->x = other.x;
            this->y = other.y;
        }
        //! Destructor
        virtual ~OpenALVector2D() {}

    protected:
        // Methods and Members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        //! OpenALVector2D Assignment operator
        OpenALVector2D& operator=(const OpenALVector2D& other)
        {
            this->x = other.x;
            this->y = other.y;
            return (*this);
        }
        //! Multiply our OpenALVector2Ds by a scalar
        OpenALVector2D operator*(float value)
        {
            return OpenALVector2D(this->x * value, this->y * value);
        }
        //! Divide our OpenALVector2Ds by a scalar
        OpenALVector2D operator/(float value)
        {
            return OpenALVector2D(this->x / value, this->y / value);
        }
        //! Adding two OpenALVector2Ds
        OpenALVector2D operator+(OpenALVector2D& other)
        {
            return OpenALVector2D(this->x + other.x, this->y + other.y);
        }
        //! Subtracting two OpenALVector2Ds
        OpenALVector2D operator-(OpenALVector2D& other)
        {
            return OpenALVector2D(this->x + other.x, this->y - other.y);
        }

    protected:
        // Methods and Members

    // ********************
    // * VECTOR FUNCTIONS *
    // ********************
    public:
        //! Magnitude
        virtual float magnitude()
        {
            // Return magnitude of the vector
            return sqrt(this->x * this->x + this->y * this->y);
        }
        //! Normalise this vector
        virtual void normalise()
        {
            float m = this->magnitude();
            if (m > 0.0f)
            {
                this->x = this->x / m;
                this->y = this->y / m;
            }
        }
        //! Normalised version of this vector
        virtual OpenALVector2D normalised()
        {
            OpenALVector2D v;
            float m = this->magnitude();
            if (m > 0.0f)
            {
                v.x = this->x / m;
                v.y = this->y / m;
            }
            return v;
        }
        //! Dot Product
        virtual float dotProduct(OpenALVector2D other)
        {
            // Calculate Dot product
            return this->x * other.x + this->y * other.y;
        }
        virtual float angleBetween(OpenALVector2D other)
        {
            float angle = 0.0f;
            float m1 = this->magnitude();
            float m2 = other.magnitude();
            if (m1 > 0.0f && m2 > 0.0f)
                angle = acos(this->dotProduct(other) / (m1 * m2));
            return angle;
        }
        /* NOTE: No cross product exits for 2D Vectors
        //! Cross Product
        virtual OpenALVector2D crossProduct(OpenALVector2D other)  */


    protected:
        // Methods and Members

    // *********************
    // * VECTOR COMPONENTS *
    // *********************
    public:
        //! Get X
        virtual float getX() { return this->x; }
        //! Set X
        virtual void setX(float x) { this->x = x; }
        //! Get Y
        virtual float getY() { return this->y; }
        //! Set Y
        virtual void setY(float y) { this->y = y; }
        //! Set Position
        virtual void setPosition(float x, float y) { this->x = x; this->y = y; }

    public:
        // Horizontal component
        float x;
        // Vertical component
        float y;

    protected:
        // Methods and Members

//    // ****************
//    // * LUA BINDINGS *
//    // ****************
//    public:
//        //! Bind this class to a lua state
//        static void bindToLua(lua_State* pLuaState)
//        {
//
//        }
};

#endif // OPENALVECTOR2D_H

/**
  * @file   OpenALVector3D.h
  * @Author Sergeant Neipo (sergeant.neipo@gmail.com)
  * @date   August, 2016
  * @brief  OpenALVector3D is a utility class providing
  * support for 3D mathematical vectors
*/

#ifndef OPENALVECTOR3D_H
#define OPENALVECTOR3D_H

// C/C++ Includes
#include <cmath>

/** @class OpenALVector3D
  * @brief A simple class for for a mathematical 3D Vector
  * @detail The OpenALVector3D contains an x,y,z co-ordinate pairs
  * and overloaded operations to support vector comparison
  * addition, subtraction. It also has standard functions for
  * vector maginitude and dot/cross product aswell as normalisation **/
class OpenALVector3D
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Constructor
        OpenALVector3D()
        {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
        }
        //! Constructor
        OpenALVector3D(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        //! Copy Constructor
        OpenALVector3D(const OpenALVector3D& other)
        {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
        }
        //! Destructor
        virtual ~OpenALVector3D() {}

    protected:
        // Methods and Members

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        //! OpenALVector3D Assignment operator
        OpenALVector3D& operator=(const OpenALVector3D& other)
        {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            return (*this);
        }
        //! Multiply our OpenALVector3Ds by a scalar
        OpenALVector3D operator*(float value)
        {
            return OpenALVector3D(this->x * value, this->y * value, this->z * value);
        }
        //! Divide our OpenALVector3Ds by a scalar
        OpenALVector3D operator/(float value)
        {
            return OpenALVector3D(this->x / value, this->y / value, this->z / value);
        }
        //! Adding two OpenALVector3Ds
        OpenALVector3D operator+(OpenALVector3D& other)
        {
            return OpenALVector3D(this->x + other.x, this->y + other.y, this->z + other.z);
        }
        //! Subtracting two OpenALVector3Ds
        OpenALVector3D operator-(OpenALVector3D& other)
        {
            return OpenALVector3D(this->x + other.x, this->y - other.y, this->z - other.z);
        }

    // ********************
    // * VECTOR FUNCTIONS *
    // ********************
    public:
        //! Magnitude
        virtual float magnitude()
        {
            // Return magnitude of the vector
            return sqrt(x * x + y * y + z * z);
        }
        //! Normalise this vector
        virtual void normalise()
        {
            float m = this->magnitude();
            if (m > 0.0f)
            {
                this->x = this->x / m;
                this->y = this->y / m;
                this->z = this->z / m;
            }
        }
        //! Normalised version of this vector
        virtual OpenALVector3D normalised()
        {
            OpenALVector3D v;
            float m = this->magnitude();
            if (m > 0.0f)
            {
                v.x = this->x / m;
                v.y = this->y / m;
                v.z = this->z / m;
            }
            return v;
        }
        //! Dot Product
        virtual float dotProduct(OpenALVector3D other)
        {
            // Calculate Dot product
            return this->x * other.x + this->y * other.y + this->z * other.z;
        }
        //! Cross Product
        virtual OpenALVector3D crossProduct(OpenALVector3D other)
        {
            // Cross Product
            return OpenALVector3D(this->y * other.z - this->z * other.y,
                                  this->z * other.x - this->x * other.z,
                                  this->x * other.y - this->y * other.x);
        }

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
        //! Get Z
        virtual float getZ() { return this->z; }
        //! Set Z
        virtual void setZ(float z) { this->z = z; }
        //! Set Position
        virtual void setPosition(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

    public:
        // Horizontal component
        float x;
        // Vertical component
        float y;
        // Depth component
        float z;

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

#endif // OPENALVECTOR3D_H

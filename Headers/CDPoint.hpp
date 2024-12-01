#pragma once
#ifndef MESHEDGECOLLAPSING_CDPOINT_HPP
#define MESHEDGECOLLAPSING_CDPOINT_HPP

/**
 * @class CDPoint
 * A 3D point in the space
 */
class CDPoint
{
public:
    /**
     * Empty constructor
     */
    CDPoint()
        : CDPoint(0.0)
    {}

    /**
     * Constructor
     * @param[in] pValue The coordinates of the point
     */
    CDPoint(double pValue)
        : CDPoint(pValue, pValue, pValue)
    {}

    /**
     * Constructor
     * @param[in] pX The x coordinate
     * @param[in] pY The y coordinate
     * @param[in] pZ The z coordinate
     */
    CDPoint(double pX, double pY, double pZ)
        : mX(pX)
        , mY(pY)
        , mZ(pZ)
    {}

    /**
     * Destructor
     */
    virtual ~CDPoint() { }

    /**
     * Get the x coordinate
     * @return X coordinate
     */
    inline double GetX() const { return mX ; }

    /**
     * Get the y coordinate
     * @return Y coordinate
     */
    inline double GetY() const { return mY ; }

    /**
     * Get the z coordinate
     * @return Z coordinate
     */
    inline double GetZ() const { return mZ ; }

    /**
     * < operator, useful for placing points into an ordered container
     * @param pPoint The other point
     * @return true if the point is smaller or not
     */
    bool operator<(const CDPoint& pPoint) const
    {
        if(mX != pPoint.GetX())
            return mX < pPoint.GetX() ;
        else if(mY != pPoint.GetY())
            return mY < pPoint.GetY() ;
        else
            return mZ < pPoint.GetZ() ;

    }

    CDPoint operator+(const CDPoint& pPoint) const
    {
        return { mX + pPoint.GetX(), mY + pPoint.GetY(), mZ + pPoint.GetZ() } ;
    }

    CDPoint operator-(const CDPoint& pPoint) const
    {
        return { mX - pPoint.GetX(), mY - pPoint.GetY(), mZ - pPoint.GetZ() } ;
    }

    CDPoint operator*(const double pValue) const
    {
        return { mX * pValue, mY * pValue, mZ * pValue } ;
    }

    CDPoint operator/(const double pValue) const
    {
        return { mX / pValue, mY / pValue, mZ / pValue } ;
    }

    CDPoint& operator+=(const CDPoint& pPoint)
    {
        mX += pPoint.GetX() ;
        mY += pPoint.GetY() ;
        mZ += pPoint.GetZ() ;
        return *this ;
    }

private:
    double mX ; /**< The X coordinate of the point */
    double mY ; /**< The Y coordinate of the point */
    double mZ ; /**< The Z coordinate of the point */
};

#endif //MESHEDGECOLLAPSING_CDPOINT_HPP

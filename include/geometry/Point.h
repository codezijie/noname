
namespace geometry
{
    /**
     *  @brief A Point represents a coordinate in 2D space.
     *  
     *  @note The coordinate should be integer, which means all the points should be snapped at input.
     */
    class Point
    {
    private:
        int m_x, m_y;
    public:
        // TODO: all the involved Points should be normalized in Polygon, so override operator< is necessary.
        Point(/* args */);
        ~Point();
    };
    
} // namespace geometry

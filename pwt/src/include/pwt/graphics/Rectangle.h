/*
 * Rectangle.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_GRAPHICS_RECTANGLE_H_
#define INCLUDE_PWT_GRAPHICS_RECTANGLE_H_

namespace pwt {
/**
 * A point representing a location in {@code (x,y)} coordinate space,
 * specified in integer precision.
 *
 * @author      Sami Shaio
 * @since       1.0
 */
class Point {
public:
    /**
     * The X coordinate of this <code>Point</code>.
     * If no X coordinate is set it will default to 0.
     *
     * @serial
     * @see #getLocation()
     * @see #move(int, int)
     * @since 1.0
     */
     int x;

    /**
     * The Y coordinate of this <code>Point</code>.
     * If no Y coordinate is set it will default to 0.
     *
     * @serial
     * @see #getLocation()
     * @see #move(int, int)
     * @since 1.0
     */
     int y;

    /**
     * Constructs and initializes a point at the origin
     * (0,&nbsp;0) of the coordinate space.
     * @since       1.1
     */
     Point() {
         this->x = 0;
         this->y = 0;
    }

    /**
     * Constructs and initializes a point at the specified
     * {@code (x,y)} location in the coordinate space.
     * @param x the X coordinate of the newly constructed <code>Point</code>
     * @param y the Y coordinate of the newly constructed <code>Point</code>
     * @since 1.0
     */
     Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    /**
     * {@inheritDoc}
     * @since 1.2
     */
     double getX() {
        return x;
    }

    /**
     * {@inheritDoc}
     * @since 1.2
     */
     double getY() {
        return y;
    }

    /**
     * Returns the location of this point.
     * This method is included for completeness, to parallel the
     * <code>getLocation</code> method of <code>Component</code>.
     * @return      a copy of this point, at the same location
     * @see         java.awt.Component#getLocation
     * @see         java.awt.Point#setLocation(java.awt.Point)
     * @see         java.awt.Point#setLocation(int, int)
     * @since       1.1
     */
     Point getLocation() {
        return Point(x, y);
    }

    /**
     * Sets the location of the point to the specified location.
     * This method is included for completeness, to parallel the
     * <code>setLocation</code> method of <code>Component</code>.
     * @param       p  a point, the new location for this point
     * @see         java.awt.Component#setLocation(java.awt.Point)
     * @see         java.awt.Point#getLocation
     * @since       1.1
     */
     void setLocation(Point& p) {
        setLocation(p.x, p.y);
    }

    /**
     * Changes the point to have the specified location.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>setLocation</code> method of <code>Component</code>.
     * Its behavior is identical with <code>move(int,&nbsp;int)</code>.
     * @param       x the X coordinate of the new location
     * @param       y the Y coordinate of the new location
     * @see         java.awt.Component#setLocation(int, int)
     * @see         java.awt.Point#getLocation
     * @see         java.awt.Point#move(int, int)
     * @since       1.1
     */
     void setLocation(int x, int y) {
        move(x, y);
    }

    /**
     * Sets the location of this point to the specified double coordinates.
     * The double values will be rounded to integer values.
     * Any number smaller than <code>Integer.MIN_VALUE</code>
     * will be reset to <code>MIN_VALUE</code>, and any number
     * larger than <code>Integer.MAX_VALUE</code> will be
     * reset to <code>MAX_VALUE</code>.
     *
     * @param x the X coordinate of the new location
     * @param y the Y coordinate of the new location
     * @see #getLocation
     */
     void setLocation(double x, double y) {
        this->x = (int) x;
        this->y = (int) y;
    }

    /**
     * Moves this point to the specified location in the
     * {@code (x,y)} coordinate plane. This method
     * is identical with <code>setLocation(int,&nbsp;int)</code>.
     * @param       x the X coordinate of the new location
     * @param       y the Y coordinate of the new location
     * @see         java.awt.Component#setLocation(int, int)
     */
     void move(int x, int y) {
        this->x = x;
        this->y = y;
    }

    /**
     * Translates this point, at location {@code (x,y)},
     * by {@code dx} along the {@code x} axis and {@code dy}
     * along the {@code y} axis so that it now represents the point
     * {@code (x+dx,y+dy)}.
     *
     * @param       dx   the distance to move this point
     *                            along the X axis
     * @param       dy    the distance to move this point
     *                            along the Y axis
     */
     void translate(int dx, int dy) {
        this->x += dx;
        this->y += dy;
    }
};


/**
 * The <code>Dimension</code> class encapsulates the width and
 * height of a component (in integer precision) in a single object.
 * The class is
 * associated with certain properties of components. Several methods
 * defined by the <code>Component</code> class and the
 * <code>LayoutManager</code> interface return a
 * <code>Dimension</code> object.
 * <p>
 * Normally the values of <code>width</code>
 * and <code>height</code> are non-negative integers.
 * The constructors that allow you to create a dimension do
 * not prevent you from setting a negative value for these properties.
 * If the value of <code>width</code> or <code>height</code> is
 * negative, the behavior of some methods defined by other objects is
 * undefined.
 *
 * @author      Sami Shaio
 * @author      Arthur van Hoff
 * @see         java.awt.Component
 * @see         java.awt.LayoutManager
 * @since       1.0
 */
class Dimension {
public:

    /**
     * The width dimension; negative values can be used.
     *
     * @serial
     * @see #getSize
     * @see #setSize
     * @since 1.0
     */
     int width;

    /**
     * The height dimension; negative values can be used.
     *
     * @serial
     * @see #getSize
     * @see #setSize
     * @since 1.0
     */
     int height;

    /**
     * Creates an instance of <code>Dimension</code> with a width
     * of zero and a height of zero.
     */
     Dimension() {
         this->width = 0;
         this->height = 0;
    }

    /**
     * Constructs a <code>Dimension</code> and initializes
     * it to the specified width and specified height.
     *
     * @param width the specified width
     * @param height the specified height
     */
     Dimension(int width, int height) {
        this->width = width;
        this->height = height;
    }

    /**
     * {@inheritDoc}
     * @since 1.2
     */
     double getWidth() {
        return width;
    }

    /**
     * {@inheritDoc}
     * @since 1.2
     */
     double getHeight() {
        return height;
    }

    /**
     * Sets the size of this <code>Dimension</code> object to
     * the specified width and height in double precision.
     * Note that if <code>width</code> or <code>height</code>
     * are larger than <code>Integer.MAX_VALUE</code>, they will
     * be reset to <code>Integer.MAX_VALUE</code>.
     *
     * @param width  the new width for the <code>Dimension</code> object
     * @param height the new height for the <code>Dimension</code> object
     * @since 1.2
     */
     void setSize(double width, double height) {
        this->width = width;
        this->height = height;
    }

    /**
     * Gets the size of this <code>Dimension</code> object.
     * This method is included for completeness, to parallel the
     * <code>getSize</code> method defined by <code>Component</code>.
     *
     * @return   the size of this dimension, a new instance of
     *           <code>Dimension</code> with the same width and height
     * @see      java.awt.Dimension#setSize
     * @see      java.awt.Component#getSize
     * @since    1.1
     */
     Dimension getSize() {
        return Dimension(width, height);
    }

    /**
     * Sets the size of this <code>Dimension</code> object to the specified size.
     * This method is included for completeness, to parallel the
     * <code>setSize</code> method defined by <code>Component</code>.
     * @param    d  the new size for this <code>Dimension</code> object
     * @see      java.awt.Dimension#getSize
     * @see      java.awt.Component#setSize
     * @since    1.1
     */
     void setSize(Dimension& d) {
        setSize(d.width, d.height);
    }

    /**
     * Sets the size of this <code>Dimension</code> object
     * to the specified width and height.
     * This method is included for completeness, to parallel the
     * <code>setSize</code> method defined by <code>Component</code>.
     *
     * @param    width   the new width for this <code>Dimension</code> object
     * @param    height  the new height for this <code>Dimension</code> object
     * @see      java.awt.Dimension#getSize
     * @see      java.awt.Component#setSize
     * @since    1.1
     */
     void setSize(int width, int height) {
        this->width = width;
        this->height = height;
    }
};

/**
 * A <code>Rectangle</code> specifies an area in a coordinate space that is
 * enclosed by the <code>Rectangle</code> object's upper-left point
 * {@code (x,y)}
 * in the coordinate space, its width, and its height.
 * <p>
 * A <code>Rectangle</code> object's <code>width</code> and
 * <code>height</code> are <code>public</code> fields. The constructors
 * that create a <code>Rectangle</code>, and the methods that can modify
 * one, do not prevent setting a negative value for width or height.
 * <p>
 * <a name="Empty">
 * A {@code Rectangle} whose width or height is exactly zero has location
 * along those axes with zero dimension, but is otherwise considered empty.
 * The {@link #isEmpty} method will return true for such a {@code Rectangle}.
 * Methods which test if an empty {@code Rectangle} contains or intersects
 * a point or rectangle will always return false if either dimension is zero.
 * Methods which combine such a {@code Rectangle} with a point or rectangle
 * will include the location of the {@code Rectangle} on that axis in the
 * result as if the {@link #add(Point)} method were being called.
 * </a>
 * <p>
 * <a name="NonExistant">
 * A {@code Rectangle} whose width or height is negative has neither
 * location nor dimension along those axes with negative dimensions.
 * Such a {@code Rectangle} is treated as non-existant along those axes.
 * Such a {@code Rectangle} is also empty with respect to containment
 * calculations and methods which test if it contains or intersects a
 * point or rectangle will always return false.
 * Methods which combine such a {@code Rectangle} with a point or rectangle
 * will ignore the {@code Rectangle} entirely in generating the result.
 * If two {@code Rectangle} objects are combined and each has a negative
 * dimension, the result will have at least one negative dimension.
 * </a>
 * <p>
 * Methods which affect only the location of a {@code Rectangle} will
 * operate on its location regardless of whether or not it has a negative
 * or zero dimension along either axis.
 * <p>
 * Note that a {@code Rectangle} constructed with the default no-argument
 * constructor will have dimensions of {@code 0x0} and therefore be empty.
 * That {@code Rectangle} will still have a location of {@code (0,0)} and
 * will contribute that location to the union and add operations.
 * Code attempting to accumulate the bounds of a set of points should
 * therefore initially construct the {@code Rectangle} with a specifically
 * negative width and height or it should use the first point in the set
 * to construct the {@code Rectangle}.
 * For example:
 * <pre>
 *     Rectangle bounds = new Rectangle(0, 0, -1, -1);
 *     for (int i = 0; i < points.length; i++) {
 *         bounds.add(points[i]);
 *     }
 * </pre>
 * or if we know that the points array contains at least one point:
 * <pre>
 *     Rectangle bounds = new Rectangle(points[0]);
 *     for (int i = 1; i < points.length; i++) {
 *         bounds.add(points[i]);
 *     }
 * </pre>
 * <p>
 * This class uses 32-bit integers to store its location and dimensions.
 * Frequently operations may produce a result that exceeds the range of
 * a 32-bit integer.
 * The methods will calculate their results in a way that avoids any
 * 32-bit overflow for intermediate results and then choose the best
 * representation to store the final results back into the 32-bit fields
 * which hold the location and dimensions.
 * The location of the result will be stored into the {@link #x} and
 * {@link #y} fields by clipping the true result to the nearest 32-bit value.
 * The values stored into the {@link #width} and {@link #height} dimension
 * fields will be chosen as the 32-bit values that encompass the largest
 * part of the true result as possible.
 * Generally this means that the dimension will be clipped independently
 * to the range of 32-bit integers except that if the location had to be
 * moved to store it into its pair of 32-bit fields then the dimensions
 * will be adjusted relative to the "best representation" of the location.
 * If the true result had a negative dimension and was therefore
 * non-existant along one or both axes, the stored dimensions will be
 * negative numbers in those axes.
 * If the true result had a location that could be represented within
 * the range of 32-bit integers, but zero dimension along one or both
 * axes, then the stored dimensions will be zero in those axes.
 *
 * @author      Sami Shaio
 * @since 1.0
 */
 class Rectangle
{
 public:
    /**
     * The X coordinate of the upper-left corner of the <code>Rectangle</code>.
     *
     * @serial
     * @see #setLocation(int, int)
     * @see #getLocation()
     * @since 1.0
     */
     int x;

    /**
     * The Y coordinate of the upper-left corner of the <code>Rectangle</code>.
     *
     * @serial
     * @see #setLocation(int, int)
     * @see #getLocation()
     * @since 1.0
     */
     int y;

    /**
     * The width of the <code>Rectangle</code>.
     * @serial
     * @see #setSize(int, int)
     * @see #getSize()
     * @since 1.0
     */
     int width;

    /**
     * The height of the <code>Rectangle</code>.
     *
     * @serial
     * @see #setSize(int, int)
     * @see #getSize()
     * @since 1.0
     */
     int height;

    /**
     * Constructs a new <code>Rectangle</code> whose upper-left corner
     * is at (0,&nbsp;0) in the coordinate space, and whose width and
     * height are both zero.
     */
     Rectangle() {
         this->x = 0;
         this->y = 0;
         this->width = 0;
         this->height = 0;
    }

    /**
     * Constructs a new <code>Rectangle</code> whose upper-left corner is
     * specified as
     * {@code (x,y)} and whose width and height
     * are specified by the arguments of the same name.
     * @param     x the specified X coordinate
     * @param     y the specified Y coordinate
     * @param     width    the width of the <code>Rectangle</code>
     * @param     height   the height of the <code>Rectangle</code>
     * @since 1.0
     */
     Rectangle(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    /**
     * Constructs a new <code>Rectangle</code> whose upper-left corner
     * is at (0,&nbsp;0) in the coordinate space, and whose width and
     * height are specified by the arguments of the same name.
     * @param width the width of the <code>Rectangle</code>
     * @param height the height of the <code>Rectangle</code>
     */
     Rectangle(int width, int height) {
         this->x = 0;
         this->y = 0;
         this->width = width;
         this->height = height;
    }

    /**
     * Constructs a new <code>Rectangle</code> whose upper-left corner is
     * specified by the {@link Point} argument, and
     * whose width and height are specified by the
     * {@link Dimension} argument.
     * @param p a <code>Point</code> that is the upper-left corner of
     * the <code>Rectangle</code>
     * @param d a <code>Dimension</code>, representing the
     * width and height of the <code>Rectangle</code>
     */
     Rectangle(Point& p, Dimension& d) {
         this->x = p.x;
         this->y = p.y;
         this->width = d.width;
         this->height = d.height;
    }

    /**
     * Constructs a new <code>Rectangle</code> whose upper-left corner is the
     * specified <code>Point</code>, and whose width and height are both zero.
     * @param p a <code>Point</code> that is the top left corner
     * of the <code>Rectangle</code>
     */
     Rectangle(Point& p) {
         this->x = p.x;
         this->y = p.y;
         this->width = 0;
         this->height = 0;
    }

    /**
     * Constructs a new <code>Rectangle</code> whose top left corner is
     * (0,&nbsp;0) and whose width and height are specified
     * by the <code>Dimension</code> argument.
     * @param d a <code>Dimension</code>, specifying width and height
     */
     Rectangle(Dimension& d) {
         this->x = 0;
         this->y = 0;
         this->width = d.width;
         this->height = d.height;
    }

    /**
     * Returns the X coordinate of the bounding <code>Rectangle</code> in
     * <code>double</code> precision.
     * @return the X coordinate of the bounding <code>Rectangle</code>.
     */
     double getX() {
        return x;
    }

    /**
     * Returns the Y coordinate of the bounding <code>Rectangle</code> in
     * <code>double</code> precision.
     * @return the Y coordinate of the bounding <code>Rectangle</code>.
     */
     double getY() {
        return y;
    }

    /**
     * Returns the width of the bounding <code>Rectangle</code> in
     * <code>double</code> precision.
     * @return the width of the bounding <code>Rectangle</code>.
     */
     double getWidth() {
        return width;
    }

    /**
     * Returns the height of the bounding <code>Rectangle</code> in
     * <code>double</code> precision.
     * @return the height of the bounding <code>Rectangle</code>.
     */
     double getHeight() {
        return height;
    }

    /**
     * Gets the bounding <code>Rectangle</code> of this <code>Rectangle</code>.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>getBounds</code> method of
     * {@link Component}.
     * @return    a new <code>Rectangle</code>, equal to the
     * bounding <code>Rectangle</code> for this <code>Rectangle</code>.
     * @see       java.awt.Component#getBounds
     * @see       #setBounds(Rectangle)
     * @see       #setBounds(int, int, int, int)
     * @since     1.1
     */
     Rectangle getBounds() {
        return Rectangle(x, y, width, height);
    }

    /**
     * Sets the bounding <code>Rectangle</code> of this <code>Rectangle</code>
     * to match the specified <code>Rectangle</code>.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>setBounds</code> method of <code>Component</code>.
     * @param r the specified <code>Rectangle</code>
     * @see       #getBounds
     * @see       java.awt.Component#setBounds(java.awt.Rectangle)
     * @since     1.1
     */
     void setBounds(Rectangle& r) {
        setBounds(r.x, r.y, r.width, r.height);
    }

    /**
     * Sets the bounding <code>Rectangle</code> of this
     * <code>Rectangle</code> to the specified
     * <code>x</code>, <code>y</code>, <code>width</code>,
     * and <code>height</code>.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>setBounds</code> method of <code>Component</code>.
     * @param x the new X coordinate for the upper-left
     *                    corner of this <code>Rectangle</code>
     * @param y the new Y coordinate for the upper-left
     *                    corner of this <code>Rectangle</code>
     * @param width the new width for this <code>Rectangle</code>
     * @param height the new height for this <code>Rectangle</code>
     * @see       #getBounds
     * @see       java.awt.Component#setBounds(int, int, int, int)
     * @since     1.1
     */
     void setBounds(int x, int y, int width, int height) {
        reshape(x, y, width, height);
    }

    /**
     * Sets the bounding <code>Rectangle</code> of this
     * <code>Rectangle</code> to the specified
     * <code>x</code>, <code>y</code>, <code>width</code>,
     * and <code>height</code>.
     * <p>
     * @param x the new X coordinate for the upper-left
     *                    corner of this <code>Rectangle</code>
     * @param y the new Y coordinate for the upper-left
     *                    corner of this <code>Rectangle</code>
     * @param width the new width for this <code>Rectangle</code>
     * @param height the new height for this <code>Rectangle</code>
     * @deprecated As of JDK version 1.1,
     * replaced by <code>setBounds(int, int, int, int)</code>.
     */
     void reshape(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    /**
     * Returns the location of this <code>Rectangle</code>.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>getLocation</code> method of <code>Component</code>.
     * @return the <code>Point</code> that is the upper-left corner of
     *                  this <code>Rectangle</code>.
     * @see       java.awt.Component#getLocation
     * @see       #setLocation(Point)
     * @see       #setLocation(int, int)
     * @since     1.1
     */
     Point getLocation() {
        return Point(x, y);
    }

    /**
     * Moves this <code>Rectangle</code> to the specified location.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>setLocation</code> method of <code>Component</code>.
     * @param p the <code>Point</code> specifying the new location
     *                for this <code>Rectangle</code>
     * @see       java.awt.Component#setLocation(java.awt.Point)
     * @see       #getLocation
     * @since     1.1
     */
     void setLocation(Point& p) {
        setLocation(p.x, p.y);
    }

    /**
     * Moves this <code>Rectangle</code> to the specified location.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>setLocation</code> method of <code>Component</code>.
     * @param x the X coordinate of the new location
     * @param y the Y coordinate of the new location
     * @see       #getLocation
     * @see       java.awt.Component#setLocation(int, int)
     * @since     1.1
     */
     void setLocation(int x, int y) {
        move(x, y);
    }

    /**
     * Moves this <code>Rectangle</code> to the specified location.
     * <p>
     * @param x the X coordinate of the new location
     * @param y the Y coordinate of the new location
     * @deprecated As of JDK version 1.1,
     * replaced by <code>setLocation(int, int)</code>.
     */
     void move(int x, int y) {
        this->x = x;
        this->y = y;
    }

    /**
     * Translates this <code>Rectangle</code> the indicated distance,
     * to the right along the X coordinate axis, and
     * downward along the Y coordinate axis.
     * @param dx the distance to move this <code>Rectangle</code>
     *                 along the X axis
     * @param dy the distance to move this <code>Rectangle</code>
     *                 along the Y axis
     * @see       java.awt.Rectangle#setLocation(int, int)
     * @see       java.awt.Rectangle#setLocation(java.awt.Point)
     */
     void translate(int dx, int dy) {
        this->x += dx;
        this->y += dy;
    }

    /**
     * Gets the size of this <code>Rectangle</code>, represented by
     * the returned <code>Dimension</code>.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>getSize</code> method of <code>Component</code>.
     * @return a <code>Dimension</code>, representing the size of
     *            this <code>Rectangle</code>.
     * @see       java.awt.Component#getSize
     * @see       #setSize(Dimension)
     * @see       #setSize(int, int)
     * @since     1.1
     */
     Dimension getSize() {
        return Dimension(width, height);
    }

    /**
     * Sets the size of this <code>Rectangle</code> to match the
     * specified <code>Dimension</code>.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>setSize</code> method of <code>Component</code>.
     * @param d the new size for the <code>Dimension</code> object
     * @see       java.awt.Component#setSize(java.awt.Dimension)
     * @see       #getSize
     * @since     1.1
     */
     void setSize(Dimension d) {
         this->width = d.width;
         this->height = d.height;
    }

    /**
     * Sets the size of this <code>Rectangle</code> to the specified
     * width and height.
     * <p>
     * This method is included for completeness, to parallel the
     * <code>setSize</code> method of <code>Component</code>.
     * @param width the new width for this <code>Rectangle</code>
     * @param height the new height for this <code>Rectangle</code>
     * @see       java.awt.Component#setSize(int, int)
     * @see       #getSize
     * @since     1.1
     */
     void setSize(int width, int height) {
         this->width = width;
         this->height = height;
    }

    /**
     * Sets the size of this <code>Rectangle</code> to the specified
     * width and height.
     * <p>
     * @param width the new width for this <code>Rectangle</code>
     * @param height the new height for this <code>Rectangle</code>
     * @deprecated As of JDK version 1.1,
     * replaced by <code>setSize(int, int)</code>.
     */
     void resize(int width, int height) {
         this->width = width;
         this->height = height;
    }

    /**
     * Checks whether or not this <code>Rectangle</code> contains the
     * specified <code>Point</code>.
     * @param p the <code>Point</code> to test
     * @return    <code>true</code> if the specified <code>Point</code>
     *            is inside this <code>Rectangle</code>;
     *            <code>false</code> otherwise.
     * @since     1.1
     */
     bool contains(Point& p) {
        return contains(p.x, p.y);
    }

    /**
     * Checks whether or not this <code>Rectangle</code> contains the
     * point at the specified location {@code (x,y)}.
     *
     * @param  x the specified X coordinate
     * @param  y the specified Y coordinate
     * @return    <code>true</code> if the point
     *            {@code (x,y)} is inside this
     *            <code>Rectangle</code>;
     *            <code>false</code> otherwise.
     * @since     1.1
     */
     bool contains(int x, int y) {
        return inside(x, y);
    }

    /**
     * Checks whether or not this <code>Rectangle</code> entirely contains
     * the specified <code>Rectangle</code>.
     *
     * @param     r   the specified <code>Rectangle</code>
     * @return    <code>true</code> if the <code>Rectangle</code>
     *            is contained entirely inside this <code>Rectangle</code>;
     *            <code>false</code> otherwise
     * @since     1.2
     */
     bool contains(Rectangle r) {
        return contains(r.x, r.y, r.width, r.height);
    }

    /**
     * Checks whether this <code>Rectangle</code> entirely contains
     * the <code>Rectangle</code>
     * at the specified location {@code (X,Y)} with the
     * specified dimensions {@code (W,H)}.
     * @param     X the specified X coordinate
     * @param     Y the specified Y coordinate
     * @param     W   the width of the <code>Rectangle</code>
     * @param     H   the height of the <code>Rectangle</code>
     * @return    <code>true</code> if the <code>Rectangle</code> specified by
     *            {@code (X, Y, W, H)}
     *            is entirely enclosed inside this <code>Rectangle</code>;
     *            <code>false</code> otherwise.
     * @since     1.1
     */
     bool contains(int X, int Y, int W, int H);

    /**
     * Checks whether or not this <code>Rectangle</code> contains the
     * point at the specified location {@code (X,Y)}.
     *
     * @param  X the specified X coordinate
     * @param  Y the specified Y coordinate
     * @return    <code>true</code> if the point
     *            {@code (X,Y)} is inside this
     *            <code>Rectangle</code>;
     *            <code>false</code> otherwise.
     * @deprecated As of JDK version 1.1,
     * replaced by <code>contains(int, int)</code>.
     */
     bool inside(int X, int Y);

    /**
     * Determines whether or not this <code>Rectangle</code> and the specified
     * <code>Rectangle</code> intersect. Two rectangles intersect if
     * their intersection is nonempty.
     *
     * @param r the specified <code>Rectangle</code>
     * @return    <code>true</code> if the specified <code>Rectangle</code>
     *            and this <code>Rectangle</code> intersect;
     *            <code>false</code> otherwise.
     */
     bool intersects(Rectangle& r);

    /**
     * Computes the intersection of this <code>Rectangle</code> with the
     * specified <code>Rectangle</code>. Returns a new <code>Rectangle</code>
     * that represents the intersection of the two rectangles.
     * If the two rectangles do not intersect, the result will be
     * an empty rectangle.
     *
     * @param     r   the specified <code>Rectangle</code>
     * @return    the largest <code>Rectangle</code> contained in both the
     *            specified <code>Rectangle</code> and in
     *            this <code>Rectangle</code>; or if the rectangles
     *            do not intersect, an empty rectangle.
     */
     Rectangle intersection(Rectangle& r){
    	 Rectangle result;
    	 this->intersection(r,result);
    	 return result;
     }
     void intersection(Rectangle& r,Rectangle& result);

    /**
     * Computes the union of this <code>Rectangle</code> with the
     * specified <code>Rectangle</code>. Returns a new
     * <code>Rectangle</code> that
     * represents the union of the two rectangles.
     * <p>
     * If either {@code Rectangle} has any dimension less than zero
     * the rules for <a href=#NonExistant>non-existant</a> rectangles
     * apply.
     * If only one has a dimension less than zero, then the result
     * will be a copy of the other {@code Rectangle}.
     * If both have dimension less than zero, then the result will
     * have at least one dimension less than zero.
     * <p>
     * If the resulting {@code Rectangle} would have a dimension
     * too large to be expressed as an {@code int}, the result
     * will have a dimension of {@code Integer.MAX_VALUE} along
     * that dimension.
     * @param r the specified <code>Rectangle</code>
     * @return    the smallest <code>Rectangle</code> containing both
     *            the specified <code>Rectangle</code> and this
     *            <code>Rectangle</code>.
     */
     Rectangle union_(Rectangle& r){
    	 Rectangle result;
    	 this->union_(r,result);
    	 return result;
     }
     void union_(Rectangle& r,Rectangle& result);

    /**
     * Adds a point, specified by the integer arguments {@code newx,newy}
     * to the bounds of this {@code Rectangle}.
     * <p>
     * If this {@code Rectangle} has any dimension less than zero,
     * the rules for <a href=#NonExistant>non-existant</a>
     * rectangles apply.
     * In that case, the new bounds of this {@code Rectangle} will
     * have a location equal to the specified coordinates and
     * width and height equal to zero.
     * <p>
     * After adding a point, a call to <code>contains</code> with the
     * added point as an argument does not necessarily return
     * <code>true</code>. The <code>contains</code> method does not
     * return <code>true</code> for points on the right or bottom
     * edges of a <code>Rectangle</code>. Therefore, if the added point
     * falls on the right or bottom edge of the enlarged
     * <code>Rectangle</code>, <code>contains</code> returns
     * <code>false</code> for that point.
     * If the specified point must be contained within the new
     * {@code Rectangle}, a 1x1 rectangle should be added instead:
     * <pre>
     *     r.add(newx, newy, 1, 1);
     * </pre>
     * @param newx the X coordinate of the new point
     * @param newy the Y coordinate of the new point
     */
     void add(int newx, int newy);

    /**
     * Adds the specified {@code Point} to the bounds of this
     * {@code Rectangle}.
     * <p>
     * If this {@code Rectangle} has any dimension less than zero,
     * the rules for <a href=#NonExistant>non-existant</a>
     * rectangles apply.
     * In that case, the new bounds of this {@code Rectangle} will
     * have a location equal to the coordinates of the specified
     * {@code Point} and width and height equal to zero.
     * <p>
     * After adding a <code>Point</code>, a call to <code>contains</code>
     * with the added <code>Point</code> as an argument does not
     * necessarily return <code>true</code>. The <code>contains</code>
     * method does not return <code>true</code> for points on the right
     * or bottom edges of a <code>Rectangle</code>. Therefore if the added
     * <code>Point</code> falls on the right or bottom edge of the
     * enlarged <code>Rectangle</code>, <code>contains</code> returns
     * <code>false</code> for that <code>Point</code>.
     * If the specified point must be contained within the new
     * {@code Rectangle}, a 1x1 rectangle should be added instead:
     * <pre>
     *     r.add(pt.x, pt.y, 1, 1);
     * </pre>
     * @param pt the new <code>Point</code> to add to this
     *           <code>Rectangle</code>
     */
     void add(Point& pt) {
        add(pt.x, pt.y);
    }

    /**
     * Adds a <code>Rectangle</code> to this <code>Rectangle</code>.
     * The resulting <code>Rectangle</code> is the union of the two
     * rectangles.
     * <p>
     * If either {@code Rectangle} has any dimension less than 0, the
     * result will have the dimensions of the other {@code Rectangle}.
     * If both {@code Rectangle}s have at least one dimension less
     * than 0, the result will have at least one dimension less than 0.
     * <p>
     * If either {@code Rectangle} has one or both dimensions equal
     * to 0, the result along those axes with 0 dimensions will be
     * equivalent to the results obtained by adding the corresponding
     * origin coordinate to the result rectangle along that axis,
     * similar to the operation of the {@link #add(Point)} method,
     * but contribute no further dimension beyond that.
     * <p>
     * If the resulting {@code Rectangle} would have a dimension
     * too large to be expressed as an {@code int}, the result
     * will have a dimension of {@code Integer.MAX_VALUE} along
     * that dimension.
     * @param  r the specified <code>Rectangle</code>
     */
     void add(Rectangle& r);

    /**
     * Resizes the <code>Rectangle</code> both horizontally and vertically.
     * <p>
     * This method modifies the <code>Rectangle</code> so that it is
     * <code>h</code> units larger on both the left and right side,
     * and <code>v</code> units larger at both the top and bottom.
     * <p>
     * The new <code>Rectangle</code> has {@code (x - h, y - v)}
     * as its upper-left corner,
     * width of {@code (width + 2h)},
     * and a height of {@code (height + 2v)}.
     * <p>
     * If negative values are supplied for <code>h</code> and
     * <code>v</code>, the size of the <code>Rectangle</code>
     * decreases accordingly.
     * The {@code grow} method will check for integer overflow
     * and underflow, but does not check whether the resulting
     * values of {@code width} and {@code height} grow
     * from negative to non-negative or shrink from non-negative
     * to negative.
     * @param h the horizontal expansion
     * @param v the vertical expansion
     */
     void grow(int h, int v);
};


} /* namespace pwt */

#endif /* INCLUDE_PWT_GRAPHICS_RECTANGLE_H_ */

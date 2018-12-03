/*
 * final-3.c
 *
 *  Problem 3.
 *
 *	This problem tests your understanding of structs and
 *	dynamic memory allocation.
 *
 *	Below are the Point, Circle, and Rectangle structs from
 *	assignment 6. You will implement functions newPoint(),
 *	newRectangle(), and newCircle() that initialize and return
 *	a Point, Rectangle, or Circle, If the functions are passed
 *	a Point, Rectangle, or Circle, they initialize those and
 *	return a pointer to them. Otherwise, they allocate,
 *	initialize, and return a new Point, Rectangle, or Circle.
 *
 *	You will also implement getBoundingBox() that takes a
 *	Rectangle and initializes it to the bounding box of a
 *	Circle. Otherwise, the function allocates, initializes
 *	and returns new bounding box Rectangle. Review your
 *	assignment-6 code for this function.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Stuct representing a point
 */
typedef struct {
	/** X value of point */
	double x;
	/** Y value of point */
	double y;
} Point;

/**
 * Struct representing a circle
 */
typedef struct {
	/** Center of circle */
	Point center;
	/** Radius of circle */
	double radius;
} Circle;

/**
 * Struct representing a rectangle
 */
typedef struct {
	/** top left point of rectangle */
	Point topLeft;
	/** width of rectangle */
	double width;
	/** height of rectangle */
	double height;
} Rectangle;

/**
 * Initialize a new point with the specified coordinates.
 * If newPoint is NULL, allocates a new point to initialize.
 * Otherwise initializes newPoint that was passed in.
 *
 * @param x the x coordinate
 * @param y the y coordinate * @param height the height of the rectangle
 * @param newPoint a new Point to initialize or NULL to allocate new one
 * @return a pointer to newPoint or to a dynamically allocated
 *   point if newPoint is NULL
 */
Point *newPoint(double x, double y, Point *newPoint) {
	// your code here
	// If the newPoint passed in is NULL, allocate storage from heap
	if (newPoint == NULL) {
		newPoint = malloc(sizeof(Point));
	}
	newPoint->x = x;
	newPoint->y = y;
	return newPoint;
}

/**
 * Initialize a new rectangle with the specified point, width, and height.
 * If newRect is NULL, allocates a new rectangle to initialize. Otherwise
 * initializes newRect that was passed in.
 *
 * @param topLeft the top left point
 * @param width the width of the rectangle
 * @param height the height of the rectangle
 * @param newRect a new Rectangle to initialize or NULL to allocate new one
 * @return a pointer to newRect or to a dynamically allocated
 *   rectangle if newRect is NULL
 */
Rectangle *newRectangle(const Point *topLeft, double width, double height,
		Rectangle *newRect) {
	// your code here
	// If newRect passed in is NULL, allocate storage from heap
//	if (topLeft == NULL){
//		return NULL;
//	}
	if (newRect == NULL) {
		newRect = malloc(sizeof(Rectangle));
	}
	newRect->height = height;
	newRect->width = width;
	// Point struct is passed by value
	newRect->topLeft = *topLeft;
	return newRect;
}

/**
 * Initialize a new circle with the specified point, width, and height.
 * If newCircle is NULL, allocates a new circle to initialize. Otherwise
 * initializes newCircle that was passed in.
 *
 * @param center the center point
 * @param radius the radius of the circle
 * @return a pointer to newCircle or to a dynamically allocated
 *   circle if newCircle is NULL
 */
Circle *newCircle(const Point *center, double radius, Circle *newCircle) {
	// your code here
	// if the circle is not on the stack, allocate space for it from heap
	if (newCircle == NULL) {
		newCircle = malloc(sizeof(Circle));
	}
	newCircle->radius = radius;
	newCircle->center = *center;
	return newCircle;
}

/**
 * Returns the bounding box of the specified circle. If bounding box
 * is NULL, creates a new bounding box to initialize. Otherwise
 * initializes boundingBox that was passed in.
 *
 * @param circle the circle
 * @param boundingBox the bounding box of the circle or to a
 *   dynamically allocated rectangle if boundingBox is NULL
 */
Rectangle *getBoundingBox(const Circle *circle, Rectangle *boundingBox) {
	// your code here
	// NOTE: implement using newPoint() and newRectangle();
	// do not malloc storage in this function.
//  no need to check whether it's NULL or not
//	if(boundingBox == NULL){
//		Point heapUpperLeft;
//		double x = circle->center.x - circle->radius;
//		double y = circle->center.y + circle->radius;
//		heapUpperLeft = *(newPoint(x, y, &heapUpperLeft));
//		double heapRectWidth = 2 * circle->radius;
//		double heapRectHeight = 2 * circle ->radius;
//		return newRectangle(&heapUpperLeft,heapRectWidth, heapRectHeight, boundingBox);
//	}
	Point topLeft;
	double x = circle->center.x - circle->radius;
	double y = circle->center.y + circle->radius;
	// Copy the point struct by value
	topLeft = *(newPoint(x, y, &topLeft));
	double width = 2 * circle->radius;
	double height = 2 * circle->radius;
	return newRectangle(&topLeft, width, height, boundingBox);
}

/**
 * Tests the deck functions
 */
int main(void) {
	printf("Start Problem 3\n");

	// test local point
	Point point1;
	Point *point1p = newPoint(10.0, 20.0, &point1);
	printf("local Point: x=%f, y=%f ", point1p->x, point1p->y);
	printf("expected: x=%f, y=%f\n", 10.0, 20.0);

	// test heap point
	Point *point2p = newPoint(30.0, 40.0, NULL);  // not freed
	printf("heap  Point: x=%f, y=%f ", point2p->x, point2p->y);
	printf("expected: x=%f, y=%f\n", 30.0, 40.0);
	// free(point2p);

	// test local rectangle
	Rectangle rect1;
	Rectangle *rect1p = newRectangle(point1p, 15.0, 30.0, &rect1);
	printf("local Rectangle: x=%f, y=%f width=%f height=%f ", rect1p->topLeft.x,
			rect1p->topLeft.y, rect1p->width, rect1p->height);
	printf("expected: x=%f, y=%f width=%f height=%f\n", point1p->x, point1p->y,
			15.0, 30.0);

	// test heap rectangle
	Rectangle *rect2p = newRectangle(point2p, 15.0, 30.0, NULL); // not freed
	printf("heap  Rectangle: x=%f, y=%f width=%f height=%f ", rect2p->topLeft.x,
			rect2p->topLeft.y, rect2p->width, rect2p->height);
	printf("expected: x=%f, y=%f width=%f height=%f\n", point2p->x, point2p->y,
			15.0, 30.0);
	// free(rect2p);

	// test local circle
	Circle circle1;
	Circle *circle1p = newCircle(point1p, 15.0, &circle1);
	printf("local Circle: x=%f, y=%f radius=%f ", circle1p->center.x,
			circle1p->center.y, circle1p->radius);
	printf("expected: x=%f, y=%f radius=%f\n", point1p->x, point1p->y, 15.0);

	// test heap circle
	Circle *circle2p = newCircle(point2p, 10.0, NULL);  // not freed
	printf("local Circle: x=%f, y=%f radius=%f ", circle2p->center.x,
			circle2p->center.y, circle2p->radius);
	printf("expected: x=%f, y=%f radius=%f\n", point2p->x, point2p->y, 10.0);
	// free(circle2p);

	// test local bounding box
	Rectangle bbox1;
	Rectangle *bbox1p = getBoundingBox(circle1p, &bbox1);
	printf("local Bounding Box: x=%f, y=%f width=%f height=%f ",
			bbox1p->topLeft.x, bbox1p->topLeft.y, bbox1p->width,
			bbox1p->height);
	printf("expected: x=%f, y=%f width=%f height=%f\n", -5.0, 35.0,
			circle1p->radius * 2.0, circle1p->radius * 2.0);

	// test heap bounding box
	Rectangle *bbox2p = getBoundingBox(circle2p, NULL);  // not freed
	printf("heap  Bounding Box: x=%f, y=%f width=%f height=%f ",
			bbox2p->topLeft.x, bbox2p->topLeft.y, bbox2p->width,
			bbox2p->height);
	printf("expected: x=%f, y=%f width=%f height=%f\n", 20.0, 50.0,
			circle2p->radius * 2.0, circle2p->radius * 2.0);
	// free( &(bbox2p->topLeft));
	// free(bbox2p);

	printf("\nEnd Problem 3\n");

}

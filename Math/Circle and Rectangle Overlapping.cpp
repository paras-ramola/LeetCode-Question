Approach:
// Find the closest point of the rectangle to the circle's center.
// If the distance to this point <= radius, they overlap.

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1,
                      int x2, int y2) {

        int x, y;

        // Find the closest X-coordinate of the rectangle to the circle center.
      
        // If circle(center) is left of rectangle -> take left side (x1)
        // If center is right of rectangle -> take right side (x2)
        // Otherwise, center is already inside the rectangle's X-range.
        if (x1 >= xCenter) {
            x = x1;
        } else if (x2 <= xCenter) {
            x = x2;
        } else {
            x = xCenter;
        }

        // Find the closest Y-coordinate of the rectangle to the circle center.
        // Same logic as X.
        if (y1 >= yCenter) {
            y = y1;
        } else if (y2 <= yCenter) {
            y = y2;
        } else {
            y = yCenter;
        }

        // Calculate distance between circle center and closest rectangle point.
        int dist = sqrt((x - xCenter) * (x - xCenter) +
                        (y - yCenter) * (y - yCenter));

        // If closest point is within the circle, they overlap.
        return dist <= radius;
    }
};

//Approach 2:clamp
//clamp does the same job as aour if else block
// For 
x = clamp(xCenter, x1, x2);
// means
if xCenter < x1  → x = x1
if xCenter > x2  → x = x2
otherwise        → x = xCenter

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1,
                      int x2, int y2) {

        // Find the closest point of the rectangle to the circle center.
        // clamp keeps the center coordinate inside the rectangle's range.
        int x = clamp(xCenter, x1, x2);
        int y = clamp(yCenter, y1, y2);

        // Calculate squared distance between the circle center
        // and the closest point of the rectangle.
        int dist = (x - xCenter) * (x - xCenter) +
                   (y - yCenter) * (y - yCenter);

        // If the closest point is inside the circle, they overlap.
        return dist <= radius * radius;
    }
};

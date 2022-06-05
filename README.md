# dodgeball-robot-project

------------------------------------------------------------------
Algorithm | Ball Tracking Algorithm
------------------------------------------------------------------

This algorithm tracks the ball continuously
and sends the ball's position to the Arduino

## Pseudocode of the Ball Tracking Algorithm

    class BallTracking
        Constructor
            Initialize the "green_lower" and "green_upper" variables for hsv color spaces
            Start the threaded video streaming and initialize it to "video_stream" variable
            Initialize the "arduino" variable over Serial USB port
            Initialize left, right and none boolean variables to all True

        Function ball_tracking
            while True:
                Read the frame and initialize it to "frame" variable
                Resize the frame size as 500x281
                Blur the image and initialize it to "blurred_image" variable
                Create a hsv array with blurred image and initialize it to "hsv_array"
                Create a mask using the hsv_array, green_lower and green_upper boundaries
                and apply operations to remove noises
                Find and grab the contours of the ball and initialize to "contours" variable

                if contours > 0:
                    Get the biggest area contour
                    Find the minimum enclosing circle and its centroid
                    Get the radius of the circle and the x_coor of centroid

                    if radius > 10 and radius < 60:
                        if ball_center_x_coor < 250:
                            Send "1" to arduino to move right

                        elif ball_center_x_coor >= 250:
                            Send "0" to arduino to move left
                else:
                    Send arduino "-1" to stop
















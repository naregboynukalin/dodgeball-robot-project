import cv2
import serial

from threaded_video_stream import ThreadedVideoStream
from constants.ball_tracking import BallTrackingConstants
from utils import *


class BallTracking:

    def __init__(self):
        self.green_lower = BallTrackingConstants.green_lower_boundaries
        self.green_upper = BallTrackingConstants.green_upper_boundaries
        self.video_stream = ThreadedVideoStream(src=0).start_thread()
        self.arduino = serial.Serial('/dev/ttyUSB0', 9600)
        self.left = True
        self.right = True
        self.none = True

    def ball_tracking(self):
        while True:
            frame = self.video_stream.read_frame()
            frame = resize(frame, width=500)
            blurred_img = blur_image(frame, (11, 11), 0)
            hsv_array = color_converter(blurred_img, cv2.COLOR_BGR2HSV)
            mask_green = mask_generator(hsv_array, self.green_lower, self.green_upper)
            contours = cv2.findContours(mask_green.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
            contours = grab_contours(contours)
            centroid = None

            if len(contours) > 0:
                max_contour = max(contours, key=cv2.contourArea)
                centroid = find_centroid(max_contour)
                ball_center_x_coor = centroid[0]
                ((x_coor, y_coor), radius) = cv2.minEnclosingCircle(max_contour)

                if radius > 10:
                    position = None
                    if ball_center_x_coor < 250 and self.left:
                        position = "left"

                    elif ball_center_x_coor >= 250 and self.right:
                        position = "right"

                    if position == "left" and self.left:
                        self.left = False
                        self.right = True
                        self.none = True
                        self.arduino.write('1'.encode('utf-8'))
                    elif position == "right" and self.right:
                        self.left = True
                        self.right = False
                        self.none = True
                        self.arduino.write('0'.encode('utf-8'))

                    cv2.circle(frame, (int(x_coor), int(y_coor)), int(radius),
                               (0, 255, 255), 2)
                    cv2.circle(frame, centroid, 5, (0, 0, 255), -1)

            elif self.none:
                self.none = False
                self.right = True
                self.left = True
                self.arduino.write('-1'.encode('utf-8'))

            key = cv2.waitKey(1) & 0xFF
            if key == ord("q") or key == ord("Q"):
                break

        cv2.destroyAllWindows()

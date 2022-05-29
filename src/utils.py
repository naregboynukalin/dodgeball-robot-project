import cv2


def resize(image, width=None, inter=cv2.INTER_AREA):
    (height, _width) = image.shape[:2]
    r = width / float(_width)
    dimension = (width, int(height * r))

    resized = cv2.resize(image, dimension, interpolation=inter)

    return resized


def grab_contours(contours):
    if len(contours) == 2:
        contours = contours[0]

    elif len(contours) == 3:
        contours = contours[1]

    return contours


def blur_image(frame, kernel_size, std_x):
    return cv2.GaussianBlur(frame, kernel_size, std_x)


def color_converter(frame, func):
    return cv2.cvtColor(frame, func)


def mask_generator(hsv_array, color_lower, color_upper):
    mask_green = cv2.inRange(hsv_array, color_lower, color_upper)
    mask_green = cv2.erode(mask_green, None, iterations=2)
    mask_green = cv2.dilate(mask_green, None, iterations=2)

    return mask_green


def find_centroid(contour):
    moments = cv2.moments(contour)
    centroid = (int(moments["m10"] / moments["m00"]), int(moments["m01"] / moments["m00"]))

    return centroid

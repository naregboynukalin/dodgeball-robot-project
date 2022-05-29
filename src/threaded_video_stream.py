from threading import Thread
import cv2


class ThreadedVideoStream:
    def __init__(self, src=0, thread_name="ThreadedVideoStream"):
        self.video_stream = cv2.VideoCapture(src)
        (self.result_val, self.frame) = self.video_stream.read()

        self.thread_name = thread_name

        self.is_stopped = False

    def start_thread(self):
        thread_obj = Thread(target=self.update_thread, name=self.thread_name, args=())
        thread_obj.daemon = True
        thread_obj.start()
        return self

    def update_thread(self):
        while True:
            if self.is_stopped:
                return

            (self.result_val, self.frame) = self.video_stream.read()

    def read_frame(self):
        return self.frame

    def stop_thread(self):
        self.is_stopped = True

import threading
import time

NUM_READERS = 3
NUM_WRITERS = 1

mutex = threading.Semaphore(1)  # Semaphore to protect readCount
db = threading.Semaphore(1)     # Semaphore to allow only one writer at a time
read_count = 0                  # Track number of readers currently reading

class Reader(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id

    def run(self):
        global read_count
        while True:
            # Start reading
            mutex.acquire()
            read_count += 1
            if read_count == 1:  # First reader acquires the database
                db.acquire()
            mutex.release()

            self.read_db()

            # Done reading
            mutex.acquire()
            read_count -= 1
            if read_count == 0:  # Last reader releases the database
                db.release()
            mutex.release()

            time.sleep(1)  # Simulating some processing time

    def read_db(self):
        print(f"Reader {self.id}: is reading the database")


class Writer(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id

    def run(self):
        while True:
            self.prepare_data()
            db.acquire()  # Writer locks the database for exclusive access
            self.write_data()
            db.release()  # Writer releases the database
            time.sleep(2)  # Simulate time taken to write

    def prepare_data(self):
        print(f"Writer {self.id}: is preparing data")

    def write_data(self):
        print(f"Writer {self.id}: is writing to the database")


if __name__ == "__main__":
    # Create and start reader threads
    readers = [Reader(i) for i in range(1, NUM_READERS + 1)]
    for reader in readers:
        reader.start()

    # Create and start writer threads
    writers = [Writer(i) for i in range(1, NUM_WRITERS + 1)]
    for writer in writers:
        writer.start()

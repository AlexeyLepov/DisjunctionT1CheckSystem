from timeit import timeit
from os import listdir
import threading

timeout_time = 5 #this may be changed later

def read(filename):
### your code goes here ###


### vvvv remove that
    pass

def find(filename):
### your code goes here ###


### vvvv remove that
    pass


def find_timeout(filename):
    p = threading.Thread(target = find, args = (filename,))
    p.start()
    p.join(timeout_time)


def main():
    files = listdir("./tests")
    # first double file is necessary for the corret time check
    times = [timeit(lambda: find_timeout("./tests/"+file), number = 1) for file in [files[0]]+files][1:]
    print(*[time if time < timeout_time else "inf" for time in times])


if __name__ == "__main__":
    main()

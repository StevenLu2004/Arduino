import datetime as dt
import serial
import time

"""
    Get the current date and time as a string
    @return {str} a string representing the current date and time
"""
def getTimeString():
    d = dt.datetime.now()
    return d.strftime("%Y_%m_%d__%H_%M_%S")

"""
    Initialize the computer-side serial and call the next step (open CSV file)
    @return {int} status code
"""
def initSerial():
    try:
        ser = serial.Serial(input("port: "))
        print("Let connection settle...")
        time.sleep(5)  # Key to success
        print(ser)
        return openFile(ser)
    except:
        return -1

"""
    Open a new CSV file named with the date and time and call the next step (reading the data)
    @param {serial.Serial} ser the serial object
    @return {int} status code
"""
def openFile(ser):
    with open(f"readings__{getTimeString()}.csv", "w") as f:
        f.write("\"Voltage (1.075mV)\",\"Count (sec)\"\n")
        return readData(ser, f)
    return -2

"""
    Read the data from the Arduino serial and save to file
    @param {serial.Serial} ser the serial object
    @param {file} f the file to save the data to
    @return {int} status code
"""
def readData(ser, f):
    # Start
    ser.write(b"connect\n")
    print(ser.readline())
    # Read
    for i in range(256):
        s = int(ser.readline())
        f.write(f"{i},{s}\n")
        # ser.write(bytes(str(s)+'\n')); ser.flush()
    f.close()
    ser.close()
    return 0

"""
    Main function
    @return {int} status code
"""
def main():
    ext = initSerial()
    print(f"initSerial() exited with status {ext}")
    return ext

if __name__ == "__main__":
    exit(main())

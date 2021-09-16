import serial
import time
arduino_port = "COM3" 		# serial port of Arduino
baud = 9600 			# arduino uno runs at 9600 baud

a = 'p'
b = '1'
c = '-'
d = 'w'
e = '1'

f = '1'

fileName = a + b + c + d + c + e + f 		# name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")

t_end = time.time() + 5		# read data for 5 seconds
while time.time() <= t_end:
#display the data to the terminal
    getData=str(ser.readline())
    data=getData[2:][:-3]	# Do not change these values or the generated file will have extra ' or '\n' in them
    if(data=='new_task_prosup_3_')
        d = 'ps'
        e = '3'

        fileName = a + b + c + d + c + e
    print(data)
    file = open(fileName, "a") 	# append the data to the file
    file.write(data + "\n") 	# write data with a newline

#add the data to the file

#close out the file
file.close()

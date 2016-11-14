import serial
import time
import thread
import sys

com_port = "COM4" # example: 5 == "COM6" == "/dev/tty5"
baudrate = 115200
max = 65535.0
euler = [0,0,0]

def read_imu():
	global euler
	while True:
		try:
			time.sleep(0.00001)
			byte = ord(ser.read(1))
			if byte == 0:
				byte = ord(ser.read(1))
				if byte == 0:
					byte = ord(ser.read(1))
					if byte == 0:
						raw_data = [ ord(byte) for byte in ser.read(6)]
						x = float(raw_data[0] | (raw_data[1] << 8))
						y = float(raw_data[2] | (raw_data[3] << 8))
						z = float(raw_data[4] | (raw_data[5] << 8))
						if x > 32757:
							x=(x-max)/ 16.0
						else:
							x=x/16.0
						if y > 32757:
							y=(y-max)/ 16.0
						else:
							y=y/16.0
						if z > 32757:
							z=(z-max)/ 16.0
						else:
							z=z/16.0
						euler = [x,y,z]
		except :
			traceback.print_exc(file=sys.stdout)

ser = serial.Serial(com_port, baudrate)
th = thread.start_new_thread(read_imu,())
while True:
	print '{0:.3f} {1:5.3f} {2:5.3f}'.format(euler[0], euler[1], euler[2])
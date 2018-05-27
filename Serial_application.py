#!/usr/bin/python3
import matplotlib as mpl
from   mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import serial
import re

plt.axis([0, 10, 0, 10])

plt.ion()
ser = serial.Serial('/dev/ttyACM0', 921600, timeout=1)

fig = plt.figure()


ax = fig.gca(projection='3d')

while True:
	raw_data = ser.readline()
	data = ser.readline().decode('utf-8') #read line and convert to String type
	print(data)
	data = data[:-2] # remove last to bytes (\r\n)
	data = re.sub(r'\s', '', data).split(',')

	data_ints = [int(i) for i in data]
	
	p1 = data_ints[0:3]
	p2 = data_ints[3:6]

	line_data = ax.plot([ 50 - p1[1] / 2, -p2[2] / 2 ], [ 50 + p1[0] / 2, -(p2[0] / 2) ], [ 50 + (p1[2] / 2), (p2[1] / 2) ])
	#,p2[2] / 2, -p2[0] / 2,'-og')

#	lines.pop(0).remove()
	ax.set_xlim(-100, 100)
	ax.set_ylim(-100, 100)
	ax.set_zlim(-100, 100)
	ax.set_xlabel('X axis')
	ax.set_ylabel('Y axis')
	ax.set_zlabel('Z axis')
#	plt.lim((-200,200))
	ser.reset_input_buffer()
	fig.canvas.draw()
	ax.clear()


if __name__ == "__main__":
    # execute only if run as a script
    main()
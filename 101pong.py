#!/usr/bin/python

import sys
import math

class Vec3(object):
	def __init__(self, x = 0.0, y = 0.0, z = 0.0):
		try:
			self.x = float(x)
			self.y = float(y)
			self.z = float(z)
		except ValueError:
			pong101error("Error: incorrect vector arguments")

	def __add__(self, other):
		if isinstance(other, Vec3):
			return Vec3(self.x + other.x, self.y + other.y, self.z + other.z)
		else:
			return Vec3(self.x + float(other), self.y + float(other), self.z + float(other))

	def __sub__(self, other):
		if isinstance(other, Vec3):
			return Vec3(self.x - other.x, self.y - other.y, self.z - other.z)
		else:
			return Vec3(self.x - float(other), self.y - float(other), self.z - float(other))

	def __mul__(self, other):
		if isinstance(other, Vec3):
			return Vec3(self.x * other.x, self.y * other.y, self.z * other.z)
		else:
			return Vec3(self.x * float(other), self.y * float(other), self.z * float(other))

	def __truediv__(self, other):
		if isinstance(other, Vec3):
			if other.x == 0.0 or other.y == 0.0 or other.z == 0.0:
				pong101error("Error: division by zero")
			return Vec3(self.x / other.x, self.y / other.y, self.z / other.z)
		else:
			if float(other) == 0.0:
				pong101error("Error: division by zero")
			return Vec3(self.x / float(other), self.y / float(other), self.z / float(other))

	def length(self):
		return math.sqrt(math.pow(self.x, 2) + math.pow(self.y, 2) + math.pow(self.z, 2))

	def normalized(self):
		return self / self.length()

	def dot(self, other):
		return self.x * other.x + self.y * other.y + self.z * other.z

	def tostring(self):
		return '(' + "{0:.2f}".format(self.x) + ';' + "{0:.2f}".format(self.y) + ';' + "{0:.2f}".format(self.z) + ')'

def pong101error(msg):
	sys.stderr.write(msg + '\n')
	sys.stderr.flush()
	sys.exit(84);

def incidence(vec0, vec1):
	return math.degrees(math.asin(vec0.dot(vec1)))

def main():
	vec0 = Vec3(sys.argv[1], sys.argv[2], sys.argv[3])
	vec1 = Vec3(sys.argv[4], sys.argv[5], sys.argv[6])
	try:
		timeshift = int(sys.argv[7])
		if timeshift < 0:
			pong101error("Error: timeshift must be greater than or equal to 0")
	except ValueError:
		pong101error("Error: incorrect timeshift argument")
	speed = vec1 - vec0
	vec2 = vec1 + speed * timeshift
	angle = 0.0
	try:
		angle = incidence(speed.normalized(), Vec3(0, 1, 1))
	except ValueError:
		angle = -1.0
	print("The speed vector coordinates are :")
	print(speed.tostring())
	print("At time t+" + str(timeshift) + ", ball coordinates will be :")
	print(vec2.tostring())
	if angle >= 0.0 and angle <= 90.0:
		print("The incidence angle is :")
		print("{0:.2f} degrees".format(angle))
	else:
		print("The ball won't reach the bat.")
	sys.exit(0)

if len(sys.argv) != 8:
	errMsg = ("Usage: " + sys.argv[0] + " x0 y0 z0 x1 y1 z1 n\n\nx0: ball abscissa at time t - 1\n"
		"y0: ball ordinate at time t - 1\nz0: ball altitude at time t - 1\nx1: ball abscissa at time t\n"
		"y1: ball ordinate at time t\nz1: ball altitude at time t\nn: time shift (greater than or equal to zero, integer)")
	pong101error(errMsg)
else:
	main()

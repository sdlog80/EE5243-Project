#! /usr/bin/python

#SpaceCannon.py 
#example to run: ./SpaceCannon.py
import numpy 
import sys 
import os
from subprocess import call
import subprocess

print "**** Welcome to the Space Cannon Ballistics Simulation ****"
print ""

print "Enter intial launch position: "
launchposition = raw_input()

print "Enter maximum length of time to wait before launching: "
launchwaittime = input()

print "Enter time willing to wait for object to travel: "
traveltime = input()

print ""
print "You have entered the following parameters:"
print "Initial Launch Position: ", launchposition
print "Maximum Length of Time to Wait Before Launching: ", launchwaittime
print "Time Willing to Wait for Object to Travel: ", traveltime
print "----------------------------------------------"

print ""

# Run the C++ Space simulation executable file, named 'Space'	
os.system("EE5243-Project/Space")

# This code reads in values from the Simfile, and then prints the data.		
data = []
file = open("Simfile", "r")
for line in file:
	data.append(line)

print data
file.close()

#This code calls the mpiexec command to spawn the MPIprocessfile.py file 2 times.
command = "mpiexec -n 2 python ./MPIprocessfile.py"
os.system(command)
print ""









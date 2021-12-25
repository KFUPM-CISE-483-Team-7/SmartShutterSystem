# -*- coding: utf-8 -*-
"""
Created on Fri Dec 24 23:19:10 2021

@author: Sectorprime
"""
import serial

SAL = serial.Serial('COM8',9600)
i = 0

while i < 60: #Run demo for 60 seconds
    # Read Data from Arduino via Serial
    sensorReadings = SAL.readline().decode().strip().split(' ')
    sensorReadingsInt = [int(numeric_string) for numeric_string in sensorReadings] #convert to integer
    
    # Processing the data (should be passed over to RL Algorithm)
    command = ((sensorReadingsInt[4]*max(sensorReadingsInt[1],1))/(sensorReadingsInt[0]+sensorReadingsInt[1]+sensorReadingsInt[2]+sensorReadingsInt[3])*180) #apply control
    print(command)
    
    # Sending control signal to Servo motor (Should be output of RL Algorithm)
    command = str(command).encode() #encode for serial transmission
    SAL.write(command)
    i = i + 1

SAL.close()
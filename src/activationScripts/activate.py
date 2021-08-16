import csv
from netaddr import IPNetwork, IPAddress
import random
import subprocess
import sys
import time

import compiler.py

with open('log.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter='\t')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            line_count += 1
        else:

            ip = row[1] 
            ip = ip.lstrip().rstrip()
	activate(ip)

def activate(ip):
	knock(ip, ports)

def knock(ip, ports):
	for i in ports:
		subprocess.run(["nc", ip, i])

def numKnock(ip, key, number):


#def portKnock(ip, key, number):


def listenerSetup(ip, port, platform, arch):
	if ip: 
		



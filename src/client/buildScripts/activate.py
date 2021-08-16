import csv
from netaddr import IPNetwork, IPAddress
import random
import subprocess
import sys
import time
from ast import literal_eval


#### Knock on all provided ports for the given IP
def knock(ip, ports):
    ip = str(ip)
    for i in literal_eval(ports):
        print("Connecting to " + ip + " on port " + str(i))
        subprocess.run(["nc", ip, str(i)])

with open('../log.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter='\t')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            line_count += 1
        else:

            ip = row[1]
            ip = ip.lstrip().rstrip()

            ports = row[5]

            knock(ip, ports)


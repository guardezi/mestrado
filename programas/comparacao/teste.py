#!/bin/python
from os import popen
import time

ar=(time.strftime("%Y-%m-%d"))+"_"+(time.strftime("%I-%M-%S"))
algs = open("algoritmos.txt","r")
desc = ["SIFT"]

for a in algs:
	det = a.split(",")
print det

for a in det:
	for d in desc:
		teste = open("testes.txt")
		for t in teste:
			if len(t) > 1:
				base = open("base.txt")
				for b in base:
					if len(b) > 1:
						txt = str("./src/compara {0} {1} {2} {3} >> resultado-{4}.txt".format(t,b,a,d,ar))
						
						y  =txt.split("\n")
						
						if len(y) == 3:
							teta = y[0]+y[1]+y[2]
						else:
							if len(y) == 2:
								teta = y[0]+y[1]

						print teta
						# popen(teta)

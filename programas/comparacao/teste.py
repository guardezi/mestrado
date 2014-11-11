#!/bin/python
from os import popen

det = ["HARRIS","MSER"]
desc = ["SIFT"]

for a in det:
	for d in desc:
		teste = open("testes.txt")
		for t in teste:
			if len(t) > 1:
				base = open("base.txt")
				for b in base:
					if len(b) > 1:
						txt = str("./src/compara {0} {1} {2} {3} >> resultado.txt".format(t,b,a,d))
						print txt
						popen(txt)

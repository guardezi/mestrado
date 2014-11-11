#!/bin/python
from os import popen

saida = open("run.sh",'w')

det = ["HARRIS","MSER"]
desc = ["SIFT"]

for a in det:
	for d in desc:
		teste = open("../testes/testes.txt")
		for t in teste:
			if len(t) > 1:
				base = open("../testes/base.txt")
				for b in base:
					if len(b) > 1:
						txt = str("./comparacao/compara {} {} {} {} >> resultado.txt".format(t,b,a,d))
						print txt
						popen(txt)

#!/bin/python

arquivoSaida = open("saida.txt",'w')

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
						print "./comparacao/compara "+t+" "+b+" "+a+" "+d



#for b in teste:
#	if len(b) > 1:
#		print b


#!/bin/python

arquivo = open("resultados.txt")
arquivoSaida = open("saida.txt",'w')

for arq in arquivo:
	#print arq
	ponto = arq.split(".")
	#	print ponto	
	teste=arq.split("\t")
	print teste
	if len(teste) > 1:
		detector  = teste[2]
		descritor = teste[3]
		pontoA 	  = teste[4]
		pontoB 	  = teste[5]
		match  	  = teste[6] 


	if len(ponto) > 1:
		final = ponto[0].split("/")
		recorte = arq.split("/")
		arquivoSaida.write(final[-1] + ".png " + recorte[-1])

arquivoSaida.close()


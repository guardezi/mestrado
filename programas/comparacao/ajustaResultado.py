#!/bin/python

def ordena( arquivo ):
	dic = []
	arquivo = arquivo.split("\n")
	for linha in arquivo:
		separado = linha.split("\t")
		separado[2] = int(separado[2])
		separado[1] = separado[1].split("-")[0]
		dic.append(separado)

	dic.sort(key=lambda x: x[2])
	# print dic[len(dic)-1]
	# print dic[len(dic)-2]
	# for d in dic:
	# 	print d
	return dic	

if __name__ == '__main__':
	arquivo = open("resultado.txt")
	arquivoSaida = open("resultadoAjustado.txt",'w')

	harris = []
	mser =[]

	ultimo="vazio"
	cont=0
	txt=""
	print txt

	for arq in arquivo:
		ponto = arq.split(".")
		teste=arq.split("\t")
		if len(teste) > 1:
			imgA      = teste[0].split("/")
			imgA	  = imgA[len(imgA)-1]
			imgA      = imgA.split(".")[0]
			
			imgB      = teste[1].split("/")
			imgB	  = imgB[len(imgB)-1]
			imgB      = imgB.split(".")[0]      
			detector  = teste[2]
			descritor = teste[3]
			pontoA 	  = teste[4]
			pontoB 	  = teste[5]
			match  	  = teste[6] 
			
			if imgA != ultimo:
				# print cont
				if cont != 0:
					if detector == "HARRIS":
						harris.append(ordena(txt))
					if detector == "MSER":
						mser.append(ordena(txt))
					
				ultimo = imgA
				cont +=1
				txt=imgA+"\t"+imgB+"\t"+match
			else:
				txt = txt + "\n" + imgA+"\t"+imgB+"\t"+match
	c=int(0)
	e=int(0)
	for i in xrange(0,len(harris)):
		a = harris[i][len(harris[i])-1]
		if a[0].split("-")[0] == a[1]:
			# print a[0].split("-")[0]+" "+a[1]+" "+str(a[2])
			c+=1
		else :
			e+=1
	print "HARRIS\ntotal ",(c+e)
	print "Corretos {} {}%".format(c,(100*c/(c+e)))
	print "errados {} {}%".format(e,(100*e/(c+e)))

	c=int(0)
	e=int(0)
	for i in xrange(0,len(mser)):
		a = mser[i][len(mser[i])-1]
		if a[0].split("-")[0] == a[1]:
			# print a[0].split("-")[0]+" "+a[1]+" "+str(a[2])
			c+=1
		else :
			e+=1
	print "\nMSER\ntotal ",(c+e)
	print "Corretos {} {}%".format(c,(100*c/(c+e)))
	print "errados {} {}%".format(e,(100*e/(c+e)))

	arquivoSaida.close()



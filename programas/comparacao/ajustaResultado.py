#!/bin/python
import sys

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
	arg=str(sys.argv[1])
	arquivo = open(arg)
	arquivoSaida = open("resultadoAjustado.txt",'w')

	harris = []
	mser =[]
	dic = {}
	ultimo="vazio"
	cont=0
	txt=""
	# print txt

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
					if detector not in dic.keys():
						dic[detector]=[]
						dic[detector].append([0,0])
					dic[detector].append(ordena(txt))
					
				ultimo = imgA
				cont +=1
				txt=imgA+"\t"+imgB+"\t"+match
			else:
				txt = txt + "\n" + imgA+"\t"+imgB+"\t"+match

	for d in dic.keys():
		v=dic[d]
		for i in xrange(1,len(v)-1):
			t=v[i]
			x= t[len(t)-1]
			x[0]=x[0].split("-")[0]
			# print "{} {} {} ".format(x[0],x[1],x[2])
			if x[0] == x[1]:
				(v[0])[0]+=1
			else:
				(v[0])[1]+=1			
		# print "\n"
		c = (v[0])[0]
		e = (v[0])[1]
		print "{} acerto {} %".format(d, (c*100)/(c+e) )
		print "[c, e]"
		print "{}_{}".format(v[0],(c+e))

		
	arquivoSaida.close()



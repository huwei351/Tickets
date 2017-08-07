#-*- coding: UTF-8 -*- 

import numpy as np  
import matplotlib.pyplot as plt  
import os

TEST_DIR = "./accuracy_test"
TEST_FILE_HEAD = "Accuracy_Test_"

def figureFiles():
	pathDir =  os.listdir(TEST_DIR)
	for allDir in pathDir:
		child = os.path.join('%s/%s' % (TEST_DIR, allDir))
		print child.decode('gbk') # .decode('gbk')是解决中文显示乱码问题
		labelname = child.strip().split(TEST_FILE_HEAD)[1]
		file = open(child, 'r')
		linesList = file.readlines()
		linesList = [line.strip().split('\n') for line in linesList]
		file.close()    
		#print(linesList)
		#years = [string.atof(x[0]) for x in linesList]
		y = [x[0] for x in linesList]
		plt.plot(y, label="$"+labelname+"$")
	plt.legend()
	plt.show()

#figureFiles()

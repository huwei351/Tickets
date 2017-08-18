#-*- coding: UTF-8 -*- 

import time
import random
import string
import numpy as np  
import matplotlib.pyplot as plt  
from matplotlib.ticker import MultipleLocator, FormatStrFormatter 
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

def figureFile(index):
	filename = TEST_DIR + "/" + TEST_FILE_HEAD + bytes(index) + ".txt"
	labelname = filename.strip().split(TEST_FILE_HEAD)[1]
	print("filename = " + filename + ", labelname = " + labelname)
	file = open(filename, 'r')
	linesList = file.readlines()
	linesList = [line.strip().split('\n') for line in linesList]
	file.close()    
	y = [x[0] for x in linesList]
	plt.plot(y, label="$"+labelname+"$")
	plt.legend()
	plt.show()

def analyseFiles():
	list_one = []
	list_zero = []
	list_dst = []
	index = []
	pathDir =  os.listdir(TEST_DIR)
	for allDir in pathDir:
		filename = os.path.join('%s/%s' % (TEST_DIR, allDir))
		#print child.decode('gbk') # .decode('gbk')是解决中文显示乱码问题
		fileindex = string.atoi((filename.strip().split(TEST_FILE_HEAD)[1]).strip().split(".")[0])
		print("filename = " + filename + ", fileindex = " + bytes(fileindex))
		file = open(filename, 'r')
		linesList = file.readlines()
		linesList = [line.strip().split('/') for line in linesList]
		file.close()    
		arr = [string.atoi(x[0]) for x in linesList]
		arr_len = len(arr);
		one_count = arr.count(1)
		zero_count = arr.count(0)
		dst_count = 0
		for i in arr:
			if i <= 5 and i > 0:
				dst_count += 1
		index += [fileindex]
		list_one += [one_count]
		list_zero += [zero_count]
		list_dst += [dst_count]
		print ("one_count = " + bytes(one_count) + "/" + bytes(arr_len) + "(" + bytes(float(one_count)/arr_len) + ")")
		print ("zero_count = " + bytes(zero_count) + "/" + bytes(arr_len) + "(" + bytes(float(zero_count)/arr_len) + ")")
		print ("dst_count = " + bytes(dst_count) + "/" + bytes(arr_len) + "(" + bytes(float(dst_count)/arr_len) + ")")
		print "极差为：{0}".format(Math.range(arr));  
		print "平均数为：{0:.2f}".format(Math.avg(arr));  
		print "中位数为：{0}".format(Math.median(arr));  
		print "众数为：{0}".format(Math.mode(arr));  
		print "方差为：{0:.2f}".format(Math.variance(arr));  
		#print "方差为：{0:.2f}".format(Math.variance2(arr)); 
	print index
	print list_one
	print list_zero
	print list_dst
	plt.figure()
	plt.scatter(index, list_one, s=40, c="red", label="$listone$")
	plt.scatter(index, list_zero, s=40, c="yellow", label="$listzero$")
	plt.scatter(index, list_dst, s=40, c="blue", label="$listdst$")
	plt.legend()
	plt.savefig("myfig.jpg")
	plt.show()

def analyseFile(index):
	filename = TEST_DIR + "/" + TEST_FILE_HEAD + bytes(index) + ".txt"
	labelname = filename.strip().split(TEST_FILE_HEAD)[1]
	print("filename = " + filename + ", labelname = " + labelname)
	file = open(filename, 'r')
	linesList = file.readlines()
	linesList = [line.strip().split('\n') for line in linesList]
	file.close()    
	arr = [string.atof(x[0]) for x in linesList]
	one_count = arr.count(1.0)
	zero_count = arr.count(0)
	dst_count = 0
	for i in arr:
		if i <= 0.500:
			dst_count += 1
	print ("one_count = " + bytes(one_count) + ", zero_count = " + bytes(zero_count) + ", dst_count = " + bytes(dst_count) + "/" + bytes(len(arr)) )
	print "极差为：{0}".format(Math.range(arr));  
	print "平均数为：{0:.2f}".format(Math.avg(arr));  
	print "中位数为：{0}".format(Math.median(arr));  
	print "众数为：{0}".format(Math.mode(arr));  
	print "方差为：{0:.2f}".format(Math.variance(arr));  
	#print "方差为：{0:.2f}".format(Math.variance2(arr)); 
	plt.plot(arr, label="$"+labelname+"$")
	plt.legend()
	plt.show() 

def barFiles():
	pathDir =  os.listdir(TEST_DIR)
	for allDir in pathDir:
		pro = []
		filename = os.path.join('%s/%s' % (TEST_DIR, allDir))
		fileindex = string.atoi((filename.strip().split(TEST_FILE_HEAD)[1]).strip().split(".")[0])
		print("filename = " + filename + ", fileindex = " + bytes(fileindex))
		file = open(filename, 'r')
		linesList = file.readlines()
		linesList = [line.strip().split('/') for line in linesList]
		file.close()    
		arr0 = [string.atoi(x[0]) for x in linesList]
		arr1 = [string.atoi(x[1]) for x in linesList]
		for i in range(max(arr1)+1):
			pro += [arr0.count(i)]
			print ("pro : " + bytes(i) + ", count = " + bytes(arr0.count(i)) + "/" + bytes(len(arr0)) + "(" + bytes(float(arr0.count(i))/len(arr0)) + ")")
		plt.figure()
		plt.bar(range(max(arr1)+1), pro)
		plt.xticks(np.arange(len(pro))+0.5, range(max(arr1)+1))
		plt.savefig("barfig_" + bytes(fileindex) + ".jpg")

def barFile(index):
	pro = []
	filename = TEST_DIR + "/" + TEST_FILE_HEAD + bytes(index) + ".txt"
	#labelname = filename.strip().split(TEST_FILE_HEAD)[1]
	print("barFile : filename = " + filename)
	file = open(filename, 'r')
	linesList = file.readlines()
	linesList = [line.strip().split('/') for line in linesList]
	file.close()    
	arr0 = [string.atoi(x[0]) for x in linesList]
	arr1 = [string.atoi(x[1]) for x in linesList]
	for i in range(max(arr1)+1):
		pro += [arr0.count(i)]
		print ("pro : " + bytes(i) + ", count = " + bytes(arr0.count(i)) + "/" + bytes(len(arr0)) + "(" + bytes(float(arr0.count(i))/len(arr0)) + ")")
	plt.bar(range(max(arr1)+1), pro)
	plt.xticks(np.arange(len(pro))+0.5, range(max(arr1)+1))
	plt.savefig("barfig_" + bytes(index) + ".jpg")
	plt.show() 

def analyseResultFile(index):
	pro_0 = []
	pro_2 = [0, 0, 0, 0, 0]
	arr0_n = []
	arr2_n = []
	filename = TEST_DIR + "/" + TEST_FILE_HEAD + bytes(index) + ".txt"
	#labelname = filename.strip().split(TEST_FILE_HEAD)[1]
	print("barFile : filename = " + filename)
	file = open(filename, 'r')
	linesList = file.readlines()
	linesList = [line.strip().split('/') for line in linesList]
	file.close()
	s = range(len(linesList))    
	arr0 = [string.atoi(x[0]) for x in linesList]
	arr1 = [string.atoi(x[1]) for x in linesList]
	arr2 = [string.atof(x[2]) for x in linesList]
	for a in arr0:
		if a != 0:
			arr0_n += [a]
	for arr in arr2:
		if arr != 0:
			arr2_n += [arr]
	arr0_c = [i/5000 for i in arr0_n]
	for r in range(max(arr0_c)+1):
		pro_0 += [arr0_c.count(r)]
	for r2 in arr2_n:
		if r2 <= 0.2:
			pro_2[0] += 1
		if r2 > 0.2 and r2 <= 0.4:
			pro_2[1] += 1
		if r2 > 0.4 and r2 <= 0.6:
			pro_2[2] += 1
		if r2 > 0.6 and r2 <= 0.8:
			pro_2[3] += 1
		if r2 > 0.8:
			pro_2[4] += 1
	for i in range(len(pro_0)):
		print("pro_0: " + bytes(i*5000) + "-" + bytes((i+1)*5000-1) + " : " + bytes(pro_0[i]) + "/" + bytes(len(arr0_c)))
	for j in range(len(pro_2)):
		print("pro_2: " + bytes(j*0.2) + " < pro_2[] <= " + bytes((j+1)*0.2) + " : " + bytes(pro_2[j]) + "/" + bytes(len(arr2_n)))
	print("arr0: 零个数为=" + bytes(arr0.count(0)) + ", 非零最小值为=" + bytes(min(arr0_n)) + ", 最大值为=" + bytes(max(arr0_n)) + 
	 ", 非零平均数为=" + bytes(Math.avg(arr0_n)) + ", 非零中位数为=" + bytes(Math.median(arr0_n)) + ", 非零方差为=" + bytes(Math.variance(arr0_n)))
	print("arr1: 最小值为=" + bytes(min(arr1)) + ", 最大值为=" + bytes(max(arr1)) + 
	 ", 平均数为=" + bytes(Math.avg(arr1)) + ", 中位数为=" + bytes(Math.median(arr1)) + ", 方差为=" + bytes(Math.variance(arr1)))
	print("arr2: 零个数为=" + bytes(arr2.count(0)) + ", 非零最小值为=" + bytes(min(arr2_n)) + ", 最大值为=" + bytes(max(arr2_n)) + 
	 ", 非零平均数为=" + bytes(Math.avg(arr2_n)) + ", 非零中位数为=" + bytes(Math.median(arr2_n)) + ", 非零方差为=" + bytes(Math.variance(arr2_n)))
	plt.figure(1)
	plt.subplot(311)
	plt.scatter(s, arr0, s=20, c="red", label="$count$")
	plt.subplot(312)
	plt.scatter(s, arr1, s=20, c="yellow", label="$total$")
	plt.subplot(313)
	plt.scatter(s, arr2, s=20, c="blue", label="$accuracy$")
	#plt.legend()
	plt.savefig("scatterfig_" + bytes(index) + ".jpg")
	plt.figure(2)
	plt.subplot(211)
	plt.bar(range(max(arr0_c)+1), pro_0)
	plt.xticks(np.arange(len(pro_0))+0.5, range(max(arr0_c)+1))
	plt.subplot(212)
	plt.bar(range(5), pro_2)
	plt.xticks(np.arange(len(pro_2))+0.5, range(5))
	plt.savefig("barfig_" + bytes(index) + ".jpg")
	plt.show() 

def globalAnalyseFiles():
	pathDir =  os.listdir(TEST_DIR)
	for allDir in pathDir:
		pro_0 = []
		pro_1 = []
		pro_2 = []
		pro_3 = [0, 0]
		pro_4 = [0, 0]
		pro_5 = [0, 0]
		pro_6 = []
		filename = os.path.join('%s/%s' % (TEST_DIR, allDir))
		fileindex = string.atoi((filename.strip().split(TEST_FILE_HEAD)[1]).strip().split(".")[0])
		print("filename = " + filename + ", fileindex = " + bytes(fileindex))
		if fileindex > 20:
			file = open(filename, 'r')
			linesList = file.readlines()
			linesList = [line.strip().split('/') for line in linesList]
			file.close()    
			arr0 = [string.atoi(x[0]) for x in linesList]
			arr1 = [string.atoi(x[1]) for x in linesList]
			arr2 = [string.atoi(x[2]) for x in linesList]
			arr3 = [string.atoi(x[3]) for x in linesList]
			arr4 = [string.atoi(x[4]) for x in linesList]
			arr5 = [string.atoi(x[5]) for x in linesList]
			arr6 = [string.atoi(x[6]) for x in linesList]
			for i in range(1, max(arr0)+1):
				pro_0 += [arr0.count(i)]
				print ("pro_0 : " + bytes(i) + ", count = " + bytes(arr0.count(i)) + "/" + bytes(len(arr0)) + "(" + bytes(float(arr0.count(i))/len(arr0)) + ")")
			for i in range(max(arr1)+1):
				pro_1 += [arr1.count(i)]
				print ("pro_1 : " + bytes(i) + ", count = " + bytes(arr1.count(i)) + "/" + bytes(len(arr1)) + "(" + bytes(float(arr1.count(i))/len(arr1)) + ")")
			for i in range(max(arr2)+1):
				pro_2 += [arr2.count(i)]
				print ("pro_2 : " + bytes(i) + ", count = " + bytes(arr2.count(i)) + "/" + bytes(len(arr2)) + "(" + bytes(float(arr2.count(i))/len(arr2)) + ")")
			pro_3[0] = arr3.count(0)
			pro_3[1] = arr3.count(1)
			pro_4[0] = arr4.count(0)
			pro_4[1] = arr4.count(1)
			pro_5[0] = arr5.count(0)
			pro_5[1] = arr5.count(1)
			print ("pro_3 :  (ODD) zero_count = " + bytes(arr3.count(0)) + "/" + bytes(len(arr3)) + "(" + bytes(float(arr3.count(0))/len(arr3)) + ")")
			print ("pro_3 :  (EVEN) one_count = " + bytes(arr3.count(1)) + "/" + bytes(len(arr3)) + "(" + bytes(float(arr3.count(1))/len(arr3)) + ")")
			print ("pro_4 :  (BIG) zero_count = " + bytes(arr4.count(0)) + "/" + bytes(len(arr4)) + "(" + bytes(float(arr4.count(0))/len(arr4)) + ")")
			print ("pro_4 :  (SMALL) one_count = " + bytes(arr4.count(1)) + "/" + bytes(len(arr4)) + "(" + bytes(float(arr4.count(1))/len(arr4)) + ")")
			print ("pro_5 :  (PRIME) zero_count = " + bytes(arr5.count(0)) + "/" + bytes(len(arr5)) + "(" + bytes(float(arr5.count(0))/len(arr5)) + ")")
			print ("pro_5 :  (COMPOSITE) one_count = " + bytes(arr5.count(1)) + "/" + bytes(len(arr5)) + "(" + bytes(float(arr5.count(1))/len(arr5)) + ")")
			for i in range(5):
				pro_6 += [arr6.count(i)]
				print ("pro_6 : " + bytes(i) + ", count = " + bytes(arr6.count(i)) + "/" + bytes(len(arr6)) + "(" + bytes(float(arr6.count(i))/len(arr6)) + ")")
			plt.figure()
			plt.subplot(421)
			plt.bar(range(1, max(arr0)+1), pro_0)
			plt.xticks(np.arange(len(pro_0))+0.5, range(1, max(arr0)))
			plt.subplot(422)
			plt.bar(range(max(arr1)+1), pro_1)
			plt.xticks(np.arange(len(pro_1))+0.5, range(max(arr1)))
			plt.subplot(423)
			plt.bar(range(max(arr2)+1), pro_2)
			plt.xticks(np.arange(len(pro_2))+0.5, range(max(arr2)))
			plt.subplot(424)
			plt.bar(range(2), pro_3)
			plt.xticks(np.arange(2)+0.5, range(2))
			plt.subplot(425)
			plt.bar(range(2), pro_4)
			plt.xticks(np.arange(2)+0.5, range(2))
			plt.subplot(426)
			plt.bar(range(2), pro_5)
			plt.xticks(np.arange(2)+0.5, range(2))
			plt.subplot(427)
			plt.bar(range(5), pro_6)
			plt.xticks(np.arange(len(pro_6))+0.5, range(5))
			plt.savefig("barfig_" + bytes(fileindex) + ".jpg")
			plt.show()

def everyYearResultFiles():
	pathDir =  os.listdir(TEST_DIR)
	for allDir in pathDir:
		filename = os.path.join('%s/%s' % (TEST_DIR, allDir))
		fileindex = string.atoi((filename.strip().split(TEST_FILE_HEAD)[1]).strip().split(".")[0])
		print("filename = " + filename + ", fileindex = " + bytes(fileindex))
		if fileindex > 300:
			file = open(filename, 'r')
			linesList = file.readlines()
			linesList = [line.strip().split('/') for line in linesList]
			file.close()    
			arr0 = [x[0] for x in linesList]
			arr1 = [x[1].strip().split(',') for x in linesList]
			arr1_0 = [string.atoi(x[0]) for x in arr1]
			arr1_1 = [string.atoi(x[1]) for x in arr1]
			arr1_2 = [string.atoi(x[2]) for x in arr1]
			arr1_3 = [string.atoi(x[3]) for x in arr1]
			arr1_4 = [string.atoi(x[4]) for x in arr1]
			arr1_5 = [string.atoi(x[5]) for x in arr1]
			arr1_6 = [string.atoi(x[6]) for x in arr1]
			arr2 = [x[2].strip().split(',') for x in linesList]
			arr2_0 = [string.atoi(x[0]) for x in arr2]
			arr2_1 = [string.atoi(x[1]) for x in arr2]
			arr2_2 = [string.atoi(x[2]) for x in arr2]
			arr2_3 = [string.atoi(x[3]) for x in arr2]
			arr2_4 = [string.atoi(x[4]) for x in arr2]
			arr2_5 = [string.atoi(x[5]) for x in arr2]
			arr2_6 = [string.atoi(x[6]) for x in arr2]
			arr3 = [x[3].strip().split(',') for x in linesList]
			arr3_0 = [string.atoi(x[0]) for x in arr3]
			arr3_1 = [string.atoi(x[1]) for x in arr3]
			arr3_2 = [string.atoi(x[2]) for x in arr3]
			arr3_3 = [string.atoi(x[3]) for x in arr3]
			arr3_4 = [string.atoi(x[4]) for x in arr3]
			arr3_5 = [string.atoi(x[5]) for x in arr3]
			arr3_6 = [string.atoi(x[6]) for x in arr3]
			arr4 = [x[4].strip().split(',') for x in linesList]
			arr4_0 = [string.atoi(x[0]) for x in arr4]
			arr4_1 = [string.atoi(x[1]) for x in arr4]
			arr4_2 = [string.atoi(x[2]) for x in arr4]
			arr4_3 = [string.atoi(x[3]) for x in arr4]
			arr4_4 = [string.atoi(x[4]) for x in arr4]
			arr4_5 = [string.atoi(x[5]) for x in arr4]
			arr4_6 = [string.atoi(x[6]) for x in arr4]
			arr5 = [x[5].strip().split(',') for x in linesList]
			arr5_0 = [string.atoi(x[0]) for x in arr5]
			arr5_1 = [string.atoi(x[1]) for x in arr5]
			arr5_2 = [string.atoi(x[2]) for x in arr5]
			arr5_3 = [string.atoi(x[3]) for x in arr5]
			arr5_4 = [string.atoi(x[4]) for x in arr5]
			arr5_5 = [string.atoi(x[5]) for x in arr5]
			arr5_6 = [string.atoi(x[6]) for x in arr5]
			arr6 = [x[6].strip().split(',') for x in linesList]
			arr6_0 = [string.atoi(x[0]) for x in arr6]
			arr6_1 = [string.atoi(x[1]) for x in arr6]
			arr6_2 = [string.atoi(x[2]) for x in arr6]
			arr6_3 = [string.atoi(x[3]) for x in arr6]
			arr6_4 = [string.atoi(x[4]) for x in arr6]
			arr6_5 = [string.atoi(x[5]) for x in arr6]
			arr6_6 = [string.atoi(x[6]) for x in arr6]
			arr7 = [x[7].strip().split(',') for x in linesList]
			arr7_0 = [string.atoi(x[0]) for x in arr7]
			arr7_1 = [string.atoi(x[1]) for x in arr7]
			arr7_2 = [string.atoi(x[2]) for x in arr7]
			arr7_3 = [string.atoi(x[3]) for x in arr7]
			arr7_4 = [string.atoi(x[4]) for x in arr7]
			arr7_5 = [string.atoi(x[5]) for x in arr7]
			arr7_6 = [string.atoi(x[6]) for x in arr7]
			arr8 = [x[8].strip().split(',') for x in linesList]
			arr8_0 = [string.atoi(x[0]) for x in arr8]
			arr8_1 = [string.atoi(x[1]) for x in arr8]
			arr8_2 = [string.atoi(x[2]) for x in arr8]
			arr8_3 = [string.atoi(x[3]) for x in arr8]
			arr8_4 = [string.atoi(x[4]) for x in arr8]
			arr8_5 = [string.atoi(x[5]) for x in arr8]
			arr = arr1_0 + arr2_0 + arr3_0 + arr4_0 + arr5_0 + arr6_0
			for i in range(1,34):
				print ("redNum : " + bytes(i) + ", count = " + bytes(arr.count(i)) + "/" + bytes(len(arr)) + "(" + bytes(float(arr.count(i))/len(arr)) + ")")
			for i in range(1, 17):
				print ("blueNum : " + bytes(i) + ", count = " + bytes(arr7_0.count(i)) + "/" + bytes(len(arr7_0)) + "(" + bytes(float(arr7_0.count(i))/len(arr7_0)) + ")")
			for i in range(min(arr1_0), max(arr1_0)+1):
				print ("Red1 Num : " + bytes(i) + ", count = " + bytes(arr1_0.count(i)) + "/" + bytes(len(arr1_0)) + "(" + bytes(float(arr1_0.count(i))/len(arr1_0)) + ")")
			for i in range(10):
				print ("Red1 Unit : " + bytes(i) + ", count = " + bytes(arr1_1.count(i)) + "/" + bytes(len(arr1_1)) + "(" + bytes(float(arr1_1.count(i))/len(arr1_1)) + ")")
			for i in range(4):
				print ("Red1 Decade : " + bytes(i) + ", count = " + bytes(arr1_2.count(i)) + "/" + bytes(len(arr1_2)) + "(" + bytes(float(arr1_2.count(i))/len(arr1_2)) + ")")
			print ("Red1 Jiou : (ODD) zero_count = " + bytes(arr1_3.count(0)) + "/" + bytes(len(arr1_3)) + "(" + bytes(float(arr1_3.count(0))/len(arr1_3)) + ")")
			print ("Red1 Jiou : (EVEN) one_count = " + bytes(arr1_3.count(1)) + "/" + bytes(len(arr1_3)) + "(" + bytes(float(arr1_3.count(1))/len(arr1_3)) + ")")
			print ("Red1 Daxiao : (BIG) zero_count = " + bytes(arr1_4.count(0)) + "/" + bytes(len(arr1_4)) + "(" + bytes(float(arr1_4.count(0))/len(arr1_4)) + ")")
			print ("Red1 Daxiao : (SMALL) one_count = " + bytes(arr1_4.count(1)) + "/" + bytes(len(arr1_4)) + "(" + bytes(float(arr1_4.count(1))/len(arr1_4)) + ")")
			print ("Red1 Zhihe : (PRIME) zero_count = " + bytes(arr1_5.count(0)) + "/" + bytes(len(arr1_5)) + "(" + bytes(float(arr1_5.count(0))/len(arr1_5)) + ")")
			print ("Red1 Zhihe : (COMPOSITE) one_count = " + bytes(arr1_5.count(1)) + "/" + bytes(len(arr1_5)) + "(" + bytes(float(arr1_5.count(1))/len(arr1_5)) + ")")
			for i in range(5):
				print ("Red1 Wuxing : " + bytes(i) + ", count = " + bytes(arr1_6.count(i)) + "/" + bytes(len(arr1_6)) + "(" + bytes(float(arr1_6.count(i))/len(arr1_6)) + ")")
			print("Red1 Num Avg = " + bytes(Math.avg(arr1_0)))
			for i in range(min(arr2_0), max(arr2_0)+1):
				print ("Red2 Num : " + bytes(i) + ", count = " + bytes(arr2_0.count(i)) + "/" + bytes(len(arr2_0)) + "(" + bytes(float(arr2_0.count(i))/len(arr2_0)) + ")")
			for i in range(10):
				print ("Red2 Unit : " + bytes(i) + ", count = " + bytes(arr2_1.count(i)) + "/" + bytes(len(arr2_1)) + "(" + bytes(float(arr2_1.count(i))/len(arr2_1)) + ")")
			for i in range(4):
				print ("Red2 Decade : " + bytes(i) + ", count = " + bytes(arr2_2.count(i)) + "/" + bytes(len(arr2_2)) + "(" + bytes(float(arr2_2.count(i))/len(arr2_2)) + ")")
			print ("Red2 Jiou : (ODD) zero_count = " + bytes(arr2_3.count(0)) + "/" + bytes(len(arr2_3)) + "(" + bytes(float(arr2_3.count(0))/len(arr2_3)) + ")")
			print ("Red2 Jiou : (EVEN) one_count = " + bytes(arr2_3.count(1)) + "/" + bytes(len(arr2_3)) + "(" + bytes(float(arr2_3.count(1))/len(arr2_3)) + ")")
			print ("Red2 Daxiao : (BIG) zero_count = " + bytes(arr2_4.count(0)) + "/" + bytes(len(arr2_4)) + "(" + bytes(float(arr2_4.count(0))/len(arr2_4)) + ")")
			print ("Red2 Daxiao : (SMALL) one_count = " + bytes(arr2_4.count(1)) + "/" + bytes(len(arr2_4)) + "(" + bytes(float(arr2_4.count(1))/len(arr2_4)) + ")")
			print ("Red2 Zhihe : (PRIME) zero_count = " + bytes(arr2_5.count(0)) + "/" + bytes(len(arr2_5)) + "(" + bytes(float(arr2_5.count(0))/len(arr2_5)) + ")")
			print ("Red2 Zhihe : (COMPOSITE) one_count = " + bytes(arr2_5.count(1)) + "/" + bytes(len(arr2_5)) + "(" + bytes(float(arr2_5.count(1))/len(arr2_5)) + ")")
			for i in range(5):
				print ("Red2 Wuxing : " + bytes(i) + ", count = " + bytes(arr2_6.count(i)) + "/" + bytes(len(arr2_6)) + "(" + bytes(float(arr2_6.count(i))/len(arr2_6)) + ")")
			print("Red2 Num Avg  = " + bytes(Math.avg(arr2_0)))
			for i in range(min(arr3_0), max(arr3_0)+1):
				print ("Red3 Num : " + bytes(i) + ", count = " + bytes(arr3_0.count(i)) + "/" + bytes(len(arr3_0)) + "(" + bytes(float(arr3_0.count(i))/len(arr3_0)) + ")")
			for i in range(10):
				print ("Red3 Unit : " + bytes(i) + ", count = " + bytes(arr3_1.count(i)) + "/" + bytes(len(arr3_1)) + "(" + bytes(float(arr3_1.count(i))/len(arr3_1)) + ")")
			for i in range(4):
				print ("Red3 Decade : " + bytes(i) + ", count = " + bytes(arr3_2.count(i)) + "/" + bytes(len(arr3_2)) + "(" + bytes(float(arr3_2.count(i))/len(arr3_2)) + ")")
			print ("Red3 Jiou : (ODD) zero_count = " + bytes(arr3_3.count(0)) + "/" + bytes(len(arr3_3)) + "(" + bytes(float(arr3_3.count(0))/len(arr3_3)) + ")")
			print ("Red3 Jiou : (EVEN) one_count = " + bytes(arr3_3.count(1)) + "/" + bytes(len(arr3_3)) + "(" + bytes(float(arr3_3.count(1))/len(arr3_3)) + ")")
			print ("Red3 Daxiao : (BIG) zero_count = " + bytes(arr3_4.count(0)) + "/" + bytes(len(arr3_4)) + "(" + bytes(float(arr3_4.count(0))/len(arr3_4)) + ")")
			print ("Red3 Daxiao : (SMALL) one_count = " + bytes(arr3_4.count(1)) + "/" + bytes(len(arr3_4)) + "(" + bytes(float(arr3_4.count(1))/len(arr3_4)) + ")")
			print ("Red3 Zhihe : (PRIME) zero_count = " + bytes(arr3_5.count(0)) + "/" + bytes(len(arr3_5)) + "(" + bytes(float(arr3_5.count(0))/len(arr3_5)) + ")")
			print ("Red3 Zhihe : (COMPOSITE) one_count = " + bytes(arr3_5.count(1)) + "/" + bytes(len(arr3_5)) + "(" + bytes(float(arr3_5.count(1))/len(arr3_5)) + ")")
			for i in range(5):
				print ("Red3 Wuxing : " + bytes(i) + ", count = " + bytes(arr3_6.count(i)) + "/" + bytes(len(arr3_6)) + "(" + bytes(float(arr3_6.count(i))/len(arr3_6)) + ")")
			print("Red3 Num Avg = " + bytes(Math.avg(arr3_0)))
			for i in range(min(arr4_0), max(arr4_0)+1):
				print ("Red4 Num : " + bytes(i) + ", count = " + bytes(arr4_0.count(i)) + "/" + bytes(len(arr4_0)) + "(" + bytes(float(arr4_0.count(i))/len(arr4_0)) + ")")
			for i in range(10):
				print ("Red4 Unit : " + bytes(i) + ", count = " + bytes(arr4_1.count(i)) + "/" + bytes(len(arr4_1)) + "(" + bytes(float(arr4_1.count(i))/len(arr4_1)) + ")")
			for i in range(4):
				print ("Red4 Decade : " + bytes(i) + ", count = " + bytes(arr4_2.count(i)) + "/" + bytes(len(arr4_2)) + "(" + bytes(float(arr4_2.count(i))/len(arr4_2)) + ")")
			print ("Red4 Jiou : (ODD) zero_count = " + bytes(arr4_3.count(0)) + "/" + bytes(len(arr4_3)) + "(" + bytes(float(arr4_3.count(0))/len(arr4_3)) + ")")
			print ("Red4 Jiou : (EVEN) one_count = " + bytes(arr4_3.count(1)) + "/" + bytes(len(arr4_3)) + "(" + bytes(float(arr4_3.count(1))/len(arr4_3)) + ")")
			print ("Red4 Daxiao : (BIG) zero_count = " + bytes(arr4_4.count(0)) + "/" + bytes(len(arr4_4)) + "(" + bytes(float(arr4_4.count(0))/len(arr4_4)) + ")")
			print ("Red4 Daxiao : (SMALL) one_count = " + bytes(arr4_4.count(1)) + "/" + bytes(len(arr4_4)) + "(" + bytes(float(arr4_4.count(1))/len(arr4_4)) + ")")
			print ("Red4 Zhihe : (PRIME) zero_count = " + bytes(arr4_5.count(0)) + "/" + bytes(len(arr4_5)) + "(" + bytes(float(arr4_5.count(0))/len(arr4_5)) + ")")
			print ("Red4 Zhihe : (COMPOSITE) one_count = " + bytes(arr4_5.count(1)) + "/" + bytes(len(arr4_5)) + "(" + bytes(float(arr4_5.count(1))/len(arr4_5)) + ")")
			for i in range(5):
				print ("Red4 Wuxing : " + bytes(i) + ", count = " + bytes(arr4_6.count(i)) + "/" + bytes(len(arr4_6)) + "(" + bytes(float(arr4_6.count(i))/len(arr4_6)) + ")")
			print("Red4 Num Avg  = " + bytes(Math.avg(arr4_0)))
			for i in range(min(arr5_0), max(arr5_0)+1):
				print ("Red5 Num : " + bytes(i) + ", count = " + bytes(arr5_0.count(i)) + "/" + bytes(len(arr5_0)) + "(" + bytes(float(arr5_0.count(i))/len(arr5_0)) + ")")
			for i in range(10):
				print ("Red5 Unit : " + bytes(i) + ", count = " + bytes(arr5_1.count(i)) + "/" + bytes(len(arr5_1)) + "(" + bytes(float(arr5_1.count(i))/len(arr5_1)) + ")")
			for i in range(4):
				print ("Red5 Decade : " + bytes(i) + ", count = " + bytes(arr5_2.count(i)) + "/" + bytes(len(arr5_2)) + "(" + bytes(float(arr5_2.count(i))/len(arr5_2)) + ")")
			print ("Red5 Jiou : (ODD) zero_count = " + bytes(arr5_3.count(0)) + "/" + bytes(len(arr5_3)) + "(" + bytes(float(arr5_3.count(0))/len(arr5_3)) + ")")
			print ("Red5 Jiou : (EVEN) one_count = " + bytes(arr5_3.count(1)) + "/" + bytes(len(arr5_3)) + "(" + bytes(float(arr5_3.count(1))/len(arr5_3)) + ")")
			print ("Red5 Daxiao : (BIG) zero_count = " + bytes(arr5_4.count(0)) + "/" + bytes(len(arr5_4)) + "(" + bytes(float(arr5_4.count(0))/len(arr5_4)) + ")")
			print ("Red5 Daxiao : (SMALL) one_count = " + bytes(arr5_4.count(1)) + "/" + bytes(len(arr5_4)) + "(" + bytes(float(arr5_4.count(1))/len(arr5_4)) + ")")
			print ("Red5 Zhihe : (PRIME) zero_count = " + bytes(arr5_5.count(0)) + "/" + bytes(len(arr5_5)) + "(" + bytes(float(arr5_5.count(0))/len(arr5_5)) + ")")
			print ("Red5 Zhihe : (COMPOSITE) one_count = " + bytes(arr5_5.count(1)) + "/" + bytes(len(arr5_5)) + "(" + bytes(float(arr5_5.count(1))/len(arr5_5)) + ")")
			for i in range(5):
				print ("Red5 Wuxing : " + bytes(i) + ", count = " + bytes(arr5_6.count(i)) + "/" + bytes(len(arr5_6)) + "(" + bytes(float(arr5_6.count(i))/len(arr5_6)) + ")")
			print("Red5 Num Avg  = " + bytes(Math.avg(arr5_0)))
			for i in range(min(arr6_0), max(arr6_0)+1):
				print ("Red6 Num : " + bytes(i) + ", count = " + bytes(arr6_0.count(i)) + "/" + bytes(len(arr6_0)) + "(" + bytes(float(arr6_0.count(i))/len(arr6_0)) + ")")
			for i in range(10):
				print ("Red6 Unit : " + bytes(i) + ", count = " + bytes(arr6_1.count(i)) + "/" + bytes(len(arr6_1)) + "(" + bytes(float(arr6_1.count(i))/len(arr6_1)) + ")")
			for i in range(4):
				print ("Red6 Decade : " + bytes(i) + ", count = " + bytes(arr6_2.count(i)) + "/" + bytes(len(arr6_2)) + "(" + bytes(float(arr6_2.count(i))/len(arr6_2)) + ")")
			print ("Red6 Jiou : (ODD) zero_count = " + bytes(arr6_3.count(0)) + "/" + bytes(len(arr6_3)) + "(" + bytes(float(arr6_3.count(0))/len(arr6_3)) + ")")
			print ("Red6 Jiou : (EVEN) one_count = " + bytes(arr6_3.count(1)) + "/" + bytes(len(arr6_3)) + "(" + bytes(float(arr6_3.count(1))/len(arr6_3)) + ")")
			print ("Red6 Daxiao : (BIG) zero_count = " + bytes(arr6_4.count(0)) + "/" + bytes(len(arr6_4)) + "(" + bytes(float(arr6_4.count(0))/len(arr6_4)) + ")")
			print ("Red6 Daxiao : (SMALL) one_count = " + bytes(arr6_4.count(1)) + "/" + bytes(len(arr6_4)) + "(" + bytes(float(arr6_4.count(1))/len(arr6_4)) + ")")
			print ("Red6 Zhihe : (PRIME) zero_count = " + bytes(arr6_5.count(0)) + "/" + bytes(len(arr6_5)) + "(" + bytes(float(arr6_5.count(0))/len(arr6_5)) + ")")
			print ("Red6 Zhihe : (COMPOSITE) one_count = " + bytes(arr6_5.count(1)) + "/" + bytes(len(arr6_5)) + "(" + bytes(float(arr6_5.count(1))/len(arr6_5)) + ")")
			for i in range(5):
				print ("Red6 Wuxing : " + bytes(i) + ", count = " + bytes(arr6_6.count(i)) + "/" + bytes(len(arr6_6)) + "(" + bytes(float(arr6_6.count(i))/len(arr6_6)) + ")")
			print("Red6 Num Avg  = " + bytes(Math.avg(arr6_0)))
			for i in range(min(arr7_0), max(arr7_0)+1):
				print ("Blue Num : " + bytes(i) + ", count = " + bytes(arr7_0.count(i)) + "/" + bytes(len(arr7_0)) + "(" + bytes(float(arr7_0.count(i))/len(arr7_0)) + ")")
			for i in range(10):
				print ("Blue Unit : " + bytes(i) + ", count = " + bytes(arr7_1.count(i)) + "/" + bytes(len(arr7_1)) + "(" + bytes(float(arr7_1.count(i))/len(arr7_1)) + ")")
			for i in range(4):
				print ("Blue Decade : " + bytes(i) + ", count = " + bytes(arr7_2.count(i)) + "/" + bytes(len(arr7_2)) + "(" + bytes(float(arr7_2.count(i))/len(arr7_2)) + ")")
			print ("Blue Jiou : (ODD) zero_count = " + bytes(arr7_3.count(0)) + "/" + bytes(len(arr7_3)) + "(" + bytes(float(arr7_3.count(0))/len(arr7_3)) + ")")
			print ("Blue Jiou : (EVEN) one_count = " + bytes(arr7_3.count(1)) + "/" + bytes(len(arr7_3)) + "(" + bytes(float(arr7_3.count(1))/len(arr7_3)) + ")")
			print ("Blue Daxiao : (BIG) zero_count = " + bytes(arr7_4.count(0)) + "/" + bytes(len(arr7_4)) + "(" + bytes(float(arr7_4.count(0))/len(arr7_4)) + ")")
			print ("Blue Daxiao : (SMALL) one_count = " + bytes(arr7_4.count(1)) + "/" + bytes(len(arr7_4)) + "(" + bytes(float(arr7_4.count(1))/len(arr7_4)) + ")")
			print ("Blue Zhihe : (PRIME) zero_count = " + bytes(arr7_5.count(0)) + "/" + bytes(len(arr7_5)) + "(" + bytes(float(arr7_5.count(0))/len(arr7_5)) + ")")
			print ("Blue Zhihe : (COMPOSITE) one_count = " + bytes(arr7_5.count(1)) + "/" + bytes(len(arr7_5)) + "(" + bytes(float(arr7_5.count(1))/len(arr7_5)) + ")")
			for i in range(5):
				print ("Blue Wuxing : " + bytes(i) + ", count = " + bytes(arr7_6.count(i)) + "/" + bytes(len(arr7_6)) + "(" + bytes(float(arr7_6.count(i))/len(arr7_6)) + ")")
			print("Blue Num Avg = " + bytes(Math.avg(arr7_0)))
			print("RedSum avg = " + bytes(Math.avg(arr8_0)))
			print("UnitSum avg = " + bytes(Math.avg(arr8_1)))
			print ("jiouRatio : (0:6) count = " + bytes(arr8_3.count(0)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(0))/len(arr8_3)) + ")")
			print ("jiouRatio : (1:5) count = " + bytes(arr8_3.count(1)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(1))/len(arr8_3)) + ")")
			print ("jiouRatio : (2:4) count = " + bytes(arr8_3.count(2)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(2))/len(arr8_3)) + ")")
			print ("jiouRatio : (3:3) count = " + bytes(arr8_3.count(3)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(3))/len(arr8_3)) + ")")
			print ("jiouRatio : (4:2) count = " + bytes(arr8_3.count(4)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(4))/len(arr8_3)) + ")")
			print ("jiouRatio : (5:1) count = " + bytes(arr8_3.count(5)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(5))/len(arr8_3)) + ")")
			print ("jiouRatio : (6:0) count = " + bytes(arr8_3.count(6)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(6))/len(arr8_3)) + ")")
			print ("daxiaoRatio : (0:6) count = " + bytes(arr8_4.count(0)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(0))/len(arr8_4)) + ")")
			print ("daxiaoRatio : (1:5) count = " + bytes(arr8_4.count(1)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(1))/len(arr8_4)) + ")")
			print ("daxiaoRatio : (2:4) count = " + bytes(arr8_4.count(2)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(2))/len(arr8_4)) + ")")
			print ("daxiaoRatio : (3:3) count = " + bytes(arr8_4.count(3)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(3))/len(arr8_4)) + ")")
			print ("daxiaoRatio : (4:2) count = " + bytes(arr8_4.count(4)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(4))/len(arr8_4)) + ")")
			print ("daxiaoRatio : (5:1) count = " + bytes(arr8_4.count(5)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(5))/len(arr8_4)) + ")")
			print ("daxiaoRatio : (6:0) count = " + bytes(arr8_4.count(6)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(6))/len(arr8_4)) + ")")
			print ("zhiheRatio : (0:6) count = " + bytes(arr8_5.count(0)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(0))/len(arr8_5)) + ")")
			print ("zhiheRatio : (1:5) count = " + bytes(arr8_5.count(1)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(1))/len(arr8_5)) + ")")
			print ("zhiheRatio : (2:4) count = " + bytes(arr8_5.count(2)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(2))/len(arr8_5)) + ")")
			print ("zhiheRatio : (3:3) count = " + bytes(arr8_5.count(3)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(3))/len(arr8_5)) + ")")
			print ("zhiheRatio : (4:2) count = " + bytes(arr8_5.count(4)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(4))/len(arr8_5)) + ")")
			print ("zhiheRatio : (5:1) count = " + bytes(arr8_5.count(5)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(5))/len(arr8_5)) + ")")
			print ("zhiheRatio : (6:0) count = " + bytes(arr8_5.count(6)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(6))/len(arr8_5)) + ")")

def everyYearResultFile(fileindex):
	filename = TEST_DIR + "/" + TEST_FILE_HEAD + bytes(fileindex) + ".txt"
	print("filename = " + filename)
	file = open(filename, 'r')
	linesListFull = file.readlines()
	linesListFull = [line.strip().split('/') for line in linesListFull]
	file.close()
	index = []
	pro1 = []
	pro2 = []
	pro3 = []
	pro4 = []
	pro5 = []
	pro6 = []
	pro7 = []
	for i in range(16, len(linesListFull)+1):
		linesList = linesListFull[:i]    
		arr0 = [x[0] for x in linesList]
		arr1 = [x[1].strip().split(',') for x in linesList]
		arr1_0 = [string.atoi(x[0]) for x in arr1]
		arr1_1 = [string.atoi(x[1]) for x in arr1]
		arr1_2 = [string.atoi(x[2]) for x in arr1]
		arr1_3 = [string.atoi(x[3]) for x in arr1]
		arr1_4 = [string.atoi(x[4]) for x in arr1]
		arr1_5 = [string.atoi(x[5]) for x in arr1]
		arr1_6 = [string.atoi(x[6]) for x in arr1]
		arr2 = [x[2].strip().split(',') for x in linesList]
		arr2_0 = [string.atoi(x[0]) for x in arr2]
		arr2_1 = [string.atoi(x[1]) for x in arr2]
		arr2_2 = [string.atoi(x[2]) for x in arr2]
		arr2_3 = [string.atoi(x[3]) for x in arr2]
		arr2_4 = [string.atoi(x[4]) for x in arr2]
		arr2_5 = [string.atoi(x[5]) for x in arr2]
		arr2_6 = [string.atoi(x[6]) for x in arr2]
		arr3 = [x[3].strip().split(',') for x in linesList]
		arr3_0 = [string.atoi(x[0]) for x in arr3]
		arr3_1 = [string.atoi(x[1]) for x in arr3]
		arr3_2 = [string.atoi(x[2]) for x in arr3]
		arr3_3 = [string.atoi(x[3]) for x in arr3]
		arr3_4 = [string.atoi(x[4]) for x in arr3]
		arr3_5 = [string.atoi(x[5]) for x in arr3]
		arr3_6 = [string.atoi(x[6]) for x in arr3]
		arr4 = [x[4].strip().split(',') for x in linesList]
		arr4_0 = [string.atoi(x[0]) for x in arr4]
		arr4_1 = [string.atoi(x[1]) for x in arr4]
		arr4_2 = [string.atoi(x[2]) for x in arr4]
		arr4_3 = [string.atoi(x[3]) for x in arr4]
		arr4_4 = [string.atoi(x[4]) for x in arr4]
		arr4_5 = [string.atoi(x[5]) for x in arr4]
		arr4_6 = [string.atoi(x[6]) for x in arr4]
		arr5 = [x[5].strip().split(',') for x in linesList]
		arr5_0 = [string.atoi(x[0]) for x in arr5]
		arr5_1 = [string.atoi(x[1]) for x in arr5]
		arr5_2 = [string.atoi(x[2]) for x in arr5]
		arr5_3 = [string.atoi(x[3]) for x in arr5]
		arr5_4 = [string.atoi(x[4]) for x in arr5]
		arr5_5 = [string.atoi(x[5]) for x in arr5]
		arr5_6 = [string.atoi(x[6]) for x in arr5]
		arr6 = [x[6].strip().split(',') for x in linesList]
		arr6_0 = [string.atoi(x[0]) for x in arr6]
		arr6_1 = [string.atoi(x[1]) for x in arr6]
		arr6_2 = [string.atoi(x[2]) for x in arr6]
		arr6_3 = [string.atoi(x[3]) for x in arr6]
		arr6_4 = [string.atoi(x[4]) for x in arr6]
		arr6_5 = [string.atoi(x[5]) for x in arr6]
		arr6_6 = [string.atoi(x[6]) for x in arr6]
		arr7 = [x[7].strip().split(',') for x in linesList]
		arr7_0 = [string.atoi(x[0]) for x in arr7]
		arr7_1 = [string.atoi(x[1]) for x in arr7]
		arr7_2 = [string.atoi(x[2]) for x in arr7]
		arr7_3 = [string.atoi(x[3]) for x in arr7]
		arr7_4 = [string.atoi(x[4]) for x in arr7]
		arr7_5 = [string.atoi(x[5]) for x in arr7]
		arr7_6 = [string.atoi(x[6]) for x in arr7]
		arr8 = [x[8].strip().split(',') for x in linesList]
		arr8_0 = [string.atoi(x[0]) for x in arr8]
		arr8_1 = [string.atoi(x[1]) for x in arr8]
		arr8_2 = [string.atoi(x[2]) for x in arr8]
		arr8_3 = [string.atoi(x[3]) for x in arr8]
		arr8_4 = [string.atoi(x[4]) for x in arr8]
		arr8_5 = [string.atoi(x[5]) for x in arr8]
		arr = arr1_0 + arr2_0 + arr3_0 + arr4_0 + arr5_0 + arr6_0
		print("i = " + bytes(i))
		print("Red1 Num Avg = " + bytes(Math.avg(arr1_0)))
		print("Red2 Num Avg  = " + bytes(Math.avg(arr2_0)))
		print("Red3 Num Avg  = " + bytes(Math.avg(arr3_0)))
		print("Red4 Num Avg  = " + bytes(Math.avg(arr4_0)))
		print("Red5 Num Avg  = " + bytes(Math.avg(arr5_0)))
		print("Red6 Num Avg  = " + bytes(Math.avg(arr6_0)))
		print("Blue Num Avg  = " + bytes(Math.avg(arr7_0)))
		print("RedSum avg = " + bytes(Math.avg(arr8_0)))
		print("UnitSum avg = " + bytes(Math.avg(arr8_1)))
		index += [i]
		pro1 += [Math.avg(arr1_0)]
		pro2 += [Math.avg(arr2_0)]
		pro3 += [Math.avg(arr3_0)]
		pro4 += [Math.avg(arr4_0)]
		pro5 += [Math.avg(arr5_0)]
		pro6 += [Math.avg(arr6_0)]
		pro7 += [Math.avg(arr7_0)]
	plt.figure()
	plt.scatter(index, pro1, s=20, c="black")
	#plt.scatter(index, pro2, s=20, c="yellow")
	#plt.scatter(index, pro3, s=20, c="red")
	#plt.scatter(index, pro4, s=20, c="gold")
	#plt.scatter(index, pro5, s=20, c="brown")
	#plt.scatter(index, pro6, s=20, c="coral")
	#plt.scatter(index, pro7, s=20, c="blue")
	plt.savefig("test.jpg")
	plt.show()
'''
	for i in range(1,34):
		print ("redNum : " + bytes(i) + ", count = " + bytes(arr.count(i)) + "/" + bytes(len(arr)) + "(" + bytes(float(arr.count(i))/len(arr)) + ")")
	for i in range(1, 17):
		print ("blueNum : " + bytes(i) + ", count = " + bytes(arr7_0.count(i)) + "/" + bytes(len(arr7_0)) + "(" + bytes(float(arr7_0.count(i))/len(arr7_0)) + ")")
	for i in range(min(arr1_0), max(arr1_0)+1):
		print ("Red1 Num : " + bytes(i) + ", count = " + bytes(arr1_0.count(i)) + "/" + bytes(len(arr1_0)) + "(" + bytes(float(arr1_0.count(i))/len(arr1_0)) + ")")
	for i in range(10):
		print ("Red1 Unit : " + bytes(i) + ", count = " + bytes(arr1_1.count(i)) + "/" + bytes(len(arr1_1)) + "(" + bytes(float(arr1_1.count(i))/len(arr1_1)) + ")")
	for i in range(4):
		print ("Red1 Decade : " + bytes(i) + ", count = " + bytes(arr1_2.count(i)) + "/" + bytes(len(arr1_2)) + "(" + bytes(float(arr1_2.count(i))/len(arr1_2)) + ")")
	print ("Red1 Jiou : (ODD) zero_count = " + bytes(arr1_3.count(0)) + "/" + bytes(len(arr1_3)) + "(" + bytes(float(arr1_3.count(0))/len(arr1_3)) + ")")
	print ("Red1 Jiou : (EVEN) one_count = " + bytes(arr1_3.count(1)) + "/" + bytes(len(arr1_3)) + "(" + bytes(float(arr1_3.count(1))/len(arr1_3)) + ")")
	print ("Red1 Daxiao : (BIG) zero_count = " + bytes(arr1_4.count(0)) + "/" + bytes(len(arr1_4)) + "(" + bytes(float(arr1_4.count(0))/len(arr1_4)) + ")")
	print ("Red1 Daxiao : (SMALL) one_count = " + bytes(arr1_4.count(1)) + "/" + bytes(len(arr1_4)) + "(" + bytes(float(arr1_4.count(1))/len(arr1_4)) + ")")
	print ("Red1 Zhihe : (PRIME) zero_count = " + bytes(arr1_5.count(0)) + "/" + bytes(len(arr1_5)) + "(" + bytes(float(arr1_5.count(0))/len(arr1_5)) + ")")
	print ("Red1 Zhihe : (COMPOSITE) one_count = " + bytes(arr1_5.count(1)) + "/" + bytes(len(arr1_5)) + "(" + bytes(float(arr1_5.count(1))/len(arr1_5)) + ")")
	for i in range(5):
		print ("Red1 Wuxing : " + bytes(i) + ", count = " + bytes(arr1_6.count(i)) + "/" + bytes(len(arr1_6)) + "(" + bytes(float(arr1_6.count(i))/len(arr1_6)) + ")")
	print("Red1 Num Avg = " + bytes(Math.avg(arr1_0)))
	for i in range(min(arr2_0), max(arr2_0)+1):
		print ("Red2 Num : " + bytes(i) + ", count = " + bytes(arr2_0.count(i)) + "/" + bytes(len(arr2_0)) + "(" + bytes(float(arr2_0.count(i))/len(arr2_0)) + ")")
	for i in range(10):
		print ("Red2 Unit : " + bytes(i) + ", count = " + bytes(arr2_1.count(i)) + "/" + bytes(len(arr2_1)) + "(" + bytes(float(arr2_1.count(i))/len(arr2_1)) + ")")
	for i in range(4):
		print ("Red2 Decade : " + bytes(i) + ", count = " + bytes(arr2_2.count(i)) + "/" + bytes(len(arr2_2)) + "(" + bytes(float(arr2_2.count(i))/len(arr2_2)) + ")")
	print ("Red2 Jiou : (ODD) zero_count = " + bytes(arr2_3.count(0)) + "/" + bytes(len(arr2_3)) + "(" + bytes(float(arr2_3.count(0))/len(arr2_3)) + ")")
	print ("Red2 Jiou : (EVEN) one_count = " + bytes(arr2_3.count(1)) + "/" + bytes(len(arr2_3)) + "(" + bytes(float(arr2_3.count(1))/len(arr2_3)) + ")")
	print ("Red2 Daxiao : (BIG) zero_count = " + bytes(arr2_4.count(0)) + "/" + bytes(len(arr2_4)) + "(" + bytes(float(arr2_4.count(0))/len(arr2_4)) + ")")
	print ("Red2 Daxiao : (SMALL) one_count = " + bytes(arr2_4.count(1)) + "/" + bytes(len(arr2_4)) + "(" + bytes(float(arr2_4.count(1))/len(arr2_4)) + ")")
	print ("Red2 Zhihe : (PRIME) zero_count = " + bytes(arr2_5.count(0)) + "/" + bytes(len(arr2_5)) + "(" + bytes(float(arr2_5.count(0))/len(arr2_5)) + ")")
	print ("Red2 Zhihe : (COMPOSITE) one_count = " + bytes(arr2_5.count(1)) + "/" + bytes(len(arr2_5)) + "(" + bytes(float(arr2_5.count(1))/len(arr2_5)) + ")")
	for i in range(5):
		print ("Red2 Wuxing : " + bytes(i) + ", count = " + bytes(arr2_6.count(i)) + "/" + bytes(len(arr2_6)) + "(" + bytes(float(arr2_6.count(i))/len(arr2_6)) + ")")
	print("Red2 Num Avg  = " + bytes(Math.avg(arr2_0)))
	for i in range(min(arr3_0), max(arr3_0)+1):
		print ("Red3 Num : " + bytes(i) + ", count = " + bytes(arr3_0.count(i)) + "/" + bytes(len(arr3_0)) + "(" + bytes(float(arr3_0.count(i))/len(arr3_0)) + ")")
	for i in range(10):
		print ("Red3 Unit : " + bytes(i) + ", count = " + bytes(arr3_1.count(i)) + "/" + bytes(len(arr3_1)) + "(" + bytes(float(arr3_1.count(i))/len(arr3_1)) + ")")
	for i in range(4):
		print ("Red3 Decade : " + bytes(i) + ", count = " + bytes(arr3_2.count(i)) + "/" + bytes(len(arr3_2)) + "(" + bytes(float(arr3_2.count(i))/len(arr3_2)) + ")")
	print ("Red3 Jiou : (ODD) zero_count = " + bytes(arr3_3.count(0)) + "/" + bytes(len(arr3_3)) + "(" + bytes(float(arr3_3.count(0))/len(arr3_3)) + ")")
	print ("Red3 Jiou : (EVEN) one_count = " + bytes(arr3_3.count(1)) + "/" + bytes(len(arr3_3)) + "(" + bytes(float(arr3_3.count(1))/len(arr3_3)) + ")")
	print ("Red3 Daxiao : (BIG) zero_count = " + bytes(arr3_4.count(0)) + "/" + bytes(len(arr3_4)) + "(" + bytes(float(arr3_4.count(0))/len(arr3_4)) + ")")
	print ("Red3 Daxiao : (SMALL) one_count = " + bytes(arr3_4.count(1)) + "/" + bytes(len(arr3_4)) + "(" + bytes(float(arr3_4.count(1))/len(arr3_4)) + ")")
	print ("Red3 Zhihe : (PRIME) zero_count = " + bytes(arr3_5.count(0)) + "/" + bytes(len(arr3_5)) + "(" + bytes(float(arr3_5.count(0))/len(arr3_5)) + ")")
	print ("Red3 Zhihe : (COMPOSITE) one_count = " + bytes(arr3_5.count(1)) + "/" + bytes(len(arr3_5)) + "(" + bytes(float(arr3_5.count(1))/len(arr3_5)) + ")")
	for i in range(5):
		print ("Red3 Wuxing : " + bytes(i) + ", count = " + bytes(arr3_6.count(i)) + "/" + bytes(len(arr3_6)) + "(" + bytes(float(arr3_6.count(i))/len(arr3_6)) + ")")
	print("Red3 Num Avg = " + bytes(Math.avg(arr3_0)))
	for i in range(min(arr4_0), max(arr4_0)+1):
		print ("Red4 Num : " + bytes(i) + ", count = " + bytes(arr4_0.count(i)) + "/" + bytes(len(arr4_0)) + "(" + bytes(float(arr4_0.count(i))/len(arr4_0)) + ")")
	for i in range(10):
		print ("Red4 Unit : " + bytes(i) + ", count = " + bytes(arr4_1.count(i)) + "/" + bytes(len(arr4_1)) + "(" + bytes(float(arr4_1.count(i))/len(arr4_1)) + ")")
	for i in range(4):
		print ("Red4 Decade : " + bytes(i) + ", count = " + bytes(arr4_2.count(i)) + "/" + bytes(len(arr4_2)) + "(" + bytes(float(arr4_2.count(i))/len(arr4_2)) + ")")
	print ("Red4 Jiou : (ODD) zero_count = " + bytes(arr4_3.count(0)) + "/" + bytes(len(arr4_3)) + "(" + bytes(float(arr4_3.count(0))/len(arr4_3)) + ")")
	print ("Red4 Jiou : (EVEN) one_count = " + bytes(arr4_3.count(1)) + "/" + bytes(len(arr4_3)) + "(" + bytes(float(arr4_3.count(1))/len(arr4_3)) + ")")
	print ("Red4 Daxiao : (BIG) zero_count = " + bytes(arr4_4.count(0)) + "/" + bytes(len(arr4_4)) + "(" + bytes(float(arr4_4.count(0))/len(arr4_4)) + ")")
	print ("Red4 Daxiao : (SMALL) one_count = " + bytes(arr4_4.count(1)) + "/" + bytes(len(arr4_4)) + "(" + bytes(float(arr4_4.count(1))/len(arr4_4)) + ")")
	print ("Red4 Zhihe : (PRIME) zero_count = " + bytes(arr4_5.count(0)) + "/" + bytes(len(arr4_5)) + "(" + bytes(float(arr4_5.count(0))/len(arr4_5)) + ")")
	print ("Red4 Zhihe : (COMPOSITE) one_count = " + bytes(arr4_5.count(1)) + "/" + bytes(len(arr4_5)) + "(" + bytes(float(arr4_5.count(1))/len(arr4_5)) + ")")
	for i in range(5):
		print ("Red4 Wuxing : " + bytes(i) + ", count = " + bytes(arr4_6.count(i)) + "/" + bytes(len(arr4_6)) + "(" + bytes(float(arr4_6.count(i))/len(arr4_6)) + ")")
	print("Red4 Num Avg  = " + bytes(Math.avg(arr4_0)))
	for i in range(min(arr5_0), max(arr5_0)+1):
		print ("Red5 Num : " + bytes(i) + ", count = " + bytes(arr5_0.count(i)) + "/" + bytes(len(arr5_0)) + "(" + bytes(float(arr5_0.count(i))/len(arr5_0)) + ")")
	for i in range(10):
		print ("Red5 Unit : " + bytes(i) + ", count = " + bytes(arr5_1.count(i)) + "/" + bytes(len(arr5_1)) + "(" + bytes(float(arr5_1.count(i))/len(arr5_1)) + ")")
	for i in range(4):
		print ("Red5 Decade : " + bytes(i) + ", count = " + bytes(arr5_2.count(i)) + "/" + bytes(len(arr5_2)) + "(" + bytes(float(arr5_2.count(i))/len(arr5_2)) + ")")
	print ("Red5 Jiou : (ODD) zero_count = " + bytes(arr5_3.count(0)) + "/" + bytes(len(arr5_3)) + "(" + bytes(float(arr5_3.count(0))/len(arr5_3)) + ")")
	print ("Red5 Jiou : (EVEN) one_count = " + bytes(arr5_3.count(1)) + "/" + bytes(len(arr5_3)) + "(" + bytes(float(arr5_3.count(1))/len(arr5_3)) + ")")
	print ("Red5 Daxiao : (BIG) zero_count = " + bytes(arr5_4.count(0)) + "/" + bytes(len(arr5_4)) + "(" + bytes(float(arr5_4.count(0))/len(arr5_4)) + ")")
	print ("Red5 Daxiao : (SMALL) one_count = " + bytes(arr5_4.count(1)) + "/" + bytes(len(arr5_4)) + "(" + bytes(float(arr5_4.count(1))/len(arr5_4)) + ")")
	print ("Red5 Zhihe : (PRIME) zero_count = " + bytes(arr5_5.count(0)) + "/" + bytes(len(arr5_5)) + "(" + bytes(float(arr5_5.count(0))/len(arr5_5)) + ")")
	print ("Red5 Zhihe : (COMPOSITE) one_count = " + bytes(arr5_5.count(1)) + "/" + bytes(len(arr5_5)) + "(" + bytes(float(arr5_5.count(1))/len(arr5_5)) + ")")
	for i in range(5):
		print ("Red5 Wuxing : " + bytes(i) + ", count = " + bytes(arr5_6.count(i)) + "/" + bytes(len(arr5_6)) + "(" + bytes(float(arr5_6.count(i))/len(arr5_6)) + ")")
	print("Red5 Num Avg  = " + bytes(Math.avg(arr5_0)))
	for i in range(min(arr6_0), max(arr6_0)+1):
		print ("Red6 Num : " + bytes(i) + ", count = " + bytes(arr6_0.count(i)) + "/" + bytes(len(arr6_0)) + "(" + bytes(float(arr6_0.count(i))/len(arr6_0)) + ")")
	for i in range(10):
		print ("Red6 Unit : " + bytes(i) + ", count = " + bytes(arr6_1.count(i)) + "/" + bytes(len(arr6_1)) + "(" + bytes(float(arr6_1.count(i))/len(arr6_1)) + ")")
	for i in range(4):
		print ("Red6 Decade : " + bytes(i) + ", count = " + bytes(arr6_2.count(i)) + "/" + bytes(len(arr6_2)) + "(" + bytes(float(arr6_2.count(i))/len(arr6_2)) + ")")
	print ("Red6 Jiou : (ODD) zero_count = " + bytes(arr6_3.count(0)) + "/" + bytes(len(arr6_3)) + "(" + bytes(float(arr6_3.count(0))/len(arr6_3)) + ")")
	print ("Red6 Jiou : (EVEN) one_count = " + bytes(arr6_3.count(1)) + "/" + bytes(len(arr6_3)) + "(" + bytes(float(arr6_3.count(1))/len(arr6_3)) + ")")
	print ("Red6 Daxiao : (BIG) zero_count = " + bytes(arr6_4.count(0)) + "/" + bytes(len(arr6_4)) + "(" + bytes(float(arr6_4.count(0))/len(arr6_4)) + ")")
	print ("Red6 Daxiao : (SMALL) one_count = " + bytes(arr6_4.count(1)) + "/" + bytes(len(arr6_4)) + "(" + bytes(float(arr6_4.count(1))/len(arr6_4)) + ")")
	print ("Red6 Zhihe : (PRIME) zero_count = " + bytes(arr6_5.count(0)) + "/" + bytes(len(arr6_5)) + "(" + bytes(float(arr6_5.count(0))/len(arr6_5)) + ")")
	print ("Red6 Zhihe : (COMPOSITE) one_count = " + bytes(arr6_5.count(1)) + "/" + bytes(len(arr6_5)) + "(" + bytes(float(arr6_5.count(1))/len(arr6_5)) + ")")
	for i in range(5):
		print ("Red6 Wuxing : " + bytes(i) + ", count = " + bytes(arr6_6.count(i)) + "/" + bytes(len(arr6_6)) + "(" + bytes(float(arr6_6.count(i))/len(arr6_6)) + ")")
	print("Red6 Num Avg  = " + bytes(Math.avg(arr6_0)))
	for i in range(min(arr7_0), max(arr7_0)+1):
		print ("Blue Num : " + bytes(i) + ", count = " + bytes(arr7_0.count(i)) + "/" + bytes(len(arr7_0)) + "(" + bytes(float(arr7_0.count(i))/len(arr7_0)) + ")")
	for i in range(10):
		print ("Blue Unit : " + bytes(i) + ", count = " + bytes(arr7_1.count(i)) + "/" + bytes(len(arr7_1)) + "(" + bytes(float(arr7_1.count(i))/len(arr7_1)) + ")")
	for i in range(4):
		print ("Blue Decade : " + bytes(i) + ", count = " + bytes(arr7_2.count(i)) + "/" + bytes(len(arr7_2)) + "(" + bytes(float(arr7_2.count(i))/len(arr7_2)) + ")")
	print ("Blue Jiou : (ODD) zero_count = " + bytes(arr7_3.count(0)) + "/" + bytes(len(arr7_3)) + "(" + bytes(float(arr7_3.count(0))/len(arr7_3)) + ")")
	print ("Blue Jiou : (EVEN) one_count = " + bytes(arr7_3.count(1)) + "/" + bytes(len(arr7_3)) + "(" + bytes(float(arr7_3.count(1))/len(arr7_3)) + ")")
	print ("Blue Daxiao : (BIG) zero_count = " + bytes(arr7_4.count(0)) + "/" + bytes(len(arr7_4)) + "(" + bytes(float(arr7_4.count(0))/len(arr7_4)) + ")")
	print ("Blue Daxiao : (SMALL) one_count = " + bytes(arr7_4.count(1)) + "/" + bytes(len(arr7_4)) + "(" + bytes(float(arr7_4.count(1))/len(arr7_4)) + ")")
	print ("Blue Zhihe : (PRIME) zero_count = " + bytes(arr7_5.count(0)) + "/" + bytes(len(arr7_5)) + "(" + bytes(float(arr7_5.count(0))/len(arr7_5)) + ")")
	print ("Blue Zhihe : (COMPOSITE) one_count = " + bytes(arr7_5.count(1)) + "/" + bytes(len(arr7_5)) + "(" + bytes(float(arr7_5.count(1))/len(arr7_5)) + ")")
	for i in range(5):
		print ("Blue Wuxing : " + bytes(i) + ", count = " + bytes(arr7_6.count(i)) + "/" + bytes(len(arr7_6)) + "(" + bytes(float(arr7_6.count(i))/len(arr7_6)) + ")")
	print("Blue Num Avg = " + bytes(Math.avg(arr7_0)))
	print("RedSum avg = " + bytes(Math.avg(arr8_0)))
	print("UnitSum avg = " + bytes(Math.avg(arr8_1)))
	print ("jiouRatio : (0:6) count = " + bytes(arr8_3.count(0)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(0))/len(arr8_3)) + ")")
	print ("jiouRatio : (1:5) count = " + bytes(arr8_3.count(1)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(1))/len(arr8_3)) + ")")
	print ("jiouRatio : (2:4) count = " + bytes(arr8_3.count(2)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(2))/len(arr8_3)) + ")")
	print ("jiouRatio : (3:3) count = " + bytes(arr8_3.count(3)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(3))/len(arr8_3)) + ")")
	print ("jiouRatio : (4:2) count = " + bytes(arr8_3.count(4)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(4))/len(arr8_3)) + ")")
	print ("jiouRatio : (5:1) count = " + bytes(arr8_3.count(5)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(5))/len(arr8_3)) + ")")
	print ("jiouRatio : (6:0) count = " + bytes(arr8_3.count(6)) + "/" + bytes(len(arr8_3)) + "(" + bytes(float(arr8_3.count(6))/len(arr8_3)) + ")")
	print ("daxiaoRatio : (0:6) count = " + bytes(arr8_4.count(0)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(0))/len(arr8_4)) + ")")
	print ("daxiaoRatio : (1:5) count = " + bytes(arr8_4.count(1)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(1))/len(arr8_4)) + ")")
	print ("daxiaoRatio : (2:4) count = " + bytes(arr8_4.count(2)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(2))/len(arr8_4)) + ")")
	print ("daxiaoRatio : (3:3) count = " + bytes(arr8_4.count(3)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(3))/len(arr8_4)) + ")")
	print ("daxiaoRatio : (4:2) count = " + bytes(arr8_4.count(4)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(4))/len(arr8_4)) + ")")
	print ("daxiaoRatio : (5:1) count = " + bytes(arr8_4.count(5)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(5))/len(arr8_4)) + ")")
	print ("daxiaoRatio : (6:0) count = " + bytes(arr8_4.count(6)) + "/" + bytes(len(arr8_4)) + "(" + bytes(float(arr8_4.count(6))/len(arr8_4)) + ")")
	print ("zhiheRatio : (0:6) count = " + bytes(arr8_5.count(0)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(0))/len(arr8_5)) + ")")
	print ("zhiheRatio : (1:5) count = " + bytes(arr8_5.count(1)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(1))/len(arr8_5)) + ")")
	print ("zhiheRatio : (2:4) count = " + bytes(arr8_5.count(2)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(2))/len(arr8_5)) + ")")
	print ("zhiheRatio : (3:3) count = " + bytes(arr8_5.count(3)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(3))/len(arr8_5)) + ")")
	print ("zhiheRatio : (4:2) count = " + bytes(arr8_5.count(4)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(4))/len(arr8_5)) + ")")
	print ("zhiheRatio : (5:1) count = " + bytes(arr8_5.count(5)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(5))/len(arr8_5)) + ")")
	print ("zhiheRatio : (6:0) count = " + bytes(arr8_5.count(6)) + "/" + bytes(len(arr8_5)) + "(" + bytes(float(arr8_5.count(6))/len(arr8_5)) + ")")
'''

class Math:  
	#求极差  
	@staticmethod  
	def range(l):  
		return max(l)-min(l);  
	#求平均数  
	@staticmethod  
	def avg(l):  
		return float(sum(l))/len(l);  
	#求中位数  
	@staticmethod  
	def median(l):  
		l=sorted(l);#先排序  
		if len(l)%2==1:  
			return l[len(l)/2];  
		else:  
			return (l[len(l)/2-1]+l[len(l)/2])/2.0;  
	#求众数  
	@staticmethod  
	def mode(l):  
		#统计list中各个数值出现的次数  
		count_dict={};  
		for i in l:  
			if count_dict.has_key(i):  
				count_dict[i]+=1;  
			else:  
				count_dict[i]=1;  
		#求出现次数的最大值  
		max_appear=0  
		for v in count_dict.values():  
			if v>max_appear:  
				 max_appear=v;  
		if max_appear==1:  
			return;  
		mode_list=[];  
		for k,v in count_dict.items():  
			if v==max_appear:  
				mode_list.append(k);  
		return mode_list;  
	#求方差  
	@staticmethod  
	def variance(l):#平方的期望-期望的平方  
		s1=0;  
		s2=0;  
		for i in l:  
			s1+=i**2;  
			s2+=i;  
		return float(s1)/len(l)-(float(s2)/len(l))**2;  
	  
	#求方差2  
	@staticmethod      
	def variance2(l):#平方-期望的平方的期望  
		ex=float(sum(l))/len(l);  
		s=0;  
		for i in l:  
			s+=(i-ex)**2;  
		return float(s)/len(l);      

  
#figureFiles()
#figureFile(3)
#analyseFile(1)
#analyseFiles()
#barFile(11)
#barFiles()
#analyseResultFile(11)
#globalAnalyseFiles()
#everyYearResultFiles()
everyYearResultFile(315)
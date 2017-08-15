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

def test():
	x = [8, 4, 0, 5, 10, 2, 9, 1, 7, 6, 3]
	y1 = [269, 247, 253, 244, 269, 243, 265, 249, 260, 253, 245]
	y2 = [199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199]
	y3 = [1008, 840, 724, 892, 1009, 751, 1019, 734, 991, 940, 787]
	#plt.plot(x, y1, label="$y1$")
	#plt.plot(x, y2, label="$y2$")
	#plt.plot(x, y3, label="$y3$")
	plt.scatter(x, y1, s=40, c="red", label="$y1$")
	plt.scatter(x, y2, s=40, c="yellow", label="$y2$")
	plt.scatter(x, y3, s=40, c="blue", label="$y3$")
	plt.legend()
	plt.show() 
  
#figureFiles()
#figureFile(3)
#analyseFile(1)
#analyseFiles()
#test()
#barFile(11)
#barFiles()
#analyseResultFile(11)
globalAnalyseFiles()
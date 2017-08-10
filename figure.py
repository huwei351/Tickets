#-*- coding: UTF-8 -*- 

import time
import random
import string
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
analyseFiles()
#test()
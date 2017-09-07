#-*- coding: UTF-8 -*-

import string
import mysql.connector
from bs4 import BeautifulSoup
import requests
import re
import sys
reload(sys)
sys.setdefaultencoding('utf8')

MYSQL_HOSTS = '127.0.0.1'
MYSQL_USER = 'root'
MYSQL_PASSWORD = 'huwei351'
MYSQL_PORT = '3306'
MYSQL_DB = 'dlt'

cnx = mysql.connector.connect(user = MYSQL_USER,password= MYSQL_PASSWORD,host =MYSQL_HOSTS,database=MYSQL_DB)
cur = cnx.cursor(buffered=True)

def update_database(qid):
    res = -2
    url='http://www.lottery.gov.cn/historykj/history.jspx?_ltype=dlt'
    html = requests.get(url)
    content=BeautifulSoup(html.text, 'lxml')
    rows = content.findAll('tr')
    for row in rows:
        if re.search("blue", str(row)):
            columns = row.findAll('td')
            rid = re.findall('>(\d+)<', str(columns[0]))[0]
            datestr = str(columns[19])
            date = re.findall('>(\S+)<', str(columns[19]))[0]
            rb1 = re.findall('>(\d+)<', str(columns[1]))[0]
            rb2 = re.findall('>(\d+)<', str(columns[2]))[0]
            rb3 = re.findall('>(\d+)<', str(columns[3]))[0]
            rb4 = re.findall('>(\d+)<', str(columns[4]))[0]
            rb5 = re.findall('>(\d+)<', str(columns[5]))[0]
            bb1 = re.findall('>(\d+)<', str(columns[6]))[0]
            bb2 = re.findall('>(\d+)<', str(columns[7]))[0]
            dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'bb1':bb1, 'bb2':bb2}
            if (rid > bytes(qid)):
                print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", bb1=" + bb1 + ", bb2=" + bb2)
                save_result_into_database(dict)
                res = 0
    return res

def save_result_into_database(dict):
    date = dict['date']
    ret = select_title(date)
    if ret[0] ==1:
        print('result already exsisted')
    else:
        rid = dict['rid']
        rb1 = dict['rb1']
        rb2 = dict['rb2']
        rb3 = dict['rb3']
        rb4 = dict['rb4']
        rb5 = dict['rb5']
        bb1 = dict['bb1']
        bb2 = dict['bb2']
        insert_dlt_result(rid,date,rb1,rb2,rb3,rb4,rb5,bb1,bb2)
        print('starting save results')

def insert_dlt_result(rid,date,rb1,rb2,rb3,rb4,rb5,bb1,bb2):
    sql = 'INSERT INTO dlt_result (`rid`,`date`,`rb1`,`rb2`,`rb3`,`rb4`,`rb5`,`bb1`,`bb2`) VALUES (%(rid)s,%(date)s,%(rb1)s,%(rb2)s,%(rb3)s,%(rb4)s,%(rb5)s,%(bb1)s,%(bb2)s)'
    value = {
        'rid':rid,
        'date':date,
        'rb1':rb1,
        'rb2':rb2,
        'rb3':rb3,
        'rb4':rb4,
        'rb5':rb5,
        'bb1':bb1,
        'bb2':bb2,
    }
    cur.execute(sql,value)
    cnx.commit()

def select_title(date):#这个是利用标题去重的，虽然按照区域划分应该不会重复，只是预防万一
    sql= 'SELECT EXISTS (SELECT 1 FROM dlt_result WHERE date = %(date)s)'
    value = {
        'date':date
    }
    cur.execute(sql,value)
    return  cur.fetchall()[0]

def select_result(rid):
    sql= 'SELECT * FROM dlt_result WHERE rid = %(rid)s'
    value = {
        'rid':rid
    }
    cur.execute(sql,value)
    return  cur.fetchone()

def select_local_latest_result():
    sql= 'SELECT * FROM dlt_result ORDER BY date DESC'
    cur.execute(sql)
    return  cur.fetchall()[0]

def get_win_level(presult, aresult):
    red = 0
    blue = 0
    level = 0
    if (presult[5] == aresult[5] and presult[6] == aresult[6]):
        blue = 2
    elif ((presult[5] == aresult[5] and presult[6] != aresult[6]) or (presult[5] != aresult[5] and presult[6] == aresult[6]) or (presult[5] == aresult[6] and presult[6] != aresult[5]) or (presult[6] == aresult[5] and presult[5] != aresult[6])):
        blue = 1
    for i in range(5):
        for j in range(5):
            if(presult[j] == aresult[i]):
                red += 1
                break
    if (blue == 2):
        if red == 5:
            level = 1
        elif red == 4:
            level = 3
        elif red == 3:
            level = 4
        elif red == 2:
            level = 5
        else:
            level = 6  
    elif (blue == 1):
        if red == 5:
            level = 2
        elif red == 4:
            level = 4
        elif red == 3:
            level = 5
        elif red == 2:
            level = 6
    else:
        if red == 5:
            level = 3
        elif red == 4:
            level = 5
        elif red == 3:
            level = 6
    return level

def calculate_income(qid,full):
    aresult = list(select_result(qid)[3:])
    print("第" + bytes(qid) + "开奖结果为：")
    print(aresult)
    if full:
        filename = "./dlt_results/" + bytes(qid) + "-predict-full.txt"
    else:
        filename = "./dlt_results/" + bytes(qid) + "-predict.txt"
    print("filename = " + filename)
    file = open(filename, 'r')
    linesList = file.readlines()
    linesList = [line.strip().split(',') for line in linesList]
    file.close()
    level_one = []
    level_two = []
    level_three = []
    level_four = []
    level_five = []
    level_six = []
    for i in range(len(linesList)):
        temp = linesList[i][4].strip().split('+')
        linesList[i][4] = temp[0]
        linesList[i].insert(5, temp[1])
        presult = [string.atoi(line) for line in linesList[i]]
        level = get_win_level(presult, aresult)
        if (level == 1):
            level_one += [i + 1]
        elif (level == 2):
            level_two += [i + 1] 
        elif (level == 3):
            level_three += [i + 1]
        elif (level == 4):
            level_four += [i + 1]
        elif (level == 5):
            level_five += [i + 1]
        elif (level == 6):
            level_six += [i + 1]
    print("一等奖" + bytes(len(level_one)) + "注")
    print(level_one)
    print("二等奖" + bytes(len(level_two)) + "注")
    print(level_two)
    print("三等奖" + bytes(len(level_three)) + "注")
    print(level_three)
    print("四等奖" + bytes(len(level_four)) + "注")
    print(level_four)
    print("五等奖" + bytes(len(level_five)) + "注")
    print(level_five)
    print("六等奖" + bytes(len(level_six)) + "注")
    print(level_six)
    income = (len(level_one)*5000000 + len(level_two)*100000)*0.8 + len(level_three)*3000 + len(level_four)*200 + len(level_five)*10 + len(level_six)*5
    print("总共投注" + bytes(len(linesList)) + "注, 共花费" + bytes(len(linesList)*2) + "元")
    print("中奖总金额" + bytes(income) + "元， 净利润" + bytes(income-len(linesList)*2) + "元")
    return 0

latest_rid = select_local_latest_result()[1]
update_database(latest_rid)
latest_rid = select_local_latest_result()[1]
calculate_income(latest_rid, 1)
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
MYSQL_DB = 'ssq'

cnx = mysql.connector.connect(user = MYSQL_USER,password= MYSQL_PASSWORD,host =MYSQL_HOSTS,database=MYSQL_DB)
cur = cnx.cursor(buffered=True)

def update_database(qid):
    res = -2
    url='http://kaijiang.zhcw.com/zhcw/html/ssq/list.html'
    html = requests.get(url) 
    content=BeautifulSoup(html.text, 'lxml')
    rows = content.findAll('tr')
    for row in rows:
        if re.search("em class", str(row)):
            columns = row.findAll('td')
            rid = re.findall(r'(\d+)', str(columns[1]))[0]
            date = str(columns[0])[19:29]
            balls = re.findall(r'(\d+)', str(columns[2]))
            rb1 = balls[1]
            rb2 = balls[2]
            rb3 = balls[3]
            rb4 = balls[4]
            rb5 = balls[5]
            rb6 = balls[6]
            bb = balls[7]
            dict = {'rid':rid, 'date':date, 'rb1':rb1, 'rb2':rb2, 'rb3':rb3, 'rb4':rb4, 'rb5':rb5, 'rb6':rb6, 'bb':bb}
            if (rid > bytes(qid)):
                print("rid=" + rid + ", date=" + date + ", rb1=" + rb1 + ", rb2=" + rb2 + ", rb3=" + rb3 + ", rb4=" + rb4 + ", rb5=" + rb5 + ", rb6=" + rb6 + ", bb=" + bb)
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
        rb6 = dict['rb6']
        bb = dict['bb']
        insert_ssq_result(rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb)
        print('starting save results')

def insert_ssq_result(rid,date,rb1,rb2,rb3,rb4,rb5,rb6,bb):
    sql = 'INSERT INTO ssq_result (`rid`,`date`,`rb1`,`rb2`,`rb3`,`rb4`,`rb5`,`rb6`,`bb`) VALUES (%(rid)s,%(date)s,%(rb1)s,%(rb2)s,%(rb3)s,%(rb4)s,%(rb5)s,%(rb6)s,%(bb)s)'
    value = {
        'rid':rid,
        'date':date,
        'rb1':rb1,
        'rb2':rb2,
        'rb3':rb3,
        'rb4':rb4,
        'rb5':rb5,
        'rb6':rb6,
        'bb':bb,
    }
    cur.execute(sql,value)
    cnx.commit()

def select_title(date):#这个是利用标题去重的，虽然按照区域划分应该不会重复，只是预防万一
    sql= 'SELECT EXISTS (SELECT 1 FROM ssq_result WHERE date = %(date)s)'
    value = {
        'date':date
    }
    cur.execute(sql,value)
    return  cur.fetchall()[0]

def select_result(rid):
    sql= 'SELECT * FROM ssq_result WHERE rid = %(rid)s'
    value = {
        'rid':rid
    }
    cur.execute(sql,value)
    return  cur.fetchone()

def select_local_latest_result():
    sql= 'SELECT * FROM ssq_result ORDER BY date DESC'
    cur.execute(sql)
    return  cur.fetchall()[0]

def get_win_level(presult, aresult):
    red = 0
    blue = 0
    level = 0
    if (presult[6] == aresult[6]):
        blue = 1
    for i in range(6):
        for j in range(6):
            if(presult[j] == aresult[i]):
                red += 1
                break
    if (blue == 1):
        if red == 6:
            level = 1
        elif red == 5:
            level = 3
        elif red == 4:
            level = 4
        elif red == 3:
            level = 5
        else:
            level = 6
    else:
        if red == 6:
            level = 2
        elif red == 5:
            level = 4
        elif red == 4:
            level = 5
    return level


def calculate_income(qid,full):
    aresult = list(select_result(qid)[3:])
    print("第" + bytes(qid) + "开奖结果为：")
    print(aresult)
    if full:
        filename = "./ssq_results/" + bytes(qid) + "-predict-full.txt"
    else:
        filename = "./ssq_results/" + bytes(qid) + "-predict.txt"
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
        temp = linesList[i][5].strip().split('+')
        linesList[i][5] = temp[0]
        linesList[i] += [temp[1]]
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
    income = (len(level_one)*5000000 + len(level_two)*250000)*0.8 + len(level_three)*3000 + len(level_four)*200 + len(level_five)*10 + len(level_six)*5
    print("总共投注" + bytes(len(linesList)) + "注, 共花费" + bytes(len(linesList)*2) + "元")
    print("中奖总金额" + bytes(income) + "元， 净利润" + bytes(income-len(linesList)*2) + "元")
    return 0

latest_rid = select_local_latest_result()[1]
update_database(latest_rid)
latest_rid = select_local_latest_result()[1]
calculate_income(latest_rid, 1)